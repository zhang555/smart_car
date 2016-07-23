
#include "include.h"
#include "ccd_data_processing.h"
#include "ccd.h"
#include "bianmaqi.h"
#include "futaba_pid.h"
#include "upload.h"

u8 Timer_1ms = 0;            //1ms计时
u8 Timer_10ms_flag = 0;
u8 Timer_100ms = 0;
u8 Timer_100ms_flag = 0;

u8 count=0;

u16 hongwai1 , hongwai2 ;

extern u8 Pixel[128],CCD2_Pixel[128];
extern u8 IntegrationTime;
extern u8 CCD2_Enable;

extern u8 stop_flag;

extern u16 start_count;



// 1ms中断
void PIT1_IRQHandler(void)
{
   PIT_Flag_Clear(PIT1);       //清中断标志位


  Timer_1ms++;
    
  if(Timer_1ms == (10-IntegrationTime) )  //2ms  开始曝光  10ms曝光8ms
  {
     StartIntegration();
     
     if(CCD2_Enable)
      CCD2_StartIntegration();
  }
  
  if(Timer_1ms == 7 )  
  { 
      hongwai1 = ad_once(ADC1, AD9, ADC_8bit);
      hongwai2 = ad_once(ADC0, AD12, ADC_8bit);
      
      if(hongwai1 > 100 && hongwai2 > 100 && start_count > 40)
      {
        stop_flag = 1;
      }
      
      
  }      
  
  if(Timer_1ms == 8 )  
  { 
    
  }    
  
  if(Timer_1ms == 9 )  
  {
      speed();
  }  
  
  if(Timer_1ms >= 10)
  {
     Timer_1ms = 0;     
     Timer_10ms_flag=1;
     
    gpio_set(PTA26,1);  //灭
    gpio_set(PTA25,1);


     ImageCapture(Pixel);      
     CalculateIntegrationTime();
     ccd_data_processing();
     
     if(CCD2_Enable)
     {
       CCD2_ImageCapture(CCD2_Pixel);
       gpio_set(PTA26,0); 
     }

    Futaba();

    Timer_100ms++;
    if(Timer_100ms>=10) 
    {
      Timer_100ms_flag=1;
      Timer_100ms=0;    
    }

     gpio_set(PTA25,0);    //亮
    
  }
  

}

/*
void USART1_IRQHandler(void)
{
    uint8 ch;

    DisableInterrupts;		    //关总中断

    //接收一个字节数据并回发
    ch = uart_getchar (UART1);      //接收到一个数据
    uart_sendStr  (UART1, "\n你发送的数据为：");
    uart_putchar (UART1, ch);       //就发送出去

    EnableInterrupts;		    //开总中断
}

*/


void PIT0_IRQHandler(void)
{
   PIT_Flag_Clear(PIT0);       //清中断标志位
   

}



