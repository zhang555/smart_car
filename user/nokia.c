
#include "common.h"
#include "include.h"
#include "nokia.h"
#include "MK60_gpio.h"



/************************************************************************
     NOKIA5110 一行可以显示14个字符，可以显示六行。
************************************************************************/
/*-----------------------------------------------------------------------
font5x8【】        : 数据表
编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/

const u8 font5x8[]={
0x00, 0x00, 0x00, 0x00, 0x00,   // sp    1
0x00, 0x00, 0x2f, 0x00, 0x00,   // !     2
0x00, 0x07, 0x00, 0x07, 0x00,   // "     3
0x14, 0x7f, 0x14, 0x7f, 0x14,   // #     4
0x24, 0x2a, 0x7f, 0x2a, 0x12,   // $     5
0x62, 0x64, 0x08, 0x13, 0x23,   // %     6
0x36, 0x49, 0x55, 0x22, 0x50,   // &     7
0x00, 0x05, 0x03, 0x00, 0x00,   // ’    8
0x00, 0x1c, 0x22, 0x41, 0x00,   // (     9
0x00, 0x41, 0x22, 0x1c, 0x00,   // )     10
0x14, 0x08, 0x3E, 0x08, 0x14,   // *     11
0x08, 0x08, 0x3E, 0x08, 0x08,   // +     12
0x00, 0x00, 0xA0, 0x60, 0x00,   // ,     13
0x08, 0x08, 0x08, 0x08, 0x08,   // -     14
0x00, 0x60, 0x60, 0x00, 0x00,   // .     15
0x20, 0x10, 0x08, 0x04, 0x02,   // /     16
0x3E, 0x51, 0x49, 0x45, 0x3E,   // 0     17
0x00, 0x42, 0x7F, 0x40, 0x00,   // 1     18
0x42, 0x61, 0x51, 0x49, 0x46,   // 2     19
0x21, 0x41, 0x45, 0x4B, 0x31,   // 3     20
0x18, 0x14, 0x12, 0x7F, 0x10,   // 4     21
0x27, 0x45, 0x45, 0x45, 0x39,   // 5     22
0x3C, 0x4A, 0x49, 0x49, 0x30,   // 6     23
0x01, 0x71, 0x09, 0x05, 0x03,   // 7     24
0x36, 0x49, 0x49, 0x49, 0x36,   // 8     25
0x06, 0x49, 0x49, 0x29, 0x1E,   // 9     26
0x00, 0x36, 0x36, 0x00, 0x00,   // :     27
0x00, 0x56, 0x36, 0x00, 0x00,   // ;     28
0x08, 0x14, 0x22, 0x41, 0x00,   // <     29
0x14, 0x14, 0x14, 0x14, 0x14,   // =     30
0x00, 0x41, 0x22, 0x14, 0x08,   // >     31
0x02, 0x01, 0x51, 0x09, 0x06,   // ?     32
0x32, 0x49, 0x59, 0x51, 0x3E,   // @     33
0x7C, 0x12, 0x11, 0x12, 0x7C,   // A     34
0x7F, 0x49, 0x49, 0x49, 0x36,   // B     35
0x3E, 0x41, 0x41, 0x41, 0x22,   // C     36
0x7F, 0x41, 0x41, 0x22, 0x1C,   // D     37
0x7F, 0x49, 0x49, 0x49, 0x41,   // E     38
0x7F, 0x09, 0x09, 0x09, 0x01,   // F     39
0x3E, 0x41, 0x49, 0x49, 0x7A,   // G     40
0x7F, 0x08, 0x08, 0x08, 0x7F,   // H     41
0x00, 0x41, 0x7F, 0x41, 0x00,   // I     42
0x20, 0x40, 0x41, 0x3F, 0x01,   // J     43
0x7F, 0x08, 0x14, 0x22, 0x41,   // K     44
0x7F, 0x40, 0x40, 0x40, 0x40,   // L     45
0x7F, 0x02, 0x0C, 0x02, 0x7F,   // M     46
0x7F, 0x04, 0x08, 0x10, 0x7F,   // N     47
0x3E, 0x41, 0x41, 0x41, 0x3E,   // O     48
0x7F, 0x09, 0x09, 0x09, 0x06,   // P     49
0x3E, 0x41, 0x51, 0x21, 0x5E,   // Q     50
0x7F, 0x09, 0x19, 0x29, 0x46,   // R     51
0x46, 0x49, 0x49, 0x49, 0x31,   // S     52
0x01, 0x01, 0x7F, 0x01, 0x01,   // T     53
0x3F, 0x40, 0x40, 0x40, 0x3F,   // U     54
0x1F, 0x20, 0x40, 0x20, 0x1F,   // V     55
0x3F, 0x40, 0x38, 0x40, 0x3F,   // W     56
0x63, 0x14, 0x08, 0x14, 0x63,   // X     57
0x07, 0x08, 0x70, 0x08, 0x07,   // Y     58
0x61, 0x51, 0x49, 0x45, 0x43,   // Z     59
0x00, 0x7F, 0x41, 0x41, 0x00,   // [     60
0x55, 0x2A, 0x55, 0x2A, 0x55,   // 55    61
0x00, 0x41, 0x41, 0x7F, 0x00,   // ]     62
0x04, 0x02, 0x01, 0x02, 0x04,   // ^     63
0x40, 0x40, 0x40, 0x40, 0x40,   // _     64
0x00, 0x01, 0x02, 0x04, 0x00,   // ’    65
0x20, 0x54, 0x54, 0x54, 0x78,   // a     66
0x7F, 0x48, 0x44, 0x44, 0x38,   // b     67
0x38, 0x44, 0x44, 0x44, 0x20,   // c     68
0x38, 0x44, 0x44, 0x48, 0x7F,   // d     69
0x38, 0x54, 0x54, 0x54, 0x18,   // e     70
0x08, 0x7E, 0x09, 0x01, 0x02,   // f     71
0x18, 0xA4, 0xA4, 0xA4, 0x7C,   // g     72
0x7F, 0x08, 0x04, 0x04, 0x78,   // h     73
0x00, 0x44, 0x7D, 0x40, 0x00,   // i     74
0x40, 0x80, 0x84, 0x7D, 0x00,   // j     75
0x7F, 0x10, 0x28, 0x44, 0x00,   // k     76
0x00, 0x41, 0x7F, 0x40, 0x00,   // l     77
0x7C, 0x04, 0x18, 0x04, 0x78,   // m     78
0x7C, 0x08, 0x04, 0x04, 0x78,   // n     79
0x38, 0x44, 0x44, 0x44, 0x38,   // o     80
0xFC, 0x24, 0x24, 0x24, 0x18,   // p     81
0x18, 0x24, 0x24, 0x18, 0xFC,   // q     82
0x7C, 0x08, 0x04, 0x04, 0x08,   // r     83
0x48, 0x54, 0x54, 0x54, 0x20,   // s     84
0x04, 0x3F, 0x44, 0x40, 0x20,   // t     85
0x3C, 0x40, 0x40, 0x20, 0x7C,   // u     86
0x1C, 0x20, 0x40, 0x20, 0x1C,   // v     87
0x3C, 0x40, 0x30, 0x40, 0x3C,   // w     88
0x44, 0x28, 0x10, 0x28, 0x44,   // x     89
0x1C, 0xA0, 0xA0, 0xA0, 0x7C,   // y     90
0x44, 0x64, 0x54, 0x4C, 0x44,   // z     91
0x00, 0x08, 0x36, 0x41, 0x00,   // {     92
0x00, 0x00, 0x7F, 0x00, 0x00,   // |     93
0x00, 0x41, 0x36, 0x08, 0x00,   // }     94
0x08, 0x10, 0x08, 0x04, 0x08    // ~     95
};

/*-----------------------------------------------------------------------
write_chinese[][24]   : 数据表
-----------------------------------------------------------------------*/
const u8  write_chinese[][24]={

//蓝
	{0x00,0x02,0xE2,0x02,0x07,0xF2,0x82,0x42,0x32,0x22,0x67,0xA2,0x00,0x20,0x20,0x3E,0x22,0x23,0x3E,0x22,0x3E,0x22,0x22,0x3E},
//宙
	{0x00,0x1C,0xC4,0x44,0x44,0x44,0x45,0xF6,0x44,0x44,0x44,0x44,0x00,0x00,0x3F,0x12,0x12,0x12,0x12,0x1F,0x12,0x12,0x12,0x12},
//电
	{0x00,0xFC,0x94,0x94,0x94,0xFF,0x94,0x94,0x94,0xFE,0x04,0x00,0x00,0x01,0x00,0x00,0x00,0x03,0x04,0x04,0x04,0x04,0x06,0x00},
//子
	{0x20,0x21,0x21,0x21,0x21,0xF9,0x29,0x25,0x23,0x31,0x20,0x00,0x00,0x00,0x00,0x04,0x04,0x07,0x00,0x00,0x00,0x00,0x00,0x00},

//测
	{0x89,0xF2,0x00,0xFF,0x01,0xF9,0xFF,0x00,0xFC,0x00,0xFF,0x00,0x00,0x07,0x04,0x04,0x02,0x01,0x02,0x04,0x01,0x04,0x07,0x00},
//试
	{0x11,0xF6,0x00,0x04,0x24,0xE4,0x24,0x24,0xFF,0x05,0x06,0x00,0x00,0x07,0x02,0x01,0x02,0x03,0x01,0x01,0x01,0x02,0x07,0x00},
//程
	{0x8A,0x6A,0xFF,0x49,0x20,0xAF,0xA9,0xE9,0xA9,0xAF,0x20,0x00,0x01,0x00,0x07,0x00,0x04,0x04,0x04,0x07,0x04,0x04,0x04,0x00},
//序
	{0x00,0xFE,0x42,0x4A,0x4A,0x5B,0xEA,0x5A,0x4A,0xC2,0x42,0x00,0x06,0x01,0x00,0x00,0x04,0x04,0x07,0x00,0x00,0x00,0x00,0x00},
};
/*-----------------------------------------------------------------------
delay_1us         : 延时程序
编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/

void delay_1us(void)                 //1.28us延时函数
  {
   volatile u16 i;
  for(i=0;i<15;i++) ;

  }
/*-----------------------------------------------------------------------
delay_1ns         : 延时程序
编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/

void delay_1ns(void)                 //500ns延时函数
  {
   volatile u16 i;

  for(i=0;i<15;i++) ;


  }
/*-----------------------------------------------------------------------
LCD_clear         : LCD清屏函数
编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/
void LCD_clear(void)
  {
    unsigned int i;

    LCD_write_byte(0x0c, 0);
    LCD_write_byte(0x80, 0);

    for (i=0; i<504; i++)
      LCD_write_byte(0, 1);
  }

/***********************************************************
函数名称：LCD_write_byte
函数功能：模拟SPI接口时序写数据/命令LCD
入口参数：data    ：写入的数据；
          command ：写数据/命令选择；
出口参数：无
备 注：
***********************************************************/
void LCD_write_byte(u8 dat, u8 command)
{
    u8 i;
    LCD_CE = 0;					  //5110片选有效，允许输入数据
    if (command == 0)				 //写命令
          LCD_DC = 0;
    else  LCD_DC = 1;			  //写数据
	for(i=0;i<8;i++)				     //传送8bit数据
        {
            if(dat&0x80)
               SDIN = 1;
            else
               SDIN = 0;
            SCLK = 0;
            dat = dat << 1;
            delay_1ns();
        //    DELAY_MS(1) ;
            SCLK = 1;
        //    DELAY_MS(1) ;
            delay_1ns();
        }
     LCD_CE = 1;					  //禁止5110
}
/***********************************************************
函数名称：LCD_init
函数功能：5110初始化
入口参数：无
出口参数：无
备 注：
***********************************************************/
void LCD_init(void)
{

     gpio_init(PTC15,GPO,0);
     gpio_init(PTC6,GPO,0);
     gpio_init(PTB22,GPO,0);
     gpio_init(PTB21,GPO,0);
     gpio_init(PTC7,GPO,0); 
    

    
   LCD_RST = 0;     // 产生一个让LCD复位的低电平脉冲
    delay_1us();
 //  DELAY_MS(1) ;
   LCD_RST = 1;

   LCD_CE = 0;     // 关闭LCD
    delay_1us();
 //  DELAY_MS(1) ;
   LCD_CE = 1;     // 使能LCD
    delay_1us();
 //  DELAY_MS(1) ;

    LCD_write_byte(0x21, 0);	// 使用扩展命令设置LCD模式
    LCD_write_byte(0xc8, 0);	// 设置液晶偏置电压
    LCD_write_byte(0x06, 0);	// 温度校正
    LCD_write_byte(0x13, 0);	// 1:48
    LCD_write_byte(0x20, 0);	// 使用基本命令，V=0，水平寻址
    LCD_clear();	           // 清屏
    LCD_write_byte(0x0c, 0);	// 设定显示模式，正常显示

    LCD_CE = 0;      // 关闭LCD
  }
