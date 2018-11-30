#ifndef SYS_CONFIG_H_
#define SYS_CONFIG_H_

#include "SC92F732x_C.H"
#include "data_type.h"

/**
	@brief:系统时间设置
*/
#define SYS_FRE_SET					12000000UL

#ifndef ON
#define ON  1
#endif

#ifndef OFF
#define OFF 0
#endif

typedef void (*Cb_Func_t)(void);

/**
	@brief:error code 
*/
typedef unsigned char SOC_ERR_T;
#define FAILED						0
#define SUCCEED						1	

/**
	@breif:定义到外部RAM
*/
#define XDATA						xdata
/**
	@brief:IO 方向控制
*/
#define IO_OUT						1
#define IO_IN							0

#define Get_Low(x)					((x) & 0XFF)
#define Get_High(x)					(((x) >> 8) & 0XFF)
#define Get_32bit(x,y)					((((x) << 8) | (y)) & 0XFFFF)


/**
	@brief:IO 控制寄存器设置
*/
#define SET_REG_CON(X,Y)				(P##X##CON |= ((1)<<(Y)))
#define CLR_REG_CON(X,Y)				(P##X##CON &= ~((1)<<(Y)))

/**
	@brief:IO 上拉设置
*/
#define SET_IO_PU(X,Y)				(P##X##PH |= ((1)<<(Y)))
#define CLR_IO_PU(X,Y)				(P##X##PH &= ~((1)<<(Y)))

/**
	@brief:功能定义
*/
#define COOL_FUNC_ENABLE
//#define HEAT_FUNC_ENABLE
#ifdef COOL_FUNC_ENABLE
	#define HC_FUNC_ENABLE
#endif
#ifdef HEAT_FUNC_ENABLE
	#define HC_FUNC_ENABLE
#endif
#define MSGE_FUNC_ENABLE
#define PUSH_FUNC_ENABLE
#define WARN_FUNC_ENABLE
#define LED_FUNC_ENABLE
#define LOCK_LONG_DET_ENABLE	
#define RESET_LONG_DET_ENABLE

/**
	@brief:喂狗功能
*/
#define SYS_ENABLE_WDT
#define CLEAR_WDT()					(WDTCON  = 0x10)	

/**
	@brief:串口使能
*/
#define UART0_ENABLE
//#define UART1_ENABLE









#endif
