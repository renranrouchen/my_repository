
#ifndef __USART2_H
#define	__USART2_H
#include "stm32f10x.h"
#define USART2_REC_LEN 100
extern u8 IRQURA2;//串口2 接受数据完毕标志 
extern u8 USART2_RX_BUF[USART2_REC_LEN];//串口2接受数据反冲去
void usart2_init(u32 band);//串口2 初始化函数
void usart2_SendStringByLen(unsigned char * data,u8 len);//
void usart2_SendString(unsigned char * data);
u16 usart2_receive(u32 time);
void USART2SendByte(unsigned char SendData);
#endif

/*demo

#include "usart2.h"

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
//    uart_init(9600);
    LCD1602_Init();
		usart2_init(9600);
    while(1)
    {
			usart2_SendString("hello");
			delay_ms(1000);
    }
}
*/

