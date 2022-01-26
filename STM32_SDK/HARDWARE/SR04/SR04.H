#ifndef __SR04_H
#define __SR04_H

#include "sys.h"
#include "delay.h"

#define Trig   PAout(3)
#define Echo   PAin(4)
void SR04_Init(void);
void SR04_Processing(unsigned short *Length_Value);
#endif

/**demo

unsigned short Lenght;
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
//    uart_init(9600);
    LCD1602_Init();
		SR04_Init( );
    while(1)
    {
			SR04_Processing(&Lenght);
			Lcd1602_Display_Three_bit(0,0,Lenght);
			delay_ms(1000);
    }
}
**/
