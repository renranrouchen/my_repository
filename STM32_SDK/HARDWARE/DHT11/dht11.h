#ifndef __DHT11_H
#define __DHT11_H 
#include "sys.h"   
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//DHT11数字温湿度传感器驱动代码	   

//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
 
//IO方向设置
#define DHT11_IO_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=3<<20;}
////IO操作函数											   
#define	DHT11_DQ_OUT PCout(13) //数据端口	PA0 
#define	DHT11_DQ_IN  PCin(13)  //数据端口	PA0 


u8 DHT11_Init(void);//初始化DHT11
u8 DHT11_Read_Data(u8 *temp,u8 *humi);//读取温湿度
u8 DHT11_Read_Byte(void);//读出一个字节
u8 DHT11_Read_Bit(void);//读出一个位
u8 DHT11_Check(void);//检测是否存在DHT11
void DHT11_Rst(void);//复位DHT11    
#endif


/*demo

unsigned char Temp,RhValue;
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

    LCD1602_Init();
	  Lcd1602_Display_Two_bit(0,0,1);
	  DHT11_Init();
    while(1)
    {
			if(DHT11_Read_Data(&Temp,&RhValue) == 0)
			{
				Lcd1602_Display_Three_bit(0,0,Temp);//读出温湿度，只取整数部分
				Lcd1602_Display_Three_bit(1,0,RhValue);
			}
			delay_ms(200);
    }
}

*/












