#include "bsp_test.h"


void Test_Init(void)
{
    P1CON &= ~0X01;
    P1PH  |= 0X01;     //P10ÎªÈí¼þÇÐ»»GPIO
}
