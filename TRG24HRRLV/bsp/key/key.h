#ifndef KEY_H_
#define KEY_H_

#include "sys_config.h"


/**
	@function: °´¼üÉ¨ÃèµÄÊ±¼ä¶¨Òå
	@brief: Ê±»ù125us
*/
#define 	KEY_SCAN_TIME			160				//	20ms		
#define 	KEY_JITTER_TIME			160				// 	20ms
#define 	KEY_CP_TIME				160				//	ms
#define 	KEY_CPH_TIME			2000				//  200ms	³¤°´±£³Ö´¥·¢Ê±¼

/**
	@function:msg
	@brief:  Ö§³Ö¶Ì°´£¬³¤°´£¬³¤°´±£³Ö£¬³¤°´·ÅÊÖ
*/ 
typedef enum
{
	MSG_KEY_NONE=0,
	MSG_KEY1_PRESS ,
	MSG_KEY1_SHORT_PRESS ,
	MSG_KEY1_LONGPRESS,
	MSG_KEY1_LONGPRESS_HD,
	MSG_KEY1_LONGPRESS_RE,
	MSG_KEY2_PRESS,
	MSG_KEY2_SHORT_PRESS,
	MSG_KEY2_LONGPRESS,
	MSG_KEY2_LONGPRESS_HD,
	MSG_KEY2_LONGPRESS_RE,
	MSG_KEY3_PRESS,
	MSG_KEY3_SHORT_PRESS,
	MSG_KEY3_LONGPRESS,
	MSG_KEY3_LONGPRESS_HD,
	MSG_KEY3_LONGPRESS_RE,
	MSG_KEY4_PRESS,
	MSG_KEY4_SHORT_PRESS,
	MSG_KEY4_LONGPRESS,
	MSG_KEY4_LONGPRESS_HD,
	MSG_KEY4_LONGPRESS_RE,
	MSG_KEY5_PRESS,
	MSG_KEY5_SHORT_PRESS,
	MSG_KEY5_LONGPRESS,
	MSG_KEY5_LONGPRESS_HD,
	MSG_KEY5_LONGPRESS_RE,
	MSG_KEY6_PRESS,
	MSG_KEY6_SHORT_PRESS,
	MSG_KEY6_LONGPRESS,
	MSG_KEY6_LONGPRESS_HD,
	MSG_KEY6_LONGPRESS_RE,
	MSG_KEY7_PRESS,
	MSG_KEY7_SHORT_PRESS,
	MSG_KEY7_LONGPRESS,
	MSG_KEY7_LONGPRESS_HD,
	MSG_KEY7_LONGPRESS_RE,
	MSG_INVALID = 0XFF
}t_KEY_MSG;






/************************************************************/

/**
	@function:IO ºÍ°´¼üÉ¨Ãè×´Ì¬µÄ³õÊ¼»¯
*/
void Key_Init(void);

void Key_Register(void (*cb)(unsigned char));

void Key_Poll(void);
#endif