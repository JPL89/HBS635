// @File		HBS635.H		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		Brazil
// @Date		04/05/23
//
//
// Copyright (C) 2021  JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
//
#define _NOP()  __asm__ __volatile__("nop")

#define HBS635_DIO  PORTAbits.RA2
#define HBS635_CLK  PORTAbits.RA3

#define HBS635_DIO_TRIS  TRISAbits.RA2
#define HBS635_CLK_TRIS  TRISAbits.RA3

#define HBS635_COMMAND2 0x40
#define HBS635_COMMAND3 0xC0
#define HBS635_COMMAND4 0x80

// COMMAND2 BYTE
#define HBS635_COMMAND2_WRITE_DATA 0x00
#define HBS635_COMMAND2_READ_KEY 0x02
#define HBS635_COMMAND2_FIXED_ADDRESS 0x04
#define HBS635_COMMAND2_MODE_NORMAL 0x00
#define HBS635_COMMAND2_MODE_TEST 0x01

// COMMAND3 BYTE
#define HBS635_COMMAND3_ADDRESS0 0x00
#define HBS635_COMMAND3_ADDRESS1 0x01
#define HBS635_COMMAND3_ADDRESS2 0x02
#define HBS635_COMMAND3_ADDRESS3 0x03

// COMMAND4 BYTE
#define HBS635_COMMAND4_PULSE_1_16 0x00
#define HBS635_COMMAND4_PULSE_2_16 0x01
#define HBS635_COMMAND4_PULSE_4_16 0x02
#define HBS635_COMMAND4_PULSE_10_16 0x03
#define HBS635_COMMAND4_PULSE_11_16 0x04
#define HBS635_COMMAND4_PULSE_12_16 0x05
#define HBS635_COMMAND4_PULSE_13_16 0x06
#define HBS635_COMMAND4_PULSE_14_16 0x07
#define HBS635_COMMAND4_DISPLAY_ON 0x08

static const unsigned char HBS635_Font[] =
{
	0x3f, // 0
	0x06, // 1
	0x5b, // 2
	0x4f, // 3
	0x66, // 4
	0x6d, // 5
	0x7d, // 6
	0x27, // 7
	0x7f, // 8
	0x6f, // 9
};

void HBS635_Start(void)
{
    HBS635_CLK = 1;
    _NOP();
    HBS635_DIO = 1;
    _NOP();
    HBS635_DIO = 0;
    _NOP();
    HBS635_CLK = 0;
}

void HBS635_Stop(void)
{
    HBS635_DIO = 0;
    _NOP();
    HBS635_CLK = 1;
    _NOP();
    HBS635_DIO = 1;  
}

void HBS635_Write(unsigned char data)
{
    for (unsigned char mask = 0x01; mask; mask <<= 1)
   {                          
		if(data & mask) HBS635_DIO = 1; else HBS635_DIO = 0;
		
		HBS635_CLK = 1;
		_NOP();
		HBS635_CLK = 0;
    }

    HBS635_CLK = 1;
    _NOP();
    HBS635_CLK = 0;
}

void  HBS635_Command(unsigned char cmd)
{
    HBS635_Start();
    HBS635_Write(cmd);
    HBS635_Stop();
}

void HBS635_Data(unsigned char address, unsigned char data)
{
    HBS635_Command(HBS635_COMMAND2|HBS635_COMMAND2_FIXED_ADDRESS); 

    HBS635_Start();
    HBS635_Write(HBS635_COMMAND3|address);
    HBS635_Write(data);
    HBS635_Stop();
}

unsigned char HBS635_Receive(void)
{
    unsigned char data = 0;
	
    HBS635_DIO = 1;

    HBS635_DIO_TRIS = 1;

    for (unsigned char bit = 0; bit < 8; bit++)
    {	

        data <<= 1;
        if((HBS635_DIO == 1)) data |= 1;
        
        HBS635_CLK = 1;
        _NOP();
        HBS635_CLK = 0;	
        
    }
    
    HBS635_DIO_TRIS = 0;
    
    HBS635_CLK = 1;
    _NOP();
    HBS635_CLK = 0; 
    
	return ( data );	
}

unsigned char HBS635_GetKey(void)
{
    unsigned char key = 0;

    HBS635_Start();
    
    HBS635_Write(HBS635_COMMAND2|HBS635_COMMAND2_READ_KEY);
	    
    key |= HBS635_Receive();
    
    HBS635_Stop();
    
    return key;
}

void HBS635_Init(void)
{
    HBS635_DIO_TRIS = 0;
    HBS635_CLK_TRIS = 0;    

    HBS635_Command( HBS635_COMMAND4|HBS635_COMMAND4_DISPLAY_ON|HBS635_COMMAND4_PULSE_14_16);
}