/***********************************************************
函数名称：LCD_set_XY
函数功能：设置LCD坐标函数
入口参数：X       ：0－83
          Y       ：0－5
出口参数：无
备 注：
***********************************************************/
void LCD_set_XY(u8 X, u8 Y)
  {
    LCD_write_byte(0x40 | Y, 0);	// column
    LCD_write_byte(0x80 | X, 0);        // row
  }
/***********************************************************
函数名称：LCD_write_char
函数功能：显示英文字符
入口参数：c	:  显示的字符
出口参数：无
备 注：
***********************************************************/
void LCD_write_char(u8 c)
{
    u8 line;
    u16 cout ;
    cout =  c ;
    if((cout < 32)||((cout > 126)))
         cout = 0;

    cout -= 32;                       //数组的行号
    cout = cout*5 ;

    for (line=0; line<5; line++)
    {
      LCD_write_byte(font5x8[cout], 1);
      cout ++ ;
    }
    LCD_write_byte(0, 1);
}

/****************************************************************************************
函数名称：LCD_Write_String
函数功能：显示英文字符串
入口参数：X       ：0－83
          Y       ：0－5
          *s      ：英文字符串的指针
出口参数：无
备 注：
****************************************************************************************/
void LCD_Write_String(u8 X,u8 Y,char *s)
{
    LCD_set_XY(X,Y);
    while (*s)
    {
	 	LCD_write_char(*s);
	 	s++;
    }
}

