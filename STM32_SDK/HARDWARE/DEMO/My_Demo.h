#ifndef __MY_DEMO_H
#define __MY_DEMO_H	 
#include "sys.h"
#include "delay.h"
#include "My_config.h"
#if CONFIG_LCD1602 == ENABLED
// D0  D1 D2 D3 D4 D5 D6 D7 E   RW RS
// A15 B3 B4 B5 B6 B7 B8 B9 A12    A11
#define RS                  PAout(11)                            
#define RW									PAout(10) 
#define EN                  PAout(12)  

#define D0                  PAout(15)  
#define D1                  PBout(3)
#define D2                  PBout(4)
#define D3                  PBout(5)
#define D4                  PBout(6) 
#define D5                  PBout(7)
#define D6                  PBout(8)
#define D7                  PBout(9)
 
 
#define LCD1602_CLK  RCC_APB2Periph_GPIOA  

#define LCD1602_GPIO_PORT   GPIOA

#define LCD1602_E    GPIO_Pin_12              //定义使能引脚
//#define LCD1602_RW   GPIO_Pin_13             //定义读写引脚
#define LCD1602_RS   GPIO_Pin_11             //定义数据、命名引脚

void LCD1602_Init_Demo(void);
void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p);
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date);
 void LCD_Clear_Demo(void) ;
#if CONFIG_DS1302 == ENABLED
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao);
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao);
#endif

#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date);
#endif 
 /*demo
 
 int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

    LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"hello world");

    while(1)
    {


			delay_ms(100);
    }
}
 
 
 */
#endif	 






#if CONFIG_KEY == ENABLED

#define Demo_KEY1 PBin(12)
#define Demo_KEY2 PBin(13)
#define Demo_KEY3 PBin(14)
#define Demo_KEY4 PBin(15)
#define Demo_KEY5 PAin(8)
#define Demo_KEY6 PBin(17)
#define KEY_COUNT 3 //定义需要几个按键，最多6个
typedef void (*pKey_Process)(unsigned char );
void Key_value_Demo(pKey_Process key_Process);	
void KEY_Init_Demo(void);

/******Key Demo******
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //设置键
	{
		Menu_Count ++;

		if(Menu_Count >= 2)
		{
			//处理返回界面
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}

	if(Key_value == 2)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}
	
	if(Key_value == 3)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}		
		
}

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
		ADC1_Config_Demo();
    LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"hello world");
	  KEY_Init_Demo();
    while(1)
    {

			Key_value_Demo(Key_Process_Demo);
			delay_ms(100);
    }
}
***/
#endif

#if CONFIG_ADC == ENABLED
#include "stm32f10x_adc.h"
#define Channel_Num_Demo  4			//
#define Sample_Num_Demo  10			//

void ADC1_Config_Demo(void);
uint16_t ReadADCAverageValue_Demo(uint16_t Channel);

/*DEMO


volatile u16 PH0_Value = 0;
volatile u16 PH1_Value = 0;
volatile u16 PH2_Value = 0;

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
		ADC1_Config_Demo();
    LCD1602_Init_Demo();


    while(1)
    {
			PH0_Value = ReadADCAverageValue_Demo(0);
			PH1_Value = ReadADCAverageValue_Demo(1);
			PH2_Value = ReadADCAverageValue_Demo(2);
			PH0_Value = (4096-PH0_Value)*100/4096;
			PH1_Value = (4096-PH1_Value)*100/4096;
			PH2_Value = (4096-PH2_Value)*100/4096;
			Lcd1602_Display_Three_bit(0,0,PH0_Value);
			Lcd1602_Display_Three_bit(0,5,PH1_Value);
			Lcd1602_Display_Three_bit(0,10,PH2_Value);
			Key_value_Demo(Key_Process_Demo);
			delay_ms(100);
    }
}

*/

#endif

#if CONFIG_OLED_4PIN == ENABLED
#define SCL3_0	GPIO_ResetBits(GPIOB,GPIO_Pin_9)			// Serial Clock Input
#define SDA3_0	GPIO_ResetBits(GPIOB,GPIO_Pin_8)				// Serial Data Input


#define SCL3_1	GPIO_SetBits(GPIOB,GPIO_Pin_9)					// Serial Clock Input
#define SDA3_1	GPIO_SetBits(GPIOB,GPIO_Pin_8)					// Serial Data Input

void	OLED_Init3_Demo(void);
void OLED_ShowStr_ENCH_Demo(u8 x, u8 y,unsigned char *s);
void OLED_ShowNum_Demo(u8 x, u8 y,unsigned int num);
void OLED_ShowNum_Three_Demo(unsigned char row,unsigned char col,unsigned int s);
void OLED_ShowNum_Temp_Demo(unsigned char row,unsigned char col,unsigned int s);
void OLED_ShowNum_Ds13b02_DisPlay(unsigned char row,unsigned char col,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao);
void OLED_Refresh_Gram_Demo(void);

/**demo

volatile u16 PH0_Value = 0;
volatile u16 PH1_Value = 0;
volatile u16 PH2_Value = 0;

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
		ADC1_Config_Demo();
		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
	  

    while(1)
    {
			PH0_Value = ReadADCAverageValue_Demo(0);
			PH1_Value = ReadADCAverageValue_Demo(1);
			PH2_Value = ReadADCAverageValue_Demo(2);
			PH0_Value = (4096-PH0_Value)*100/4096;
			PH1_Value = (4096-PH1_Value)*100/4096;
			PH2_Value = (4096-PH2_Value)*100/4096;
			OLED_ShowNum_Three_Demo(0,16,PH0_Value);
			OLED_ShowNum_Three_Demo(0,32,PH1_Value);
			OLED_ShowNum_Three_Demo(0,48,PH2_Value);
			
			delay_ms(100);
    }
}


**/
#endif

#if CONFIG_TIMER2 == ENABLED
typedef void (*pTime2Process_Demo)(); 
void TIM2_Int_Init_demo(u16 Period,u16 Prescaler,pTime2Process_Demo TimeProcess);
#endif
#if CONFIG_TIMER3 == ENABLED
typedef void (*pTimeProcess_Demo)(); 
void TIM3_Int_Init_Demo(u16 Period,u16 Prescaler,pTimeProcess_Demo TimeProcess);

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

		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
	  //定时器3初始化
		TIM3_Int_Init_Demo(10000, 7200,Tim3_Handle_Process_m);	  

    while(1)
    {

			OLED_ShowNum_Three_Demo(0,16,milli);

			
			delay_ms(100);
    }
}


*/
#endif

#if CONFIG_TIMER3_PWN == ENABLED

void TIM3_PWM_Init_Demo(u16 arr,u16 psc);

/**DEMO


int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
		TIM3_PWM_Init_Demo(899, 0);//0~900,bu fen ping
    while(1)
    {
			TIM_SetCompare2(TIM3, 100); //0最亮，899最暗
			delay_ms(100);
    }
}
**/

#endif

#if CONFIG_TIMER4 == ENABLED
typedef void (*pTime4Process_Demo)(); 
void TIM4_Int_Init_demo(u16 Period,u16 Prescaler,pTime2Process_Demo TimeProcess);
#endif
#if CONFIG_DS18b02 == ENABLED

//IO方向设置 PB0 切换的时候注意是CRL(0~7) 还是CRH(8~15)
#define DS18B20_IO_IN()  {GPIOB->CRL&=0xFFFFFFF0;GPIOB->CRL|=0x00000008;}
#define DS18B20_IO_OUT() {GPIOB->CRL&=0xFFFFFFF0;GPIOB->CRL|=0x00000003;}
////IO操作函数											   
#define	DS18B20_DQ_OUT PBout(0) //数据端口	PA10
#define	DS18B20_DQ_IN  PBin(0)  //数据端口	PA10 

u8 DS18B20_Init_Demo(void);
short DS18B20_Get_Temp_Demo(void);

/**demo

short temp;

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
		DS18B20_Init_Demo();

    while(1)
    {
		  //3wei shu
      temp = DS18B20_Get_Temp_Demo();
			OLED_ShowNum_Three_Demo(0,16,temp);

			
			delay_ms(1000);
    }
}

**/
#endif

#if CONFIG_MOTO_STEP == ENABLED

#define MOTO_PIN0 PAout(4)
#define MOTO_PIN1 PAout(5)
#define MOTO_PIN2 PAout(6)
#define MOTO_PIN3 PAout(7)

