

#ifndef  CCD_H
#define  CCD_H  

#include "common.h"


#define SI_SetVal()   PTE4_OUT = 1
#define SI_ClrVal()   PTE4_OUT = 0
#define CLK_ClrVal()  PTE5_OUT = 0
#define CLK_SetVal()  PTE5_OUT = 1

#define CCD2_SI_SetVal()   PTE6_OUT = 1
#define CCD2_SI_ClrVal()   PTE6_OUT = 0
#define CCD2_CLK_ClrVal()  PTE7_OUT = 0
#define CCD2_CLK_SetVal()  PTE7_OUT = 1



void StartIntegration(void) ;   
void ImageCapture(unsigned char * ImageData) ;
void SendHex(unsigned char hex) ;
void SamplingDelay(void) ;
void CCD_init1(void) ;

void CCD_init2(void) ;
void CCD2_StartIntegration(void) ;   
void CCD2_ImageCapture(unsigned char * ImageData) ;

u8 PixelAverage(u8 len, u8 *data) ;
void SendImageData(unsigned char * ImageData) ;



#endif
