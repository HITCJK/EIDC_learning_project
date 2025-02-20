/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "board.h"
#include "oled.h"
#include "voltage_list.h"
#include <stdio.h>

int main(void)
{
    // 开发板初始化
    board_init();
    OLED_Init(); // 初始化OLED
    OLED_Clear();
    char*scr="VPP:";
    char*scr_="f:";
    char*VPP="2.5V";
    char*fre="1kHz";
    voltage_list *list = create_voltage_list_sine_wave(700, 3, get_unit_of_time(700));

    while (1)
    {
        OLED_Clear();
        OLED_DisplayTurn(1);//屏幕翻转180°
        OLED_DrawLine(0,48,127,48,1);
        OLED_DrawLine(63,48,63,63,1);
        OLED_ShowString(0,49,scr,12,1);
        OLED_ShowString(24,49,VPP,12,1);//显示Vpp
        OLED_ShowString(64,49,scr_,12,1);
        OLED_ShowString(76,49,fre,12,1);//显示fre
        for (int i = 0; i < 128; i++)
        {
            if(list->voltage_count_display<=63)
            {
                OLED_DrawPoint(i, list->voltage_count_display, 1);
            }
            else 
            {
                for(int j=0;j<60;j++)
                {
                    OLED_DrawPoint(i,j,1);
                }
            }
            list = list->next;
        }
        OLED_Refresh();        
        delay_ms(500);
    }
}
