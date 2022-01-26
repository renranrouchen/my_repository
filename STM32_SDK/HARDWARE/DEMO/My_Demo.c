#include "My_Demo.h"
#include "My_Config.h"

#if CONFIG_LCD1602 == ENABLED


/*-----------------------------------------------
  名称：LCD1602
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过标准程序静态显示字符
  引脚定义如下：1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-
              判忙函数
------------------------------------------------*/

/*------------------------------------------------
              写入命令函数
------------------------------------------------*/
void LCD_PORT_Demo(unsigned char com)
{
	if (com&0x01)
			D0=1;
	else
			D0=0;

	if (com&0x02)
			D1=1;
	else
			D1=0;

	if (com&0x04)
			D2=1;
	else
			D2=0;

	if (com&0x08)
			D3=1;
	else
			D3=0; 
	if (com&0x10)
			D4=1;
	else
			D4=0;

	if (com&0x20)
			D5=1;
	else
			D5=0;

	if (com&0x40)
			D6=1;
	else
			D6=0;

	if (com&0x80)
			D7=1;
	else
			D7=0; 	
}
 void LCD_Write_Com_Demo(unsigned char com) 
{

	delay_us(2500);
	RS =0;
	EN=0;	
	delay_us(5);
  EN=1;
  //delay_us(10);	
  LCD_PORT_Demo(com);

	delay_us(10);	
  EN=0;                   
	delay_us(400);	
	delay_ms(4);	
}

/*------------------------------------------------
              写入数据函数
------------------------------------------------*/
 void LCD_Write_Data_Demo(unsigned char Data) 
{

  delay_us(2500);
  RS=1;
  delay_us(30);	
  EN=1;
  //RW=0;
  LCD_PORT_Demo(Data);
  delay_us(10);	
  EN=0;                  
	delay_us(400);	
	delay_ms(4);	
  	
}

void LCD1602_GPIO_Config_Demo(void)
{
	
	GPIO_InitTypeDef LCD1602_GPIOStruct;
	//不可缺？PA13/14/15 & PB3/4默认配置为JTAG功能，需要把JTAG关掉
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	
	 
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9 ;     //设置为开漏输出 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;//
	GPIO_Init(GPIOB,&LCD1602_GPIOStruct);
	
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15 ;     //设置为开漏输出 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;//GPIO_Speed_10MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA,&LCD1602_GPIOStruct);
	
	

	
	
}




void LCD1602_Init_Demo(void)
{
	  LCD1602_GPIO_Config_Demo();   //开启GPIO口
    LCD_Write_Com_Demo(0X38);  //16*2显示，5*7点阵，8位数据接口
    LCD_Write_Com_Demo(0x0C);  //显示器开，光标关闭
    LCD_Write_Com_Demo(0x06);  //文字不动，地址自动+1
    LCD_Write_Com_Demo(0x01);  //清屏

	
}


void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	LCD_Write_Data_Demo(0x30+date/10%10);
	LCD_Write_Data_Demo(0x30+date%10);	
}
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	LCD_Write_Data_Demo(0x30+date/100%10);
	LCD_Write_Data_Demo(0x30+date/10%10);
	LCD_Write_Data_Demo(0x30+date%10);	
}
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
		while(1)
		{
			if(*p == '\0')  break;
			LCD_Write_Data_Demo(*p);
			p++;
		}	
}

/*****************控制光标函数********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	if(date == 1)
		LCD_Write_Com_Demo(0x0f);     //显示光标并且闪烁	
	else 
		LCD_Write_Com_Demo(0x0c);   //关闭光标
}

 /*------------------------------------------------
                清屏函数
------------------------------------------------*/
 void LCD_Clear_Demo(void) 
 { 
 LCD_Write_Com_Demo(0x01); 
 delay_ms(5);
 }

/*------------------------------------------------*/
 
// D0  D1 D2 D3 D4 D5 D6 D7 E   RW RS
// A15 B3 B4 B5 B6 B7 B8 B9 A12    A11

#if CONFIG_DS1302 == ENABLED
/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add); 
	
	LCD_Write_Data_Demo(yue%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(yue%10+0x30);				// 个位
	LCD_Write_Data_Demo('-');
	LCD_Write_Data_Demo(ri%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(ri%10+0x30);				// 个位
	LCD_Write_Data_Demo(' ');	
	LCD_Write_Data_Demo(shi%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(shi%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(fen%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(fen%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(miao%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(miao%10+0x30);				// 个位

}

/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add); 
	

	LCD_Write_Data_Demo(shi%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(shi%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(fen%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(fen%10+0x30);				// 个位
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(miao%100/10+0x30);		// 十位
	LCD_Write_Data_Demo(miao%10+0x30);				// 个位

}
#endif
#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	LCD_Write_Data_Demo(0x30+date/100%10);
	LCD_Write_Data_Demo(0x30+date/10%10);
	LCD_Write_Data_Demo('.');
	LCD_Write_Data_Demo(0x30+date%10);	
}
#endif 
#endif
 
#if CONFIG_KEY == ENABLED
 
void Key_value_Demo(pKey_Process key_Process)	 //独立按键程序
{
	unsigned char Key_value;
#if KEY_COUNT == 1
	if(Demo_KEY1 == 0)
	{
		delay_ms(5);//去抖动 
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}				
	}	
#endif	
#if KEY_COUNT == 2
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0))
	{
		delay_ms(5);//去抖动 
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
				
	}	
	
#endif	
#if KEY_COUNT == 3
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) )
	{
	  delay_ms(5);//去抖动 
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		
	}	
#endif	
#if KEY_COUNT == 4
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) || (Demo_KEY4 == 0) )
	{
	  delay_ms(5);//去抖动 
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		if(Demo_KEY4 == 0)
		{
			Key_value = 4;
			while(!Demo_KEY4);
		}
	
	}	
#endif	
#if KEY_COUNT == 5
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) || (Demo_KEY4 == 0) || (Demo_KEY5 == 0))
	{
	  delay_ms(5);//去抖动 
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		if(Demo_KEY4 == 0)
		{
			Key_value = 4;
			while(!Demo_KEY4);
		}
		if(Demo_KEY5 == 0)
		{
			Key_value = 5;
			while(!Demo_KEY5);
		}
	
	}	
#endif	
#if KEY_COUNT == 6
	if((Demo_KEY1 == 0) || (Demo_KEY2 == 0) || (Demo_KEY3 == 0) || (Demo_KEY4 == 0) || (Demo_KEY5 == 0) || (Demo_KEY6 == 0))
	{
	  delay_ms(5);//去抖动 
		if(Demo_KEY1 == 0)
		{
			Key_value = 1;
			while(!Demo_KEY1);
		}
			
		if(Demo_KEY2 == 0)
		{
			Key_value = 2;
			while(!Demo_KEY2);
		}
			
		if(Demo_KEY3 == 0)
		{
			Key_value = 3;
			while(!Demo_KEY3);
		}
		if(Demo_KEY4 == 0)
		{
			Key_value = 4;
			while(!Demo_KEY4);
		}
		if(Demo_KEY5 == 0)
		{
			Key_value = 5;
			while(!Demo_KEY5);
		}
		if(Demo_KEY6 == 0)
		{
			Key_value = 6;
			while(!Demo_KEY6);
		}		
	}
#endif	
	else
		Key_value = 21;
	
	key_Process(Key_value);

}


void KEY_Init_Demo(void)
{
	
	GPIO_InitTypeDef GPIO_InitStructure;

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//关闭jtag，使能SWD，可以用SWD模式调试

#if KEY_COUNT == 1

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 2
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 3
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 4
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15	
#endif

#if KEY_COUNT == 5
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15	
#endif




	
} 
 
#endif
#if CONFIG_ADC == ENABLED

//内存中存储转换结果
vu16 ADC_ConvertedValue_Demo[Sample_Num_Demo][Channel_Num_Demo];
 
 
//DMA??:ADC1->CR --> ADC_ConvertedValue
void ADC_DMA_Config_Demo(void)
{
	 DMA_InitTypeDef DMA_InitStructure;
				   
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 DMA_DeInit(DMA1_Channel1);												//DMA的通道1寄存器设为缺省值
	 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		//DMA外设ADC基地址
	 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue_Demo;		//DMA内存基地址
	 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//内存作为数据传输的目的地
	 DMA_InitStructure.DMA_BufferSize = Sample_Num_Demo*Channel_Num_Demo;				//DMA通道的DMA缓存大小
	 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//外设地址不变
	 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//内存地址递增
	 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//DMA通道的DMA缓存大小
	 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//DMA通道的DMA缓存大小
	 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//工作在循环缓存模式
	 DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMA通道x拥有高优先级
	 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;			//DMA通道x没有设置为内存到内存传输
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);			//
	 DMA_Cmd(DMA1_Channel1,ENABLE);
}
 
 
void ADC1_Config_Demo(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	   
	//PA0 通道0 PA1 通道1 PA2 通道2
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//模拟输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 ADC_DMA_Config_Demo();
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6); 		//设置ADC分频因子6 72M/6=12M，ADC最大时间不能超过14M
	
	// ADC_DeInit(ADC1);
	 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//ADC1和ADC2工作在独立模式
	 ADC_InitStructure.ADC_ScanConvMode = ENABLE;							//多通道
	 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//连续转换
	 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//软件启动转换
	 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//转换结果右对齐
	 ADC_InitStructure.ADC_NbrOfChannel = Channel_Num_Demo;						//通道数
	 ADC_Init(ADC1, &ADC_InitStructure); 
 
	   
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);	//
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);
	 ADC_RegularChannelConfig(ADC1, ADC_Channel_3, 4, ADC_SampleTime_55Cycles5);
 
	   
	 ADC_DMACmd(ADC1, ENABLE);	   
	 ADC_Cmd(ADC1, ENABLE);
	 
	 ADC_ResetCalibration(ADC1);					
	 while(ADC_GetResetCalibrationStatus(ADC1));  	//
	 ADC_StartCalibration(ADC1);					//??AD??
	 while(ADC_GetCalibrationStatus(ADC1));			//
	 
	 ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//
}
 
 
uint16_t ReadADCAverageValue_Demo(uint16_t Channel)
{
	uint8_t i;
	uint32_t sum = 0;
	for(i=0; i<Sample_Num_Demo; i++)
	{
		sum+=ADC_ConvertedValue_Demo[i][Channel];		//
	}
	return (sum/Sample_Num_Demo);
}


#endif
 
#if CONFIG_OLED_4PIN == ENABLED

unsigned char OLED_GRAM_Demo[128][8]={0};

