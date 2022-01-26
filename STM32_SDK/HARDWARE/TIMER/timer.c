/**
 *  @file           timer.h
 *  @brief          STM32F10x 定时中断程序
 *  @version 1.0
 *  @author         李其建
 *  @date           2016年11月25日
 */

#include "timer.h"

static unsigned long RunTime=0;
/**
 * @Description: 通用定时器TIM3定时中断初始化
 * @param  Period    - 自动重装值
 * @param  Prescaler - 时钟预分频数
 * @note1 :中断时间(s)=(Period*Prescaler)/时钟(72M)
 * @note1 :这里时钟选择为APB1的2倍，而APB1为36M,详见时钟树图
 */
static pTimeProcess Tim3_Handle_Process;
void TIM3_Int_Init(u16 Period,u16 Prescaler,pTimeProcess TimeProcess)
{
    TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 			//时钟使能

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   						//使能或者失能指定的TIM中断
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn;//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
	Tim3_Handle_Process = TimeProcess;
	TIM_Cmd(TIM3, ENABLE);  										//使能TIMx外设							 
}
	   
/**
 * @Description: 通用定时器TIM3中断函数
 */
void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(Tim3_Handle_Process != 0)
			Tim3_Handle_Process();
		RunTime++; 
	}
}

unsigned long millis(void)
{
  return RunTime;
}


void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIO
 
   //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
 
	TIM_Cmd(TIM3, ENABLE); 

}
/**DEMO

TIM3_PWM_Init(899, 0);//0~900

TIM_SetCompare2(TIM3, 100);
**/