#define MOTO_SET_Demo 300
enum MotoStau_Demo
{
	MotoStop_Demo,
	MotoZheng_Demo,
	MotoFan_Demo,
};

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


#if CONFIG_USART1 == ENABLED
extern u8 a1;
void uart1_init_Demo(u32 bound);
void UART1_Send_String_Demo(unsigned char *Index);
void UART1_Send_Byte_Demo(unsigned char a);


/*DEMO
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
		uart1_init_Demo(9600);
		usart2_init_Demo(9600);
	  USART3_ConfigDemo(9600);
    while(1)
    {
			OLED_ShowNum_Three_Demo(0,16,a1);
      OLED_ShowNum_Three_Demo(0,32,a3);
			UART1_Send_String_Demo("usart1 hello\r\n");
			usart2_SendString_Demo("usart2 hello\r\n");
			usart3_SendString_Demo("usart3 hello\r\n");
			delay_ms(1000);
    }
}


*/
#endif

#if CONFIG_USART2 == ENABLED
#define USART2_REC_LEN_DEMO 100
void usart2_init_Demo(u32 band);
void USART2SendByte_Demo(unsigned char SendData);
void usart2_SendStringByLen_Demo(unsigned char * data,u8 len);
void usart2_SendString_Demo(unsigned char * data);
/*DEMO
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
		uart1_init_Demo(9600);
		usart2_init_Demo(9600);
	  USART3_ConfigDemo(9600);
    while(1)
    {
			OLED_ShowNum_Three_Demo(0,16,a1);
      OLED_ShowNum_Three_Demo(0,32,a3);
			UART1_Send_String_Demo("usart1 hello\r\n");
			usart2_SendString_Demo("usart2 hello\r\n");
			usart3_SendString_Demo("usart3 hello\r\n");
			delay_ms(1000);
    }
}


*/
#endif

#if CONFIG_USART3 == ENABLED
extern u8 a3;
void USART3_ConfigDemo(u32 band);
void USART3SendByte_Demo(unsigned char SendData);
void usart3_SendStringByLen_Demo(unsigned char * data,u8 len);
void usart3_SendString_Demo(unsigned char * data);
/*DEMO
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
		uart1_init_Demo(9600);
		usart2_init_Demo(9600);
	  USART3_ConfigDemo(9600);
    while(1)
    {
			OLED_ShowNum_Three_Demo(0,16,a1);
      OLED_ShowNum_Three_Demo(0,32,a3);
			UART1_Send_String_Demo("usart1 hello\r\n");
			usart2_SendString_Demo("usart2 hello\r\n");
			usart3_SendString_Demo("usart3 hello\r\n");
			delay_ms(1000);
    }
}


*/
#endif

#if CONFIG_SR04 == ENABLED
#define Trig   PAout(3)
#define Echo   PAin(4)
void SR04_Init_Demo(void);
void SR04_Processing_Demo(unsigned short *Length_Value);

/*demo

unsigned short length;
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
		SR04_Init_Demo();
		OLED_Init3_Demo();
		OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"欢迎使用密码");
	  
    while(1)
    {
      SR04_Processing_Demo(&length);
			OLED_ShowNum_Three_Demo(0,16,length);
			delay_ms(1000);
    }
}


*/
#endif

#if CONFIG_FLASH == ENABLED

//////////////////////////////////////////////////////////////////////////////////////////////////////
//用户根据自己的需要设置
#define STM32_FLASH_SIZE 64 	 		//所选STM32的FLASH容量大小(单位为K)
#define STM32_FLASH_WREN 1              //使能FLASH写入(0，不是能;1，使能)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH起始地址
#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH的起始地址
//FLASH解锁键值

void STMFLASH_Write_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite);
void STMFLASH_Read_Demo(u32 ReadAddr,u16 *pBuffer,u16 NumToRead);
/**DEMO

#include "stmflash.h"
#define FLASH_SAVE_ADDR  0X0800fe00	//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
u16 test_flash[2];

void read_flash()
{
	
	STMFLASH_Read_Demo(FLASH_SAVE_ADDR,test_flash,2);
	//if(test_flash[0]==0xffff) return;  //如果为空，直接返回。
	//取数据

	
}
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
		read_flash();

    while(1)
    {
			test_flash[0]=1;
			test_flash[1]=2;
			STMFLASH_Write_Demo(FLASH_SAVE_ADDR,test_flash,2);  //测试缓存数据
			//delay_ms(200);
    }
}


**/
#endif


#if CONFIG_DS1302 == ENABLED

//IO方向设置
#define DS1302_IO_IN()  {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=8<<4;}
#define DS1302_IO_OUT() {GPIOB->CRL&=0XFFFFFF0F;GPIOB->CRL|=3<<4;}
//IO操作函数									   
#define	DS1302_DATA_OUT PBout(1) //数据端口	PB1 
#define	DS1302_DATA_IN  PBin(1)  //数据端口	PB1 

#define	DS1302_SCK  PBout(0)
#define	DS1302_RST  PBout(10)

//DS1302地址定义
#define ds1302_sec_add			  0x80		//秒数据地址
#define ds1302_min_add			  0x82		//分数据地址
#define ds1302_hr_add			    0x84		//时数据地址
#define ds1302_date_add			  0x86		//日数据地址
#define ds1302_month_add		  0x88		//月数据地址
#define ds1302_day_add			  0x8a		//星期数据地址
#define ds1302_year_add			  0x8c		//年数据地址
#define ds1302_control_add		0x8e		//控制数据地址
#define ds1302_charger_add		0x90 					 
#define ds1302_clkburst_add		0xbe

void DS1302_Init_Demo(void);
void Ds1302_Read_Time_Demo(unsigned char *arry);
void Ds1302_Save_Demo(unsigned char  po, unsigned char  dat);


/******DS1302 Demo******

	case 5:
		if(Time_arry[4]<12)
			Time_arry[4]++;
		OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
		Ds1302_Save_Demo(0x88,Time_arry[4]);				
		break;
	case 6:
		if(Time_arry[3]<31)
			Time_arry[3]++;
		OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
		Ds1302_Save_Demo(0x86,Time_arry[3]);				
		break;
	case 7:
		if(Time_arry[2]<24)
			Time_arry[2]++;
		OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
		Ds1302_Save_Demo(0x84,Time_arry[2]);				
		break;
	case 8:
		if(Time_arry[1]<60)
			Time_arry[1]++;
		OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
		Ds1302_Save_Demo(0x82,Time_arry[1]);				
		break;
	case 9:
		if(Time_arry[0]<60)
			Time_arry[0]++;
		OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
		Ds1302_Save_Demo(0x80,Time_arry[0]);				
		break;
				
		case 5:
			if(Time_arry[4]>0)
				Time_arry[4]--;
			OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
			Ds1302_Save_Demo(0x88,Time_arry[4]);				
			break;
		case 6:
			if(Time_arry[3]>0)
				Time_arry[3]--;
			OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
			Ds1302_Save_Demo(0x86,Time_arry[3]);				
			break;
		case 7:
			if(Time_arry[2]>0)
				Time_arry[2]--;
			OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
			Ds1302_Save_Demo(0x84,Time_arry[2]);				
			break;
		case 8:
			if(Time_arry[1]>0)
				Time_arry[1]--;
			OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
			Ds1302_Save_Demo(0x82,Time_arry[1]);				
			break;
		case 9:
			if(Time_arry[0]>0)
				Time_arry[0]--;
			OLED_ShowNum_Ds13b02_DisPlay(0,16,Time_arry[4],Time_arry[3],Time_arry[2],Time_arry[1],Time_arry[0]);
			Ds1302_Save_Demo(0x80,Time_arry[0]);				
			break;					

unsigned char Time_arry[7];

void main()
{
	DS1302_Init_Demo();
	while(1)
	{
		Ds1302_Read_Time(arry);
		Ds13b02_DisPlay(0,6,arry[2],arry[1],arry[0]);	//使能1602
		DelayMs_utrl(100);
		
		//设置时月秒
		//Ds1302_Save(ds1302_hr_add,arry[2]);
		//Ds1302_Save(ds1302_min_add,arry[1]);
		//Ds1302_Save(ds1302_sec_add,arry[0]);	
	}
}

*/

#endif