const unsigned char  zm8x16_index_Demo[]="0123456789: |-+<.^";//字串索引
const unsigned char  zm8x16_Table_Demo[][16]={
0x00,0x00,0x07,0xF0,0x08,0x08,0x10,0x04,0x10,0x04,0x08,0x08,0x07,0xF0,0x00,0x00,/*"0",0*/

0x00,0x00,0x00,0x00,0x08,0x04,0x08,0x04,0x1F,0xFC,0x00,0x04,0x00,0x04,0x00,0x00,/*"1",1*/

0x00,0x00,0x0E,0x0C,0x10,0x14,0x10,0x24,0x10,0x44,0x10,0x84,0x0F,0x0C,0x00,0x00,/*"2",2*/

0x00,0x00,0x0C,0x18,0x10,0x04,0x10,0x84,0x10,0x84,0x11,0x44,0x0E,0x38,0x00,0x00,/*"3",3*/

0x00,0x00,0x00,0x60,0x01,0xA0,0x02,0x24,0x0C,0x24,0x1F,0xFC,0x00,0x24,0x00,0x24,/*"4",4*/

0x00,0x00,0x1F,0x98,0x11,0x04,0x11,0x04,0x11,0x04,0x10,0x88,0x10,0x70,0x00,0x00,/*"5",5*/

0x00,0x00,0x07,0xF0,0x08,0x88,0x11,0x04,0x11,0x04,0x09,0x04,0x00,0xF8,0x00,0x00,/*"6",6*/

0x00,0x00,0x18,0x00,0x10,0x00,0x10,0x7C,0x11,0x80,0x16,0x00,0x18,0x00,0x00,0x00,/*"7",7*/

0x00,0x00,0x0E,0x38,0x11,0x44,0x10,0x84,0x10,0x84,0x11,0x44,0x0E,0x38,0x00,0x00,/*"8",8*/

0x00,0x00,0x0F,0x80,0x10,0x48,0x10,0x44,0x10,0x44,0x08,0x88,0x07,0xF0,0x00,0x00,/*"9",9*/

0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x0C,0x03,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,/*":",10*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",11*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,/*"|",12*/

0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x80,0x00,0x00,/*"-",13*/

0x00,0x00,0x00,0x80,0x00,0x80,0x00,0x80,0x07,0xF0,0x00,0x80,0x00,0x80,0x00,0x80,/*"+",14*/

0x00,0x00,0x00,0x80,0x01,0x40,0x02,0x20,0x04,0x10,0x08,0x08,0x10,0x04,0x00,0x00,/*"<",15*/

0x00,0x00,0x00,0x0C,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*".",16*/

0x00,0x00,0x00,0x00,0x20,0x00,0x40,0x00,0x40,0x00,0x20,0x00,0x00,0x00,0x00,0x00,/*"^",0*/
};
const unsigned char  zm16x16_index_Demo[]="欢迎使用密码锁请输入密码";//字串索引
const unsigned char  zm16x16_Table_Demo[][32]={

0x20,0x08,0x24,0x10,0x22,0x60,0x21,0x80,0x26,0x41,0x39,0x32,0x02,0x04,0x0C,0x18,
0xF0,0x60,0x13,0x80,0x10,0x60,0x10,0x18,0x14,0x04,0x18,0x02,0x00,0x01,0x00,0x00,/*"?",0*/

0x02,0x00,0x02,0x02,0x42,0x04,0x33,0xF8,0x00,0x04,0x00,0x02,0x3F,0xF2,0x20,0x22,
0x40,0x42,0x00,0x02,0x3F,0xFE,0x20,0x42,0x20,0x22,0x3F,0xC2,0x00,0x02,0x00,0x00,/*"?",1*/

0x01,0x00,0x06,0x00,0x1F,0xFF,0xE0,0x00,0x20,0x01,0x27,0x81,0x24,0xA2,0x24,0x94,
0x24,0x88,0xFF,0xF4,0x24,0x82,0x24,0x82,0x24,0x81,0x27,0x81,0x20,0x01,0x00,0x00,/*"?",2*/

0x00,0x01,0x00,0x06,0x7F,0xF8,0x44,0x40,0x44,0x40,0x44,0x40,0x44,0x40,0x7F,0xFE,
0x44,0x40,0x44,0x40,0x44,0x42,0x44,0x41,0x7F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,/*"?",3*/

0x08,0x40,0x31,0x40,0x22,0x5E,0x20,0x82,0x27,0x82,0x20,0xC2,0xA9,0x42,0x65,0x7E,
0x22,0x42,0x24,0x42,0x28,0x42,0x21,0xC2,0x22,0x1F,0x29,0x00,0x30,0x00,0x00,0x00,/*"?",4*/

0x20,0x40,0x21,0x80,0x27,0xFE,0x3A,0x08,0x22,0x08,0x23,0xFC,0x00,0x00,0x40,0x10,
0x4F,0x10,0x41,0x10,0x41,0x10,0x41,0x12,0x7F,0x11,0x01,0x02,0x01,0xFC,0x00,0x00,/*"?",5*/

0x04,0x80,0x08,0x80,0x34,0x80,0xE7,0xFE,0x24,0x84,0x24,0x88,0x00,0x01,0x47,0xF2,
0x34,0x04,0x04,0x08,0xFD,0xF0,0x04,0x08,0x14,0x04,0x67,0xF2,0x00,0x01,0x00,0x00,/*"?",6*/

0x02,0x00,0x42,0x00,0x33,0xFE,0x00,0x04,0x00,0x08,0x22,0x00,0x2A,0xFF,0x2A,0xA8,
0x2A,0xA8,0xFE,0xA8,0x2A,0xAA,0x2A,0xA9,0x2A,0xFE,0x22,0x00,0x02,0x00,0x00,0x00,/*"?",7*/

0x11,0x90,0x16,0x98,0xF8,0x90,0x13,0xFF,0x10,0xA0,0x08,0x00,0x13,0xFF,0x2A,0x48,
0x4A,0x49,0x8B,0xFF,0x48,0x00,0x29,0xFA,0x10,0x01,0x0B,0xFE,0x08,0x00,0x00,0x00,/*"?",8*/

0x00,0x01,0x00,0x02,0x00,0x04,0x00,0x08,0x00,0x30,0x80,0xC0,0x47,0x00,0x38,0x00,
0x07,0x00,0x00,0xC0,0x00,0x30,0x00,0x0C,0x00,0x02,0x00,0x01,0x00,0x01,0x00,0x00,/*"?",9*/

0x08,0x40,0x31,0x40,0x22,0x5E,0x20,0x82,0x27,0x82,0x20,0xC2,0xA9,0x42,0x65,0x7E,
0x22,0x42,0x24,0x42,0x28,0x42,0x21,0xC2,0x22,0x1F,0x29,0x00,0x30,0x00,0x00,0x00,/*"?",10*/

0x20,0x40,0x21,0x80,0x27,0xFE,0x3A,0x08,0x22,0x08,0x23,0xFC,0x00,0x00,0x40,0x10,
0x4F,0x10,0x41,0x10,0x41,0x10,0x41,0x12,0x7F,0x11,0x01,0x02,0x01,0xFC,0x00,0x00,/*"?",11*/
			
};

//****************************************************************************
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
//  Read/Write Sequence
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
void I2C_3_Demo(unsigned char mcmd)
{
unsigned char length = 8;			// Send Command

	while(length--)
	{
		if(mcmd & 0x80)
		{
			SDA3_1;
		}
		else
		{
			SDA3_0;
		}
//		uDelay(3);
		SCL3_1;
//		uDelay(3);
		SCL3_0;
//		uDelay(3);
		mcmd = mcmd << 1;
	}
}


void I2C_Ack3_Demo()
{
	SDA3_1;
//	uDelay(3);
	SCL3_1;
//	uDelay(3);
	SCL3_0;
//	uDelay(3);
}


void I2C_NAck3_Demo()
{
	SDA3_0;
//	uDelay(3);
	SCL3_1;
//	uDelay(3);
	SCL3_0;
//	uDelay(3);
}


void I2C_Start3_Demo()
{
	SDA3_0;
//	uDelay(3);
	SCL3_1;
//	uDelay(3);
	SCL3_0;
//	uDelay(3);
	I2C_3_Demo(0x78);
	I2C_Ack3_Demo();
}


void I2C_Stop3_Demo()
{
	SCL3_1;
//	uDelay(5);
	SDA3_0;
//	uDelay(5);
	SDA3_1;
//	uDelay(5);
}


void Write_Command3_Demo(unsigned char Data)
{
	I2C_Start3_Demo();
	I2C_3_Demo(0x00);
	I2C_Ack3_Demo();
	I2C_3_Demo(Data);
	I2C_Ack3_Demo();
	I2C_Stop3_Demo();
}


void Write_Data3_Demo(unsigned char Data)
{
	I2C_Start3_Demo();
	I2C_3_Demo(0x40);
	I2C_Ack3_Demo();
	I2C_3_Demo(Data);
	I2C_Ack3_Demo();
	I2C_Stop3_Demo();
}

//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!	  
void OLED_Clear_Demo(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM_Demo[n][i]=0X00;  
	//OLED_Refresh_Gram();//更新显示
}

void	OLED_Init3_Demo(void)
{
	
  GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  ,ENABLE);
 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);  
  
 
	delay_ms(300);
	
	
//		RES3=0;
//		//uDelay(2);
//		RES3=1;
//		//internal setting


		Write_Command3_Demo(0xae);	//--turn off oled panel

		Write_Command3_Demo(0x00);	//--set low column address
		Write_Command3_Demo(0x10);	//--set high column address

		Write_Command3_Demo(0x40);	//--set start line address

		Write_Command3_Demo(0xb0);	//--set page address

		Write_Command3_Demo(0x81);	//--set contrast control register
		Write_Command3_Demo(0xff);

		Write_Command3_Demo(0xa1);	//--set segment re-map 127 to 0   a0:0 to seg127
		Write_Command3_Demo(0xa6);	//--set normal display


		//切换显示角度 上下颠倒显示
		//Write_Command3(0xc0);	//--set com(N-1)to com0  c0:com0 to com(N-1)
		
		//切换显示角度
		Write_Command3_Demo(0xc0);	//--set com(N-1)to com0  c0:com0 to com(N-1)

		Write_Command3_Demo(0xa8);	//--set multiples ratio(1to64)
		Write_Command3_Demo(0x3f);	//--1/64 duty

		Write_Command3_Demo(0xd3);	//--set display offset
		Write_Command3_Demo(0x00);	//--not offset

		Write_Command3_Demo(0xd5);	//--set display clock divide ratio/oscillator frequency
		Write_Command3_Demo(0x80);	//--set divide ratio

		Write_Command3_Demo(0xd9);	//--set pre-charge period
		Write_Command3_Demo(0xf1);

		Write_Command3_Demo(0xda);	//--set com pins hardware configuration
		Write_Command3_Demo(0x12);

		Write_Command3_Demo(0xdb);	//--set vcomh
		Write_Command3_Demo(0x40);

		Write_Command3_Demo(0x8d);	//--set chare pump enable/disable
		Write_Command3_Demo(0x14);	//--set(0x10) disable
		//Write_Command3(0x10);	//--set(0x10) disable
		Write_Command3_Demo(0xaf);	//--turn on oled panel
		//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=void 	LCD_Init(void)
		
		OLED_Clear_Demo();
		

}

//更新显存到LCD		 
void OLED_Refresh_Gram_Demo(void)
{
	u8 j,n;
	
	for(j=0;j<8;j++)
	{
		Write_Command3_Demo(0x22);//--set page1
		Write_Command3_Demo(j);//--set start page
		Write_Command3_Demo(0x07);//--set end page

		
		for(n=0;n<128;n++)Write_Data3_Demo(OLED_GRAM_Demo[n][j]); 
		
	}
	
}

/* 返回一个8*16字符索引位置 */					
unsigned char enN_Demo(unsigned char *s){
	unsigned char i;
	for(i=0;zm8x16_index_Demo[i]!=0;i++)if(zm8x16_index_Demo[i]==s[0])break;
	return i;	
}
/* 返回一个16*16字符索引位置 */
unsigned char cnN_Demo(unsigned char *s){
	unsigned char i;
	for(i=0;zm16x16_index_Demo[i]!=0;i+=2)
		if(zm16x16_index_Demo[i]==*s&&zm16x16_index_Demo[i+1]==*(s+1))break ;
	return i/2;
}


//画点 
//x:0~127
//y:0~63
//t:1 填充 0,清空				   
void OLED_DrawPoint_Demo(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//超出范围了.
	pos=7-y/8;
	bx=y%8;
	temp=1<<(7-bx);
	if(t)OLED_GRAM_Demo[x][pos]|=temp;
	else OLED_GRAM_Demo[x][pos]&=~temp;	    
}


