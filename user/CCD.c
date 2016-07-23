
#include "include.h"
#include "CCD.h"
/*

  CCD1  
  SI    E4
  CLK   E5
  AD    B4
    
*/

void CCD_init1(void)
{
  gpio_init (PTE4, GPO,HIGH);
  gpio_init (PTE5, GPO,HIGH);
  adc_init(ADC1, AD10) ;
}

void CCD_init2(void)
{
  gpio_init (PTE6, GPO,HIGH);
  gpio_init (PTE7, GPO,HIGH);
  adc_init(ADC1, AD11) ;
}



void StartIntegration(void) {

    unsigned char i;

    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
}
void CCD2_StartIntegration(void) {

    unsigned char i;

    CCD2_SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CCD2_CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    CCD2_SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();
    CCD2_CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) {
        SamplingDelay();
        SamplingDelay();
        CCD2_CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        CCD2_CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_ClrVal();           /* CLK = 0 */
}
void CCD2_ImageCapture(unsigned char * ImageData) 
{

    unsigned char i;


    CCD2_SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CCD2_CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    CCD2_SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 250; i++) {                    //更改250，让CCD的图像看上去比较平滑，
      SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
    }

    //Sampling Pixel 1

    *ImageData =  ad_once(ADC1, AD11, ADC_8bit);
    
    ImageData ++ ;
    CCD2_CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) 
    {
        SamplingDelay();
        SamplingDelay();
        CCD2_CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128

      *ImageData =  ad_once(ADC1, AD11, ADC_8bit);
        
        ImageData ++ ;
        CCD2_CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CCD2_CLK_ClrVal();           /* CLK = 0 */
    
    
    
}


void ImageCapture(unsigned char * ImageData) 
{

    unsigned char i;


    SI_SetVal();            /* SI  = 1 */
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SI_ClrVal();            /* SI  = 0 */
    SamplingDelay();

    //Delay 10us for sample the first pixel
    /**/
    for(i = 0; i < 250; i++) {                    //更改250，让CCD的图像看上去比较平滑，
      SamplingDelay() ;  //200ns                  //把该值改大或者改小达到自己满意的结果。
    }

    //Sampling Pixel 1

    *ImageData =  ad_once(ADC1, AD10, ADC_8bit);
    
    ImageData ++ ;
    CLK_ClrVal();           /* CLK = 0 */

    for(i=0; i<127; i++) 
    {
        SamplingDelay();
        SamplingDelay();
        CLK_SetVal();       /* CLK = 1 */
        SamplingDelay();
        SamplingDelay();
        //Sampling Pixel 2~128

      *ImageData =  ad_once(ADC1, AD10, ADC_8bit);
        
        ImageData ++ ;
        CLK_ClrVal();       /* CLK = 0 */
    }
    SamplingDelay();
    SamplingDelay();
    CLK_SetVal();           /* CLK = 1 */
    SamplingDelay();
    SamplingDelay();
    CLK_ClrVal();           /* CLK = 0 */
    
    
    
}



#define usat UART0
//#define usat UART

void SendHex(unsigned char hex) {
  unsigned char temp;
  temp = hex >> 4;
  if(temp < 10) {
    uart_putchar(usat,temp + '0');
  } else {
    uart_putchar(usat,temp - 10 + 'A');
  }
  temp = hex & 0x0F;
  if(temp < 10) {
    uart_putchar(usat,temp + '0');
  } else {
   uart_putchar(usat,temp - 10 + 'A');
  }
}


void SendImageData(unsigned char * ImageData) {

    unsigned char i;
    unsigned char crc = 0;

    /* Send Data */
    uart_putchar(usat,'*');
    uart_putchar(usat,'L');
    uart_putchar(usat,'D');

    SendHex(0);
    SendHex(0);
    SendHex(0);
    SendHex(0);

    for(i=0; i<128; i++) {
      SendHex(*ImageData++);
    }

    SendHex(crc);
    uart_putchar(usat,'#');
}


void SamplingDelay(void)
{
   volatile u8 i ;
   for(i=0;i<1;i++) {
    asm("nop");
    asm("nop");}
}

















