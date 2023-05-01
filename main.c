// @File		MAIN.C		 		
// @Author		JOSIMAR PEREIRA LEITE
// @country		BRAZIL
// @Date		01/05/23
//
//
// Copyright (C) 2023 JOSIMAR PEREIRA LEITE
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
#include "config.h"
#include "wire.h"
#include "ks0066.h"
#include "hbs635.h"

void main(void)
{     
    PIC18F2520();  
    PIC18F2520();    
    KS0066_Init();
    KS0066_Clear(0);
    KS0066_Clear(1);
    KS0066_Goto(0,0);
    KS0066_String("TEST");
    
    HBS635_Init();
    
    HBS635_Data(0x00, HBS635_Font[ 0 ]);
    HBS635_Data(0x01, HBS635_Font[ 1 ]);
    HBS635_Data(0x02, HBS635_Font[ 2 ]);
    HBS635_Data(0x03, HBS635_Font[ 3 ]);
    
    while(1){};
    
    return;
}