#if CONFIG_DHT11 == ENABLED

//IO方向设置
#define DHT11_IO_IN()  {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=8<<20;}
#define DHT11_IO_OUT() {GPIOC->CRH&=0XFF0FFFFF;GPIOC->CRH|=3<<20;}
////IO操作函数											   
#define	DHT11_DQ_OUT PCout(13) //数据端口	PA0 
#define	DHT11_DQ_IN  PCin(13)  //数据端口	PA0 


u8 DHT11_Init_Demo(void);
u8 DHT11_Read_Data_Demo(u8 *temp,u8 *humi);
/*demo

unsigned char Temp,RhValue;
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

    LCD1602_Init();
	  Lcd1602_Display_Two_bit(0,0,1);
	  DHT11_Init_Demo();
    while(1)
    {
			if(DHT11_Read_Data_Demo(&Temp,&RhValue) == 0)
			{
				Lcd1602_Display_Three_bit(0,0,Temp);//读出温湿度，只取整数部分
				Lcd1602_Display_Three_bit(1,0,RhValue);
			}
			delay_ms(200);
    }
}

*/
#endif

#if CONFIG_HX711 == ENABLED
#define GapValue 405

void GPIO_Weigh_Init_Demo(void);
unsigned long Get_Maopi_Demo(void);
unsigned long Get_Weight_Demo(void);
/*demo

unsigned long Weight_Maopi2,Weight;
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);
    uart_init(9600);
    LCD1602_Init();
    GPIO_Weigh_Init();
	  Weight_Maopi2 = Get_Maopi();
    while(1)
    {
			Weight = Get_Weight();
			
			delay_ms(1000);
    }
}


*/
#endif

#if CONFIG_LED == ENABLED

#define LED PBout(10)
void LED_Init_Demo(void);
#endif

#if CONFIG_MP3 == ENABLED
#define BUSY   PBin(12)
void MP3_Init_Demo(void);
void Uart_SendCMD_Demo(unsigned char CMD ,unsigned char feedback , unsigned int dat);
/*demo

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
    MP3_Init_Demo();
		//语音提示
		Uart_SendCMD_Demo(0x06,0,30);
		delay_ms(500);
		Uart_SendCMD_Demo(0x06,0,30);
		delay_ms(500);
		Uart_SendCMD_Demo(0x03,0,4);//欢迎使用语音电子称
		delay_ms(500);	  
    while(1)
    {

			delay_ms(1000);
    }
}

*/
#endif

#if CONFIG_GPS == ENABLED
extern char string_n[15];
extern char string_e[15];
void GPS_Init_Demo(void);

/*demo**

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
    GPS_Init_Demo();
		LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"N:             ");
		Lcd1602_Display_String(1,0,(u8*)"E:             ");		  
    while(1)
    {
			Lcd1602_Display_String(0,2,(u8*)string_n);
			Lcd1602_Display_String(1,2,(u8*)string_e);
			delay_ms(1000);
    }
}
*/
#endif

#if CONFIG_HEART_RATE == ENABLED
//用到外部中断0 PA0 定时器3

extern unsigned int xinLv;    //心率值
void heart_rate_init_demo(void);
#endif

#if CONFIG_GSM == ENABLED

void gsm_init_demo(void);
void GSM_SENT_demo(void);
void gsm_usart3_SendString_Demo(unsigned char * data);
 void gsm_usart3_send_byte_Demo(unsigned char SendData);
 void SendNum(unsigned char num);
 void SendTwoNum(unsigned char num);
 void SendNum_char(unsigned char num);
 /*demo
 
 u8 stauts=0;
unsigned char  dianhuahaoma[12]="18459195135";
void Send_SMS_CH(unsigned char *sta,unsigned char option)
{
	
		unsigned char _Data[1];
		static unsigned char Step = 0;
		u8 send_number;
			
			if(*sta!=0)
			{
				switch(Step)
				{
					case 0:
								gsm_usart3_SendString_Demo((u8*)" AT\r\n"); Step++;
								break;
					
					case 1: gsm_usart3_SendString_Demo((u8*)"ATE0\r\n");  Step++;  break;

					
					case 2:gsm_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");Step++;break;
			 
					case 3:gsm_usart3_SendString_Demo((u8*)"AT+CSCS=\"UCS2\"\r\n");Step++;break;
			 

					case 4: gsm_usart3_SendString_Demo((u8*)"AT+CSMP=17,0,2,25\r\n");Step++;  break;
			 
					case 5: gsm_usart3_SendString_Demo((u8*)"AT+CMGS=\"");Step++; 
									for(send_number=0;send_number<11;send_number++)//在每位号码前加003
									{
										SendNum_char(dianhuahaoma[send_number]);
									} 								
									gsm_usart3_SendString_Demo((u8*)"\"\r\n");

					break;

					case 6: 
									switch(option)
									{
										case 0:
											gsm_usart3_SendString_Demo((u8*)"52305403836F65F695F48BF753CA65F65403836F"); 
										break;
									}
									
									gsm_usart3_SendString_Demo((u8*)"0020");			//发送空格
									_Data[0] = 0x1A;
									gsm_usart3_send_byte_Demo(*_Data);
									Step = 0;
									*sta=0;
									break;
					default: Step = 0;
					break;
				}
				delay_ms(100);
		 }


}
void Send_SMS_EN(unsigned char *sta,unsigned char option)
{
	
		unsigned char _Data[1];
		static unsigned char Step = 0;

			
			if(*sta!=0)
			{
				switch(Step)
				{
					case 0:
								gsm_usart3_SendString_Demo((u8*)" AT\r\n"); Step++;
								break;
					
					case 1: gsm_usart3_SendString_Demo((u8*)"ATE0\r\n");  Step++;  break;

					
					case 2:gsm_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");Step++;break;
			 
					case 3:gsm_usart3_SendString_Demo((u8*)"AT+CSCS=\"GSM\"\r\n");Step++;break;
			 
			 
					case 4: gsm_usart3_SendString_Demo((u8*)"AT+CMGS=\"");Step++; 
									gsm_usart3_SendString_Demo(dianhuahaoma);  								
									gsm_usart3_SendString_Demo((u8*)"\"\r\n");
					break;

					case 5: 
									switch(option)
									{
										case 0:
											gsm_usart3_SendString_Demo((u8*)"HELLO"); 
										break;
									}
									
									_Data[0] = 0x1A;
									gsm_usart3_send_byte_Demo(*_Data);
									Step = 0;
									*sta=0;
									break;
					default: Step = 0;
					break;
				}
				delay_ms(100);
		 }


}

unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //设置键
	{
		Menu_Count ++;
		if(dianhuahaoma[0]<'9')
		dianhuahaoma[0]++;
    //Lcd1602_Display_String(0,0,dianhuahaoma);
		if(Menu_Count >= 2)
		{
			//处理返回界面
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}

	if(Key_value == 2)	 //
	{
				if(dianhuahaoma[0]>'0')
		dianhuahaoma[0]--;
    //Lcd1602_Display_String(0,0,dianhuahaoma);
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}
	
	if(Key_value == 3)	 //
	{stauts=1;
		//SendString("AT\r\n");
		switch(Menu_Count)
		{
			case 0:
				
				break;
			case 1:
				break;
			case 2:
				break;
		}
	}		
		
}
 
 
 
unsigned char  PhoneNO[]= "18120747907"; //接收方号码


unsigned char  dianhuahaoma[12]={1,8,1,2,0,7,4,7,9,0,7};
void TransmitText(unsigned char Status)
{
	unsigned char send_number;
	//需要空一格
	gsm_usart3_SendString_Demo(" AT+CMGF=1\r\n"); //设置文本模式
  delay_ms(1000);	
	gsm_usart3_SendString_Demo("AT+CSCS=\"UCS2\"\r\n");//设置短信格式，发送汉字模式
	delay_ms(1000);
	gsm_usart3_SendString_Demo("AT+CSMP=17,0,2,25\r\n");//设置短信文本模式参数（具体内容参考开发资料内的模块资料）
	delay_ms(1000);
	
	gsm_usart3_SendString_Demo("AT+CMGS=");	//信息发送指令 AT+CMGS=//
	gsm_usart3_send_byte_Demo('"');
	for(send_number=0;send_number<11;send_number++)//在每位号码前加003
	{
		SendNum(dianhuahaoma[send_number]);
	}   
	gsm_usart3_send_byte_Demo('"');
	gsm_usart3_send_byte_Demo('\r');			//发送回车指令//
	gsm_usart3_send_byte_Demo('\n');			//发送换行指令//
	//该延时会影响下一个发送的第一个字节的数据
//	delay_ms(1000);			
	
  //确保数据完整，不然会发送失败
	gsm_usart3_SendString_Demo("8BF753CA65F6590474060021");//,请及时处理！
	gsm_usart3_SendString_Demo("0020");			//发送空格
	delay_ms(1000);	
	gsm_usart3_send_byte_Demo(0x1a);  //确定发送短信
	
	gsm_usart3_send_byte_Demo('\r');
	gsm_usart3_send_byte_Demo('\n');					
	delay_ms(1000);
}

void GSM_SENT_demo(void)
{
		gsm_usart3_SendString_Demo((u8*)" AT+CMGF=1\r\n");	
		
		delay_ms(1000);
		
		gsm_usart3_SendString_Demo((u8*)"AT+CSCS=\"GSM\"\r\n");	
		
		delay_ms(1000);
		
		gsm_usart3_SendString_Demo((u8*)"AT+CMGS=");	//信息发送指令 AT+CMGS=//
		gsm_usart3_send_byte_Demo('"');
		gsm_usart3_SendString_Demo(PhoneNO);   
		gsm_usart3_send_byte_Demo('"');
		gsm_usart3_send_byte_Demo('\r');			//发送回车指令//
		gsm_usart3_send_byte_Demo('\n');			//发送回车指令//
		
		delay_ms(1000);
		
	  gsm_usart3_SendString_Demo((u8*)" hello ");  

		delay_ms(1000);
		
		gsm_usart3_send_byte_Demo(0x1a);
		gsm_usart3_send_byte_Demo('\r');
		gsm_usart3_send_byte_Demo('\n');					
		delay_ms(1000);		
}

unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //设置键
	{
    GSM_SENT_demo();
		Lcd1602_Display_String(1,0,"h");
	}

	if(Key_value == 2)	 //
	{
    TransmitText(1);
		Lcd1602_Display_String(1,0,"2");
	}
	
	if(Key_value == 3)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}		
		
}
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
	  KEY_Init_Demo();
    gsm_init_demo();
    LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"hello world");	
    while(1)
    {
      Key_value_Demo(Key_Process_Demo);
			delay_ms(100);
    }
}


 */
