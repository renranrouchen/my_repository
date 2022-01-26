#ifndef _MOTO_SETP_H
#define _MOTO_SETP_H

#include "sys.h"
#include "timer.h"
#define MOTO_PIN0 PAout(4)
#define MOTO_PIN1 PAout(5)
#define MOTO_PIN2 PAout(6)
#define MOTO_PIN3 PAout(7)

#define MOTO_SET 300
enum MotoStau
{
	MotoStop,
	MotoZheng,
	MotoFan,
};
void MotoSpeedControl(unsigned char *status,unsigned int speed);
void MotoStep_Init(pTimeProcess  TimeProce);
void Moto_Zheng(unsigned char dat);
void Moto_Fan(unsigned char dat);
void MotoStopFun(void);

/*demo

u32 MotoPoint;
unsigned char Motostatus,MotoNext;

void Tim3_Handle_Process_m()
{
	static u8 i;
	

	switch(Motostatus)
	{
		case MotoStop:
			MotoStopFun();
			break;
		case MotoZheng:

			if(MotoPoint<500)
			{
				i++;
				if(i>=8)
				{
					i=0;
					MotoPoint++;
				}
				
				Moto_Zheng(i);
				
			}else
				Motostatus=MotoStop;
					
			
			break;
		case MotoFan:
			if(MotoPoint>0)
			{
				i++;
				if(i>=8)
				{
					i=0;
					MotoPoint--;
				}
				Moto_Fan(i);
				
			}else
				Motostatus=MotoStop;	
			break;		
	}

			
}
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3();

	  //MOTO init
	  MotoStep_Init(Tim3_Handle_Process_m);
	 
		OLED_ShowStr_ENCH(0,0,(unsigned char *)"    欢迎使用",1);
	  OLED_ShowString(0,16,(u8*)"AD0:     K:");
	  OLED_ShowString(0,32,(u8*)"AD1:     TI:");
	  OLED_ShowString(0,48,(u8*)"AD2:     Te:");	
	  //刷新
		OLED_Refresh_Gram();	
		
		Motostatus= MotoZheng;
    while(1)
    {

			
			
			if(Motostatus == MotoStop)
			{
				switch(MotoNext)
				{
					case MotoStop:
						Motostatus = MotoZheng;
					  MotoNext = MotoZheng;
						break;
					case MotoZheng:
						Motostatus = MotoFan;
					  MotoNext = MotoFan;
						break;
					case MotoFan:
						Motostatus = MotoZheng;
					  MotoNext = MotoZheng;
						break;					
				}
			}
			//delay_ms(200);
    }
}


*/
#endif

