#include "system.h"

TIMEOUT_PARA TimeOut_Para[2];
unsigned char Data;
unsigned char App_Flag;

/************************���Ȳ���������*************************************/
unsigned char Heat_Flag;
unsigned int  Heat_Cnt;
unsigned char Heat_Cnt30Min_Flag;
unsigned int  Heat_Cnt30Min;
unsigned int  App_Heat_Cnt1s;
/***************************************************************************/

/************************����������***************************************/
unsigned char Mass_Flag;
unsigned int  Mass_Cnt;
unsigned char Mass_Cnt30Min_Flag;
unsigned int  Mass_Cnt30Min;
unsigned int  App_Mass_Cnt1s;
/***************************************************************************/

/************************�ŵƱ�������***************************************/
unsigned char Foot_Led_Flag;
unsigned int  Foot_Led_Cnt;
/***************************************************************************/
void Key_Handle(unsigned char Get_Key)
{  
    /******************************************************************************************************************************************/
    /**************************************************************�����Ȳ����ŵơ�˫��****************************************************/ 
    /******************************************************************************************************************************************/ 
    if(TEST_PIN == 1)
    {
        if(Get_Key == MSG_KEY_NONE)
        {
           Rev_Data_Handle();
           if(!App_Flag)
           {
              Data = STOP;  
           }
           Mass_Flag     = 0;
           Heat_Flag     = 0;
           Foot_Led_Flag = 0;
        }
        else if(Get_Key == MSG_KEY1_LONGPRESS)//K7
        {
           App_Flag  = 0;
           Data = HEAD_UP;        
        }
        else if(Get_Key == MSG_KEY2_LONGPRESS)//K5
        {
           App_Flag  = 0;
           Data = HEAD_DOWN;     
        }
        else if(Get_Key == MSG_KEY3_LONGPRESS)//K4
        {
           App_Flag  = 0;
           Data = CLOSE;         
        }
        else if(Get_Key == MSG_KEY4_LONGPRESS)//K6
        {
           App_Flag  = 0;
           Data = OPEN;               
        }
        else if(Get_Key == MSG_KEY5_LONGPRESS_HD)//K1
        {
           App_Flag  = 0;
           Data = HOME_POSITION;         
        }
        else if(Get_Key == MSG_KEY6_PRESS)//K2
        {
           
            if(!Mass_Flag)
            {
               App_Flag  = 1;
               Mass_Flag = 1;
               ++ Mass_Cnt;
               if(Mass_Cnt & 0x01)
               {
                  Mass_Cnt30Min_Flag = True;
                  Mass_Cnt30Min = 0;          //������0
                  App_Mass_Cnt1s = 0;         //������0
                  Data = MASS_OPEN; 
                  LED1_SET(0);                  
               }   
               else
               {
                  Mass_Cnt30Min_Flag = False;
                  Data = MASS_CLOSE;  
                  LED1_SET(0);                
               }               
            } 
             #if 0
            if(!Foot_Led_Flag)
            {
               App_Flag  = 1;
               Foot_Led_Flag = 1;
               ++ Foot_Led_Cnt;
               if(Foot_Led_Cnt & 0x01)
               {
                  Data = FOOT_LIGHT_OPEN; 
               }
               else 
               {
                  Data = FOOT_LIGHT_CLOSE; 
               }
            } 
            #endif             
        }
        else if(Get_Key == MSG_KEY7_PRESS)//K3
        {
           if(!Heat_Flag)
           {
               App_Flag  = 1;
               Heat_Flag = 1;
               ++ Heat_Cnt;
               if(Heat_Cnt & 0x01)
               {
                 App_Heat_Cnt1s = 0; 
                 Heat_Cnt30Min  = 0;
                 Heat_Cnt30Min_Flag = True;
                 Data = HEAT_ON;
                 LED2_SET(1);               
               }
               else
               {
                 Heat_Cnt30Min_Flag = False;  
                 Data = HEAT_OFF;
                 LED2_SET(0); 
               }
           }            
        }
        #if 1
        else if(Get_Key == MSG_KEY5_SHORT_PRESS)
        {
            if(!Foot_Led_Flag)
            {
               App_Flag  = 1;
               Foot_Led_Flag = 1;
               ++ Foot_Led_Cnt;
               if(Foot_Led_Cnt & 0x01)
               {
                  Data = FOOT_LIGHT_OPEN; 
               }
               else 
               {
                  Data = FOOT_LIGHT_CLOSE; 
               }
            }
        }
        #endif
    }        
    /******************************************************************************************************************************************/
    /**************************************************************���ƣ��ŵ�/��λ��������****************************************************/ 
    /******************************************************************************************************************************************/ 
    else
    {
        if(Get_Key == MSG_KEY_NONE)
        {
           Rev_Data_Handle();
           if(!App_Flag)
           {
              Data = STOP;  
           }
           Mass_Flag     = 0;
           Heat_Flag     = 0;
           Foot_Led_Flag = 0;
        }
        else if(Get_Key == MSG_KEY1_LONGPRESS)//K7
        {
           App_Flag  = 0;
           Data = HEAD_DOWN;        
        }
        else if(Get_Key == MSG_KEY2_LONGPRESS)//K5
        {
           App_Flag  = 0;
           Data = HEAD_UP;     
        }
        else if(Get_Key == MSG_KEY3_LONGPRESS)//K4
        {
           App_Flag  = 0;
           Data = OPEN;         
        }
        else if(Get_Key == MSG_KEY4_LONGPRESS)//K6
        {
           App_Flag  = 0;
           Data = CLOSE;               
        }
        else if(Get_Key == MSG_KEY5_LONGPRESS_HD)//K1
        {
           App_Flag  = 0;
           Data = HOME_POSITION;         
        }
        else if(Get_Key == MSG_KEY6_PRESS)//K2
        {
           if(!Heat_Flag)
           {
               App_Flag  = 1;
               Heat_Flag = 1;
               ++ Heat_Cnt;
               if(Heat_Cnt & 0x01)
               {
                 App_Heat_Cnt1s = 0; 
                 Heat_Cnt30Min  = 0;
                 Heat_Cnt30Min_Flag = True;
                 Data = HEAT_ON;
                 LED1_SET(1);               
               }
               else
               {
                 Heat_Cnt30Min_Flag = False;  
                 Data = HEAT_OFF;
                 LED1_SET(0); 
               }
           }             
        }
        else if(Get_Key == MSG_KEY7_PRESS)//K3
        {
           if(!Mass_Flag)
            {
               App_Flag  = 1;
               Mass_Flag = 1;
               ++ Mass_Cnt;
               if(Mass_Cnt & 0x01)
               {
                  Mass_Cnt30Min_Flag = True;
                  Mass_Cnt30Min = 0;          //������0
                  App_Mass_Cnt1s = 0;         //������0
                  Data = MASS_OPEN; 
                  LED2_SET(0);                  
               }   
               else
               {
                  Mass_Cnt30Min_Flag = False;
                  Data = MASS_CLOSE;  
                  LED2_SET(0);                
               }               
            } 
             #if 0
            if(!Foot_Led_Flag)
            {
               App_Flag  = 1;
               Foot_Led_Flag = 1;
               ++ Foot_Led_Cnt;
               if(Foot_Led_Cnt & 0x01)
               {
                  Data = FOOT_LIGHT_OPEN; 
               }
               else 
               {
                  Data = FOOT_LIGHT_CLOSE; 
               }
            } 
            #endif            
        }
        else if(Get_Key == MSG_KEY5_SHORT_PRESS)
        {
            if(!Foot_Led_Flag)
            {
               App_Flag  = 1;
               Foot_Led_Flag = 1;
               ++ Foot_Led_Cnt;
               if(Foot_Led_Cnt & 0x01)
               {
                  Data = FOOT_LIGHT_OPEN; 
               }
               else 
               {
                  Data = FOOT_LIGHT_CLOSE; 
               }
            }
        }
    }
}


