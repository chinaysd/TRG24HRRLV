#include "bsp_led.h"


LED_PARA_T Led_Para[LED_NUM];

unsigned char Led_Init(unsigned char id)
{
    if(id > LED_NUM)
        return LED_ERROR;
    if(id == 0)
    {
        P1CON |= 0X80;
        P1PH  &= ~0X80;
        return LED_SUCCESS;
    }
    else if(id == 1)
    {
        P1CON |= 0X01;
        P1PH  &= ~0X01;
        return LED_SUCCESS;
    }
    else if(id == 2)
    {
        P2CON |= 0X08;
        P2PH  &= ~0X08;
        return LED_SUCCESS;
    }
    return LED_ERROR;
}

unsigned char Led_App_Init(LED_PARA_T *P)
{
   unsigned char Led_Init(unsigned char ID);
   return Led_Init(P->ID);    
}

unsigned char Led_App_Handle(unsigned char sum)
{
    static unsigned char i;
    if(sum > LED_NUM)
    {
        return LED_ERROR;
    }
    for(i = 0 ; i < sum; i ++)
    {
        Led_Para[i].ID = i;
        Led_App_Init(&Led_Para[i]);
    }
    if(i != sum)
    {
        return LED_ERROR;
    }
    else 
    {
        return LED_SUCCESS;
    }
}






