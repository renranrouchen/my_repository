#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/8/18
//版本：V1.5
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
//V1.5修改说明
//1,增加了对UCOSII的支持
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);
void UART1_Send_String(unsigned char *Index);
void USART1_Send_Data(unsigned char *Data,unsigned short Length);

/*DEMO

unsigned char buff[30];
unsigned long milli;
u8 keyVal;
void Bule_Send()
{
		buff[0]= 'H';
		buff[1]= ':';
	  buff[2]= PH0_Value/1000%10+0x30;
		buff[3]= PH0_Value/100%10+0x30;
		buff[4]= PH0_Value/10%10+0x30;
		buff[5]= PH0_Value%10+0x30;
		buff[6]= ',';
		buff[7]= PH1_Value/1000%10+0x30;
		buff[8]= PH1_Value/100%10+0x30;
		buff[9]= PH1_Value/10%10+0x30;
		buff[10]= PH1_Value%10+0x30;	
		buff[11]= ',';
		buff[12]= PH2_Value/1000%10+0x30;
		buff[13]= PH2_Value/100%10+0x30;
		buff[14]= PH2_Value/10%10+0x30;
		buff[15]= PH2_Value%10+0x30;
		buff[16]= ',';			
		buff[17]= 'E';	
		USART1_Send_Data(buff,sizeof(buff));		
}

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	 // GPIO_TEST();
	  delay_ms(500);

	  uart_init(9600);
		OLED_Init3();


		OLED_ShowStr_ENCH(0,0,(unsigned char *)"01欢迎使用密码",1);

		OLED_Refresh_Gram();	
    while(1)
    {

			Bule_Send();
			printf("hello");

			delay_ms(100);
    }
}



*/
#endif