void System_Init(void)
{
  TimeOutDet_Init();
  Timer_Init();
  Uart_Init(9600);
  Led_App_Handle(LED_NUM);
  Test_Init();
  Key_Init();
  Key_Register(Key_Handle);
  WDTCON |= 0X40;
  EA = 1;
}

void System_Handle(void)
{
   WDTCON |= 0X40;
   Key_Poll();
   if(TimeOutDet_Check(&TimeOut_Para[0]))
   {
      TimeOut_Record(&TimeOut_Para[0],OnLine_Time); 
      Protocol_Send(SEND_ADDR,SEND_ID,Data);         
   }
}

/**************************************************
*�������ƣ�void timer0/1/2() interrupt 1/3/5
*�������ܣ���ʱ���жϲ�������
*��ڲ�����void
*���ڲ�����void
**************************************************/
void timer0() interrupt 1
{
  extern unsigned int Mass_Cnt;
  extern unsigned int Heat_Cnt;
  extern unsigned int Foot_Led_Cnt;
  TL0 = (65536 - 6000)%256;
  TH0 = (65536 - 6000)/256;
  TimeOutDet_DecHandle();
  /***********************��ﶨʱ�ر�*************************/
  if(Mass_Cnt30Min_Flag)
  {
     App_Mass_Cnt1s ++; 
  }      
  if(App_Mass_Cnt1s > 1000)
  {
     App_Mass_Cnt1s = 0;
     Mass_Cnt30Min ++;      
  }
  if(Mass_Cnt30Min > 1800)
  {
     Mass_Cnt30Min = 0; 
     App_Mass_Cnt1s = 0;     
     Mass_Cnt30Min_Flag = False;
     Data = MASS_CLOSE;  
     LED2_SET(0);
     Mass_Cnt = 0;
  }
  /**************************���Ȳ���ʱ�ر�************************************/
  if(Heat_Cnt30Min_Flag)
  {
    App_Heat_Cnt1s ++; 
  }
  if(App_Heat_Cnt1s > 1000)
  {
     App_Heat_Cnt1s = 0; 
     Heat_Cnt30Min ++;
  }
  if(Heat_Cnt30Min > 1800)
  {
     App_Heat_Cnt1s = 0; 
     Heat_Cnt30Min  = 0;
     Heat_Cnt30Min_Flag = False;
     Data = HEAT_OFF;
     LED1_SET(0); 
     Heat_Cnt = 0;
  }
  
}

void timer1() interrupt 3
{

}

void Timer2Int(void) interrupt 5
{		
	TF2 = 0;   //�������
 
}


