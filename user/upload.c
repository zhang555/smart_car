
#include "include.h"
#include "upload.h"
#include "bianmaqi.h"



void Upload_01(void)
{
      u8 len=17; //长度  2+1+1+12+1
  
	u8 send_buf[32]={0};
	u8 i;
	
	u8 sum = 0;
         
	send_buf[0]=0xAA;
	send_buf[1]=0xAA;
	send_buf[2]=0x01;
	send_buf[3]=len-5;
        
	send_buf[4]=(((u16)DMA_count_get(DMA_CH0)*100)>>8)&0XFF;  //高8位
	send_buf[5]=((u16)DMA_count_get(DMA_CH0)*100)&0XFF; //低8位
        
	send_buf[6]=(((u16)DMA_count_get(DMA_CH1)*100)>>8)&0XFF;
	send_buf[7]=((u16)DMA_count_get(DMA_CH1)*100)&0XFF;
        
	send_buf[8]=0;
	send_buf[9]=0xff;
        
	send_buf[10]=0;
	send_buf[11]=0;
	send_buf[12]=0;
	send_buf[13]=0;
        
	send_buf[14]=0;
	send_buf[15]=0;	


	for(i=0;i<len-1;i++)
		sum += send_buf[i];
	send_buf[16] = sum;

        uart_putbuff (UART3, send_buf, len);

     
}

/*
void Upload_02(void)
{
      u8 len=27; //长度  2+1+1+22+1

	u8 send_buf[32]={0};
	u8 i;
	
	u8 sum = 0;
         
	send_buf[0]=0xAA;
	send_buf[1]=0xAA;
	send_buf[2]=0x02;
	send_buf[3]=len-5;
        
	send_buf[4]=(n1>>8)&0XFF;  //高8位
	send_buf[5]=n1&0XFF; //低8位
        
	send_buf[6]=(n2>>8)&0XFF;
	send_buf[7]=n2&0XFF;
        
	send_buf[8]=(n3>>8)&0XFF;
	send_buf[9]=n3&0XFF;
        
	send_buf[10]=(n4>>8)&0XFF;
	send_buf[11]=n4&0XFF;
	
	send_buf[12]=0;
	send_buf[13]=0xff;
        
	send_buf[14]=0;
	send_buf[15]=0;	

	send_buf[16]=0;
	send_buf[17]=0;
        
	send_buf[18]=0;
	send_buf[19]=0;	
        
	send_buf[20]=0;
	send_buf[21]=0;	        
        
	send_buf[22]=0;
	send_buf[23]=0;	        
	send_buf[24]=0;
	send_buf[25]=0;	        
        
        
	for(i=0;i<len-1;i++)
		sum += send_buf[i];
	send_buf[26] = sum;

        uart_putbuff (UART3, send_buf, len);

     
}

*/
u16 upload_count=0;
//加速度 角速度 磁场
void Upload_02(void)
{
  extern s16 L_Line_1[10] ;
  extern s16 R_Line_1[10] ;
  extern s16 Track_C_Line_1[10];
  extern s32 left_dianji_pwm,right_dianji_pwm;
  extern s16 Ave_count;
//static u16 upload_count=0;

      u8 len=27; //长度  2+1+1+22+1

	u8 send_buf[32]={0};
	u8 i;
	
	u8 sum = 0;
         
        upload_count++;
        
	send_buf[0]=0xAA;
	send_buf[1]=0xAA;
	send_buf[2]=0x02;
	send_buf[3]=len-5;
        
        //加速度
	send_buf[4]=upload_count>>8 & 0XFF;
	send_buf[5]=upload_count&0XFF;
        
	send_buf[6]= left_count>>8&0XFF;  //高8位       
 	send_buf[7]=left_count&0XFF; //低8位	
        
        send_buf[8]=right_count>>8&0XFF;
	send_buf[9]=right_count&0XFF;

      //角速度
	send_buf[10]=L_Line_1[0]>>8&0XFF;
	send_buf[11]=L_Line_1[0]&0XFF;

	send_buf[12]=R_Line_1[0]>>8&0XFF;
	send_buf[13]=R_Line_1[0]&0XFF;
        
	send_buf[14]=Track_C_Line_1[0]>>8&0XFF;
	send_buf[15]=Track_C_Line_1[0]&0XFF;

        //磁场 
	send_buf[16]= Ave_count >> 8 & 0xff;
	send_buf[17]= Ave_count      & 0xff;
        
	send_buf[18]= left_dianji_pwm >> 8 & 0xff;
	send_buf[19]= left_dianji_pwm      & 0xff;	
        
	send_buf[20]=0;
	send_buf[21]=0;	        
        
	send_buf[22]=0;
	send_buf[23]=0;	        
	send_buf[24]=0;
	send_buf[25]=0;	        
        
        
	for(i=0;i<len-1;i++)
		sum += send_buf[i];
	send_buf[26] = sum;

        uart_putbuff (UART0, send_buf, len);

     
}



