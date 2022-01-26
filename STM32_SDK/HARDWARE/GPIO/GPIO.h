#ifndef __GPIO_H
#define __GPIO_H	 
#include "sys.h"
#include "delay.h"
//////////////////////////////////////////////////////////////////////////////////	 

//#define KEY1   PBin(12)	
//#define KEY2   PBin(13)	
//#define KEY3   PBin(14)

#define BEEP   PBout(9)

#define      PA_0                GPIOA->BRR  = 0x00000002 //PC.13
#define      PA_1          			 GPIOA->BSRR  = 0x00000002 //PC.14

#define LED0 PAout(1)
#define LED1 PAout(2)
#define LED2 PAout(3)

void Key_Init(void);
	 				    
#endif