#endif


#if CONFIG_BMP180 == ENABLED

#define SDA_IN()  {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)8<<28;}
#define SDA_OUT() {GPIOB->CRL&=0X0FFFFFFF;GPIOB->CRL|=(u32)3<<28;}

//IO操作函数	 
#define IIC_SCL    PBout(6) //SCL
#define IIC_SDA    PBout(7) //SDA	 
#define READ_SDA   PBin(7)  //输入SDA 

typedef struct __BMP180
{
	short AC1;
	short AC2;
	short AC3;
	unsigned short AC4;
	unsigned short AC5;
	unsigned short AC6;
	short B1;
	short B2;
	short MB;
	short MC;
	short MD;
	long UT;
	long UP;
	long X1;
	long X2;
	long X3;
	long B3;
	unsigned long B4;
	long B5;
	long B6;
	long B7;
	long p;
	long Temp;
	float altitude;
}_bmp180;


extern _bmp180 bmp180;
void BMP_Init(void);
uint8_t BMP_ReadOneByte(uint8_t ReadAddr);
void BMP_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite);
short BMP_ReadTwoByte(uint8_t ReadAddr);
void BMP_ReadCalibrationData(void);
long BMP_Read_UT(void);
long BMP_Read_UP(void);
void BMP_UncompemstatedToTrue(void);
/*demo

 int main(void)
 {	 
	u8 ID = 0;
	u16 i=0;
	delay_init();	    	 //延时函数初始化	  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	LED_Init();		  		//初始化与LED连接的硬件接口 	 	
	 
	BMP_Init();
	BMP_ReadCalibrationData();	
 
	while(1)
	{
	  ID = BMP_ReadOneByte(0xd0);
		BMP_UncompemstatedToTrue();
		printf("ID = %d\t  temp = %d.%dC\t   Pressure = %ldPa\t   Altitude = %.5fm\r\n",ID,bmp180.Temp/10,bmp180.Temp%10,bmp180.p,bmp180.altitude);
		i++;
		delay_ms(1000);
		if(i==1)
		{
			LED0=!LED0;//提示系统正在运行	
			i=0;
		}		   
	}
}

*/
#endif

#if CONFIG_ESP8266 == ENABLED
extern u8 a1;
void Esp8266_init(void);
void esp8266_UART1_Send_String_Demo(unsigned char *Index);
void ESP8266_Set(unsigned char *puf);
/**demo
unsigned char buff[30];
unsigned char buff[30];
void EPS8266_Send(void)
{
	static unsigned char Cnt1 = 1;
  if(++Cnt1 == 5)
	{
		//IP为192.168.4.1 ，端口号为 5000
		//ESP8266_Set 已经有加/r/n了AT+CIPSEND=0,26后要加回车，26为发送的长度，数量一定要准
		ESP8266_Set((u8*)"AT+CIPSEND=0,26");	   ////发送字符长度  
	}else if(Cnt1 >= 10)
	{
		count++;
		Cnt1 = 0;
		buff[0]= 'H';
		buff[1]= ':';
		buff[2]= 123/100%10+0x30;
		buff[3]= 123/10%10+0x30;
		buff[4]= 123%10+0x30;
		buff[5]= ',';
		buff[6]= 456/100%10+0x30;
		buff[7]= 456/10%10+0x30;
		buff[8]= ',';
		buff[9]= 456%10+0x30;
		buff[10]= ',';
		buff[11]= 789/100%10+0x30;
		buff[12]= 789/10%10+0x30;
		buff[13]= 789%10+0x30;
		buff[14]= ',';
   	buff[15]= 1+0x30;
		buff[16]= ',';
   	buff[17]= 1+0x30;
		buff[18]= ',';	
   	buff[19]= 1+0x30;
		buff[20]= ',';	
   	buff[21]= 1+0x30;
		buff[22]= ',';	
   	buff[23]= 1+0x30;
		buff[24]= ',';			
		buff[25]= 'E';	
			
		esp8266_UART1_Send_String_Demo(buff);		
	}	
}

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
	  Esp8266_init();
    LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"hello world");	
    while(1)
    {
			//接收到的数据为 +IPD,0,1:A
			if(a1=='A')
			{
				
				Lcd1602_Display_String(1,0,(u8*)"A");
				a1=0;
			}
			//接收到的数据为 +IPD,0,1:B
			if(a1=='B')
			{
				
				Lcd1602_Display_String(1,0,(u8*)"B");
				a1=0;
			}
			//接收到的数据为 +IPD,0,1:C
			if(a1=='C')
			{
				
				Lcd1602_Display_String(1,0,(u8*)"C");
				a1=0;
			}			
      EPS8266_Send();
			delay_ms(100);
    }
}

**/
#endif

#if CONFIG_MPU6050 == ENABLED

//如果移植程序时只要改一下三个地方就行了
#define I2C_SCL GPIO_Pin_6
#define I2C_SDA GPIO_Pin_7
#define GPIO_I2C GPIOA
#define RCC_GPIO RCC_APB2Periph_GPIOA

#define I2C_SCL_H GPIO_SetBits(GPIO_I2C,I2C_SCL)
#define I2C_SCL_L GPIO_ResetBits(GPIO_I2C,I2C_SCL)

#define I2C_SDA_H GPIO_SetBits(GPIO_I2C,I2C_SDA)
#define I2C_SDA_L GPIO_ResetBits(GPIO_I2C,I2C_SDA)

void MPU6050_Init(void);
void MPU6050ReadAcc(short *accData);
void MPU6050ReadGyro(short *gyroData);
void MPU6050ReadTemp(short *tempData);

// MPU6050, Standard address 0x68
#define MPU6050_ADDRESS         0x68
#define MPU6050_WHO_AM_I        0x75
#define MPU6050_SMPLRT_DIV      0  //8000Hz
#define MPU6050_DLPF_CFG        0
#define MPU6050_GYRO_OUT        0x43     //MPU6050陀螺仪数据寄存器地址
#define MPU6050_ACC_OUT         0x3B     //MPU6050加速度数据寄存器地址

