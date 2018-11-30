#include "bsp_uart.h"
#include "bsp_led.h"
#include "system.h"

unsigned char UartSendFlag,UartReceiveFlag;

/*****************************************�������ݱ�������**********************************************/
unsigned char Res,Rev_Num,Rev_Sum,Rev_String[REV_BUF_SIZE];
unsigned int Temp;
/*****************************************�������ݵ�ȫ�ֱ���*******************************************/
extern unsigned char Data;
extern unsigned char App_Flag;
/******************************************************************************************************/

/************************���Ȳ���������*************************************/
extern unsigned char Heat_Flag;
extern unsigned int  Heat_Cnt;
extern unsigned char Heat_Cnt30Min_Flag;
extern unsigned int  Heat_Cnt30Min;
extern unsigned int  App_Heat_Cnt1s;
/***************************************************************************/

/************************����������***************************************/
extern unsigned char Mass_Flag;
extern unsigned int  Mass_Cnt;
extern unsigned char Mass_Cnt30Min_Flag;
extern unsigned int  Mass_Cnt30Min;
extern unsigned int  App_Mass_Cnt1s;
/***************************************************************************/


void Uart_Init(unsigned int Baud)
{
    SCON=0x50;
	PCON|=0x80;
	T2CON&=~0x30;
	TMCON|=0x02;
	TMOD&=0x0f;
	TMOD|=0x20;
	TH1=256 - Freq/Baud/16/2*2;
	TR1=0;
	TR1=1;
	EUART=1; 
}

void Send_Byte(unsigned char TX_BUF)
{
    SBUF = TX_BUF;
    while(!UartSendFlag);
    UartSendFlag = 0;
}

unsigned char Send_Data(PROTOCOL_TX *p)
{
    static unsigned char i;
    for(i = 0; i < BUF_SIZE; i ++)
    {
       Send_Byte(p->Buf[i]);
    }
    return 0;
}

unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned char TX_DATA)
{
    PROTOCOL_TX buf;
    memset(&buf,0,sizeof(buf));
    buf.Buf_Para.ADDR = addr;
    buf.Buf_Para.ID   = id;
    buf.Buf_Para.DATA = TX_DATA;
    buf.Buf_Para.CHECKSUM = (unsigned char)(buf.Buf_Para.ADDR + buf.Buf_Para.ID + buf.Buf_Para.DATA);
    return Send_Data(&buf);
}

/*****************************************************�����Ӻ���******************************************/

unsigned char Rev_Data(void)
{
    static unsigned char SSDAT;
    while(!UartReceiveFlag);
    UartReceiveFlag = 0;
    SSDAT = SBUF;
    return SSDAT;
}

unsigned char IF_Rev_Data(void)
{
    if(Rev_Num & 0x80)
    {
       Rev_Num &= 0x00;
       return 1;        
    }
    else 
    {
        return 0;
    }
}

void Serial_Rev_Data(void)
{
    Res = Rev_Data();
    if((Rev_Num & 0x80) == 0)
    {
        if(Rev_Num & 0x40)
        {
            if(Res == 0xfb)
            {
               Rev_Num |= 0x80; 
            }
            else 
            {
               Rev_Num &= 0x00; 
            }
        }
        else 
        {
            if(Rev_Num == 5)
            {
                if(Res == Rev_Sum)
                {
                   Rev_Num |= 0x40; 
                }
                else
                {
                   Rev_Num &= 0x00;  
                }
            }
            else
            {
                Rev_String[Rev_Num] = Res;
                Rev_Num ++;
                Rev_Sum = (unsigned char)(Rev_String[0]+Rev_String[1]+Rev_String[2]+Rev_String[3]+Rev_String[4]);
                if(Rev_String[0] != 0xA5)
                {
                   Rev_Num &= 0X00; 
                }
            }
        }
    }
}

