#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#include "sc92f732x_c.h"
#include "TimeOut.h"
#include "bsp_led.h"
#include "bsp_timer.h"
#include "bsp_uart.h"
#include "key.h"
#include "bsp_test.h"

#define True     1
#define False    0


#define OnLine_Time    40





void System_Init(void);
void System_Handle(void);




#endif