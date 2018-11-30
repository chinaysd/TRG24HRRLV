#ifndef _BSP_LED_H_
#define _BSP_LED_H_

#include "sc92f732x_c.h"

#define LED_NUM     3
#define LED_ERROR   1
#define LED_SUCCESS 0

#define LED1_PORT     P1
#define LED1_PIN      P17
#define LED1_SET(X)   ((X)?(LED1_PIN=X):(LED1_PIN=X))

#define LED2_PORT     P2
#define LED2_PIN      P23
#define LED2_SET(X)   ((X)?(LED2_PIN=X):(LED2_PIN=X))

#define LED3_PORT     P1
#define LED3_PIN      P10
#define LED3_SET(X)   ((X)?(LED3_PIN=X):(LED3_PIN=X))

typedef struct
{
    unsigned char ID;
}
LED_PARA_T;

unsigned char Led_App_Handle(unsigned char sum);


#endif