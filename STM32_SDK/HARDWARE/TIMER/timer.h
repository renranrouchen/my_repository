/**
 *  @file           timer.h
 *  @brief          STM32F10x 定时中断程序
 *  @version 1.0
 *  @author         李其建
 *  @date           2016年11月25日
 */


#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
/**
 * *FLAG_TIM3定时器3中断状态
 *  0-main中未在处理数据
 *  1-定时中断发生，main可以处理数据
 * -1-main处理数据超时
 */
 
typedef void (*pTimeProcess)(); 
extern s8 FLAG_TIM3;
void TIM3_Int_Init(u16 Period,u16 Prescaler,pTimeProcess TimeProcess);
unsigned long millis(void); 

/*DEMO

unsigned long milli;

void Tim3_Handle_Process_m()
{
		milli++;
}
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3();
	  //定时器3初始化
		TIM3_Int_Init(10000, 7200,Tim3_Handle_Process_m);//  1秒 72M/(7200)*(10000)
	  //按键初始化

	 
		OLED_ShowStr_ENCH(0,0,(unsigned char *)"    欢迎使用",1);

	  //刷新
		OLED_Refresh_Gram();	
		
		Motostatus= MotoZheng;
    while(1)
    {


      OLED_ShowNum(8*13,32,milli,3,16);		


			OLED_Refresh_Gram();

			
			//delay_ms(200);
    }
}


*/
#endif
