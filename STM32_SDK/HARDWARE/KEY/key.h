#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK miniSTM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PCin(5)   	
//#define KEY1 PAin(15)	 
//#define WK_UP  PAin(0)	 
typedef void (*pKey_Process)(unsigned char );

#define KEY0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13)//读取按键1
#define KEY2   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_14)//读取按键2 
#define KEY3   GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_15)//读取按键2 

#define KEY0_PRES	1		//KEY0  
#define KEY1_PRES	2		//KEY1 
#define KEY2_PRES	3		//WK_UP  
#define KEY3_PRES	4		//WK_UP 
void KEY_Init(void);//IO初始化
u8 KEY_Scan(u8 mode);  	//按键扫描函数					
void Key_Process(pKey_Process Key_Process_p);

/*DEMO

u8 keyVal;

void Key_Process_s(unsigned char keyValue)
{
	if(keyValue == 1 )
	{
		keyVal++;

	}
	if(keyValue == 2 )
	{
		keyVal=keyVal+2;

	}
	if(keyValue == 3 )
	{
		keyVal=keyVal+3;

	}	
	if(keyValue == 4 )
	{
		keyVal=keyVal+4;

	}		
}
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	 // GPIO_TEST();
	  delay_ms(500);

		OLED_Init3();

		KEY_Init();
		OLED_ShowStr_ENCH(0,0,(unsigned char *)"01欢迎使用密码",1);

		OLED_Refresh_Gram();	
    while(1)
    {
			Key_Process(Key_Process_s);

			OLED_ShowNum(16*3,32,keyVal,4,16);
			OLED_Refresh_Gram();	


			delay_ms(100);
    }
}



*/
#endif