#define MPU6050_SLAVE_ADDRESS  0xd0      //MPU6050器件读地址
//#define MPU6050_SLAVE_ADDRESS		0x68

#define MPU6050_ADDRESS_AD0_LOW     0x68 // address pin low (GND), default for InvenSense evaluation board
#define MPU6050_ADDRESS_AD0_HIGH    0x69 // address pin high (VCC)
#define MPU6050_DEFAULT_ADDRESS     MPU6050_ADDRESS_AD0_LOW

#define MPU6050_RA_XG_OFFS_TC       0x00 //[7] PWR_MODE, [6:1] XG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_YG_OFFS_TC       0x01 //[7] PWR_MODE, [6:1] YG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_ZG_OFFS_TC       0x02 //[7] PWR_MODE, [6:1] ZG_OFFS_TC, [0] OTP_BNK_VLD
#define MPU6050_RA_X_FINE_GAIN      0x03 //[7:0] X_FINE_GAIN
#define MPU6050_RA_Y_FINE_GAIN      0x04 //[7:0] Y_FINE_GAIN
#define MPU6050_RA_Z_FINE_GAIN      0x05 //[7:0] Z_FINE_GAIN
#define MPU6050_RA_XA_OFFS_H        0x06 //[15:0] XA_OFFS
#define MPU6050_RA_XA_OFFS_L_TC     0x07
#define MPU6050_RA_YA_OFFS_H        0x08 //[15:0] YA_OFFS
#define MPU6050_RA_YA_OFFS_L_TC     0x09
#define MPU6050_RA_ZA_OFFS_H        0x0A //[15:0] ZA_OFFS
#define MPU6050_RA_ZA_OFFS_L_TC     0x0B
#define MPU6050_RA_XG_OFFS_USRH     0x13 //[15:0] XG_OFFS_USR
#define MPU6050_RA_XG_OFFS_USRL     0x14
#define MPU6050_RA_YG_OFFS_USRH     0x15 //[15:0] YG_OFFS_USR
#define MPU6050_RA_YG_OFFS_USRL     0x16
#define MPU6050_RA_ZG_OFFS_USRH     0x17 //[15:0] ZG_OFFS_USR
#define MPU6050_RA_ZG_OFFS_USRL     0x18
#define MPU6050_RA_SMPLRT_DIV       0x19
#define MPU6050_RA_CONFIG           0x1A
#define MPU6050_RA_GYRO_CONFIG      0x1B
#define MPU6050_RA_ACCEL_CONFIG     0x1C
#define MPU6050_RA_FF_THR           0x1D
#define MPU6050_RA_FF_DUR           0x1E
#define MPU6050_RA_MOT_THR          0x1F
#define MPU6050_RA_MOT_DUR          0x20
#define MPU6050_RA_ZRMOT_THR        0x21
#define MPU6050_RA_ZRMOT_DUR        0x22
#define MPU6050_RA_FIFO_EN          0x23
#define MPU6050_RA_I2C_MST_CTRL     0x24
#define MPU6050_RA_I2C_SLV0_ADDR    0x25
#define MPU6050_RA_I2C_SLV0_REG     0x26
#define MPU6050_RA_I2C_SLV0_CTRL    0x27
#define MPU6050_RA_I2C_SLV1_ADDR    0x28
#define MPU6050_RA_I2C_SLV1_REG     0x29
#define MPU6050_RA_I2C_SLV1_CTRL    0x2A
#define MPU6050_RA_I2C_SLV2_ADDR    0x2B
#define MPU6050_RA_I2C_SLV2_REG     0x2C
#define MPU6050_RA_I2C_SLV2_CTRL    0x2D
#define MPU6050_RA_I2C_SLV3_ADDR    0x2E
#define MPU6050_RA_I2C_SLV3_REG     0x2F
#define MPU6050_RA_I2C_SLV3_CTRL    0x30
#define MPU6050_RA_I2C_SLV4_ADDR    0x31
#define MPU6050_RA_I2C_SLV4_REG     0x32
#define MPU6050_RA_I2C_SLV4_DO      0x33
#define MPU6050_RA_I2C_SLV4_CTRL    0x34
#define MPU6050_RA_I2C_SLV4_DI      0x35
#define MPU6050_RA_I2C_MST_STATUS   0x36
#define MPU6050_RA_INT_PIN_CFG      0x37
#define MPU6050_RA_INT_ENABLE       0x38
#define MPU6050_RA_DMP_INT_STATUS   0x39
#define MPU6050_RA_INT_STATUS       0x3A
#define MPU6050_RA_ACCEL_XOUT_H     0x3B
#define MPU6050_RA_ACCEL_XOUT_L     0x3C
#define MPU6050_RA_ACCEL_YOUT_H     0x3D
#define MPU6050_RA_ACCEL_YOUT_L     0x3E
#define MPU6050_RA_ACCEL_ZOUT_H     0x3F
#define MPU6050_RA_ACCEL_ZOUT_L     0x40
#define MPU6050_RA_TEMP_OUT_H       0x41
#define MPU6050_RA_TEMP_OUT_L       0x42
#define MPU6050_RA_GYRO_XOUT_H      0x43
#define MPU6050_RA_GYRO_XOUT_L      0x44
#define MPU6050_RA_GYRO_YOUT_H      0x45
#define MPU6050_RA_GYRO_YOUT_L      0x46
#define MPU6050_RA_GYRO_ZOUT_H      0x47
#define MPU6050_RA_GYRO_ZOUT_L      0x48
#define MPU6050_RA_EXT_SENS_DATA_00 0x49
#define MPU6050_RA_EXT_SENS_DATA_01 0x4A
#define MPU6050_RA_EXT_SENS_DATA_02 0x4B
#define MPU6050_RA_EXT_SENS_DATA_03 0x4C
#define MPU6050_RA_EXT_SENS_DATA_04 0x4D
#define MPU6050_RA_EXT_SENS_DATA_05 0x4E
#define MPU6050_RA_EXT_SENS_DATA_06 0x4F
#define MPU6050_RA_EXT_SENS_DATA_07 0x50
#define MPU6050_RA_EXT_SENS_DATA_08 0x51
#define MPU6050_RA_EXT_SENS_DATA_09 0x52
#define MPU6050_RA_EXT_SENS_DATA_10 0x53
#define MPU6050_RA_EXT_SENS_DATA_11 0x54
#define MPU6050_RA_EXT_SENS_DATA_12 0x55
#define MPU6050_RA_EXT_SENS_DATA_13 0x56
#define MPU6050_RA_EXT_SENS_DATA_14 0x57
#define MPU6050_RA_EXT_SENS_DATA_15 0x58
#define MPU6050_RA_EXT_SENS_DATA_16 0x59
#define MPU6050_RA_EXT_SENS_DATA_17 0x5A
#define MPU6050_RA_EXT_SENS_DATA_18 0x5B
#define MPU6050_RA_EXT_SENS_DATA_19 0x5C
#define MPU6050_RA_EXT_SENS_DATA_20 0x5D
#define MPU6050_RA_EXT_SENS_DATA_21 0x5E
#define MPU6050_RA_EXT_SENS_DATA_22 0x5F
#define MPU6050_RA_EXT_SENS_DATA_23 0x60
#define MPU6050_RA_MOT_DETECT_STATUS    0x61
#define MPU6050_RA_I2C_SLV0_DO      0x63
#define MPU6050_RA_I2C_SLV1_DO      0x64
#define MPU6050_RA_I2C_SLV2_DO      0x65
#define MPU6050_RA_I2C_SLV3_DO      0x66
#define MPU6050_RA_I2C_MST_DELAY_CTRL   0x67
#define MPU6050_RA_SIGNAL_PATH_RESET    0x68
#define MPU6050_RA_MOT_DETECT_CTRL      0x69
#define MPU6050_RA_USER_CTRL        0x6A
#define MPU6050_RA_PWR_MGMT_1       0x6B
#define MPU6050_RA_PWR_MGMT_2       0x6C
#define MPU6050_RA_BANK_SEL         0x6D
#define MPU6050_RA_MEM_START_ADDR   0x6E
#define MPU6050_RA_MEM_R_W          0x6F
#define MPU6050_RA_DMP_CFG_1        0x70
#define MPU6050_RA_DMP_CFG_2        0x71
#define MPU6050_RA_FIFO_COUNTH      0x72
#define MPU6050_RA_FIFO_COUNTL      0x73
#define MPU6050_RA_FIFO_R_W         0x74
#define MPU6050_RA_WHO_AM_I         0x75

