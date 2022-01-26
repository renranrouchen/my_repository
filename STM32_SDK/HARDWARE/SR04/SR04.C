#include "SR04.H"
#include "usart.h"
//#include <stdio.h>
volatile unsigned char Time2_Over_Flag = 0;
void Tim2_Init(void)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
//  NVIC_InitTypeDef NVIC_InitStructure;

	 RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
	TIM_DeInit(TIM2);//复位TIM2定时器
	TIM_TimeBaseStructure.TIM_Period = 49999;
	TIM_TimeBaseStructure.TIM_Prescaler = 71;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, & TIM_TimeBaseStructure);
	 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	 
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	//NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;  
	//NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	//NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4; 
	//NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	//NVIC_Init(&NVIC_InitStructure); 	
}

void SR04_Init(void)
{
 	GPIO_InitTypeDef GPIO_InitStructure;
 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTE时钟

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;// 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //设置成 输出
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	Tim2_Init();
}
void TIM2_IRQHandler(void)
{

	Time2_Over_Flag = 1;
	
	 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}
void SR04_Processing(unsigned short *Length_Value)
{
	
	unsigned short i;
			
			Trig = 1;  //拉高TRIG超过10US。
			i = 0xFFF;
			while(--i);
			i = 0xFFF;
			while(--i);	
			Trig = 0;	
			TIM2->CNT=0;//计数器清0
			while(1)//等待ECHO脚高电平
			{
				 if(Echo == 1)
				  {
							TIM_Cmd(TIM2, ENABLE);// TIM2 enable counter [允许tim2计数]
							break;
				  }
				 if	(Time2_Over_Flag)
				 {
						Time2_Over_Flag = 0;
				  	break;
				 }					
			}
			
			while(1)
			{
				
				  if(Echo == 0)
				  {
						TIM_Cmd(TIM2, DISABLE);
						break;
				  }
				 if	(Time2_Over_Flag)
				 {
						Time2_Over_Flag = 0;
				  	break;
				 }								
			} 
			
			//	Length_Value(cm) = (TIM5->CNT(us)*340m/s)/2 = (TIM5->CNT/1000000*340*100)/2=	TIM5->CNT/(1000000*2/340)=TIM5->CNT*58.82
			*Length_Value =TIM2->CNT/58.0;//ECHO脚低电平后读取计数器的值，从而算出往返时间
       //printf("legth %ld,value %d\r\n",*Length_Value,TIM2->CNT);
			//大于4米
			if(*Length_Value >= 400) *Length_Value = 400;
}