void Rev_Data_Handle(void)
{
    if(IF_Rev_Data())
    {
        Temp = (unsigned int)Get_32Bit(Rev_String[3],Rev_String[4]);
        memset(&Rev_String,0,sizeof(Rev_String));
        switch (Temp)
        {
            case COCO_Stop:                         //ֹͣ
                              Data = STOP;
                              App_Flag = 1;
                              break;         
            case COCO_Recline:                        //���δ�
                              Data = OPEN;
                              App_Flag = 1;
                              break;
            case COCO_Close:                         //�����ջ�
                              Data = CLOSE;
                              App_Flag = 1;
                              break;
            case COCO_Head_Up:                       //ͷ���
                              Data = HEAD_UP;
                              App_Flag = 1;
                              break;
            case COCO_Head_Down:                     //ͷ���ջ�
                              Data = HEAD_DOWN;
                              App_Flag = 1;
                              break;
            case COCO_Lumbar_Up:                     //������
                              Data = LARBUM_UP;
                              App_Flag = 1;            
                              break;
            case COCO_Lumbar_Down:                   //�����ջ�
                              Data = LARBUM_DOWN; 
                              App_Flag = 1;
                              break;
            case COCO_Home_Position:                 //��λ
                              Data = HOME_POSITION; 
                              App_Flag = 1;
                              break;
            case COCO_Sleep_Position:                //˯��λ��
                              Data = SLEEP_POSITION; 
                              App_Flag = 1;
                              break;
            case COCO_TV_Position:                   //������λ��
                              Data = WATCH_TV_POSITION; 
                              App_Flag = 1;
                              break;
            case COCO_Reading_Position:              //�Ķ�λ�� 
                              Data = READING_POSITION;
                              App_Flag = 1;
                              break;
            case COCO_Set_Sleep_Position:            //����˯��λ��
                              Data = SET_SLEEP_POSITION;
                              App_Flag = 1;
                              break;
            case COCO_Set_TV_Position:               //���ÿ�����λ��
                              Data = SET_WATCH_TV_POSITION;
                              App_Flag = 1;
                              break;
            case COCO_Set_Reading_Position:          //�����Ķ�λ��
                              Data = SET_READING_POSITION;
                              App_Flag = 1;
                              break;
            case COCO_Light_On:                      //�򿪽ŵ�
                              Data = FOOT_LIGHT_OPEN;
                              App_Flag = 1;
                              break;
            case COCO_Light_Off:                     //�رսŵ�
                              Data = FOOT_LIGHT_CLOSE;
                              App_Flag = 1;
                              break;
            case COCO_Heat_On:                       //���Ȳ�����
                              App_Heat_Cnt1s = 0; 
                              Heat_Cnt30Min  = 0;
                              Heat_Cnt30Min_Flag = True;
                              Data = HEAT_ON;
                              LED2_SET(1);
                              App_Flag = 1;
                              Heat_Cnt = 1;
                              break;
            case COCO_Heat_Off:                      //���Ȳ��ر�
                              Heat_Cnt30Min_Flag = False;
                              Data = HEAT_OFF;
                              LED2_SET(0);
                              App_Flag = 1;
                              Heat_Cnt = 1;
                              break;
            case COCO_Massage_Start:                 //��￪��
                              App_Mass_Cnt1s = 0; 
                              Mass_Cnt30Min  = 0;
                              Mass_Cnt30Min_Flag = True;
                              Data = MASS_OPEN;
                              LED1_SET(1);
                              App_Flag = 1;
                              Mass_Cnt = 1;
                              break;
            case COCO_Massage_Stop:                  //���ر�
                              Mass_Cnt30Min_Flag = False;
                              Data = MASS_CLOSE;
                              LED1_SET(0);
                              App_Flag = 1;
                              Mass_Cnt = 1;
                              break;
            default:
                              App_Flag = 0;
                              Data = STOP;
                              break;
        }  
    }
    
}

/*****************************************************
*�������ƣ�void UartInt(void) interrupt 4
*�������ܣ�Uart0�жϺ���
*��ڲ�����void
*���ڲ�����void
*****************************************************/
void UartInt(void) interrupt 4
{
	if(TI)
	{
		TI = 0;	
		UartSendFlag = 1;		
	}
	if(RI)
	{
		RI = 0;	
		UartReceiveFlag = 1;
		Serial_Rev_Data();	
	}
  
}