void OLED_ShowStr_ENCH_Demo(u8 x, u8 y,unsigned char *s)
{
	 u8 temp,t,t1,value;
   u8 y0=y;
	 unsigned char i;
	 for(i=0;s[i]!=0;i++){
	 	if(s[i]<0x80){ 	//英文
			value=enN_Demo(&s[i]);
			
			for(t=0;t<16;t++)
			{  
				  temp = zm8x16_Table_Demo[value][t];    //调用1616字体

					for(t1=0;t1<8;t1++)
					{
							if(temp&0x80)OLED_DrawPoint_Demo(x,y,1);
							else OLED_DrawPoint_Demo(x,y,!1);
							temp<<=1;
							y++;
							if((y-y0)==16)
							{
									y=y0;
									x++;
									break;
							}
					}    
			} 	
			//x=x+8;	
		}else{			//中文
			value=cnN_Demo(&s[i]);
			for(t=0;t<32;t++)
			{  
				  temp = zm16x16_Table_Demo[value][t];    //调用1616字体

					for(t1=0;t1<8;t1++)
					{
							if(temp&0x80)OLED_DrawPoint_Demo(x,y,1);
							else OLED_DrawPoint_Demo(x,y,!1);
							temp<<=1;
							y++;
							if((y-y0)==16)
							{
									y=y0;
									x++;
									break;
							}
					}    
			}
			//中文两个字节，需要加1
			i+=1;			
		}//中文
		
	}
	OLED_Refresh_Gram_Demo();	
}

void OLED_ShowNum_Demo(u8 x, u8 y,unsigned int num)
{
	u8 t,temp,t1;
	u8 y0=y;	
	for(t=0;t<16;t++)
	{  
		temp = zm8x16_Table_Demo[num][t];    //调用1616字体

		for(t1=0;t1<8;t1++)
		{
				if(temp&0x80)OLED_DrawPoint_Demo(x,y,1);
				else OLED_DrawPoint_Demo(x,y,!1);
				temp<<=1;
				y++;
				if((y-y0)==16)
				{
						y=y0;
						x++;
						break;
				}
		}    
	} 	
		
}
void OLED_ShowNum_Three_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/100%10);
	OLED_ShowNum_Demo(row+8,col,s/10%10);
	OLED_ShowNum_Demo(row+16,col,s%10);
	OLED_Refresh_Gram_Demo();	
}
void OLED_ShowNum_Temp_Demo(unsigned char row,unsigned char col,unsigned int s)
{
	OLED_ShowNum_Demo(row,col,s/100%10);
	OLED_ShowNum_Demo(row+8,col,s/10%10);
	OLED_ShowNum_Demo(row+16,col,16);
	OLED_ShowNum_Demo(row+24,col,s%10);
	OLED_Refresh_Gram_Demo();	
}

void OLED_ShowNum_Ds13b02_DisPlay(unsigned char row,unsigned char col,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao)
{

	
	OLED_ShowNum_Demo(row,col,yue/10%10);		// 十位
	OLED_ShowNum_Demo(row+8,col,yue%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+16,col,(u8*)"-");
	OLED_ShowNum_Demo(row+24,col,ri%100/10);		// 十位
	OLED_ShowNum_Demo(row+32,col,ri%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+40,col,(u8*)" ");	
	OLED_ShowNum_Demo(row+48,col,shi%100/10);		// 十位
	OLED_ShowNum_Demo(row+56,col,shi%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+64,col,(u8*)":");
	OLED_ShowNum_Demo(row+72,col,fen%100/10);		// 十位
	OLED_ShowNum_Demo(row+80,col,fen%10);				// 个位
	OLED_ShowStr_ENCH_Demo(row+88,col,(u8*)":");
	OLED_ShowNum_Demo(row+96,col,miao%100/10);		// 十位
	OLED_ShowNum_Demo(row+104,col,miao%10);				// 个位
	OLED_Refresh_Gram_Demo();

}
#endif
#if CONFIG_TIMER2 == ENABLED
static pTime2Process_Demo Tim2_Handle_Process;
void TIM2_Int_Init_demo(u16 Period,u16 Prescaler,pTime2Process_Demo TimeProcess)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			//时钟使能

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   						//使能或者失能指定的TIM中断
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
	Tim2_Handle_Process = TimeProcess;
	TIM_Cmd(TIM2, ENABLE);  										//使能TIMx外设							 
}
	   
/**
 * @Description: 通用定时器TIM3中断函数
 */
void TIM2_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(Tim2_Handle_Process != 0)
			Tim2_Handle_Process();
		
	}
}

#endif
#if CONFIG_TIMER3 == ENABLED


static pTimeProcess_Demo Tim3_Handle_Process_Demo;
void TIM3_Int_Init_Demo(u16 Period,u16 Prescaler,pTimeProcess_Demo TimeProcess)
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
  
	Tim3_Handle_Process_Demo = TimeProcess;
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
		if(Tim3_Handle_Process_Demo != 0)
			Tim3_Handle_Process_Demo();
		 
	}
}

#endif

#if CONFIG_TIMER3_PWN == ENABLED
void TIM3_PWM_Init_Demo(u16 arr,u16 psc)
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
//0为最亮，899为最暗
TIM3_PWM_Init_Demo(899, 0);//0~900,bu fen ping

TIM_SetCompare2(TIM3, 100);
**/

#endif
#if CONFIG_TIMER4 == ENABLED
static pTime4Process_Demo Tim4_Handle_Process_Demo;
void TIM4_Int_Init_Demo(u16 arr,u16 psc,pTimeProcess_Demo TimeProcess)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	

	TIM_TimeBaseStructure.TIM_Period = arr; 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
 
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 


	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4; 
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
	NVIC_Init(&NVIC_InitStructure); 
	Tim4_Handle_Process_Demo = TimeProcess;
	TIM_Cmd(TIM4, ENABLE);  
}

void TIM4_IRQHandler(void)   
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		if(Tim4_Handle_Process_Demo != 0)
			Tim4_Handle_Process_Demo();
		 
	}
  
	
}

#endif
#if CONFIG_DS18b02 == ENABLED

//复位DS18B20
void DS18B20_Rst_Demo(void)	   
{                 
	DS18B20_IO_OUT(); //SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; //拉低DQ
    delay_us(750);    //拉低750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}
//等待DS18B20的回应
//返回1:未检测到DS18B20的存在
//返回0:存在
u8 DS18B20_Check_Demo(void) 	   
{   
	u8 retry=0;
	DS18B20_IO_IN();//SET PA0 INPUT	 
    while (DS18B20_DQ_IN&&retry<200)
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=200)return 1;
	else retry=0;
    while (!DS18B20_DQ_IN&&retry<240)
	{
		retry++;
		delay_us(1);
	};
	if(retry>=240)return 1;	    
	return 0;
}
//从DS18B20读取一个位
//返回值：1/0
u8 DS18B20_Read_Bit_Demo(void) 			 // read one bit
{
    u8 data;
	DS18B20_IO_OUT();//SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; 
	delay_us(2);
    DS18B20_DQ_OUT=1; 
	DS18B20_IO_IN();//SET PA0 INPUT
	delay_us(12);
	if(DS18B20_DQ_IN)data=1;
    else data=0;	 
    delay_us(50);           
    return data;
}
//从DS18B20读取一个字节
//返回值：读到的数据
u8 DS18B20_Read_Byte_Demo(void)    // read one byte
{        
    u8 i,j,dat;
    dat=0;
	for (i=1;i<=8;i++) 
	{
        j=DS18B20_Read_Bit_Demo();
        dat=(j<<7)|(dat>>1);
    }						    
    return dat;
}
//写一个字节到DS18B20
//dat：要写入的字节
void DS18B20_Write_Byte_Demo(u8 dat)     
 {             
    u8 j;
    u8 testb;
	DS18B20_IO_OUT();//SET PA0 OUTPUT;
    for (j=1;j<=8;j++) 
	{
        testb=dat&0x01;
        dat=dat>>1;
        if (testb) 
        {
            DS18B20_DQ_OUT=0;// Write 1
            delay_us(2);                            
            DS18B20_DQ_OUT=1;
            delay_us(60);             
        }
        else 
        {
            DS18B20_DQ_OUT=0;// Write 0
            delay_us(60);             
            DS18B20_DQ_OUT=1;
            delay_us(2);                          
        }
    }
}
//开始温度转换
void DS18B20_Start_Demo(void)// ds1820 start convert
{   						               
    DS18B20_Rst_Demo();	   
	DS18B20_Check_Demo();	 
    DS18B20_Write_Byte_Demo(0xcc);// skip rom
    DS18B20_Write_Byte_Demo(0x44);// convert
} 
//初始化DS18B20的IO口 DQ 同时检测DS的存在
//返回1:不存在
//返回0:存在    	 
u8 DS18B20_Init_Demo(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PORTA口时钟 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PORTA0 推挽输出
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_0);    //输出1

	DS18B20_Rst_Demo();

	return DS18B20_Check_Demo();
}  
//从ds18b20得到温度值
//精度：0.1C
//返回值：温度值 （-550~1250） 
short DS18B20_Get_Temp_Demo(void)
{
    u8 temp;
    u8 TL,TH;
	  short tem;
    DS18B20_Start_Demo ();                    // ds1820 start convert
    DS18B20_Rst_Demo();
    DS18B20_Check_Demo();	 
    DS18B20_Write_Byte_Demo(0xcc);// skip rom
    DS18B20_Write_Byte_Demo(0xbe);// convert	    
    TL=DS18B20_Read_Byte_Demo(); // LSB   
    TH=DS18B20_Read_Byte_Demo(); // MSB  
	    	  
    if(TH>7)
    {
        TH=~TH;
        TL=~TL; 
        temp=0;//温度为负  
    }else temp=1;//温度为正	  	  
    tem=TH; //获得高八位
    tem<<=8;    
    tem+=TL;//获得底八位
    tem=(float)tem*0.625;//转换     
	if(temp)return tem; //返回温度值
	else return -tem;    
} 
 

#endif

#if CONFIG_MOTO_STEP == ENABLED



//按键对应IO初始化函数
void MotoStep_Init_Demo(pTimeProcess_Demo  TimeProce)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PA时钟
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//定时器3初始化
	TIM3_Int_Init_Demo (10, 7200,TimeProce);//10ms faster
}

/***********************正转****************************/
void Moto_Zheng_Demo(unsigned char dat)
{
	switch(dat)
	{

		
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
void Moto_Fan_Demo(unsigned char dat)
{
	switch(dat)
	{

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
void MotoStopFun_Demo(void)
{
	MOTO_PIN0=0;MOTO_PIN1=0;MOTO_PIN2=0;MOTO_PIN3=0;
}

#endif

#if CONFIG_USART1 == ENABLED

#include <stdio.h>
u8 a1;

#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}

void uart1_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


void UART1_Send_Byte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //开始发送
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void UART1_Send_String_Demo(unsigned char *Index)
{

	while(*Index)//检测字符串结束符
	{
		UART1_Send_Byte_Demo(*Index++);//发送当前字符
	}

}



void USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
		/* Place your implementation of fputc here */
		/* e.g. write a character to the USART */
		USART_SendData(USART1, *Data++);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{}
	}

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a1 =USART_ReceiveData(USART1);	//读取接收到的数据

	} 

}

#endif

#if CONFIG_USART2 == ENABLED

u8 uart2flag_Demo=0; 
u8 USART2_RX_BUF_Demo[USART2_REC_LEN_DEMO];
u8 USART_Length_Demo;
void usart2_init_Demo(u32 band)
{
	//GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//使能USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	
	//重新定义管脚
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // 引脚不能更改
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化   

  //Usart NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//抢占优先级3 原3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3     原2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = band;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART2, &USART_InitStructure); //初始化串口2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART2, ENABLE);                    //使能串口2
}
 /*发送一个字节数据*/
 void USART2SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART2,SendData);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart2_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2, data[i]); //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart2_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART2, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
