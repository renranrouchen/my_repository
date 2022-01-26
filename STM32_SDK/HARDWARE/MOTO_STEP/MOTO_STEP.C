#include "MOTO_STEP.H"
#include "delay.h"

u16 Moto_value;   //步进电机的量

//按键对应IO初始化函数
void MotoStep_Init(pTimeProcess  TimeProce)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//定时器3初始化
//	TIM3_Int_Init(10, 7200,TimeProce);
}

/***********************正转****************************/
void Moto_Zheng(unsigned char dat)
{
	switch(dat)
	{
		#if 0
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 1: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		#endif
		
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 1: MOTO_PIN0=1;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 4: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 5: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=1; break;
		case 6: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 7: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;		
		
	}
}

/***********************正转****************************/
void Moto_Fan(unsigned char dat)
{
	switch(dat)
	{
		#if 0
		case 0: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 1: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		#endif
		case 7: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 6: MOTO_PIN0=1;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 5: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=0;MOTO_PIN3=0; break;
		case 4: MOTO_PIN0=0;MOTO_PIN1=1;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 3: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=0; break;
		case 2: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=1;MOTO_PIN3=1; break;
		case 1: MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;
		case 0: MOTO_PIN0=1;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=1; break;	
	}
}
void MotoStopFun(void)
{
	MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0;
}
#if 0
void MotoSpeedControl(unsigned char *status,unsigned int speed)
{
	unsigned char i;
	if(*status != MotoStop)
	{
		if(*status == MotoZheng)
		{
				if(Moto_value >= MOTO_SET)
				{
					 MotoStopFun();
					*status=MotoStop;
				}else
				{
					Moto_value++;
					for(i=0;i<8;i++)
					{
						if(*status == MotoZheng)
						{
							zheng(i);
						}else if(*status == MotoFan)
						{
							fan(i);
						}
						delay_us(speed);
					}					
				}

		}else if(*status == MotoFan)
		{
				if(Moto_value <= 1)
				{
					MotoStopFun();
					*status=MotoStop;
				}else
				{
					Moto_value--;
					for(i=0;i<8;i++)
					{
						if(*status == MotoZheng)
						{
							zheng(i);
						}else if(*status == MotoFan)
						{
							fan(i);
						}
						delay_us(speed);
					}						
				}			
		}
		
			
		
	}
}
#endif