#define MPU6050_TC_PWR_MODE_BIT     7
#define MPU6050_TC_OFFSET_BIT       6
#define MPU6050_TC_OFFSET_LENGTH    6
#define MPU6050_TC_OTP_BNK_VLD_BIT  0

#define MPU6050_VDDIO_LEVEL_VLOGIC  0
#define MPU6050_VDDIO_LEVEL_VDD     1

#define MPU6050_CFG_EXT_SYNC_SET_BIT    5
#define MPU6050_CFG_EXT_SYNC_SET_LENGTH 3
#define MPU6050_CFG_DLPF_CFG_BIT    2
#define MPU6050_CFG_DLPF_CFG_LENGTH 3

#define MPU6050_EXT_SYNC_DISABLED       0x0
#define MPU6050_EXT_SYNC_TEMP_OUT_L     0x1
#define MPU6050_EXT_SYNC_GYRO_XOUT_L    0x2
#define MPU6050_EXT_SYNC_GYRO_YOUT_L    0x3
#define MPU6050_EXT_SYNC_GYRO_ZOUT_L    0x4
#define MPU6050_EXT_SYNC_ACCEL_XOUT_L   0x5
#define MPU6050_EXT_SYNC_ACCEL_YOUT_L   0x6
#define MPU6050_EXT_SYNC_ACCEL_ZOUT_L   0x7

#define MPU6050_DLPF_BW_256         0x00
#define MPU6050_DLPF_BW_188         0x01
#define MPU6050_DLPF_BW_98          0x02
#define MPU6050_DLPF_BW_42          0x03
#define MPU6050_DLPF_BW_20          0x04
#define MPU6050_DLPF_BW_10          0x05
#define MPU6050_DLPF_BW_5           0x06

#define MPU6050_GCONFIG_FS_SEL_BIT      4
#define MPU6050_GCONFIG_FS_SEL_LENGTH   2

#define MPU6050_GYRO_FS_250         0x00
#define MPU6050_GYRO_FS_500         0x01
#define MPU6050_GYRO_FS_1000        0x02
#define MPU6050_GYRO_FS_2000        0x03

#define MPU6050_ACONFIG_XA_ST_BIT           7
#define MPU6050_ACONFIG_YA_ST_BIT           6
#define MPU6050_ACONFIG_ZA_ST_BIT           5
#define MPU6050_ACONFIG_AFS_SEL_BIT         4
#define MPU6050_ACONFIG_AFS_SEL_LENGTH      2
#define MPU6050_ACONFIG_ACCEL_HPF_BIT       2
#define MPU6050_ACONFIG_ACCEL_HPF_LENGTH    3

#define MPU6050_ACCEL_FS_2          0x00
#define MPU6050_ACCEL_FS_4          0x01
#define MPU6050_ACCEL_FS_8          0x02
#define MPU6050_ACCEL_FS_16         0x03

#define MPU6050_DHPF_RESET          0x00
#define MPU6050_DHPF_5              0x01
#define MPU6050_DHPF_2P5            0x02
#define MPU6050_DHPF_1P25           0x03
#define MPU6050_DHPF_0P63           0x04
#define MPU6050_DHPF_HOLD           0x07

#define MPU6050_TEMP_FIFO_EN_BIT    7
#define MPU6050_XG_FIFO_EN_BIT      6
#define MPU6050_YG_FIFO_EN_BIT      5
#define MPU6050_ZG_FIFO_EN_BIT      4
#define MPU6050_ACCEL_FIFO_EN_BIT   3
#define MPU6050_SLV2_FIFO_EN_BIT    2
#define MPU6050_SLV1_FIFO_EN_BIT    1
#define MPU6050_SLV0_FIFO_EN_BIT    0

#define MPU6050_MULT_MST_EN_BIT     7
#define MPU6050_WAIT_FOR_ES_BIT     6
#define MPU6050_SLV_3_FIFO_EN_BIT   5
#define MPU6050_I2C_MST_P_NSR_BIT   4
#define MPU6050_I2C_MST_CLK_BIT     3
#define MPU6050_I2C_MST_CLK_LENGTH  4

#define MPU6050_CLOCK_DIV_348       0x0
#define MPU6050_CLOCK_DIV_333       0x1
#define MPU6050_CLOCK_DIV_320       0x2
#define MPU6050_CLOCK_DIV_308       0x3
#define MPU6050_CLOCK_DIV_296       0x4
#define MPU6050_CLOCK_DIV_286       0x5
#define MPU6050_CLOCK_DIV_276       0x6
#define MPU6050_CLOCK_DIV_267       0x7
#define MPU6050_CLOCK_DIV_258       0x8
#define MPU6050_CLOCK_DIV_500       0x9
#define MPU6050_CLOCK_DIV_471       0xA
#define MPU6050_CLOCK_DIV_444       0xB
#define MPU6050_CLOCK_DIV_421       0xC
#define MPU6050_CLOCK_DIV_400       0xD
#define MPU6050_CLOCK_DIV_381       0xE
#define MPU6050_CLOCK_DIV_364       0xF

#define MPU6050_I2C_SLV_RW_BIT      7
#define MPU6050_I2C_SLV_ADDR_BIT    6
#define MPU6050_I2C_SLV_ADDR_LENGTH 7
#define MPU6050_I2C_SLV_EN_BIT      7
#define MPU6050_I2C_SLV_BYTE_SW_BIT 6
#define MPU6050_I2C_SLV_REG_DIS_BIT 5
#define MPU6050_I2C_SLV_GRP_BIT     4
#define MPU6050_I2C_SLV_LEN_BIT     3
#define MPU6050_I2C_SLV_LEN_LENGTH  4

#define MPU6050_I2C_SLV4_RW_BIT         7
#define MPU6050_I2C_SLV4_ADDR_BIT       6
#define MPU6050_I2C_SLV4_ADDR_LENGTH    7
#define MPU6050_I2C_SLV4_EN_BIT         7
#define MPU6050_I2C_SLV4_INT_EN_BIT     6
#define MPU6050_I2C_SLV4_REG_DIS_BIT    5
#define MPU6050_I2C_SLV4_MST_DLY_BIT    4
#define MPU6050_I2C_SLV4_MST_DLY_LENGTH 5

#define MPU6050_MST_PASS_THROUGH_BIT    7
#define MPU6050_MST_I2C_SLV4_DONE_BIT   6
#define MPU6050_MST_I2C_LOST_ARB_BIT    5
#define MPU6050_MST_I2C_SLV4_NACK_BIT   4
#define MPU6050_MST_I2C_SLV3_NACK_BIT   3
#define MPU6050_MST_I2C_SLV2_NACK_BIT   2
#define MPU6050_MST_I2C_SLV1_NACK_BIT   1
#define MPU6050_MST_I2C_SLV0_NACK_BIT   0

#define MPU6050_INTCFG_INT_LEVEL_BIT        7
#define MPU6050_INTCFG_INT_OPEN_BIT         6
#define MPU6050_INTCFG_LATCH_INT_EN_BIT     5
#define MPU6050_INTCFG_INT_RD_CLEAR_BIT     4
#define MPU6050_INTCFG_FSYNC_INT_LEVEL_BIT  3
#define MPU6050_INTCFG_FSYNC_INT_EN_BIT     2
#define MPU6050_INTCFG_I2C_BYPASS_EN_BIT    1
#define MPU6050_INTCFG_CLKOUT_EN_BIT        0

#define MPU6050_INTMODE_ACTIVEHIGH  0x00
#define MPU6050_INTMODE_ACTIVELOW   0x01

#define MPU6050_INTDRV_PUSHPULL     0x00
#define MPU6050_INTDRV_OPENDRAIN    0x01

#define MPU6050_INTLATCH_50USPULSE  0x00
#define MPU6050_INTLATCH_WAITCLEAR  0x01

#define MPU6050_INTCLEAR_STATUSREAD 0x00
#define MPU6050_INTCLEAR_ANYREAD    0x01

