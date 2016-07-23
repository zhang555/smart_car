#include "include.h"
#include "ccd.h"
#include "OLED.h"
#include "isr.h"
#include "nokia.h"
#include "VCAN_NRF24L0.h"
#include "common.h"

void init()
{
     uart_init(UART0,115200);  

 //    FTM_PWM_init(FTM2, FTM_CH0,50,0);    //A10 舵机  左27 中45 右63
     FTM_PWM_init(FTM2, FTM_CH0,100,0);    //A10 舵机 
      
     FTM_PWM_init(FTM0, FTM_CH4,5000,0);    // D4  左轮正转
     FTM_PWM_init(FTM0, FTM_CH5,5000,0);    // D5
     FTM_PWM_init(FTM0, FTM_CH6,5000,0);    // D6  右轮正转
     FTM_PWM_init(FTM0, FTM_CH7,5000,0);    // D7

    lptmr_pulse_init(LPT0_ALT1,10000,LPT_Rising);
    DMA_count_Init(DMA_CH0, PTA8, 0xffff, DMA_rising_up); //右
      
     gpio_init(PTA25,GPO,0);
     gpio_init(PTA26,GPO, LOW); //B20 led2
        
      pit_init_ms(PIT1, 1);
      set_vector_handler(PIT1_VECTORn ,PIT1_IRQHandler);      //设置PIT0的中断服务函数为 PIT0_IRQHandler
      enable_irq (PIT1_IRQn);     

     CCD_init1() ;             //CCD传感器初始化
     CCD_init2();

     adc_init(ADC1,AD9);        //B1
     adc_init(ADC0,AD12);  //B2
       
    // OLED_Init();
     
     key_init(KEY_U);
     key_init(KEY_D);

     
     LCD_init();
     
    nrf_init(RX_MODE);
     
}
  














