/*
 * File:		nokia.h
 * Purpose:		Serial Input/Output routines
 *
 */

#ifndef _NOKIA_H
#define _NOKIA_H

#include "MK60_gpio.h"
/********************************************************************/
/*-----------------------------------------------------------------------
LCD_init          : 5110LCD初始化

编写日期          ：2012-11-01
最后修改日期      ：2012-11-01
-----------------------------------------------------------------------*/
#define LCD_RST   PTC15_OUT
#define LCD_CE    PTC6_OUT
#define SDIN      PTB22_OUT
#define SCLK      PTB21_OUT
#define LCD_DC    PTC7_OUT


void delay_1us(void)  ;
void delay_1ns(void)  ;
void LCD_clear(void);
void LCD_write_byte(u8 dat, u8 command);
void LCD_init(void) ;
void LCD_write_char(u8 c) ;
void LCD_set_XY(u8 X, u8 Y);
void LCD_Write_String(u8 X,u8 Y,char *s);
void LCD_Write_Chinese(u8 X, u8 Y, u8 ch_with,u8 num,u8 row);

void NOKIA_show();


/********************************************************************/

#endif