#define MPU6050_INTERRUPT_FF_BIT            7
#define MPU6050_INTERRUPT_MOT_BIT           6
#define MPU6050_INTERRUPT_ZMOT_BIT          5
#define MPU6050_INTERRUPT_FIFO_OFLOW_BIT    4
#define MPU6050_INTERRUPT_I2C_MST_INT_BIT   3
#define MPU6050_INTERRUPT_PLL_RDY_INT_BIT   2
#define MPU6050_INTERRUPT_DMP_INT_BIT       1
#define MPU6050_INTERRUPT_DATA_RDY_BIT      0

// TODO: figure out what these actually do
// UMPL source code is not very obivous
#define MPU6050_DMPINT_5_BIT            5
#define MPU6050_DMPINT_4_BIT            4
#define MPU6050_DMPINT_3_BIT            3
#define MPU6050_DMPINT_2_BIT            2
#define MPU6050_DMPINT_1_BIT            1
#define MPU6050_DMPINT_0_BIT            0

#define MPU6050_MOTION_MOT_XNEG_BIT     7
#define MPU6050_MOTION_MOT_XPOS_BIT     6
#define MPU6050_MOTION_MOT_YNEG_BIT     5
#define MPU6050_MOTION_MOT_YPOS_BIT     4
#define MPU6050_MOTION_MOT_ZNEG_BIT     3
#define MPU6050_MOTION_MOT_ZPOS_BIT     2
#define MPU6050_MOTION_MOT_ZRMOT_BIT    0

#define MPU6050_DELAYCTRL_DELAY_ES_SHADOW_BIT   7
#define MPU6050_DELAYCTRL_I2C_SLV4_DLY_EN_BIT   4
#define MPU6050_DELAYCTRL_I2C_SLV3_DLY_EN_BIT   3
#define MPU6050_DELAYCTRL_I2C_SLV2_DLY_EN_BIT   2
#define MPU6050_DELAYCTRL_I2C_SLV1_DLY_EN_BIT   1
#define MPU6050_DELAYCTRL_I2C_SLV0_DLY_EN_BIT   0

#define MPU6050_PATHRESET_GYRO_RESET_BIT    2
#define MPU6050_PATHRESET_ACCEL_RESET_BIT   1
#define MPU6050_PATHRESET_TEMP_RESET_BIT    0

#define MPU6050_DETECT_ACCEL_ON_DELAY_BIT       5
#define MPU6050_DETECT_ACCEL_ON_DELAY_LENGTH    2
#define MPU6050_DETECT_FF_COUNT_BIT             3
#define MPU6050_DETECT_FF_COUNT_LENGTH          2
#define MPU6050_DETECT_MOT_COUNT_BIT            1
#define MPU6050_DETECT_MOT_COUNT_LENGTH         2

#define MPU6050_DETECT_DECREMENT_RESET  0x0
#define MPU6050_DETECT_DECREMENT_1      0x1
#define MPU6050_DETECT_DECREMENT_2      0x2
#define MPU6050_DETECT_DECREMENT_4      0x3

#define MPU6050_USERCTRL_DMP_EN_BIT             7
#define MPU6050_USERCTRL_FIFO_EN_BIT            6
#define MPU6050_USERCTRL_I2C_MST_EN_BIT         5
#define MPU6050_USERCTRL_I2C_IF_DIS_BIT         4
#define MPU6050_USERCTRL_DMP_RESET_BIT          3
#define MPU6050_USERCTRL_FIFO_RESET_BIT         2
#define MPU6050_USERCTRL_I2C_MST_RESET_BIT      1
#define MPU6050_USERCTRL_SIG_COND_RESET_BIT     0

#define MPU6050_PWR1_DEVICE_RESET_BIT   7
#define MPU6050_PWR1_SLEEP_BIT          6
#define MPU6050_PWR1_CYCLE_BIT          5
#define MPU6050_PWR1_TEMP_DIS_BIT       3
#define MPU6050_PWR1_CLKSEL_BIT         2
#define MPU6050_PWR1_CLKSEL_LENGTH      3

#define MPU6050_CLOCK_INTERNAL          0x00
#define MPU6050_CLOCK_PLL_XGYRO         0x01
#define MPU6050_CLOCK_PLL_YGYRO         0x02
#define MPU6050_CLOCK_PLL_ZGYRO         0x03
#define MPU6050_CLOCK_PLL_EXT32K        0x04
#define MPU6050_CLOCK_PLL_EXT19M        0x05
#define MPU6050_CLOCK_KEEP_RESET        0x07

#define MPU6050_PWR2_LP_WAKE_CTRL_BIT       7
#define MPU6050_PWR2_LP_WAKE_CTRL_LENGTH    2
#define MPU6050_PWR2_STBY_XA_BIT            5
#define MPU6050_PWR2_STBY_YA_BIT            4
#define MPU6050_PWR2_STBY_ZA_BIT            3
#define MPU6050_PWR2_STBY_XG_BIT            2
#define MPU6050_PWR2_STBY_YG_BIT            1
#define MPU6050_PWR2_STBY_ZG_BIT            0

#define MPU6050_WAKE_FREQ_1P25      0x0
#define MPU6050_WAKE_FREQ_2P5       0x1
#define MPU6050_WAKE_FREQ_5         0x2
#define MPU6050_WAKE_FREQ_10        0x3

#define MPU6050_BANKSEL_PRFTCH_EN_BIT       6
#define MPU6050_BANKSEL_CFG_USER_BANK_BIT   5
#define MPU6050_BANKSEL_MEM_SEL_BIT         4
#define MPU6050_BANKSEL_MEM_SEL_LENGTH      5

#define MPU6050_WHO_AM_I_BIT        6
#define MPU6050_WHO_AM_I_LENGTH     6

#define MPU6050_DMP_MEMORY_BANKS        8
#define MPU6050_DMP_MEMORY_BANK_SIZE    256
#define MPU6050_DMP_MEMORY_CHUNK_SIZE   16

void MPU6050ReadTemp(short *tempData);
void MPU6050ReadGyro(short *gyroData);
void MPU6050ReadAcc(short *accData);
void MPU6050_ReturnTemp(short*Temperature);
void MPU6050_Init(void);
void MPU6050ReadID(void);
void PMU6050_ReadData(u8 reg_add,unsigned char*Read,u8 num);
void PMU6050_WriteReg(u8 reg_add,u8 reg_dat);

void MPU6050_PWR_MGMT_1_INIT(void);



void MPU6050_pro(void);
extern short Accel[3];
/*DEMO

short Accel[3];
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
		MPU6050_Init();
    LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"hello world");
    while(1)
    {
      MPU6050ReadAcc(Accel);
			Lcd1602_Display_Three_bit(1,0,Accel[0]);
			Lcd1602_Display_Three_bit(1,5,Accel[1]);
			Lcd1602_Display_Three_bit(1,10,Accel[2]);
			delay_ms(100);
    }
}
*/

#endif


#if CONFIG_GSM_TXRX == ENABLED

#include <string.h>
//接收时间太短，数据容易丢失
#define UART3_RXD_TIME       20  //定义串口超时时间 20*20ms

#define UART3_RXD_SIZE     128
#define UART3_RXD_END        0
#define GPRS_AT_CREG             0  //注册成功 标志位
#define GPRS_SEND_DATA           1  //有GPRS数据需要发送的时候置为 1  
#define GPRS_CCLK_OK             2
#define GPRS_RXD_DATA            3

#define CMD_READY          0
#define CMD_OK             1
#define CMD_WaitData       2
#define CMD_SendOK         3
#define CMD_CREG           4
#define CMD_CGATT1         5
#define CMD_CGATT0         6
#define CMD_ERROR          7

#define CMD_CONNECT_OK     8
#define CMD_CLOSE          9
#define CMD_RING           10
#define CMD_CSQ            11
#define CMD_CCLK           12
#define CMD_SHUT_OK        13

#define CMD_RING_NUMBER    14
#define CMD_NO_CARRIER     15


#define GPRS_RETRY      10



#define SMS_TXD_ENA           0


#define SMS_RXD_CMGR          2
#define SMS_RXD_CMTI          3
#define SMS_RXD_ENA           4
#define SMS_RXD_DATA          5

#define SMS_WaitData          0  /*等待数据*/
#define SMS_RXD_OK            1  /*收到OK*/
#define SMS_ERROR             2
#define SMS_CMGS              3