/*
串口2中断函数
*/
void USART2_IRQHandler(void)                	//串口2中断服务程序
{
	static u8 i;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{	
		if(uart2flag_Demo==0)
		{
			USART2_RX_BUF_Demo[0] = USART_ReceiveData(USART2);	
			if( USART2_RX_BUF_Demo[0]=='O') 
			{
				//USART2SendByte('k'); //判断是否开始接收
				uart2flag_Demo=1; i = 1;   //开始接收
			}
			else
			{
				USART2_RX_BUF_Demo[0]=0;
			}
		}
		else	
		{ 
			USART2_RX_BUF_Demo[i] = USART_ReceiveData(USART2);  //接收9位
			i++; 
			if(i ==4) //接收完毕
			{
				i=0;
				uart2flag_Demo=0;	 

			}
		}	
	}  
}
#endif


#if CONFIG_USART3 == ENABLED
u8 a3;
void USART3_ConfigDemo(u32 band)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----Pb.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----Pb.11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=band;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //

	USART_Cmd(USART3,ENABLE);                           //

}

void USART3_IRQHandler(void) //??1??????
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE) != RESET)  //
	{			
		a3=USART_ReceiveData(USART3);
		

	
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
 /*发送一个字节数据*/
 void USART3SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
} 

/*
根据长度向串口2 发送数据
*/
void usart3_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART3, data[i]); //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		//i++;
	}
	//i++;
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}

#endif

#if CONFIG_SR04 == ENABLED

volatile unsigned char Time2_Over_Flag_Demo = 0;
void Tim2_Init_Demo(void)
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

void SR04_Init_Demo(void)
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
	
	Tim2_Init_Demo();
}
void TIM2_IRQHandler(void)
{

	Time2_Over_Flag_Demo = 1;
	
	 
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
}
void SR04_Processing_Demo(unsigned short *Length_Value)
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
				 if	(Time2_Over_Flag_Demo)
				 {
						Time2_Over_Flag_Demo = 0;
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
				 if	(Time2_Over_Flag_Demo)
				 {
						Time2_Over_Flag_Demo = 0;
				  	break;
				 }								
			} 
			
			//	Length_Value(cm) = (TIM5->CNT(us)*340m/s)/2 = (TIM5->CNT/1000000*340*100)/2=	TIM5->CNT/(1000000*2/340)=TIM5->CNT*58.82
			*Length_Value =TIM2->CNT/58.0;//ECHO脚低电平后读取计数器的值，从而算出往返时间
       //printf("legth %ld,value %d\r\n",*Length_Value,TIM2->CNT);
			//大于4米
			if(*Length_Value >= 400) *Length_Value = 400;
}

#endif

#if CONFIG_FLASH == ENABLED
#include "stm32f10x_flash.h"

//读取指定地址的半字(16位数据)
//faddr:读地址(此地址必须为2的倍数!!)
//返回值:对应数据.
u16 STMFLASH_ReadHalfWord_Demo(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN	//如果使能了写   
//不检查的写入
//WriteAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数   
void STMFLASH_Write_NoCheck_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//地址增加2.
	}  
}

//从指定地址开始读出指定长度的数据
//ReadAddr:起始地址
//pBuffer:数据指针
//NumToWrite:半字(16位)数
void STMFLASH_Read_Demo(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord_Demo(ReadAddr);//读取2个字节.
		ReadAddr+=2;//偏移2个字节.	
	}
}
//从指定地址开始写入指定长度的数据
//WriteAddr:起始地址(此地址必须为2的倍数!!)
//pBuffer:数据指针
//NumToWrite:半字(16位)数(就是要写入的16位数据的个数.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //字节
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF_Demo[STM_SECTOR_SIZE/2];//最多是2K字节
void STMFLASH_Write_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //扇区地址
	u16 secoff;	   //扇区内偏移地址(16位字计算)
	u16 secremain; //扇区内剩余地址(16位字计算)	   
 	u16 i;    
	u32 offaddr;   //去掉0X08000000后的地址
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//非法地址
	FLASH_Unlock();						//解锁
	offaddr=WriteAddr-STM32_FLASH_BASE;		//实际偏移地址.
	secpos=offaddr/STM_SECTOR_SIZE;			//扇区地址  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//在扇区内的偏移(2个字节为基本单位.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//扇区剩余空间大小   
	if(NumToWrite<=secremain)secremain=NumToWrite;//不大于该扇区范围
	while(1) 
	{	
		STMFLASH_Read_Demo(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF_Demo,STM_SECTOR_SIZE/2);//读出整个扇区的内容
		for(i=0;i<secremain;i++)//校验数据
		{
			if(STMFLASH_BUF_Demo[secoff+i]!=0XFFFF)break;//需要擦除  	  
		}
		if(i<secremain)//需要擦除
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//擦除这个扇区
			for(i=0;i<secremain;i++)//复制
			{
				STMFLASH_BUF_Demo[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck_Demo(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF_Demo,STM_SECTOR_SIZE/2);//写入整个扇区  
		}else STMFLASH_Write_NoCheck_Demo(WriteAddr,pBuffer,secremain);//写已经擦除了的,直接写入扇区剩余区间. 				   
		if(NumToWrite==secremain)break;//写入结束了
		else//写入未结束
		{
			secpos++;				//扇区地址增1
			secoff=0;				//偏移位置为0 	 
		   	pBuffer+=secremain;  	//指针偏移
			WriteAddr+=secremain;	//写地址偏移	   
		   	NumToWrite-=secremain;	//字节(16位)数递减
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//下一个扇区还是写不完
			else secremain=NumToWrite;//下一个扇区可以写完了
		}	 
	};	
	FLASH_Lock();//上锁
}
#endif



//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:起始地址
//WriteData:要写入的数据
void Test_Write_Demo(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write_Demo(WriteAddr,&WriteData,1);//写入一个字 
}

#endif

#if CONFIG_DS1302 == ENABLED

const unsigned char  Ds1302_write_add_Demo[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //写地址
const unsigned char  Ds1302_read_add_Demo[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //读地址

//DS1302初始化
void DS1302_Init_Demo(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_1);                 //PB1拉高
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_10); //PB0，PB10置低
}

//向DS1302写入一个字节数据
void DS1302_Write_Byte_Demo(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr & 0xFE;  //最低位置零，写数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //写数据
	{
	  if(data & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //停止DS1302总线
}

//从DS1302读出一个字节数据
u8 DS1302_Read_Byte_Demo(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //停止DS1302总线
	delay_us(10);
	DS1302_RST = 1;      //启动DS1302总线
	addr = addr | 0x01;  //最低位置高，读数据
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //写地址
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //读数据
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN)
			temp |= 0x80;
		else
			temp &= 0x7F;
		
		DS1302_SCK = 1;   //产生时钟
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //停止DS1302总线
	return temp;
}


unsigned char BCD_Decimal_Demo(unsigned char bcd)//BCD码转十进制函数，输入BCD，返回十进制
{
	 unsigned char Decimal;
	 Decimal=bcd>>4;
	 return(Decimal=Decimal*10+(bcd&=0x0F));
}
/*************把要的时间 年月日 都读出来***************/
//arry[7]
void Ds1302_Read_Time_Demo(unsigned char *arry)
{
	*arry      = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[0]));	//读秒
	*(arry+1)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[1]));	//读分
	*(arry+2)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[2]));	//读时
	*(arry+3)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[3]));	//读日
	*(arry+4)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[4]));	//读月
	*(arry+5)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[5]));	//读年
	*(arry+6)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[6]));	//读星期
}

void Ds1302_Save_Demo(unsigned char  po, unsigned char  dat)
{
	unsigned char  temp;
	temp=(dat)/10*16+(dat)%10;//十进制转换成DS1302要求的DCB码
	DS1302_Write_Byte_Demo(0x8e,0x00);//允许写，禁止写保护 
	DS1302_Write_Byte_Demo(po,temp);//向DS1302内写分寄存器82H写入调整后的分数据BCD码
	DS1302_Write_Byte_Demo(0x8e,0x80);//打开写保护	
}

#endif

#if CONFIG_DHT11 == ENABLED

 //////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//DHT11数字温湿度传感器驱动代码	   
//修改日期:2012/9/12
//版本：V1.0
//版权所有，盗版必究。
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
      
//复位DHT11
void DHT11_Rst_Demo(void)	   
{                 
	  DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//拉低DQ
    delay_ms(20);    	//拉低至少18ms
    DHT11_DQ_OUT=1; 	//DQ=1 
	  delay_us(30);     	//主机拉高20~40us
}
//等待DHT11的回应
//返回1:未检测到DHT11的存在
//返回0:存在
u8 DHT11_Check_Demo(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11会拉低40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11拉低后会再次拉高40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//从DHT11读取一个位
//返回值：1/0
u8 DHT11_Read_Bit_Demo(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//等待变为低电平
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//等待变高电平
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//等待40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//从DHT11读取一个字节
//返回值：读到的数据
u8 DHT11_Read_Byte_Demo(void)    
{        
    u8 i,dat;
    dat=0;
	for (i=0;i<8;i++) 
	{
   		dat<<=1; 
	    dat|=DHT11_Read_Bit_Demo();
    }						    
    return dat;
}
//从DHT11读取一次数据
//temp:温度值(范围:0~50°)
//humi:湿度值(范围:20%~90%)
//返回值：0,正常;1,读取失败
u8 DHT11_Read_Data_Demo(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst_Demo();
	if(DHT11_Check_Demo()==0)
	{
		for(i=0;i<5;i++)//读取40位数据
		{
			buf[i]=DHT11_Read_Byte_Demo();
		}
		if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
		{
			*humi=buf[0];
			*temp=buf[2];
		}
	}else return 1;
	return 0;	    
}
//初始化DHT11的IO口 DQ 同时检测DHT11的存在
//返回1:不存在
//返回0:存在    	 
u8 DHT11_Init_Demo(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //使能PG端口时钟
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PG11端口配置
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				 //初始化IO口
 	GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC13 输出高
			    
	DHT11_Rst_Demo();  //复位DHT11
	return DHT11_Check_Demo();//等待DHT11的回应
} 


#endif

#if CONFIG_HX711 == ENABLED

unsigned long Weight_Maopi_Demo;

void GPIO_Weigh_Init_Demo(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

uint32_t Read_Weigh_Demo(void)
{
	uint8_t i;
	uint32_t value = 0;
	

	GPIO_SetBits(GPIOB, GPIO_Pin_7); //????DT??????
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); //????SCK??????
	

	while(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7));
	delay_us(1);

	for(i=0; i<24; i++) //24???????????????????
	{

		GPIO_SetBits(GPIOB, GPIO_Pin_6);
		delay_us(1);
		GPIO_ResetBits(GPIOB, GPIO_Pin_6);
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 0)
		{
			value = value << 1;
			value |= 0x00;
		}
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_7) == 1)
		{
			value = value << 1;
			value |= 0x01;
		}
		delay_us(1);
	}
	
	//? 25? 27 ???????????? A/D ??????????
	GPIO_SetBits(GPIOB, GPIO_Pin_6); 
	value = value^0x800000; 
	delay_us(1); 
	GPIO_ResetBits(GPIOB, GPIO_Pin_6); 
	delay_us(1);  
	return value; 	
}

