#include "key.h"
#include "timeout.h"

typedef enum {
    KEY_STATE_IDLE,
    KEY_STATE_JITTER,
    KEY_STATE_PRESS_DOWN,
    KEY_STATE_CP
} KEY_STATE;


static TIMEOUT_PARA Key_Scan_Timer,Key_Wait_Timer;
static KEY_STATE	KeyState;
static t_KEY_MSG Key_Msg;
static unsigned char PreKeyIndex = MSG_INVALID;
static void (*GetValueCb)(unsigned char);


/**
	@function: 按键事件，更多按键时，对应增加按键按键
	
*/
static xdata unsigned char KeyEvent[8][5]=
{
	//按键开始(按下)	    		短按								长按					长按保持						长按松开
	{MSG_KEY_NONE,					MSG_KEY_NONE,						MSG_KEY_NONE,			MSG_KEY_NONE,						MSG_KEY_NONE},			// 空，无用
	{MSG_KEY1_PRESS,				MSG_KEY1_SHORT_PRESS,				MSG_KEY1_LONGPRESS,	MSG_KEY1_LONGPRESS_HD,				MSG_KEY1_LONGPRESS_RE},							// key1
	{MSG_KEY2_PRESS,				MSG_KEY2_SHORT_PRESS,				MSG_KEY2_LONGPRESS,	MSG_KEY2_LONGPRESS_HD,				MSG_KEY2_LONGPRESS_RE},							// key2
	{MSG_KEY3_PRESS,				MSG_KEY3_SHORT_PRESS, 				MSG_KEY3_LONGPRESS, 	MSG_KEY3_LONGPRESS_HD,				MSG_KEY3_LONGPRESS_RE},							// key3	
	{MSG_KEY4_PRESS,				MSG_KEY4_SHORT_PRESS, 				MSG_KEY4_LONGPRESS, 	MSG_KEY4_LONGPRESS_HD,				MSG_KEY4_LONGPRESS_RE},							// key4	
	{MSG_KEY5_PRESS,				MSG_KEY5_SHORT_PRESS, 				MSG_KEY5_LONGPRESS, 	MSG_KEY5_LONGPRESS_HD,				MSG_KEY5_LONGPRESS_RE},							// key5
	{MSG_KEY6_PRESS,				MSG_KEY6_SHORT_PRESS, 				MSG_KEY6_LONGPRESS, 	MSG_KEY6_LONGPRESS_HD,				MSG_KEY6_LONGPRESS_RE},							// key6
	{MSG_KEY7_PRESS,				MSG_KEY7_SHORT_PRESS, 				MSG_KEY7_LONGPRESS, 	MSG_KEY7_LONGPRESS_HD,				MSG_KEY7_LONGPRESS_RE},							// key7
};

/**
	@function:	获取按键索引值
	根据按键的个数，需要做相应的修改
*/
static unsigned char GetKeyIndex(void)
{
	extern unsigned char Key_Port_Read(unsigned char num);
	unsigned char value = 0,cnt = 0;
	if(!Key_Port_Read(1))
		cnt ++,value = 1;
	if(!Key_Port_Read(2))
		cnt ++,value = 2;
	if(!Key_Port_Read(3))
		cnt ++,value = 3;
	if(!Key_Port_Read(4))
		cnt ++,value = 4;
	if(!Key_Port_Read(5))
		cnt ++,value = 5;
	if(!Key_Port_Read(6))
		cnt ++,value = 6;
	if(!Key_Port_Read(7))
		cnt ++,value = 7;
	if(cnt > 1)
		value = MSG_INVALID;
	return value;	
}

/**
	@function:IO 和按键扫描状态的初始化
*/
void Key_Init(void){
	extern unsigned char Key_Port_Init(void);
	
	Key_Port_Init();
	KeyState=KEY_STATE_IDLE;
	TimeOut_Record(&Key_Scan_Timer,0);
}

/**
	@function:按键的扫描
	@return :t_KEY_MSG 类型的消息，消息集在t_KEY_MSG中定义
*/
t_KEY_MSG Key_Scan(void){
	unsigned char KeyIndex;
	
	if(!(TimeOutDet_Check(&Key_Scan_Timer))){
		return MSG_INVALID;
	}
	
	TimeOut_Record(&Key_Scan_Timer,KEY_SCAN_TIME);
	
	KeyIndex=GetKeyIndex();
	if(KeyIndex == MSG_INVALID)
		return MSG_INVALID;

	switch(KeyState){
		case KEY_STATE_IDLE:{
			if(!KeyIndex){
				return MSG_KEY_NONE;
			}
			
			PreKeyIndex = KeyIndex;
			TimeOut_Record(&Key_Wait_Timer,KEY_JITTER_TIME);
			KeyState = KEY_STATE_JITTER;
			break;
		}
		
		case KEY_STATE_JITTER:{
			if(PreKeyIndex != KeyIndex){
				KeyState = KEY_STATE_IDLE;
			}else if(TimeOutDet_Check(&Key_Wait_Timer)){
				TimeOut_Record(&Key_Wait_Timer,KEY_CP_TIME);
				KeyState = KEY_STATE_PRESS_DOWN;
				return KeyEvent[PreKeyIndex][0];
			}
			break;
		}

		case KEY_STATE_PRESS_DOWN:{
			if(PreKeyIndex != KeyIndex){
				KeyState = KEY_STATE_IDLE;
				return KeyEvent[PreKeyIndex][1];
			}else if(TimeOutDet_Check(&Key_Wait_Timer)){
				TimeOut_Record(&Key_Wait_Timer,KEY_CPH_TIME);
				KeyState = KEY_STATE_CP;
				return KeyEvent[PreKeyIndex][2];
			}
			break;
		}
		
		case KEY_STATE_CP:{
			if(PreKeyIndex != KeyIndex){
				KeyState = KEY_STATE_IDLE;
				return KeyEvent[PreKeyIndex][4];
			}else if(TimeOutDet_Check(&Key_Wait_Timer)){
				TimeOut_Record(&Key_Wait_Timer,KEY_CPH_TIME);
				return KeyEvent[PreKeyIndex][3];
			}
			break;
		}
		
		default:{
			KeyState = KEY_STATE_IDLE;
			break;
		}
	}
	return MSG_INVALID;
}

void Key_Register(void (*cb)(unsigned char))
{
	if(cb){
		GetValueCb = cb;
	}
}

void Key_Poll(void)
{
	Key_Msg = Key_Scan();
	if(GetValueCb){
		GetValueCb(Key_Msg);
	}
}