/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：SysTick_Handler
*  功能说明：系统滴答定时器中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-18    已测试
*  备    注：ucos里用得到
*************************************************************************/
void SysTick_Handler(void)
{
    //    OSIntEnter();
    //    OSTimeTick();
    //    OSIntExit();
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PendSV_Handler
*  功能说明：PendSV（可悬起系统调用）中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-15    已测试
*  备    注：uC/OS用来切换任务
*************************************************************************/
void PendSV_Handler(void)
{
}
/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：HardFault_Handler
*  功能说明：硬件上访中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-4    已测试
*  备    注：可以用LED闪烁来指示发生了硬件上访
*************************************************************************/
void HardFault_Handler(void)
{
    while (1)
    {
        printf("\n****硬件上访错误!!!*****\r\n\n");
    }
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PORTA_IRQHandler
*  功能说明：PORTA端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要自己初始化来清除
*************************************************************************/

   u16   key8cout = 0 ;
   u8    key8start = 0 ;
   u8    key8flg = 0 ;   
   u16   key9cout = 0 ;
   u8    key9start = 0 ;
   u8    key9flg = 0 ;
   u16   key10cout = 0 ;
   u8    key10start = 0 ;
   u8    key10flg = 0 ;
   u16   key11cout = 0 ;
   u8    key11start = 0 ;
   u8    key11flg = 0 ;


void PORTD_IRQHandler(){
    
    u8  n = 0;    //引脚号
    n = 8;
    if(PORTD_ISFR & (1 << n))         //PTDn触发中断
    {
        PORTD_ISFR  |= (1 << n);        //写1清中断标志位
        if( key8cout == 0 )
        {
          key8start = 1 ;
        } else if( key8cout > 13)
        {
          key8cout = 0 ;
          key8start = 0 ;
          key8flg ++ ;
        }
    }
    
    n = 9;
    if(PORTD_ISFR & (1 << n))         //PTDn触发中断
    {
        PORTD_ISFR  |= (1 << n);        //写1清中断标志位
        if( key9cout == 0 )
        {
          key9start = 1 ;
        } else if( key9cout > 13)
        {
          key9cout = 0 ;
          key9start = 0 ;
          key9flg ++ ;
        }
    }
    
    n = 10;
    if(PORTD_ISFR & (1 << n))         //PTDn触发中断
    {
        PORTD_ISFR  |= (1 << n);        //写1清中断标志位
        if( key10cout == 0 )
        {
          key10start = 1 ;
        } else if( key10cout > 13)
        {
          key10cout = 0 ;
          key10start = 0 ;
          key10flg ++ ;
        }
    } 
    n = 11;
    if(PORTD_ISFR & (1 << n))         //PTDn触发中断
    {
        PORTD_ISFR  |= (1 << n);        //写1清中断标志位
        if( key11cout == 0 )
        {
          key11start = 1 ;
        } else if( key11cout > 13)
        {
          key11cout = 0 ;
          key11start = 0 ;
          key11flg ++ ;
        }
    }
}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：PORTB_IRQHandler
*  功能说明：PORTB端口中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-1-25    已测试
*  备    注：引脚号需要根据自己初始化来修改
*************************************************************************/
void PORTB_IRQHandler()
{
    
  //  PORT_PCR_REG(PORTB , 10) |= PORT_PCR_ISF(1);
    u8  n = 0;    //引脚号
    n = 0;
    if(PORTB_ISFR & (1 << n))         //PTB0触发中断
    {
        PORTB_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */

    }

    n = 10;
    if(PORTB_ISFR & (1 << n))         //PTB10触发中断
    {
        PORTB_ISFR  |= (1 << n);        //写1清中断标志位
        /*  用户任务  */



    }
}


/*************************************************************************
*                             蓝宙嵌入式开发工作室
*
*  函数名称：PIT2_IRQHandler
*  功能说明：PIT2定时中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-9-18    已测试
*  备    注：
*************************************************************************/

void PIT2_IRQHandler(void)
{
   PIT_Flag_Clear(PIT2);       //清中断标志位
   

   if(key8start)
   { 
     key8cout ++ ;
   }
   if( key8cout > 150)
   {
     key8cout = 0 ;
     key8start = 0 ;
   }

   if(key9start)
   { 
     key9cout ++ ;
   }
   if( key9cout > 150)
   {
     key9cout = 0 ;
     key9start = 0 ;
   }
   
   if(key10start)
   { 
     key10cout ++ ;
   }
   if( key10cout > 150)
   {
     key10cout = 0 ;
     key10start = 0 ;
   }
   
   if(key11start)
   { 
     key11cout ++ ;
   }
   if( key11cout > 150)
   {
     key11cout = 0 ;
     key11start = 0 ;
   }   
   
}
/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：FTM0_IRQHandler
*  功能说明：FTM0输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/
void FTM0_IRQHandler()
{


}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：FTM1_IRQHandler
*  功能说明：FTM1输入捕捉中断服务函数
*  参数说明：无
*  函数返回：无
*  修改时间：2012-2-25
*  备    注：引脚号需要根据自己初始化来修改，参考现有的代码添加自己的功能
*************************************************************************/

void FTM1_IRQHandler()
{
    u8 s = FTM1_STATUS;             //读取捕捉和比较状态  All CHnF bits can be checked using only one read of STATUS.
    u8 n;
    FTM1_STATUS = 0x00;               //清中断标志位

    n = 0;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */      
          

        
        
    //    printf("\nFTM1发送中断\n");

        /*********************/
        //不建议在这里开启输入捕捉中断，而是在main函数里根据需要来开启
        //通道 CH0、CH1、Ch2、Ch3 有滤波器
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
        //delayms(10);        //因为输入的信号跳变过程不稳定，容易触发多次输入捕捉，所以添加延时
        //但考虑到中断不应该过长延时，所以开输入捕捉中断就放在main函数里，根据需要来开启
    }

    n = 1;
    if( s & (1 << n) )
    {
        FTM_CnSC_REG(FTM1_BASE_PTR, n) &= ~FTM_CnSC_CHIE_MASK; //禁止输入捕捉中断
        /*     用户任务       */


        /*********************/
        //不建议在这里开启输入捕捉中断
        //FTM_CnSC_REG(FTM1_BASE_PTR,n) |= FTM_CnSC_CHIE_MASK;  //开启输入捕捉中断
    }

}



volatile u8  pit_flag = 0;
volatile u32 dma_int_count = 0;


/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：DMA_CH4_Handler
*  功能说明：DMA通道4的中断服务函数
*  参数说明：是采集摄像头数据，本数据位摄像头AD数据，可以采集到300个点。
             设置标志位能够及时搬移。
*  函数返回：无
*  修改时间：2012-3-18    已测试
*  备    注：
*************************************************************************/
u8  DMA_Over_Flg = 0 ;     //行采集完成标志位
void DMA_CH4_Handler(void)
{
  //DMA通道4
  //  u16 i ;
 //    uart_putchar(UART0,0XAA);
  //  DMA_IRQ_CLEAN(DMA_CH4) ;
 //   DMA_IRQ_DIS(DMA_CH4);
 //   DMA_DIS(DMA_CH4);
  //  DMA_Over_Flg = 1 ;
  //   disable_irq(PORTC+87);

}

/*************************************************************************
*                             蓝宙电子工作室
*
*  函数名称：DMA_CH4_Handler
*  功能说明：DMA通道4的中断服务函数
*  参数说明：是采集摄像头数据，本数据位摄像头AD数据，可以采集到300个点。
             设置标志位能够及时搬移。
*  函数返回：无
*  修改时间：2012-3-18    已测试
*  备    注：
*************************************************************************/
void DMA_CH0_Handler(void)
{

    //DMA通道0
    printf("DMA_CH0_Handler\n");
    DMA_IRQ_CLEAN(DMA_CH0);                             //清除通道传输中断标志位    (这样才能再次进入中断)
    DMA_EN(DMA_CH0);                                    //使能通道CHn 硬件请求      (这样才能继续触发DMA传输)
  //   uart_putchar(UART0,0XAA);
}



volatile u8 LPT_INT_count = 0;
void  LPT_Handler(void)
{
    LPTMR0_CSR |= LPTMR_CSR_TCF_MASK;   //清除LPTMR比较标志
    LPT_INT_count++;                    //中断溢出加1
}