#include "voltage_list.h"
#include <math.h>

//一格的时间
int get_unit_of_time(int cycle)
{
    int unit_of_time; // 单位(us)
    if (cycle >= 1 && cycle < 10)
    {
        unit_of_time = 100;
    }
    else if (cycle > 10 && cycle < 100)
    {
        unit_of_time = 1000;
    }
    else if(cycle==10)
    {
        unit_of_time =200;
    }
    else if (cycle > 100 && cycle <= 1000)
    {
        unit_of_time = 10000;
    }
    else if(cycle==100)
    {
        unit_of_time=2000;
    }
    else
    {
        unit_of_time = -1;
    }
    return unit_of_time;
}
// 输出正弦波
// 周期单位(ms)
voltage_list *create_voltage_list_sine_wave(int cycle, float Vpp, int unit_of_time)
{
    voltage_list *head = (voltage_list *)malloc(sizeof(voltage_list));
    voltage_list *temp = head;
    //cycle *= 1000;    
    for (int i = 0; i <= (cycle*1000) / unit_of_time; i++)
    {
        temp->voltage_count_output = (int)(((Vpp / 2 * sin((float)i / ((cycle*1000) / unit_of_time) * 2 * M_PI))+Vpp/2) / 3.3 * 4095);
        temp->voltage_count_display =
            (int)fmin(((Vpp / 2 * sin((float)i / ((cycle*1000) / unit_of_time) * 2 * M_PI)) / 0.0625 + 24), 48);
        if (i < (cycle*1000) / unit_of_time)
        {
            temp->next = (voltage_list *)malloc(sizeof(voltage_list));
            temp = temp->next;
        }
        else
        {
            temp->next = head;
            temp = temp->next;
        }
    }
    return head;
}
// 输出三角波
voltage_list *create_voltage_list_triangle_wave(int cycle, float Vpp, int unit_of_time)
{
    voltage_list *head = (voltage_list *)malloc(sizeof(voltage_list));
    voltage_list *temp = head;
    //cycle *= 1000;    
    for (int i = 0; i <= (cycle*1000) / unit_of_time; i++)
    {
        /*temp->voltage_count_output = (int)((Vpp / 2 * sin((float)i / ((cycle*1000) / unit_of_time) * 2 * M_PI)) / 3.3 * 4095);
        temp->voltage_count_display =
            (int)fmin(((Vpp / 2 * sin((float)i / ((cycle*1000) / unit_of_time) * 2 * M_PI)) / 0.05 + 32), 63);*/
        if(i<=(cycle*1000) / unit_of_time /2)
        {
            temp->voltage_count_output=(int)(( Vpp / ((cycle*1000) / unit_of_time/2) *(float)i )/3.3*4095);
            temp->voltage_count_display=(int)fmin(( Vpp / ((cycle*1000) / unit_of_time/2) *(float)i )/0.0625,63);
        }
        else 
        {
            temp->voltage_count_output=
            (int)((Vpp-( Vpp / ((cycle*1000) / unit_of_time/2) *(float)(i-(cycle*1000) / unit_of_time /2)))/3.3*4095);
            temp->voltage_count_display=
            (int)fmin((Vpp-( Vpp / ((cycle*1000) / unit_of_time/2) *(float)(i-(cycle*1000) / unit_of_time /2)))/0.0625,63);
        }
        if (i < (cycle*1000) / unit_of_time)
        {
            temp->next = (voltage_list *)malloc(sizeof(voltage_list));
            temp = temp->next;
        }
        else
        {
            temp->next = head;
            temp = temp->next;
        }
    }
    return head;
}
//输出方波
voltage_list *create_voltage_list_square_wave(int cycle, float Vpp, int unit_of_time)
{
    voltage_list *head = (voltage_list *)malloc(sizeof(voltage_list));
    voltage_list *temp = head;
    //cycle *= 1000;    
    for (int i = 0; i <= (cycle*1000) / unit_of_time; i++)
    {
        /*temp->voltage_count_output = (int)((Vpp / 2 * sin((float)i / ((cycle*1000) / unit_of_time) * 2 * M_PI)) / 3.3 * 4095);
        temp->voltage_count_display =
            (int)fmin(((Vpp / 2 * sin((float)i / ((cycle*1000) / unit_of_time) * 2 * M_PI)) / 0.05 + 32), 63);*/
        if(i<(cycle*1000) / unit_of_time /2)
        {
            temp->voltage_count_display=(int)fmin(Vpp/0.0625,63);
            temp->voltage_count_output=(int)(Vpp/3.3*4095);
        }
        else if(i>(cycle*1000) / unit_of_time /2)
        {
            temp->voltage_count_display=0;
            temp->voltage_count_output=0;
        }
        else 
        {
            temp->voltage_count_display=64;
        }
        if (i < (cycle*1000) / unit_of_time)
        {
            temp->next = (voltage_list *)malloc(sizeof(voltage_list));
            temp = temp->next;
        }
        else
        {
            temp->next = head;
            temp = temp->next;
        }
    }
    return head;
}
//输出直流
voltage_list *create_voltage_list_DC_wave(int cycle, float Vpp, int unit_of_time)
{
    voltage_list *head = (voltage_list *)malloc(sizeof(voltage_list));
    voltage_list *temp = head;
    //cycle *= 1000;    
    for (int i = 0; i <= (cycle*1000) / unit_of_time; i++)
    {
        temp->voltage_count_output = (int)Vpp/3.3*4095;
        temp->voltage_count_display =(int)Vpp/0.0625;
        if (i < (cycle*1000) / unit_of_time)
        {
            temp->next = (voltage_list *)malloc(sizeof(voltage_list));
            temp = temp->next;
        }
        else
        {
            temp->next = head;
            temp = temp->next;
        }
    }
    return head;
}
// 释放内存
void free_voltage_list(voltage_list *head)
{
    voltage_list *temp = head;
    while (temp->next != head)
    {
        voltage_list *p = temp->next;
        free(temp);
        temp = p;
    }
    free(temp);
}