/****************************************************************************************
函数名称：LCD_Write_Chinese
函数功能：显示英文字符串
入口参数：X       ：0－83
          Y       ：0－5
          ch_with ：汉字宽度
          num     ：汉字个数
          row     ：汉字显示行间距
出口参数：无
备 注：
****************************************************************************************/
void LCD_Write_Chinese(u8 X, u8 Y, u8 ch_with,u8 num,u8 row)
{
    unsigned char i,n;
    LCD_set_XY(X,Y);
    for (i=0;i<num;)
    {
      	for (n=0; n<ch_with*2; n++)
      	{
      	    if (n==ch_with)
      	      {
      	        if (i==0)
					LCD_set_XY(X,Y+1);
      	        else
      	           	LCD_set_XY((X+(ch_with+row)*i),Y+1);
              }
      	    LCD_write_byte(write_chinese[i][n],1);
      	}
      	i++;
      	LCD_set_XY((X+(ch_with+row)*i),Y);
    }
}



void  NOKIA_show()
{

  extern u16 duoji_pwm;

  extern u8 PixelAverageValue;
  extern u8 IntegrationTime;
  extern s16 Track_C_Line_1[10];
//  extern s16 L_Line_1[10] ;
 // extern s16 R_Line_1[10] ;
//  extern float P;
  

//  extern u16 NRF_pwm;  
  
  extern u16 Target_count ;
  extern u16 left_dianji_pwm;
  
  extern u8 NRF_flag;
  
  extern s16 speed_P;
  extern s16 speed_I;
  extern s16 speed_D; 
  
  extern u16 hongwai1 , hongwai2;
  extern u8 stop_flag;  
  
  u8 a[4]={0};
  u8 b[4]={0};  
  u8 c[4]={0};  
  u8 g[4]={0}; 
  u8 h[4]={0};  
  u8 i[5]={0};  
  u8 j[5]={0};    
  
  u8 speed_P_ar[5],speed_I_ar[5],speed_D_ar[5];
  
  u8 k[5]={0};   
  u8 l[5]={0};   
  u8 m[4]={0};     
  
  a[0]=(PixelAverageValue)/100 + 48;
  a[1]=(PixelAverageValue)%100/10 + 48;
  a[2]=(PixelAverageValue)%10 + 48;
  
  b[0]=IntegrationTime/100 + 48;
  b[1]=IntegrationTime%100/10 + 48;
  b[2]=IntegrationTime%10 + 48;  
  
  c[0]=Track_C_Line_1[0]/100 + 48;
  c[1]=Track_C_Line_1[0]%100/10 + 48;
  c[2]=Track_C_Line_1[0]%10 + 48;  
 
  i[0]= Target_count %1000 /100 + 48;
  i[1]= Target_count %100/10 + 48;
  i[2]= Target_count %10 + 48;    
  
  j[0]= left_dianji_pwm /1000      + 48;
  j[1]= left_dianji_pwm %1000 /100 + 48;
  j[2]= left_dianji_pwm %100  /10  + 48;
  j[3]= left_dianji_pwm %10        + 48;
  
  k[0]= hongwai1 /1000      + 48;
  k[1]= hongwai1 %1000 /100 + 48;
  k[2]= hongwai1 %100  /10  + 48;
  k[3]= hongwai1 %10        + 48;  

  l[0]= hongwai2 /1000      + 48;
  l[1]= hongwai2 %1000 /100 + 48;
  l[2]= hongwai2 %100  /10  + 48;
  l[3]= hongwai2 %10        + 48; 
  
  
  m[0]= stop_flag /1000      + 48;
  m[1]= stop_flag %1000 /100 + 48;
  m[2]= stop_flag %100  /10  + 48;  
  
 /*
  speed_P_ar[0] = speed_P /1000       + 48;
  speed_P_ar[1] = speed_P %1000 /100  + 48;
  speed_P_ar[2] = speed_P %100  /10   + 48;
  speed_P_ar[3] = speed_P %10         + 48;   
  speed_P_ar[4] = 0;
  
  speed_I_ar[0] = speed_I /1000       + 48;
  speed_I_ar[1] = speed_I %1000 /100  + 48;
  speed_I_ar[2] = speed_I %100  /10   + 48;
  speed_I_ar[3] = speed_I %10         + 48;   		
  speed_I_ar[4] = 0;
  
  speed_D_ar[0] = speed_D /1000       + 48;
  speed_D_ar[1] = speed_D %1000 /100  + 48;
  speed_D_ar[2] = speed_D %100  /10   + 48;
  speed_D_ar[3] = speed_D %10         + 48;   		
  speed_D_ar[4] = 0;
    */            
                
/*  
  j[0]= NRF_pwm / 1000 +48 ;
  j[1]= NRF_pwm %1000/100 + 48;
  j[2]= NRF_pwm %100/10 + 48;
  j[3]= NRF_pwm %10 + 48;*/


    LCD_Write_String(0,0,"Val:");
    LCD_Write_String(25,0,a);
    
    LCD_Write_String(45,0,"Tim:");
    LCD_Write_String(60,0,b);
      
        
    LCD_Write_String(0,1,"T_C:");   
    LCD_Write_String(25,1,i);  
    LCD_Write_String(45,1,j);     
    
    /*
    
    LCD_Write_String(0,2,"speed_P");     LCD_Write_String(50,2,speed_P_ar);    
    LCD_Write_String(0,3,"speed_I");        LCD_Write_String(50,3,speed_I_ar);       
    LCD_Write_String(0,4,"speed_D");   LCD_Write_String(50,4,speed_D_ar);     
    
    */
    
    LCD_Write_String(0,2,"hong1");     LCD_Write_String(50,2,k);       
    LCD_Write_String(0,3,"hong2");     LCD_Write_String(50,3,l);       
   
    LCD_Write_String(0,4,"stop:");     LCD_Write_String(50,4,m);    
    
//    LCD_Write_String(0,5,"cen");   LCD_Write_String(50,5,stop_flag);    
    
    
   
    
    
    if(NRF_flag & 0X40)
    {
      LCD_Write_String(0,5,"fail"); 
    }
    else
    {
      LCD_Write_String(0,5,"OK"); 
    }
     
 

//    LCD_Write_String(40,5,"zj1:");
}














