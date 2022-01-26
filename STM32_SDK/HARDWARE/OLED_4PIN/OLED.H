
#ifndef _OLED_H
#define _OLED_H

#include "delay.h"
#include "sys.h"
#include <font.h>



#define SCL3_0	GPIO_ResetBits(GPIOB,GPIO_Pin_9)			// Serial Clock Input
#define SDA3_0	GPIO_ResetBits(GPIOB,GPIO_Pin_8)				// Serial Data Input


#define SCL3_1	GPIO_SetBits(GPIOB,GPIO_Pin_9)					// Serial Clock Input
#define SDA3_1	GPIO_SetBits(GPIOB,GPIO_Pin_8)					// Serial Data Input




//  
//#define SCL3_0	GPIO_ResetBits(GPIOB,GPIO_Pin_8)			// Serial Clock Input
//#define SDA3_0	GPIO_ResetBits(GPIOB,GPIO_Pin_9)				// Serial Data Input


//#define SCL3_1	GPIO_SetBits(GPIOB,GPIO_Pin_8)					// Serial Clock Input
//#define SDA3_1	GPIO_SetBits(GPIOB,GPIO_Pin_9)					// Serial Data Input






extern volatile unsigned char Error_Flag;

void OLED_ShowGBK(u8 x, u8 y,  u8 num, u8 size,u8 mode);


void	OLED_Init3(void);
void OLED_Refresh_Gram(void);
void OLED_Clear(void);
void OLED_ShowString(u8 x,u8 y,const u8 *p);
void OLED_Processing(void);
void OLED_ShowStr_ENCH(u8 x, u8 y,unsigned char *s,u8 mode);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
/**demo

int main(void)
{
    delay_init();	    		//—” ±∫Ø ˝≥ı ºªØ
    NVIC_Configuration();
	 // GPIO_TEST();
	  delay_ms(500);

		OLED_Init3();
	

		OLED_ShowStr_ENCH(0,0,(unsigned char *)"01ª∂”≠ π”√√‹¬Î",1);
		OLED_ShowStr_ENCH(0,16,(unsigned char *)" 02ª∂”≠",1);
		OLED_ShowStr_ENCH(0,32,(unsigned char *)"  03ª∂”≠",1);
		//OLED_ShowStr_ENCH(0,48,(unsigned char *)"   04ª∂”≠",1);
	  OLED_ShowNum(16,48,3,1,16);
		OLED_Refresh_Gram();	
    while(1)
    {

			delay_ms(1000);
    }
}

**/
#endif