//****************************************************
//获取毛皮重量
//****************************************************
unsigned long Get_Maopi_Demo(void)
{
	unsigned long Weight_Maopi_temp = 0;
mm:	Weight_Maopi_temp = Read_Weigh_Demo();
	delay_ms(200);
	Weight_Maopi_Demo = Read_Weigh_Demo();
	if(Weight_Maopi_Demo/GapValue!=Weight_Maopi_temp/GapValue)
		goto mm;
	return Weight_Maopi_Demo;

} 

//****************************************************
//称重
//****************************************************
unsigned long Get_Weight_Demo(void)
{
	long Weight_Shiwu;
	Weight_Shiwu = Read_Weigh_Demo();
	
	Weight_Shiwu = Weight_Maopi_Demo-Weight_Shiwu ;		//
//printf("weight:%d Maopi:%d,Weight_Shiwu %d\r\n",(unsigned int)Weight_Shiwu,(unsigned int)Weight_Maopi,Weight_Shiwu);	
	Weight_Shiwu = (unsigned int)((float)Weight_Shiwu/GapValue); 	//			
//printf("weight:%d Maopi:%d,Weight_Shiwu %d\r\n",(unsigned int)Weight_Shiwu,(unsigned int)Weight_Maopi,Weight_Shiwu);   	
  return Weight_Shiwu;
}

#endif

#if CONFIG_LED == ENABLED
void LED_Init_Demo(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能PC端口时钟
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //LED端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //根据设定参数初始化GPIOC
}
#endif

#if CONFIG_MP3 == ENABLED
static unsigned char Send_buf_Demo[10] = {0} ;

void MP3_uart_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}
void MP3_USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, *Data++);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	{}
	}

}
void MP3_Init_Demo(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	MP3_uart_init_Demo(9600);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//使能PORTA,PORTE时钟
	//MP3 BUSY jiao 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化		
}

/*****************************************************************************************************
 - 功能描述：串口发送一帧数据

*****************************************************************************************************/


void SendCmd_Demo(unsigned char len)
{

		MP3_USART1_Send_Data_Demo(Send_buf_Demo,len);

}

/*****************************************************************************************************
 - 功能描述：求和校验
 - 隶属模块：
 - 参数说明：
 - 返回说明：
 - 注：				和校验的思路如下
							发送的指令，去掉起始和结束。将中间的6个字节进行累加，最后取反码
							接收端就将接收到的一帧数据，去掉起始和结束。将中间的数据累加，再加上接收到的校验
							字节。刚好为0，这样就代表接收到的数据完全正确
*****************************************************************************************************/

void DoSum_Demo( unsigned char *Str, unsigned char len)
{
    unsigned int xorsum = 0;
    unsigned char i;

    for(i=0; i<len; i++)
    {
        xorsum  = xorsum + Str[i];
    }
	xorsum     = 0 -xorsum;
	*(Str+i)   = (unsigned char)(xorsum >>8);
	*(Str+i+1) = (unsigned char)(xorsum & 0x00ff);
}


/*****************************************************************************************************
 - 功能描述：串口向外发送命令【包括控制和查询】
 - 隶属模块：外部
 - 参数说明：CMD：表示控制指令，请查询指令表，还包括查询的相关指令
							feedback：是否需要应答[0：不需要应答，1：需要应答]
							data：传送的参数
 - 返回说明：
 - 注：
*****************************************************************************************************/


void Uart_SendCMD_Demo(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
		
		while(BUSY == 0){}
    Send_buf_Demo[0] = 0x7e;    //保留字节
    Send_buf_Demo[1] = 0xff;    //保留字节
    Send_buf_Demo[2] = 0x06;    //长度
    Send_buf_Demo[3] = CMD;     //控制指令
    Send_buf_Demo[4] = feedback;//是否需要反馈
    Send_buf_Demo[5] = (unsigned char)(dat >> 8);//datah
    Send_buf_Demo[6] = (unsigned char)(dat);     //datal
		Send_buf_Demo[9] = 0xef;
    DoSum_Demo(&Send_buf_Demo[1],6);        //校验
    SendCmd_Demo(10);       //发送此帧数据
		
}


#endif

#if CONFIG_GPS == ENABLED
#include <string.h>
#include "stdio.h"

#define GPS_RXD_END          0
unsigned char GPS_RXD_Index = 0;
unsigned char GPS_States = 0;
char GPS_RXD[100];
char string_n[15];
char string_e[15];


//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif

void GPS_uart_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}

/* 根据空格分隔字符串 */ 
int partition(char *src, char *par, int pos) 
{ 
  int i,j; 

  i = pos; 

  //取到第一个非空格字符 
  if(src[i] == ',') 
  { 
    ++i; 
  } 
 
  if(src[i] != '\0') 
  { 
    j = 0; 
    while((src[i] != '\0') && (src[i] != ',')) 
    { 
      par[j] = src[i]; 
      ++i; 
      ++j; 
    }
    if(j==0)
	{
	  par[0]='0'; 
    par[1]='\0';
	  return i; 	  
	}
    par[j]='\0'; 
 
    return i; 
  } 
  else 
  { 
    return -1; 
  } 
}
//GPS数据解析

//$GPRMC,055607.00,A,3959.44811,N,11625.31055,E,2.312,,300317,,,A*78
//$GPRMC,055609.00,A,3959.44931,N,11625.31260,E,0.802,,300317,,,A*79

//20180424定位数据
//$GPRMC,123824.000,A,3300.8520,N,11237.0341,E,0.00,0.00,240418,,,A*6460

//$GPGGA,124123.000,3300.8535,N,11237.0404,E,6,05,2.0,96.8,M,0.0,M,,*51
//$GPGGA,124521.000,3300.8496,N,11237.0337,E,1,06,2.1,109.9,M,0.0,M,,*6B
//$GPGGA,124932.000,3300.8753,N,11237.0498,E,6,05,9.4,77.6,M,0.0,M,,*5053

//$GPGGA,,,,,,0,00,99.99,,,,,,*48 99.99*30
void GPS_Processing(void)
{
	int position,k;
	char partition_string[20];
	if(GPS_States & (1 << GPS_RXD_END))
	{
		GPS_States &= ~(1 << GPS_RXD_END);
			
   // strcpy(GPS_Value,"$GPGGA,124932.000,3300.8753,N,11237.0498,E,6,05,9.4,77.6,M,0.0,M,,*5053");
		position=0;
		k=0;
		if(GPS_RXD[0]=='$'&&GPS_RXD[1]=='G'&&GPS_RXD[2]=='P'&&GPS_RXD[3]=='G'&&GPS_RXD[4]=='G'&&GPS_RXD[5]=='A')
		{
			//用逗号分隔，k对应的为哪个位置的逗号
		  while((position = partition(GPS_RXD,partition_string,position)) != -1) 
		  { 
				++k;
				if(k==3)
				{
					memset(string_n, 0, sizeof(string_n));
					if(partition_string[1]!='\0')
					{
						string_n[0]=partition_string[0];
						string_n[1]=partition_string[1];
						string_n[2]='.';
						string_n[3]=partition_string[2];
						string_n[4]=partition_string[3];
						//string_n[5]=',';
						//string_n[6]=partition_string[5];
						string_n[5]='\0';

					}else
						strcpy(string_n,partition_string);
					

				}
				if(k==5)
				{
					memset(string_e, 0, sizeof(string_e));
					if(partition_string[1]!='\0')
					{
						string_e[0]=partition_string[0];
						string_e[1]=partition_string[1];
						string_e[2]=partition_string[2];
						string_e[3]='.';
						string_e[4]=partition_string[3];
						string_e[5]=partition_string[4];
						//string_e[6]=',';
						//string_e[7]=partition_string[6];
						string_e[6]='\0';

					}else					
						strcpy(string_e,partition_string);


				}	

		  }
		}

	
	
	
	}
	
}
void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	u8 a;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a =USART_ReceiveData(USART1);	//读取接收到的数据
		if(a == '$')
		{
			GPS_RXD_Index = 0;
			GPS_RXD[GPS_RXD_Index] = a;	
			GPS_RXD_Index++;
		}
		else if((a == '\r')&&(GPS_RXD[4]=='G')) //收到一帧完整数据   只接受$GPGGA这一帧数据
		{
		

			
			GPS_States |= (1 <<GPS_RXD_END); //标记GPS接收完成
			
			GPS_RXD[GPS_RXD_Index] = a;	
			GPS_RXD_Index++;
			GPS_RXD_Index = GPS_RXD_Index % 100;			
			GPS_Processing();	
			//将处理完的数据清除
			memset(GPS_RXD, 0, sizeof(GPS_RXD));

		}
		else
		{
			if(GPS_RXD[0]=='$')
			{
				GPS_RXD[GPS_RXD_Index] = a;	
				GPS_RXD_Index++;
				GPS_RXD_Index = GPS_RXD_Index % 100;
			}
		}	

	} 

}
void GPS_Init_Demo(void)
{
	GPS_uart_init_Demo(9600);
}

#endif

#if CONFIG_HEART_RATE == ENABLED
#include <stm32f10x_exti.h>
unsigned int xlTab[5];//心率数组
unsigned char count=0;	//心率滤波计数
unsigned int xinLater=0;//	心率延时处理
unsigned int xinLv =0;    //心率值
//外部中断初始化函数
void EXTIX_Init_Demo(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//外部中断，需要使能AFIO时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//使能PORTA,PORTC时钟

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //设置成上拉输入
		GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA15	


    //GPIOA.0	  中断线以及中断初始化配置
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//子优先级1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		

 
}

void EXTIX_TIM3_Int_Init_Demo(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //时钟使能

	TIM_TimeBaseStructure.TIM_Period = arr; //设置在下一个更新事件装入活动的自动重装载寄存器周期的值	 计数到5000为500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //设置用来作为TIMx时钟频率除数的预分频值  10Khz的计数频率  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
 
	TIM_ITConfig(  //使能或者失能指定的TIM中断
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //使能
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

	TIM_Cmd(TIM3, ENABLE);  //使能TIMx外设
							 
}
void heart_rate_init_demo(void)
{
	EXTIX_TIM3_Int_Init_Demo(49,7199);
	EXTIX_Init_Demo();
}

void TIM3_IRQHandler(void)   //TIM3中断
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 
		

			xinLater++;   
			if(xinLater>400)	//滤波滤掉手指未放情况
			{
				xinLv = 0; 	//滤波滤掉手指未放情况
				xinLater=0;
			}
		}
}

void EXTI0_IRQHandler(void)
{

		//OLED_ShowNum_Three_Demo(0,32,xinLater);
  if(xinLater>60)   //滤波防止抖动300ms
  {
    if(xinLater>400)		//滤波滤掉手指未放情况
    {
      xinLater =0;		//此时心率为0
    }
    else
    {
      xlTab[count++]=xinLater;//记录前后两次事件间隔 
      xinLater=0;
      if(count>=4)		//记录超过4次进行滤波处理
      {
        xinLv =60000/((xlTab[0]+xlTab[1]+xlTab[2]+xlTab[3])/4*5);//60000单位ms 表示60s /4求平均  *5每次定时5ms
        count=0;		//清除本次记录
      }   
      xinLater =0;	//延时清零
    }
  }
	
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

#endif
#if CONFIG_GSM == ENABLED

u8 a3;
void GSM_USART3_ConfigDemo(u32 band)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----PB.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----PB11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=band;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //

	USART_Cmd(USART3,ENABLE);                           //

}