#define SMS_RETYR_CONST     5  /*短消息发送重试次数*/
extern volatile unsigned char UART3_RXD[UART3_RXD_SIZE];
extern volatile unsigned char SMS_CMD_Register ;
extern volatile unsigned char SMS_States_Register;
extern volatile unsigned char SMS_Retry;
//接收到数据的句柄
extern u8 send_flag;
//网络注册成功
extern u8 sim_status;

extern u8 PhoneNO[12];
extern u8 send_buff[20];
void SMS_Processing(u8* num,u8* data);
void gsm_txrx_init(void);

/*demo
//使用到了串口3跟定时器3
u8 PhoneNO[12]="18459195135";
u8 send_buff[20]="hello";
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1 || send_flag==1 )	 //设置键
	{
		//等待短信接收完成
		delay_ms(1000);
		send_flag=0;
		SMS_Retry = 5;
		SMS_States_Register |= (1 << SMS_TXD_ENA); //发送短信
		Lcd1602_Display_String(1,0,"h");
		
		switch(Menu_Count)
		{
			case 1:
			OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"                   ");
			OLED_ShowStr_ENCH_Demo(0,16,(unsigned char *)"                   ");
			OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)"                   ");
			OLED_ShowStr_ENCH_Demo(0,48,(unsigned char *)"                   ");					
				OLED_ShowStr_ENCH_Demo(0,0,(unsigned char *)"号码设置:           ");
			  OLED_ShowStr_ENCH_Demo(0,16,PhoneNO);
			  OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)"^");
			  
				break;
			case 2:
				OLED_ShowStr_ENCH_Demo(0,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8,32,(unsigned char *)"^");
				break;
			case 3:
				OLED_ShowStr_ENCH_Demo(8,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*2,32,(unsigned char *)"^");
				break;
			case 4:
				OLED_ShowStr_ENCH_Demo(8*2,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*3,32,(unsigned char *)"^");
				break;
			case 5:
				OLED_ShowStr_ENCH_Demo(8*3,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*4,32,(unsigned char *)"^");
				break;
			case 6:
				OLED_ShowStr_ENCH_Demo(8*4,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*5,32,(unsigned char *)"^");
				break;
			case 7:
				OLED_ShowStr_ENCH_Demo(8*5,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*6,32,(unsigned char *)"^");
				break;
			case 8:
				OLED_ShowStr_ENCH_Demo(8*6,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*7,32,(unsigned char *)"^");
				break;
			case 9:
				OLED_ShowStr_ENCH_Demo(8*7,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*8,32,(unsigned char *)"^");
				break;
			case 10:
				OLED_ShowStr_ENCH_Demo(8*8,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*9,32,(unsigned char *)"^");
				break;
			case 11:
				OLED_ShowStr_ENCH_Demo(8*9,32,(unsigned char *)" ");
			  OLED_ShowStr_ENCH_Demo(8*10,32,(unsigned char *)"^");
				break;			
		}		
	}

	if(Key_value == 2)	 //
	{
		if(Menu_Count>=1 && Menu_Count<=11)
		{
			if(PhoneNO[Menu_Count-1]<'9')
			{
				PhoneNO[Menu_Count-1]++;
				OLED_ShowStr_ENCH_Demo(0,16,PhoneNO);
			}
		}
		Lcd1602_Display_String(1,0,"2");
	}
	
	if(Key_value == 3)	 //
	{
		if(Menu_Count>=1 && Menu_Count<=11)
		{
			if(PhoneNO[Menu_Count-1]>'0')
			{
				PhoneNO[Menu_Count-1]--;
				OLED_ShowStr_ENCH_Demo(0,16,PhoneNO);
			}
		}		
		switch(Menu_Count)
		{
			case 1:
				break;
			case 2:
				break;
		}
	}		
		
}

void GSM_CALL(void)
{
		gsm_usart3_SendString_Demo((u8*)" AT+CMGF=1\r\n");	
		
		delay_ms(1000);
		
		gsm_usart3_SendString_Demo((u8*)"AT+CSCS=\"GSM\"\r\n");	
		
		delay_ms(1000);
		
		gsm_usart3_SendString_Demo((u8*)"atd");	//信息发送指令 AT+CMGS=//
		gsm_usart3_SendString_Demo(PhoneNO);   
		gsm_usart3_send_byte_Demo(';');
		gsm_usart3_send_byte_Demo('\r');			//发送回车指令//
		gsm_usart3_send_byte_Demo('\n');			//发送回车指令//
						
		delay_ms(1000);		
}
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
	  KEY_Init_Demo();
    gsm_txrx_init();
	  //uart1_init_Demo(9600);
    LCD1602_Init_Demo();
	  Lcd1602_Display_String(0,0,(u8*)"hello world");	
    while(1)
    {
			//printf("%s",UART3_RXD);
      Key_value_Demo(Key_Process_Demo);
			SMS_Processing(PhoneNO,send_buff);
			delay_ms(100);
    }
}



*/
#endif

#if CONFIG_ADXL345 == ENABLED

#define SDA_RCC_ADXL345			RCC_APB2Periph_GPIOA
#define SDA_GPIO_ADXL345		GPIOA
#define SDA_GPIO_PIN_ADXL345	GPIO_Pin_5

#define SCL_RCC_ADXL345			RCC_APB2Periph_GPIOA
#define SCL_GPIO_ADXL345		GPIOA
#define SCL_GPIO_PIN_ADXL345	GPIO_Pin_4

#define SCL_OUT_ADXL345() SCL_Set_Output_ADXL345() //置位scl
#define SET_SCL_ADXL345() GPIO_SetBits(SCL_GPIO_ADXL345, SCL_GPIO_PIN_ADXL345) //置位scl
#define CLE_SCL_ADXL345() GPIO_ResetBits(SCL_GPIO_ADXL345, SCL_GPIO_PIN_ADXL345)//清楚scl
                    
#define SDA_OUT_ADXL345() SDA_Set_Output_ADXL345()
#define SDA_INT_ADXL345() SDA_Set_Input_ADXL345()
#define SET_SDA_ADXL345() GPIO_SetBits(SDA_GPIO_ADXL345, SDA_GPIO_PIN_ADXL345)//置位sda
#define CLE_SDA_ADXL345() GPIO_ResetBits(SDA_GPIO_ADXL345, SDA_GPIO_PIN_ADXL345)//清楚sda
#define SDA_VAL_ADXL345() GPIO_ReadInputDataBit(SDA_GPIO_ADXL345, SDA_GPIO_PIN_ADXL345)

#define	SlaveAddress   0xA6	  //定义器件在IIC总线中的从地址,根据ALT  ADDRESS地址引脚不同修改                  //ALT  ADDRESS引脚接地时地址为0xA6，接电源时地址为0x3A

extern float temp_X,temp_Y,temp_Z;
void Init_ADXL345(void);    
void  Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data);   //??????
unsigned char Single_Read_ADXL345(unsigned char REG_Address);                   //???????????
void  Multiple_Read_ADXL345(void);                                  //????????????
void ADXL345_Start(void);
void ADXL345_Stop(void);
void ADXL345_SendACK(unsigned char ack);
unsigned char  ADXL345_RecvACK(void);
void ADXL345_SendByte(unsigned char dat);
unsigned char ADXL345_RecvByte(void);
void ADXL345_ReadPage(void);
void ADXL345_WritePage(void);
void ReadData_x(void);

/**demo

unsigned int BuShu=0;//步数
unsigned int Normal_num=0;			//正常次数
unsigned int Error_num=0;			//倾斜次数
unsigned int disBuShu = 0;  //显示步数

int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();	
	  //不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);		
	  delay_ms(500);
    Init_ADXL345();
		if(Single_Read_ADXL345(0X00)==0xe5)	
		{
			delay_ms(5);
		}
		else
		{
			delay_ms(3);
		}		
    while(1)
    {
				ReadData_x();  						//三轴检测函数
				if((temp_Y>450)||(temp_Y<-450)) //查看正常次数     
				{
					Normal_num++;  //正常次数++
				}
				else
				{
					Error_num++;//倾斜次数
				}
				if((Error_num!=0)&&(Normal_num!=0))//检测到步数
				{
					BuShu++;   //步数脉冲量++
					Error_num=0;    //清除一个周期检测
					Normal_num=0;

				}
			delay_ms(100);
    }
}


**/
#endif

#endif

