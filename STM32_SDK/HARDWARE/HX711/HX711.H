#ifndef __HX711_H
#define __HX711_H	 
#include "sys.h"
#include "delay.h"
#define GapValue 405

unsigned long Get_Maopi(void);
unsigned long Get_Weight(void);
void GPIO_Weigh_Init(void);
#endif

/*demo

unsigned long Weight_Maopi2,Weight;
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
    uart_init(9600);
    LCD1602_Init();
    GPIO_Weigh_Init();
	  Weight_Maopi2 = Get_Maopi();
    while(1)
    {
			Weight = Get_Weight();
			
			delay_ms(1000);
    }
}


*/

