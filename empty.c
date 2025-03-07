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
#include "ti/driverlib/dl_dac12.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "voltage_list.h"
#include <stdio.h>

/*char str[3];
void GetVpp(float Vpp)
{
    char str_[]="V";
    //char a[100];
    sprintf(str, "%f",Vpp);
    //sprintf(str,"%s%s",a,str_);
}*/
int main(void)
{
    // 开发板初始化
    board_init();
    OLED_Init(); // 初始化OLED
    OLED_Clear();
    char scr[]="VPP:";
    char scr_[]="Fre:";
    char VPP[]="3V";
    char fre[]="100Hz";
    /*voltage_list *list = create_voltage_list_triangle_wave(10, 3, get_unit_of_time(10));*/
    voltage_list *list1 = create_voltage_list_sine_wave(10, 3, get_unit_of_time(10));
    //GetVpp(2.5);
    while (1)
    {
        /*OLED_Clear();
        //OLED_DisplayTurn(1);//屏幕翻转180°
        OLED_DrawLine(0,15,127,15,1);
        OLED_DrawLine(63,0,63,16,1);
        OLED_ShowString(0,0,scr,8,1);
        OLED_ShowString(24,0,VPP,8,1);//显示Vpp
        OLED_ShowString(64,0,scr_,8,1);
        OLED_ShowString(88,0,fre,8,1);//显示fre
        for (int i = 0; i < 128; i++)
        {
            if(list->voltage_count_display<=63&&list->voltage_count_display!=48)
            {
                OLED_DrawPoint(i,63-list->voltage_count_display, 1);
            }
            else if(list->voltage_count_display==48)
            {
                OLED_DrawPoint(i,16,1);
            }
            else 
            {
                for(int j=15;j<64;j++)
                {
                    OLED_DrawPoint(i,j,1);
                }
            }
            list = list->next;
        }
        OLED_Refresh();
        delay_cycles(32000000*0.5);*/
        DL_DAC12_output12(DAC0,list1->voltage_count_output);
        DL_DAC12_enable(DAC0);//使能DAC输出
        list1=list1->next;  
        delay_cycles(32000*0.2);//(32000*(float)cycle/(int)(cycle*1000/get_unit_of_time(cycle)))
    }
}