void gsm_init_demo(void)
{
	GSM_USART3_ConfigDemo(9600);
}
/*串口3 发送数据到上位机 data 以\0结尾*/
void gsm_usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
 /*发送一个字节数据*/
 void gsm_usart3_send_byte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
}

void USART3_IRQHandler(void) //??1??????
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE) != RESET)  //
	{			
		a3=USART_ReceiveData(USART3);
		

	
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
void SendNum(unsigned char num)
{
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('3');
	gsm_usart3_send_byte_Demo(0x30+num);	
}
void SendNum_char(unsigned char num)
{
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('0');
	gsm_usart3_send_byte_Demo('3');
	gsm_usart3_send_byte_Demo(num);	
}
void SendTwoNum(unsigned char num)
{
		if(num>=100)
		   num = 99;
		SendNum(num/10);
		SendNum(num%10);	
}
#endif


#if CONFIG_BMP180 == ENABLED

//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//使能GPIOB时钟
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 输出高
}
//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT();     //sda线输出
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT();//sda线输出
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA设置为输入  
	IIC_SDA=1;delay_us(1);	   
	IIC_SCL=1;delay_us(1);	 
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL=0;//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=0;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	IIC_SCL=0;
	SDA_OUT();
	IIC_SDA=1;
	delay_us(2);
	IIC_SCL=1;
	delay_us(2);
	IIC_SCL=0;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        IIC_SCL=0; 
        delay_us(2);
		IIC_SCL=1;
        receive<<=1;
        if(READ_SDA)receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}

#include <math.h>
_bmp180 bmp180;

//BMP180初始化
//对使用的IIC端口进行初始化
void BMP_Init(void)
{
	IIC_Init();
}

//写一个数据到BMP180
void BMP_WriteOneByte(uint8_t WriteAddr,uint8_t DataToWrite)
{
	IIC_Start();
	
	IIC_Send_Byte(0xEE);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(WriteAddr);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(DataToWrite);
	IIC_Wait_Ack();
	IIC_Stop();
}

//从BMP180读一个字节数据
uint8_t BMP_ReadOneByte(uint8_t ReadAddr)
{
	uint8_t data = 0;
	
	IIC_Start();
	
	IIC_Send_Byte(0xEE);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();
	
	IIC_Start();
	
	IIC_Send_Byte(0xEF);
	IIC_Wait_Ack();
	
	data = IIC_Read_Byte(1);
	IIC_Stop();
	
	return data;
}

//从BMP180读一个16位的数据
short BMP_ReadTwoByte(uint8_t ReadAddr)
{
	short data;
	uint8_t msb,lsb;
	
	IIC_Start();
	
	IIC_Send_Byte(0xEE);
	IIC_Wait_Ack();
	
	IIC_Send_Byte(ReadAddr);
	IIC_Wait_Ack();
	
	IIC_Start();
	
	IIC_Send_Byte(0xEF);
	IIC_Wait_Ack();
	
	msb = IIC_Read_Byte(1);
	lsb = IIC_Read_Byte(0);
	
	IIC_Stop();
	
	data = msb*256 + lsb;
	
	return data;
}

//从BMP180的获取计算参数
void BMP_ReadCalibrationData(void)
{
	bmp180.AC1 = BMP_ReadTwoByte(0xAA);
	bmp180.AC2 = BMP_ReadTwoByte(0xAC);
	bmp180.AC3 = BMP_ReadTwoByte(0xAE);
	bmp180.AC4 = BMP_ReadTwoByte(0xB0);
	bmp180.AC5 = BMP_ReadTwoByte(0xB2);
	bmp180.AC6 = BMP_ReadTwoByte(0xB4);
	bmp180.B1  = BMP_ReadTwoByte(0xB6);
	bmp180.B2  = BMP_ReadTwoByte(0xB8);
	bmp180.MB  = BMP_ReadTwoByte(0xBA);
	bmp180.MC  = BMP_ReadTwoByte(0xBC);
	bmp180.MD  = BMP_ReadTwoByte(0xBE);
}

//从BMP180读取未修正的温度
long BMP_Read_UT(void)
{
	long temp = 0;
	BMP_WriteOneByte(0xF4,0x2E);
	
	delay_ms(5);
	temp = (long)BMP_ReadTwoByte(0xF6);
	return temp;
}

//从BMP180读取未修正的大气压
long BMP_Read_UP(void)
{
	long pressure = 0;
	
	BMP_WriteOneByte(0xF4,0x34);
	delay_ms(5);
	
	pressure = (long)BMP_ReadTwoByte(0xF6);
	//pressure = pressure + BMP_ReadOneByte(0xf8);
	pressure &= 0x0000FFFF;
	
	return pressure;
}

//用获取的参数对温度和大气压进行修正，并计算海拔
void BMP_UncompemstatedToTrue(void)
{
	bmp180.UT = BMP_Read_UT();//第一次读取错误
	bmp180.UT = BMP_Read_UT();//进行第二次读取修正参数
	bmp180.UP = BMP_Read_UP();
	
	bmp180.X1 = ((bmp180.UT - bmp180.AC6) * bmp180.AC5) >> 15;
	bmp180.X2 = (((long)bmp180.MC) << 11) / (bmp180.X1 + bmp180.MD);
	bmp180.B5 = bmp180.X1 + bmp180.X2;
	bmp180.Temp  = (bmp180.B5 + 8) >> 4;
	
	bmp180.B6 = bmp180.B5 - 4000;
	bmp180.X1 = ((long)bmp180.B2 * (bmp180.B6 * bmp180.B6 >> 12)) >> 11;
	bmp180.X2 = ((long)bmp180.AC2) * bmp180.B6 >> 11;
	bmp180.X3 = bmp180.X1 + bmp180.X2;
	
	bmp180.B3 = ((((long)bmp180.AC1) * 4 + bmp180.X3) + 2) /4;
	bmp180.X1 = ((long)bmp180.AC3) * bmp180.B6 >> 13;
	bmp180.X2 = (((long)bmp180.B1) *(bmp180.B6*bmp180.B6 >> 12)) >>16;
	bmp180.X3 = ((bmp180.X1 + bmp180.X2) + 2) >> 2;
	bmp180.B4 = ((long)bmp180.AC4) * (unsigned long)(bmp180.X3 + 32768) >> 15;
	bmp180.B7 = ((unsigned long)bmp180.UP - bmp180.B3) * 50000;
	
	if(bmp180.B7 < 0x80000000)
	{
		bmp180.p = (bmp180.B7 * 2) / bmp180.B4;		
	}
	else
	{
		bmp180.p = (bmp180.B7 / bmp180.B4) * 2;
	}
	
	bmp180.X1 = (bmp180.p >> 8) * (bmp180.p >>8);
	bmp180.X1 = (((long)bmp180.X1) * 3038) >> 16;
	bmp180.X2 = (-7357 * bmp180.p) >> 16;
	
	bmp180.p = bmp180.p + ((bmp180.X1 + bmp180.X2 + 3791) >> 4);
	
	bmp180.altitude = 44330 * (1-pow(((bmp180.p) / 101325.0),(1.0/5.255)));  
}

#endif

#if CONFIG_ESP8266 == ENABLED
u8 a1;
void esp8266_uart1_init_Demo(u32 bound){
  //GPIO端口设置
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.9
   
  //USART1_RX	  GPIOA.10初始化
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.10  

  //Usart1 NVIC 配置
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置

	USART_InitStructure.USART_BaudRate = bound;//串口波特率
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

  USART_Init(USART1, &USART_InitStructure); //初始化串口1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启串口接受中断
  USART_Cmd(USART1, ENABLE);                    //使能串口1 

}


void esp8266_UART1_Send_Byte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //开始发送
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void esp8266_UART1_Send_String_Demo(unsigned char *Index)
{

	while(*Index)//检测字符串结束符
	{
		esp8266_UART1_Send_Byte_Demo(*Index++);//发送当前字符
	}

}



void esp8266_USART1_Send_Data_Demo(unsigned char *Data,unsigned short Length)
{

	unsigned short i;


	for(i=0;i<Length;i++)
	{
		/* Place your implementation of fputc here */
		/* e.g. write a character to the USART */
		USART_SendData(USART1, *Data++);
		/* Loop until the end of transmission */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{}
	}

}

void USART1_IRQHandler(void)                	//串口1中断服务程序
{
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
	{
		a1 =USART_ReceiveData(USART1);	//读取接收到的数据

	} 

}
/******************************************************************** 
名称：WIFI模块设置函数  作用: 启动模块，以便可以实现无线接入和控制  
********************************************************************/ 
void ESP8266_Set(unsigned char *puf) 
	{                        	// 数组指针*puf指向字符串数组
    while(*puf!='\0') 
		{  		//遇到空格跳出循环
        esp8266_UART1_Send_Byte_Demo(*puf);  		//向WIFI模块发送控制指令。
        puf++;
    }
    delay_ms(5);
    esp8266_UART1_Send_Byte_Demo('\r'); 			//回车
    delay_ms(5);
    esp8266_UART1_Send_Byte_Demo('\n');   			//换行
}
void Esp8266_init(void)
{
		esp8266_uart1_init_Demo(9600);
		delay_ms(100);
	  ESP8266_Set((u8*)"AT+CWMODE=2"); 							//设置路由器模式1 station,模式2 AP,模式3 station+AP混合模式   设置前wifi的波特率设置成9600
    delay_ms(300);
    ESP8266_Set((u8*)"AT+RST"); 									//重新启动wifi模块
    delay_ms(300);
//    ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  设置模块SSID:WIFI, PWD:密码 及安全类型加密模式（WPA2-PSK）
    ESP8266_Set((u8*)"AT+CWSAP=\"wifi_yuxia\",\"12345678\",11,4");
    delay_ms(300);
//    ESP8266_Set("AT+CIPMUX=1");								//开启多连接模式，允许多个各客户端接入
    ESP8266_Set((u8*)"AT+CIPMUX=1");								//开启单连接模式
    delay_ms(300);
    ESP8266_Set((u8*)"AT+CIPSERVER=1,5000");  					//启动TCP/IP 实现基于网络//控制 	ESP8266_Set("AT+CIPSERVER=1,5000");
    delay_ms(500);
    ESP8266_Set((u8*)"AT+CIPSTO=0"); 
    delay_ms(500);	
}

#endif

#if CONFIG_MPU6050 == ENABLED

void I2C_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	
	
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);	 //使能PB,PE端口时钟
	
	GPIO_InitStructure.GPIO_Pin=I2C_SCL|I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);

	I2C_SCL_H;
	I2C_SDA_H;
}

void I2C_SDA_OUT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

void I2C_SDA_IN(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	GPIO_InitStructure.GPIO_Pin=I2C_SDA;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IPU;
	GPIO_Init(GPIO_I2C,&GPIO_InitStructure);
}

//产生起始信号
void I2C_Start(void)
{
    I2C_SDA_OUT();
	
	I2C_SDA_H;
	I2C_SCL_H;
	delay_us(5);
	I2C_SDA_L;
	delay_us(6);
	I2C_SCL_L;
}

//产生停止信号
void I2C_Stop(void)
{
   I2C_SDA_OUT();

   I2C_SCL_L;
   I2C_SDA_L;
   I2C_SCL_H;
   delay_us(6);
   I2C_SDA_H;
   delay_us(6);
}

//主机产生应答信号ACK
void I2C_Ack(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_L;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}

