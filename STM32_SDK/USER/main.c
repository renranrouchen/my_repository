#include "struct_all.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "My_Demo.h"


int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
    while(1)
    {

			delay_ms(100);
    }
}

