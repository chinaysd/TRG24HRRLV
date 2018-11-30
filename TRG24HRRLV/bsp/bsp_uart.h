#ifndef _BSP_UART_H_
#define _BSP_UART_H_

#include "sc92f732x_c.h"
#include "string.h"

#define  Freq   12000000
#define  BUF_SIZE       4
#define  REV_BUF_SIZE   7

#define  SEND_ADDR      0xff
#define  SEND_ID        0X55

#define  Get_32Bit(x,y)   ((((x)<<8)|y)&0xffff)

/*******************************************************发送的命令*********************************/
#define   STOP                    0X00     //停止
#define   OPEN                    0X04     //座椅打开
#define   CLOSE                   0X01     //座椅收回
#define   SLEEP_POSITION          0X05     //睡眠位置
#define   WATCH_TV_POSITION       0X08     //看电视位置
#define   READING_POSITION        0X0A     //阅读位置
#define   SET_SLEEP_POSITION      0X13     //记忆睡眠位置
#define   SET_WATCH_TV_POSITION   0X14    //记忆看电视位置
#define   SET_READING_POSITION    0X15    //记忆阅读位置
#define   HEAD_UP                 0X02    //头枕打开
#define   HEAD_DOWN               0X03     //头枕收回
#define   LARBUM_UP               0X06     //腰靠打开
#define   LARBUM_DOWN             0X07     //腰靠收回
#define   FOOT_LIGHT_OPEN         0X21     //脚灯打开
#define   FOOT_LIGHT_CLOSE        0X22      //脚灯关闭
#define   TEMP_FOOT_LIGHT         0X23      // 变换灯
#define   MASS_OPEN               0X30      //启动按摩
#define   MASS_CLOSE              0X31      //关闭按摩
#define   HEAT_ON                 0X41      //启动加热
#define   HEAT_OFF                0X42      //关闭加热
#define   COOL_OPEN               0X43      //启动制冷
#define   COOL_CLOSE              0X44      //关闭制冷
#define   HOME_POSITION           0X20      //复位按键
/****************************************************************************************************/

/****************************************************接收的命令**************************************/

#define     Hello_COCO                                     0x0001 
#define     COCO_Stop                                      0x0100 
#define     COCO_Recline                                   0x0101
#define     COCO_Close	                                   0x0102 
#define     COCO_Lift	                                     0x0103 
#define     COCO_Home_Position                             0x0104 
#define     COCO_Sleep_Position	                           0x0105 
#define     COCO_TV_Position	                             0x0106 
#define     COCO_Reading_Position	                         0x0107 
#define     COCO_Set_Sleep_Position                        0x0108 
#define     COCO_Set_TV_Position	                         0x0109 
#define     COCO_Set_Reading_Position	                     0x010A 
#define     COCO_Head_Up	                                 0x010B 
#define     COCO_Head_Down	                               0x010C 
#define     COCO_Lumbar_Up                                 0x010D 
#define     COCO_Lumbar_Down	                             0x010E 
#define     COCO_Foot_Up	                                 0x010F 
#define     COCO_Foot_Down	                               0x0110 
#define     COCO_Light_On                                  0x0201 
#define     COCO_Light_Off                                 0x0200
#define     COCO_Toggle_Light                              0x0202
#define     COCO_Massage_Start	                           0x0301
#define     COCO_Massage_Stop	                             0x0300 
#define     COCO_Change_Massage_Mode                       0x0302
#define     COCO_Massage_Intensity_Up	                     0x0303
#define     COCO_Massage_Intensity_Down	                   0x0304 
#define     COCO_Heat_On	                                 0x0401
#define     COCO_Heat_Off	                                 0x0402
#define     COCO_Lumbar_High_Temperature	                 0x0403 
#define     COCO_Lumbar_Medium_Temperature                 0x0404 
#define     COCO_Lumbar_Low_Temperature                    0x0405 
#define     COCO_Seat_High_Temperature	                   0x0406 
#define     COCO_Seat_Medium_Temperature	                 0x0407
#define     COCO_Seat_Low_Temperature	                     0x0408
#define     COCO_Back_High_Temperature   	                 0x0409 
#define     COCO_Back_Medium_Temperature	                 0x040A 
#define     COCO_Back_Low_Temperature	                     0x040B
#define     COCO_Neck_High_Temperature	                   0x040C
#define     COCO_Neck_Medium_Temperature	                 0x040D 
#define     COCO_Neck_Low_Temperature	                     0x040E 
#define     COCO_Footrest_High_Temperature                 0x040F
#define     COCO_Footrest_Medium_Temper	                   0x0410 
#define     COCO_Footrest_Low_Temperature                 0x0411 
#define     COCO_Heat_On_Cup                              0x0412 
#define     COCO_Heat_Off_Cup	                           0x0413 
#define     COCO_Cool_On_Cup	                             0x0414 
#define     COCO_Cool_Off_Cup                             0x0415 

#define     COCO_Play_Music                                0x0501 
#define     COCO_Stop_Music	                               0x0500 
#define     COCO_Pause_Music	                             0x0502 
#define     COCO_Mute_On                                   0x0503 
#define     COCO_Mute_Off                                  0x0504 
#define     COCO_Next_Track	                               0x0505 
#define     COCO_Previous_Track                            0x0506 
#define     COCO_Single_Loop                               0x0507 
#define     COCO_Repeat_All	                               0x0508 
#define     COCO_Random_Play                               0x0509 
#define     COCO_SB_Mode	                               0x050A 
#define     COCO_Aux_In_Mode                               0x050B
#define     COCO_Bluetooth_Mode                            0x050C 
#define     COCO_Wireless_Mode                             0x050D 
#define     COCO_Optical_Mode                              0x050E 

/*****************************************************************************************************/

typedef struct
{
    unsigned char ADDR;
    unsigned char ID;
    unsigned char DATA;
    unsigned char CHECKSUM;
}
BUF_PARA_TX;

typedef union
{
    unsigned char Buf[BUF_SIZE];
    BUF_PARA_TX Buf_Para;
}
PROTOCOL_TX;



void Uart_Init(unsigned int Baud);
unsigned char Protocol_Send(unsigned char addr,unsigned char id,unsigned char TX_DATA);

void Rev_Data_Handle(void);





#endif