//主机不产生应答信号NACK
void I2C_NAck(void)
{
   I2C_SCL_L;
   I2C_SDA_OUT();
   I2C_SDA_H;
   delay_us(2);
   I2C_SCL_H;
   delay_us(5);
   I2C_SCL_L;
}
//等待从机应答信号
//返回值：1 接收应答失败
//		  0 接收应答成功
u8 I2C_Wait_Ack(void)
{
	u8 tempTime=0;

	I2C_SDA_IN();

	I2C_SDA_H;
	delay_us(1);
	I2C_SCL_H;
	delay_us(1);

	while(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
	{
		tempTime++;
		if(tempTime>250)
		{
			I2C_Stop();
			return 1;
		}	 
	}

	I2C_SCL_L;
	return 0;
}
//I2C 发送一个字节
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//拉低时钟开始数据传输

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_us(2); //发送数据
		I2C_SCL_L;
		delay_us(2);
	}
}

//I2C 读取一个字节

u8 I2C_Read_Byte(u8 ack)
{
   u8 i=0,receive=0;

   I2C_SDA_IN();
   for(i=0;i<8;i++)
   {
   		I2C_SCL_L;
		delay_us(2);
		I2C_SCL_H;
		receive<<=1;
		if(GPIO_ReadInputDataBit(GPIO_I2C,I2C_SDA))
		   receive++;
		delay_us(1);	
   }

   	if(ack==0)
	   	I2C_NAck();
	else
		I2C_Ack();

	return receive;
}


void PMU6050_WriteReg(u8 reg_add,u8 reg_dat)
{
	I2C_Start();
	I2C_Send_Byte(MPU6050_SLAVE_ADDRESS);
	I2C_Wait_Ack();
	I2C_Send_Byte(reg_add);
	I2C_Wait_Ack();
	I2C_Send_Byte(reg_dat);
	I2C_Wait_Ack();
	I2C_Stop();
}

void PMU6050_ReadData(u8 reg_add,unsigned char*Read,u8 num)
{
	unsigned char i;
	
	I2C_Start();
	I2C_Send_Byte(MPU6050_SLAVE_ADDRESS);
	I2C_Wait_Ack();
	I2C_Send_Byte(reg_add);
	I2C_Wait_Ack();
	
	I2C_Start();
	I2C_Send_Byte(MPU6050_SLAVE_ADDRESS+1);
	I2C_Wait_Ack();
	
	for(i=0;i<(num-1);i++){
		*Read=I2C_Read_Byte(1);
		Read++;
	}
	*Read=I2C_Read_Byte(0);
	I2C_Stop();
}

void MPU6050_Init(void)
{
	
	
	I2C_Init1();

//	MPU6050_PWR_MGMT_1_INIT();
	PMU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	     //解除休眠状态
	PMU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //陀螺仪采样率
	PMU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	PMU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //配置加速度传感器工作在16G模式
	PMU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	
	
	delay_ms(100);
//	MPU6050_PWR_MGMT_1_INIT();
	PMU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	     //解除休眠状态
	PMU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //陀螺仪采样率
	PMU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	PMU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //配置加速度传感器工作在16G模式
	PMU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
	
	
}

void MPU6050ReadID(void)
{
	unsigned char Re = 0;
    PMU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //读器件地址
     //printf("%d\r\n",Re);
}
void MPU6050ReadAcc(short *accData)
{
    u8 buf[6];
    PMU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = ((buf[0] << 8) | buf[1])/172;
    accData[1] = ((buf[2] << 8) | buf[3])/172;
    accData[2] = ((buf[4] << 8) | buf[5])/172;
}
void MPU6050ReadGyro(short *gyroData)
{
    u8 buf[6];
    PMU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

void MPU6050ReadTemp(short *tempData)
{
	u8 buf[2];
    PMU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
    *tempData = (buf[0] << 8) | buf[1];
}

void MPU6050_ReturnTemp(short*Temperature)
{
	short temp3;
	u8 buf[2];
	
	PMU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //读取温度值
  temp3= (buf[0] << 8) | buf[1];
	*Temperature=(((double) (temp3 + 13200)) / 280)-13;
}


#endif

#if CONFIG_GSM_TXRX == ENABLED


u8 a3;
u8 send_flag;
u8 sim_status=0;

volatile unsigned char UART3_RXD[UART3_RXD_SIZE];
volatile unsigned char UART3_RXD_Time = 0;
volatile unsigned int UART3_RXD_Index = 0;
volatile unsigned char UART3_Status_Registe = 0;
volatile unsigned char GPRS_Time_Counter = 100;
volatile unsigned char SMS_States_Register = 0;
volatile unsigned char SMS_CMD_Register = 0;
volatile unsigned int SIM800_CMD_Register = 0;
volatile unsigned char GPRS_States_Registe = 0;
volatile unsigned char SMS_Retry = SMS_RETYR_CONST;
volatile unsigned char SMS_States_Register;
volatile unsigned int SMS_Time_Cnt = 0;
void gsm_TIM2_Int_Init_demo(u16 Period,u16 Prescaler)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			//时钟使能

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM向上计数模式
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   						//使能或者失能指定的TIM中断
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;//TIM5中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级1级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  								//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
	TIM_Cmd(TIM2, ENABLE);  										//使能TIMx外设							 
}

void TIM2_IRQHandler(void) 
{

   static unsigned char Time0_100ms_Counter = 0;	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 			//检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				//清除TIMx的中断待处理位:TIM 中断源 
	  	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //清除TIMx的中断待处理位:TIM 中断源 

        if (UART3_RXD_Time)//20ms
        {
            if (--UART3_RXD_Time == 0) //串口接收超时
            {
                UART3_Status_Registe |= 1 << UART3_RXD_END;

            }
        }
        if (++Time0_100ms_Counter >= 5)//用于注册的间隔时间
        {
            Time0_100ms_Counter = 0;


            if (GPRS_Time_Counter)
            {
                GPRS_Time_Counter--;
            }

        }				
	}
}
void UART3_RXD_CLR(void)
{
    unsigned int i;

    for (i = 0; i < UART3_RXD_SIZE; i++)
    {
        UART3_RXD[i] = 0;
    }
    UART3_Status_Registe &= ~(1 << UART3_RXD_END); //串口收到的数据已经处理完
    UART3_RXD_Index = 0;

}


void GSMTXRX__USART3_ConfigDemo(u32 band)
{
	GPIO_InitTypeDef GPIO_InitStructure;     
	USART_InitTypeDef USART_InitStructure;   
	NVIC_InitTypeDef    NVIC_InitStructure;  
		

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);      
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);    

		
	//USART3?Tx---GPIO----PB.10----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	//USART3?Rx---GPIO----PB11----
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
		
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;             
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;     
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;            
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;               
	NVIC_Init(&NVIC_InitStructure);                      
		
	USART_InitStructure.USART_BaudRate=band;             
	USART_InitStructure.USART_WordLength=USART_WordLength_8b;                      
	USART_InitStructure.USART_StopBits=USART_StopBits_1;                          
	USART_InitStructure.USART_Parity=USART_Parity_No;                              
	USART_InitStructure.USART_HardwareFlowControl=USART_HardwareFlowControl_None;  
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;   
	USART_Init(USART3,&USART_InitStructure);	        //

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);      //

	USART_Cmd(USART3,ENABLE);                           //

}

/*串口3 发送数据到上位机 data 以\0结尾*/
void gsmtxrx_usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	//printf("%s",data);
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //向串口2发送数据
		
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//等待发送结束
		i++;
	}
	i++;
}
 /*发送一个字节数据*/
 void gsmtxrx_usart3_send_byte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
	      //printf("%s",&SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
}



void USART3_IRQHandler(void) //??1??????
{
	
	if(USART_GetFlagStatus(USART3,USART_IT_RXNE) != RESET)  //
	{			
		a3=USART_ReceiveData(USART3);
		

		UART3_RXD_Time = UART3_RXD_TIME;  //重置串口接收超时

		UART3_RXD[UART3_RXD_Index] = a3;

		UART3_RXD_Index++;

		UART3_RXD_Index = UART3_RXD_Index % UART3_RXD_SIZE;	
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
void SMS_Init(void)
{
	  //文本模式
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);

    //直接配置为短信过来直接显示出来
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //配置短信显示模式
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //配置短信显示模式
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //配置短信显示模式
    delay_ms(200);

}
void GPRS_CREG(void)
{
    
    if ((~GPRS_States_Registe) & (1 << GPRS_AT_CREG)) //没有注册成功 继续注册
    {
        if (GPRS_Time_Counter == 0)
        {

            SIM800_CMD_Register = 0;

            gsmtxrx_usart3_SendString_Demo((u8*)" AT&F\r\n"); //恢复出厂默认设置
            gsmtxrx_usart3_SendString_Demo((u8*)" ATE0\r\n"); //取消回显示
            gsmtxrx_usart3_SendString_Demo((u8*)" AT+CREG?\r\n");  //模块注册
    
            SMS_Init();


            GPRS_Time_Counter = 100; //25s超时
        }
        else
        {

            if (SIM800_CMD_Register & (1 << CMD_CREG)) //收到模块返回数据
            {
                GPRS_States_Registe |= (1 << GPRS_AT_CREG); //收到模块回复CREG信息
                SIM800_CMD_Register &= ~(1 << CMD_CREG); //清空标志
            }

        }
    }
    else
    {


    }
}
char hand(char *str)
{
    char *strx = 0;
    strx = strstr((const char *)(UART3_RXD), (const char *)str);
    return ((strx != NULL) ? 1 : 0);
}
void SIM800_CMD_Coding(void)
{

//AT+CMGF=1
//AT+CNMI=2,2,0,1 收到短信内容直接显示出来
//+CMT: "+8613403779870","","17/11/26,14:09:46+32"
//close

    if (hand("+CMT:")) //收到新短信
    {

        SMS_States_Register |= (1 << SMS_RXD_CMTI);


    }

    if (hand("+CMGR:")) //读到短信内容
    {

    }

    if (hand("+CMGS:"))  //短信发送完成
    {
        SMS_CMD_Register |= (1 << SMS_CMGS);
			  //gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n"); 

    }
    if (hand("SMS Ready")) 
    {
				

    }
    if (hand("READY"))
    {
        SIM800_CMD_Register |= (1 << CMD_READY);
    }
    if (hand(">"))
    {
        SMS_CMD_Register |= (1 << SMS_WaitData);
        SIM800_CMD_Register |= (1 << CMD_WaitData);
    }

    if (hand("SEND OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_SendOK);
    }


     //可正常收到数据，AT+CREG?
    if (hand("+CREG: 0,1"))
    {
        sim_status=1;
        SIM800_CMD_Register |= (1 << CMD_CREG);
        GPRS_States_Registe |= (1 << GPRS_AT_CREG);
    }
    if (hand("+CREG: 0,5"))
    {
        sim_status=1;
        SIM800_CMD_Register |= (1 << CMD_CREG);
        GPRS_States_Registe |= (1 << GPRS_AT_CREG);
    }
    //无法接收到短信，AT+CREG?
    if (hand("+CREG: 0,2"))
    {

       // SIM800_CMD_Register |= (1 << CMD_CREG);
       // GPRS_States_Registe |= (1 << GPRS_AT_CREG);
    }

    if (hand("+CGATT: 1"))
    {
        SIM800_CMD_Register |= (1 << CMD_CGATT1);
    }
    if (hand("+CGATT: 0"))
    {
        SIM800_CMD_Register |= (1 << CMD_CGATT0);
    }
    if (hand("ERROR"))
    {
        SMS_CMD_Register |= (1 << SMS_ERROR); //接收错误
        SIM800_CMD_Register |= (1 << CMD_ERROR);
    }
    if (hand("CONNECT OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_CONNECT_OK);
    }
    if (hand("OPEN")) //读取短信数据
    {

    }
    if (hand("CLOSE")) //读取短信数据
    {
       // SIM800_CMD_Register |= (1 << CMD_CLOSE);

    }
    if (hand("DATA")) //读取短信数据，接收到数据后要发送，需要延时1秒左右才发送
    {
			send_flag = 1;
      //Lcd1602_Display_String(1,5,(u8*)"DATA ");
    }		
    if (hand("SET"))  //收到新短信
    {


    }

    if (hand("RING") | hand("CRING")) //有来电
    {

        SIM800_CMD_Register |= (1 << CMD_RING);
    }

    if (hand("OK"))
    {

        SMS_CMD_Register |= (1 << SMS_RXD_OK);
        SIM800_CMD_Register |= (1 << CMD_OK);
    }
    else;


    if (hand("SHUT OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_SHUT_OK);
    }
    else;

    if (hand("NO CARRIER"))
    {
        SIM800_CMD_Register |= (1 << CMD_NO_CARRIER);
    }

    UART3_RXD_CLR();
}


void UART3_Processing(void)
{

    if (UART3_Status_Registe & (1 << UART3_RXD_END)) //收到串口数据
    {

        SIM800_CMD_Coding();//

        UART3_RXD_CLR();
        UART3_Status_Registe &= ~(1 << UART3_RXD_END);
    }


    if (SIM800_CMD_Register & (1 << CMD_RING))
    {

        //UART0_Send_String("ATH\r\n"); //直接挂断

        //SMS_Retry = 5;
        SMS_States_Register |= (1 << SMS_TXD_ENA); //发送短信
        SIM800_CMD_Register &= ~(1 << CMD_RING);
    }

}

void SMS_Send(u8* num,u8* data)
{
    static volatile unsigned char SMS_Step = 0;

    if (SMS_Retry == 0)
    {
        //超过发送重试次数,不再发送
        SMS_States_Register &= ~(1 << SMS_TXD_ENA);
        return;
    }

    if (SMS_Time_Cnt) //超时时间
    {
        SMS_Time_Cnt--;
    }

    switch (SMS_Step)
    {

    case 0:
        SMS_CMD_Register = 0; //清空接收状态

        gsmtxrx_usart3_SendString_Demo((u8*)" AT+CMGF=1\r\n"); //设置短信模式
        SMS_Step++;
        SMS_Time_Cnt = 20; //1秒
        if (SMS_Retry) SMS_Retry--; //重试次数-1
        break;

    case 1:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //超时无应答,或者指令错误
            SMS_Step = 0;
        }

        if (SMS_CMD_Register & (1 << SMS_RXD_OK))
        {

            SMS_CMD_Register = 0; //清空接收状态

            gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGS=\""); //设置接收短信号码
            gsmtxrx_usart3_SendString_Demo(num);  //
            gsmtxrx_usart3_SendString_Demo((u8*)"\"\r\n");
            SMS_Step++;
            SMS_Time_Cnt = 60; //3秒
        }

        break;

    case 2:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //超时无应答,或者指令错误
            SMS_Step = 0;
            gsmtxrx_usart3_send_byte_Demo(0x1A);  //内容结束

        }

        if (SMS_CMD_Register & (1 << SMS_WaitData)) //等待<
        {

            SMS_CMD_Register = 0; //清空接收状态

            gsmtxrx_usart3_SendString_Demo(data); //发送短信内容

            gsmtxrx_usart3_send_byte_Demo(0x1A);  //内容结束
            SMS_Step++;
            SMS_Time_Cnt = 180; //9.3秒
        }
        break;

    case 3:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //超时无应答,或者指令错误
            SMS_Step = 0;
            gsmtxrx_usart3_send_byte_Demo(0x1A);  //内容结束
            if (SMS_Retry) SMS_Retry--; //重试次数-1

        }

        if (SMS_CMD_Register & (1 << SMS_CMGS) || (SMS_CMD_Register & (1 << SMS_RXD_OK)))
        {
            //短信发送成功
            SMS_States_Register &= ~(1 << SMS_TXD_ENA);


            SMS_CMD_Register = 0;
            SMS_Time_Cnt = 120; //6秒
            SMS_Step = 0;
        }
        break;

    default:
        SMS_Step = 0;
        break;

    }

}


