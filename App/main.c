#include "include.h"
#include "1init.h"
/*#include "OLED.h"
#include "CCD.h"
#include "ccd_data_processing.h"*/
#include "nokia.h"
#include "CCD.h"
#include "upload.h"
#include "VCAN_NRF24L0.h"

u8 NRF_txbuf[32]={0x00,0x00,0x00,0x00,0x00,0x00};
u8 NRF_rxbuf[32]={0x00,0x00,0X00,0X57,0x00,0x00};
extern u8 Timer_100ms_flag ;
extern u8 Timer_10ms_flag ;
extern u8 IntegrationTime;
extern u8 Pixel[128],CCD2_Pixel[128];

extern u16 Target_count ;
extern u16 NRF_pwm;
extern u16 duoji_pwm;

extern s16 speed_P;
extern s16 speed_I;
extern s16 speed_D;

extern u8 hongwai1 , hongwai2;
  
u8 NRF_flag=2;

u16 start_count=0;
extern u8 stop_flag;

void main()
{
  DisableInterrupts;   //禁止总中断 

  init();

  EnableInterrupts;  //开总中断  

  while(1)
  {


    if(Timer_10ms_flag)
    {    
      Timer_10ms_flag=0;
      Upload_02();                      // 1ms内不能完成    
      SendImageData(Pixel);  // 1ms内不能完成  

    }   


    if(Timer_100ms_flag)
    {
      Timer_100ms_flag=0;
      
      start_count++;
      
      if(start_count <= 30  )
      {
        stop_flag = 1;
      }


      if(start_count >= 30 && start_count <= 40)
      {
        stop_flag = 0;
      }


      NOKIA_show();
      
      /*
      NRF_flag=NRF_RxPacket(NRF_rxbuf);
      if(NRF_flag & RX_DR)
      {
        if(NRF_rxbuf[0]==0xAA && NRF_rxbuf[1]==0xAA)
        {
          Target_count = ((u8)NRF_rxbuf[3] - 0x50 ) * 10;
          
 //  NRF_pwm = ((u8)NRF_rxbuf[3] - 0x5a ) * 1000;
          
          speed_P = NRF_rxbuf[4]<<8 | NRF_rxbuf[5];
          speed_I = NRF_rxbuf[6]<<8 | NRF_rxbuf[7];
          speed_D = NRF_rxbuf[8]<<8 | NRF_rxbuf[9];          
        }
      }*/
   }

    if(key_check(KEY_U) ==  KEY_DOWN)
    {
        Target_count += 5;
 //       start_count = 0;
    }
      
    if(key_check(KEY_D) ==  KEY_DOWN)
    {
        Target_count -= 5;
//        start_count = 0;
    } 
    
/*
    if(IntegrationTime>9)
      IntegrationTime = 9;
    if(IntegrationTime<2)
      IntegrationTime = 2;          
*/
    
  } 

}



  