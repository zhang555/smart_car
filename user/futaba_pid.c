
#include "include.h"
#include "ccd_data_processing.h"
#include "bianmaqi.h"

// 频率 300hz
//3400    4000    4600
//右       中       左

// 频率 50hz
//660    750    840
//右       中       左

extern u8 stop_flag;

float pid_out;   //pid 输出值
u16 duoji_pwm;   //舵机打舵量


extern u8 CCD2_Enable;
extern s16 Track_C_Line_1[10];

  float P=2;
  float D=0;
  
  


// 频率 100hz
//1350    1500    1700
//右       中       左
  

  
  
void Futaba()
{
#define CENTER 1490
  float error;
  static float pre_error;
  float a=0.015,b=5.2;
  
  error=Track_C_Line_1[0]-64;
  
  P = a * error * error + b;
  
  pid_out = CENTER - P * error ; 
    
  pre_error = error;
  
  duoji_pwm = (u16)pid_out ; 
    
    //1350 1490 1630 
    if(duoji_pwm>1630)  
      duoji_pwm=1630;
    if(duoji_pwm<1350)  
      duoji_pwm=1350;       
    
  FTM_PWM_Duty(FTM2, FTM_CH0,duoji_pwm); //舵机   
   
    
}

  /*
void Futaba()
{
#define CENTER 1490
  
  float error;
  static float pre_error;

  
  error=Track_C_Line_1[0]-64;
  P = 4.5; 
  D = 45;
  
  pid_out = CENTER - P * error - D * (error-pre_error); 
    
  pre_error=error;
  
  duoji_pwm = (u16)pid_out ; 
    
    
    
    if(duoji_pwm>1630)  
      duoji_pwm=1630;
    if(duoji_pwm<1350)  
      duoji_pwm=1350;         
    
      if(stop_flag)    
        duoji_pwm=CENTER;
    
  FTM_PWM_Duty(FTM2, FTM_CH0,duoji_pwm); //舵机   
   
    
}*/

//动态P
/*
float P=1;
void Futaba()
{
  float error=0;

  float a=0.02,b=2;
  
  
  error=Track_C_Line_1[0]-64;
  
  P = a * error* error + b;
  
  
  pid_out = CENTER -   P * error;
  
  duoji_pwm = (u16)pid_out ; 
    
    if(duoji_pwm>840)  
      duoji_pwm=840;
    if(duoji_pwm<650)  
      duoji_pwm=650;       
    
      FTM_PWM_Duty(FTM2, FTM_CH0,duoji_pwm); //舵机   
   
    
}
*/
/*
#define border1 5
#define border2 15
#define border3 25
#define border4 35
#define border5 45

float P=1;
void Futaba()
{
  float error=0;
  
  error=Track_C_Line_1[0]-64;
  
  if(error>-border1 && error<border1)
    P=1.5;
  else if(error>-border2 && error<border2)
    P=3;
  else if(error>-border3 && error<border3)
    P=6;   
  else if(error>-border4 && error<border4)
    P=8;   
  else if(error>-border5 && error<border5)
    P=8;                   
                
                
    pid_out = CENTER - P * error ; 
    duoji_pwm = (u16)pid_out ; 
    
    if(duoji_pwm>840)  
      duoji_pwm=840;
    if(duoji_pwm<650)  
      duoji_pwm=650;       
    
      FTM_PWM_Duty(FTM2, FTM_CH0,duoji_pwm); //舵机   
   
    
}*/