void SMS_Processing(u8* num,u8* data)
{
    //未注册时，间隔时间查询注册
    GPRS_CREG();

		if ((GPRS_States_Registe) & (1 << GPRS_AT_CREG)) //注册上网络才允许发送短信
		{
				if (SMS_States_Register & (1 << SMS_TXD_ENA)) //有短信需要发送
				{
					  //发送数据
						SMS_Send(num,data);
				}
		}
    
    //处理接收到的数据
    UART3_Processing();

}
void gsm_txrx_init(void)
{
   GSMTXRX__USART3_ConfigDemo(9600);	
	 gsm_TIM2_Int_Init_demo(200, 7200);//20mw
}
#endif

#if CONFIG_ADXL345 == ENABLED


unsigned char BUF[8];                         //接收数据缓存区      	
unsigned char ge,shi,bai,qian,wan;           //显示变量
unsigned char err;
float temp_X,temp_Y,temp_Z;

void SCL_Set_Output_ADXL345(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SCL_GPIO_PIN_ADXL345;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SCL_GPIO_ADXL345, &GPIO_InitStructure);					 					
}	

void SDA_Set_Output_ADXL345(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_ADXL345;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_ADXL345, &GPIO_InitStructure);					 					
}	

void SDA_Set_Input_ADXL345(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = SDA_GPIO_PIN_ADXL345;				 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(SDA_GPIO_ADXL345, &GPIO_InitStructure);					 
}



/**************************************
起始信号
**************************************/
void ADXL345_Start(void)
{
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    SET_SDA_ADXL345();//SDA = 1;                    //拉高数据线
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//Delay5us();                 //延时
    CLE_SDA_ADXL345();//SDA = 0;                    //产生下降沿
    delay_us(2);//Delay5us();                 //延时
    CLE_SCL_ADXL345();//SCL = 0;                    //拉低时钟线
}

/**************************************
停止信号
**************************************/
void ADXL345_Stop(void)
{
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    CLE_SDA_ADXL345();//SDA = 0;                    //拉低数据线
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//Delay5us();                 //延时
    SET_SDA_ADXL345();//SDA = 1;                    //产生上升沿
    delay_us(2);//Delay5us();                 //延时
    CLE_SCL_ADXL345();
}

/**************************************
发送应答信号
入口参数:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{   
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    if(ack==0)//SDA = ack;                  //写应答信号
    {
      CLE_SDA_ADXL345();
    }
    else
    {
      SET_SDA_ADXL345();
    }
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//Delay5us();                 //延时
    CLE_SCL_ADXL345();//SCL = 0;                    //拉低时钟线
    delay_us(5);//Delay5us();                 //延时
}

/**************************************
接收应答信号
**************************************/
unsigned char ADXL345_RecvACK(void)
{
    SDA_INT_ADXL345();
    SCL_OUT_ADXL345();
    SET_SCL_ADXL345();//SCL = 1;                    //拉高时钟线
    delay_us(2);//    Delay5us();                 //延时
    SET_SCL_ADXL345();
    if(SDA_VAL_ADXL345()== Bit_SET)   //CY = SDA;                   //读应答信号
    {
      err = 1;
    }
    else
    {
      err = 0;
    }
 
    CLE_SCL_ADXL345() ;//SCL = 0;                    //拉低时钟线
    delay_us(5);//    Delay5us();                 //延时
    SDA_OUT_ADXL345();
    return err;
}

/**************************************
向IIC总线发送一个字节数据
**************************************/
void ADXL345_SendByte(unsigned char dat)
{
    unsigned char i;
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    for (i=0; i<8; i++)         //8位计数器
    {
        delay_us(5);             //延时
        if(dat&0x80)  //SDA = CY;               //送数据口
        {SET_SDA_ADXL345();}
        else
        {CLE_SDA_ADXL345();}       
        delay_us(5);             //延时
        SET_SCL_ADXL345();//SCL = 1;                //拉高时钟线
        delay_us(5);             //延时
        CLE_SCL_ADXL345();//SCL = 0;                //拉低时钟线
        dat <<= 1;              //移出数据的最高位
    }
    ADXL345_RecvACK();
}

/**************************************
从IIC总线接收一个字节数据
**************************************/
unsigned char ADXL345_RecvByte(void)
{
    unsigned char i;
    unsigned char Mid;
    unsigned char dat = 0;
    SDA_INT_ADXL345();
    SCL_OUT_ADXL345();

    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        delay_us(5);            //延时
        SET_SCL_ADXL345();

			if(SDA_VAL_ADXL345()== Bit_SET)   //CY = SDA;                   //读应答信号
			{
				Mid = 1;
			}
			else
			{
				Mid = 0;
			}
		
//        Mid=SDA_VAL();
        if(Mid) dat++;
        delay_us(5);     
        CLE_SCL_ADXL345();//SCL = 0;                //拉低时钟线
    }
    return dat;
}

//******单字节写入*******************************************

void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data)
{
    ADXL345_Start();                  //起始信号
    ADXL345_SendByte(SlaveAddress);   //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);    //内部寄存器地址，请参考中文pdf22页 
    ADXL345_SendByte(REG_data);       //内部寄存器数据，请参考中文pdf22页 
    ADXL345_Stop();                   //发送停止信号
}

//********单字节读取*****************************************
unsigned char Single_Read_ADXL345(unsigned char REG_Address)
{  unsigned char REG_data;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(REG_Address);            //发送存储单元地址，从0开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
    REG_data=ADXL345_RecvByte();              //读出寄存器数据
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //停止信号
    return REG_data; 
}
//*********************************************************
//
//连续读出ADXL345内部加速度数据，地址范围0x32~0x37
//
//*********************************************************
void Multiple_Read_ADXL345(void)
{   unsigned char i;
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress);           //发送设备地址+写信号
    ADXL345_SendByte(0x32);                   //发送存储单元地址，从0x32开始	
    ADXL345_Start();                          //起始信号
    ADXL345_SendByte(SlaveAddress+1);         //发送设备地址+读信号
	 for (i=0; i<6; i++)                      //连续读取6个地址数据，存储中BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]存储0x32地址中的数据
        if (i == 5)
        {
           ADXL345_SendACK(1);                //最后一个数据需要回NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //回应ACK
       }
   }
    ADXL345_Stop();                          //停止信号
    delay_ms(5);
}


//*****************************************************************

//初始化ADXL345，根据需要请参考pdf进行修改************************
void Init_ADXL345(void)
{
   Single_Write_ADXL345(0x31,0x0B);   //测量范围,正负16g，13位模式
   Single_Write_ADXL345(0x2C,0x08);   //速率设定为12.5 参考pdf13页
   Single_Write_ADXL345(0x2D,0x08);   //选择电源模式   参考pdf24页
   Single_Write_ADXL345(0x2E,0x80);   //使能 DATA_READY 中断
   Single_Write_ADXL345(0x1E,0x00);   //X 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x1F,0x00);   //Y 偏移量 根据测试传感器的状态写入pdf29页
   Single_Write_ADXL345(0x20,0x05);   //Z 偏移量 根据测试传感器的状态写入pdf29页
}
//***********************************************************************
//显示x轴
void ReadData_x(void)
{   
  int  dis_data;                       //变量
  Multiple_Read_ADXL345();       	//连续读出数据，存储在BUF中
  dis_data=(BUF[1]<<8)+BUF[0];  //合成数据   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_X=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
  dis_data=(BUF[3]<<8)+BUF[2];  //合成数据   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_Y=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
  dis_data=(BUF[5]<<8)+BUF[4];    //合成数据   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_Z=(float)dis_data*3.9;  //计算数据和显示,查考ADXL345快速入门第4页
}

#endif

