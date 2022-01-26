#include "My_Demo.h"
#include "My_Config.h"

#if CONFIG_LCD1602 == ENABLED


/*-----------------------------------------------
  ���ƣ�LCD1602
  ��̳��www.doflye.net
  ��д��shifang
  ���ڣ�2009.5
  �޸ģ���
  ���ݣ�ͨ����׼����̬��ʾ�ַ�
  ���Ŷ������£�1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-
              ��æ����
------------------------------------------------*/

/*------------------------------------------------
              д�������
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
              д�����ݺ���
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
	//����ȱ��PA13/14/15 & PB3/4Ĭ������ΪJTAG���ܣ���Ҫ��JTAG�ص�
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO,ENABLE);	
	 
	 GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);
	
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8| GPIO_Pin_9 ;     //����Ϊ��©��� 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_OD; //GPIO_Mode_Out_PP;//
	GPIO_Init(GPIOB,&LCD1602_GPIOStruct);
	
	
	LCD1602_GPIOStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15 ;     //����Ϊ��©��� 
	LCD1602_GPIOStruct.GPIO_Speed = GPIO_Speed_50MHz;//GPIO_Speed_10MHz;
	LCD1602_GPIOStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	
	GPIO_Init(GPIOA,&LCD1602_GPIOStruct);
	
	

	
	
}




void LCD1602_Init_Demo(void)
{
	  LCD1602_GPIO_Config_Demo();   //����GPIO��
    LCD_Write_Com_Demo(0X38);  //16*2��ʾ��5*7����8λ���ݽӿ�
    LCD_Write_Com_Demo(0x0C);  //��ʾ���������ر�
    LCD_Write_Com_Demo(0x06);  //���ֲ�������ַ�Զ�+1
    LCD_Write_Com_Demo(0x01);  //����

	
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

/*****************���ƹ�꺯��********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add);
	if(date == 1)
		LCD_Write_Com_Demo(0x0f);     //��ʾ��겢����˸	
	else 
		LCD_Write_Com_Demo(0x0c);   //�رչ��
}

 /*------------------------------------------------
                ��������
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
// Һ���������
/*********************************************************/
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add); 
	
	LCD_Write_Data_Demo(yue%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(yue%10+0x30);				// ��λ
	LCD_Write_Data_Demo('-');
	LCD_Write_Data_Demo(ri%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(ri%10+0x30);				// ��λ
	LCD_Write_Data_Demo(' ');	
	LCD_Write_Data_Demo(shi%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(shi%10+0x30);				// ��λ
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(fen%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(fen%10+0x30);				// ��λ
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(miao%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(miao%10+0x30);				// ��λ

}

/*********************************************************/
// Һ���������
/*********************************************************/
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		LCD_Write_Com_Demo(0x80+add);
	else
		LCD_Write_Com_Demo(0x80+0x40+add); 
	

	LCD_Write_Data_Demo(shi%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(shi%10+0x30);				// ��λ
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(fen%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(fen%10+0x30);				// ��λ
	LCD_Write_Data_Demo(':');
	LCD_Write_Data_Demo(miao%100/10+0x30);		// ʮλ
	LCD_Write_Data_Demo(miao%10+0x30);				// ��λ

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
 
void Key_value_Demo(pKey_Process key_Process)	 //������������
{
	unsigned char Key_value;
#if KEY_COUNT == 1
	if(Demo_KEY1 == 0)
	{
		delay_ms(5);//ȥ���� 
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
		delay_ms(5);//ȥ���� 
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
	  delay_ms(5);//ȥ���� 
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
	  delay_ms(5);//ȥ���� 
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
	  delay_ms(5);//ȥ���� 
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
	  delay_ms(5);//ȥ���� 
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

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��

	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable, ENABLE);//�ر�jtag��ʹ��SWD��������SWDģʽ����

#if KEY_COUNT == 1

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA15	
#endif

#if KEY_COUNT == 2
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA15	
#endif

#if KEY_COUNT == 3
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA15	
#endif

#if KEY_COUNT == 4
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA15	
#endif

#if KEY_COUNT == 5
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIOA15
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_8;//PA15
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15	
#endif




	
} 
 
#endif
#if CONFIG_ADC == ENABLED

//�ڴ��д洢ת�����
vu16 ADC_ConvertedValue_Demo[Sample_Num_Demo][Channel_Num_Demo];
 
 
//DMA??:ADC1->CR --> ADC_ConvertedValue
void ADC_DMA_Config_Demo(void)
{
	 DMA_InitTypeDef DMA_InitStructure;
				   
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 DMA_DeInit(DMA1_Channel1);												//DMA��ͨ��1�Ĵ�����Ϊȱʡֵ
	 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		//DMA����ADC����ַ
	 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue_Demo;		//DMA�ڴ����ַ
	 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//�ڴ���Ϊ���ݴ����Ŀ�ĵ�
	 DMA_InitStructure.DMA_BufferSize = Sample_Num_Demo*Channel_Num_Demo;				//DMAͨ����DMA�����С
	 DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;		//�����ַ����
	 DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;				//�ڴ��ַ����
	 DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	//DMAͨ����DMA�����С
	 DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;			//DMAͨ����DMA�����С
	 DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;		//������ѭ������ģʽ
	 DMA_InitStructure.DMA_Priority = DMA_Priority_High;	//DMAͨ��xӵ�и����ȼ�
	 DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;			//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	 DMA_Init(DMA1_Channel1, &DMA_InitStructure);			//
	 DMA_Cmd(DMA1_Channel1,ENABLE);
}
 
 
void ADC1_Config_Demo(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	   
	//PA0 ͨ��0 PA1 ͨ��1 PA2 ͨ��2
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//ģ������
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 ADC_DMA_Config_Demo();
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6); 		//����ADC��Ƶ����6 72M/6=12M��ADC���ʱ�䲻�ܳ���14M
	
	// ADC_DeInit(ADC1);
	 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//ADC1��ADC2�����ڶ���ģʽ
	 ADC_InitStructure.ADC_ScanConvMode = ENABLE;							//��ͨ��
	 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//����ת��
	 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//�������ת��
	 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//ת������Ҷ���
	 ADC_InitStructure.ADC_NbrOfChannel = Channel_Num_Demo;						//ͨ����
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

const unsigned char  zm8x16_index_Demo[]="0123456789: |-+<.^";//�ִ�����
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
const unsigned char  zm16x16_index_Demo[]="��ӭʹ������������������";//�ִ�����
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

//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear_Demo(void)  
{  
	u8 i,n;  
	for(i=0;i<8;i++)for(n=0;n<128;n++)OLED_GRAM_Demo[n][i]=0X00;  
	//OLED_Refresh_Gram();//������ʾ
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


		//�л���ʾ�Ƕ� ���µߵ���ʾ
		//Write_Command3(0xc0);	//--set com(N-1)to com0  c0:com0 to com(N-1)
		
		//�л���ʾ�Ƕ�
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

//�����Դ浽LCD		 
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

/* ����һ��8*16�ַ�����λ�� */					
unsigned char enN_Demo(unsigned char *s){
	unsigned char i;
	for(i=0;zm8x16_index_Demo[i]!=0;i++)if(zm8x16_index_Demo[i]==s[0])break;
	return i;	
}
/* ����һ��16*16�ַ�����λ�� */
unsigned char cnN_Demo(unsigned char *s){
	unsigned char i;
	for(i=0;zm16x16_index_Demo[i]!=0;i+=2)
		if(zm16x16_index_Demo[i]==*s&&zm16x16_index_Demo[i+1]==*(s+1))break ;
	return i/2;
}


//���� 
//x:0~127
//y:0~63
//t:1 ��� 0,���				   
void OLED_DrawPoint_Demo(u8 x,u8 y,u8 t)
{
	u8 pos,bx,temp=0;
	if(x>127||y>63)return;//������Χ��.
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
	 	if(s[i]<0x80){ 	//Ӣ��
			value=enN_Demo(&s[i]);
			
			for(t=0;t<16;t++)
			{  
				  temp = zm8x16_Table_Demo[value][t];    //����1616����

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
		}else{			//����
			value=cnN_Demo(&s[i]);
			for(t=0;t<32;t++)
			{  
				  temp = zm16x16_Table_Demo[value][t];    //����1616����

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
			//���������ֽڣ���Ҫ��1
			i+=1;			
		}//����
		
	}
	OLED_Refresh_Gram_Demo();	
}

void OLED_ShowNum_Demo(u8 x, u8 y,unsigned int num)
{
	u8 t,temp,t1;
	u8 y0=y;	
	for(t=0;t<16;t++)
	{  
		temp = zm8x16_Table_Demo[num][t];    //����1616����

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

	
	OLED_ShowNum_Demo(row,col,yue/10%10);		// ʮλ
	OLED_ShowNum_Demo(row+8,col,yue%10);				// ��λ
	OLED_ShowStr_ENCH_Demo(row+16,col,(u8*)"-");
	OLED_ShowNum_Demo(row+24,col,ri%100/10);		// ʮλ
	OLED_ShowNum_Demo(row+32,col,ri%10);				// ��λ
	OLED_ShowStr_ENCH_Demo(row+40,col,(u8*)" ");	
	OLED_ShowNum_Demo(row+48,col,shi%100/10);		// ʮλ
	OLED_ShowNum_Demo(row+56,col,shi%10);				// ��λ
	OLED_ShowStr_ENCH_Demo(row+64,col,(u8*)":");
	OLED_ShowNum_Demo(row+72,col,fen%100/10);		// ʮλ
	OLED_ShowNum_Demo(row+80,col,fen%10);				// ��λ
	OLED_ShowStr_ENCH_Demo(row+88,col,(u8*)":");
	OLED_ShowNum_Demo(row+96,col,miao%100/10);		// ʮλ
	OLED_ShowNum_Demo(row+104,col,miao%10);				// ��λ
	OLED_Refresh_Gram_Demo();

}
#endif
#if CONFIG_TIMER2 == ENABLED
static pTime2Process_Demo Tim2_Handle_Process;
void TIM2_Int_Init_demo(u16 Period,u16 Prescaler,pTime2Process_Demo TimeProcess)
{
  TIM_TimeBaseInitTypeDef  	TIM_TimeBaseStructure;
	NVIC_InitTypeDef 			NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   						//ʹ�ܻ���ʧ��ָ����TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  								//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  
	Tim2_Handle_Process = TimeProcess;
	TIM_Cmd(TIM2, ENABLE);  										//ʹ��TIMx����							 
}
	   
/**
 * @Description: ͨ�ö�ʱ��TIM3�жϺ���
 */
void TIM2_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 			//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				//���TIMx���жϴ�����λ:TIM �ж�Դ 
	  	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); 			//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);   						//ʹ�ܻ���ʧ��ָ����TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM3_IRQn;//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  								//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  
	Tim3_Handle_Process_Demo = TimeProcess;
	TIM_Cmd(TIM3, ENABLE);  										//ʹ��TIMx����							 
}
	   
/**
 * @Description: ͨ�ö�ʱ��TIM3�жϺ���
 */
void TIM3_IRQHandler(void) 
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) 			//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);				//���TIMx���жϴ�����λ:TIM �ж�Դ 
	  	TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
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
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);	//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB  | RCC_APB2Periph_AFIO, ENABLE);  
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE); 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��GPIO
 
   //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler =psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2; 
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; 
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);  

	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  
 
	TIM_Cmd(TIM3, ENABLE); 

}

/**DEMO
//0Ϊ������899Ϊ�
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
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) 			//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);				//���TIMx���жϴ�����λ:TIM �ж�Դ 
	  	TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		if(Tim4_Handle_Process_Demo != 0)
			Tim4_Handle_Process_Demo();
		 
	}
  
	
}

#endif
#if CONFIG_DS18b02 == ENABLED

//��λDS18B20
void DS18B20_Rst_Demo(void)	   
{                 
	DS18B20_IO_OUT(); //SET PA0 OUTPUT
    DS18B20_DQ_OUT=0; //����DQ
    delay_us(750);    //����750us
    DS18B20_DQ_OUT=1; //DQ=1 
	delay_us(15);     //15US
}
//�ȴ�DS18B20�Ļ�Ӧ
//����1:δ��⵽DS18B20�Ĵ���
//����0:����
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
//��DS18B20��ȡһ��λ
//����ֵ��1/0
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
//��DS18B20��ȡһ���ֽ�
//����ֵ������������
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
//дһ���ֽڵ�DS18B20
//dat��Ҫд����ֽ�
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
//��ʼ�¶�ת��
void DS18B20_Start_Demo(void)// ds1820 start convert
{   						               
    DS18B20_Rst_Demo();	   
	DS18B20_Check_Demo();	 
    DS18B20_Write_Byte_Demo(0xcc);// skip rom
    DS18B20_Write_Byte_Demo(0x44);// convert
} 
//��ʼ��DS18B20��IO�� DQ ͬʱ���DS�Ĵ���
//����1:������
//����0:����    	 
u8 DS18B20_Init_Demo(void)
{
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PORTA��ʱ�� 
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				//PORTA0 �������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		  
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	GPIO_SetBits(GPIOB,GPIO_Pin_0);    //���1

	DS18B20_Rst_Demo();

	return DS18B20_Check_Demo();
}  
//��ds18b20�õ��¶�ֵ
//���ȣ�0.1C
//����ֵ���¶�ֵ ��-550~1250�� 
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
        temp=0;//�¶�Ϊ��  
    }else temp=1;//�¶�Ϊ��	  	  
    tem=TH; //��ø߰�λ
    tem<<=8;    
    tem+=TL;//��õװ�λ
    tem=(float)tem*0.625;//ת��     
	if(temp)return tem; //�����¶�ֵ
	else return -tem;    
} 
 

#endif

#if CONFIG_MOTO_STEP == ENABLED



//������ӦIO��ʼ������
void MotoStep_Init_Demo(pTimeProcess_Demo  TimeProce)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PAʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	//��ʱ��3��ʼ��
	TIM3_Int_Init_Demo (10, 7200,TimeProce);//10ms faster
}

/***********************��ת****************************/
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

/***********************��ת****************************/
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
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}

void uart1_init_Demo(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}


void UART1_Send_Byte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //��ʼ����
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void UART1_Send_String_Demo(unsigned char *Index)
{

	while(*Index)//����ַ���������
	{
		UART1_Send_Byte_Demo(*Index++);//���͵�ǰ�ַ�
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

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		a1 =USART_ReceiveData(USART1);	//��ȡ���յ�������

	} 

}

#endif

#if CONFIG_USART2 == ENABLED

u8 uart2flag_Demo=0; 
u8 USART2_RX_BUF_Demo[USART2_REC_LEN_DEMO];
u8 USART_Length_Demo;
void usart2_init_Demo(u32 band)
{
	//GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//ʹ��USART2
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//  
	
	//���¶���ܽ�
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	//USART2_TX    
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; // ���Ų��ܸ���
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ�� 
   
  //USART2_RX	   
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;//PA 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��   

  //Usart NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;//��ռ���ȼ�3 ԭ3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3     ԭ2
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = band;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART2, &USART_InitStructure); //��ʼ������2
  USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART2, ENABLE);                    //ʹ�ܴ���2
}
 /*����һ���ֽ�����*/
 void USART2SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART2,SendData);
        while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);	    
} 

/*
���ݳ����򴮿�2 ��������
*/
void usart2_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART2, data[i]); //�򴮿�2��������
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		//i++;
	}
	//i++;
}
/*����3 �������ݵ���λ�� data ��\0��β*/
void usart2_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART2, data[i]);         //�򴮿�2��������
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		i++;
	}
	i++;
}
/*
����2�жϺ���
*/
void USART2_IRQHandler(void)                	//����2�жϷ������
{
	static u8 i;
	if(USART_GetITStatus(USART2,USART_IT_RXNE) != RESET)
	{	
		if(uart2flag_Demo==0)
		{
			USART2_RX_BUF_Demo[0] = USART_ReceiveData(USART2);	
			if( USART2_RX_BUF_Demo[0]=='O') 
			{
				//USART2SendByte('k'); //�ж��Ƿ�ʼ����
				uart2flag_Demo=1; i = 1;   //��ʼ����
			}
			else
			{
				USART2_RX_BUF_Demo[0]=0;
			}
		}
		else	
		{ 
			USART2_RX_BUF_Demo[i] = USART_ReceiveData(USART2);  //����9λ
			i++; 
			if(i ==4) //�������
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
 /*����һ���ֽ�����*/
 void USART3SendByte_Demo(unsigned char SendData)
{	   
        USART_SendData(USART3,SendData);
        while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);	    
} 

/*
���ݳ����򴮿�2 ��������
*/
void usart3_SendStringByLen_Demo(unsigned char * data,u8 len)
{
	u16 i=0;
	for(i=0;i<len;i++)
	{
		USART_SendData(USART3, data[i]); //�򴮿�2��������
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		//i++;
	}
	//i++;
}
/*����3 �������ݵ���λ�� data ��\0��β*/
void usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //�򴮿�2��������
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
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
 
	TIM_DeInit(TIM2);//��λTIM2��ʱ��
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
 
// 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTEʱ��

	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_3;// 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; //���ó� ���
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
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
			
			Trig = 1;  //����TRIG����10US��
			i = 0xFFF;
			while(--i);
			i = 0xFFF;
			while(--i);	
			Trig = 0;	
			TIM2->CNT=0;//��������0
			while(1)//�ȴ�ECHO�Ÿߵ�ƽ
			{
				 if(Echo == 1)
				  {
							TIM_Cmd(TIM2, ENABLE);// TIM2 enable counter [����tim2����]
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
			*Length_Value =TIM2->CNT/58.0;//ECHO�ŵ͵�ƽ���ȡ��������ֵ���Ӷ��������ʱ��
       //printf("legth %ld,value %d\r\n",*Length_Value,TIM2->CNT);
			//����4��
			if(*Length_Value >= 400) *Length_Value = 400;
}

#endif

#if CONFIG_FLASH == ENABLED
#include "stm32f10x_flash.h"

//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
//����ֵ:��Ӧ����.
u16 STMFLASH_ReadHalfWord_Demo(u32 faddr)
{
	return *(vu16*)faddr; 
}
#if STM32_FLASH_WREN	//���ʹ����д   
//������д��
//WriteAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��   
void STMFLASH_Write_NoCheck_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)   
{ 			 		 
	u16 i;
	for(i=0;i<NumToWrite;i++)
	{
		FLASH_ProgramHalfWord(WriteAddr,pBuffer[i]);
	    WriteAddr+=2;//��ַ����2.
	}  
}

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��
void STMFLASH_Read_Demo(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord_Demo(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}
//��ָ����ַ��ʼд��ָ�����ȵ�����
//WriteAddr:��ʼ��ַ(�˵�ַ����Ϊ2�ı���!!)
//pBuffer:����ָ��
//NumToWrite:����(16λ)��(����Ҫд���16λ���ݵĸ���.)
#if STM32_FLASH_SIZE<256
#define STM_SECTOR_SIZE 1024 //�ֽ�
#else 
#define STM_SECTOR_SIZE	2048
#endif		 
u16 STMFLASH_BUF_Demo[STM_SECTOR_SIZE/2];//�����2K�ֽ�
void STMFLASH_Write_Demo(u32 WriteAddr,u16 *pBuffer,u16 NumToWrite)	
{
	u32 secpos;	   //������ַ
	u16 secoff;	   //������ƫ�Ƶ�ַ(16λ�ּ���)
	u16 secremain; //������ʣ���ַ(16λ�ּ���)	   
 	u16 i;    
	u32 offaddr;   //ȥ��0X08000000��ĵ�ַ
	if(WriteAddr<STM32_FLASH_BASE||(WriteAddr>=(STM32_FLASH_BASE+1024*STM32_FLASH_SIZE)))return;//�Ƿ���ַ
	FLASH_Unlock();						//����
	offaddr=WriteAddr-STM32_FLASH_BASE;		//ʵ��ƫ�Ƶ�ַ.
	secpos=offaddr/STM_SECTOR_SIZE;			//������ַ  0~127 for STM32F103RBT6
	secoff=(offaddr%STM_SECTOR_SIZE)/2;		//�������ڵ�ƫ��(2���ֽ�Ϊ������λ.)
	secremain=STM_SECTOR_SIZE/2-secoff;		//����ʣ��ռ��С   
	if(NumToWrite<=secremain)secremain=NumToWrite;//�����ڸ�������Χ
	while(1) 
	{	
		STMFLASH_Read_Demo(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF_Demo,STM_SECTOR_SIZE/2);//������������������
		for(i=0;i<secremain;i++)//У������
		{
			if(STMFLASH_BUF_Demo[secoff+i]!=0XFFFF)break;//��Ҫ����  	  
		}
		if(i<secremain)//��Ҫ����
		{
			FLASH_ErasePage(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE);//�����������
			for(i=0;i<secremain;i++)//����
			{
				STMFLASH_BUF_Demo[i+secoff]=pBuffer[i];	  
			}
			STMFLASH_Write_NoCheck_Demo(secpos*STM_SECTOR_SIZE+STM32_FLASH_BASE,STMFLASH_BUF_Demo,STM_SECTOR_SIZE/2);//д����������  
		}else STMFLASH_Write_NoCheck_Demo(WriteAddr,pBuffer,secremain);//д�Ѿ������˵�,ֱ��д������ʣ������. 				   
		if(NumToWrite==secremain)break;//д�������
		else//д��δ����
		{
			secpos++;				//������ַ��1
			secoff=0;				//ƫ��λ��Ϊ0 	 
		   	pBuffer+=secremain;  	//ָ��ƫ��
			WriteAddr+=secremain;	//д��ַƫ��	   
		   	NumToWrite-=secremain;	//�ֽ�(16λ)���ݼ�
			if(NumToWrite>(STM_SECTOR_SIZE/2))secremain=STM_SECTOR_SIZE/2;//��һ����������д����
			else secremain=NumToWrite;//��һ����������д����
		}	 
	};	
	FLASH_Lock();//����
}
#endif



//////////////////////////////////////////////////////////////////////////////////////////////////////
//WriteAddr:��ʼ��ַ
//WriteData:Ҫд�������
void Test_Write_Demo(u32 WriteAddr,u16 WriteData)   	
{
	STMFLASH_Write_Demo(WriteAddr,&WriteData,1);//д��һ���� 
}

#endif

#if CONFIG_DS1302 == ENABLED

const unsigned char  Ds1302_write_add_Demo[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //д��ַ
const unsigned char  Ds1302_read_add_Demo[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //����ַ

//DS1302��ʼ��
void DS1302_Init_Demo(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 |GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_SetBits(GPIOB, GPIO_Pin_1);                 //PB1����
	GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_10); //PB0��PB10�õ�
}

//��DS1302д��һ���ֽ�����
void DS1302_Write_Byte_Demo(u8 addr, u8 data)
{
  u8 i;
	DS1302_RST = 0;      //ֹͣDS1302����
	delay_us(10);
	DS1302_RST = 1;      //����DS1302����
	addr = addr & 0xFE;  //���λ���㣬д����
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //д��ַ
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	for (i = 0; i < 8; i ++) //д����
	{
	  if(data & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;   //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
	  data = data>>1;
	}
	DS1302_RST = 0;      //ֹͣDS1302����
}

//��DS1302����һ���ֽ�����
u8 DS1302_Read_Byte_Demo(u8 addr)
{
  u8 i,temp;
	DS1302_RST = 0;      //ֹͣDS1302����
	delay_us(10);
	DS1302_RST = 1;      //����DS1302����
	addr = addr | 0x01;  //���λ�øߣ�������
	DS1302_IO_OUT();
	for(i = 0; i < 8; i ++)  //д��ַ
	{
	  if (addr & 0x01)
			DS1302_DATA_OUT = 1;
		else
			DS1302_DATA_OUT = 0;
		
		DS1302_SCK = 1;    //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
		addr = addr>>1;
	}
	DS1302_IO_IN();
	for (i = 0; i < 8; i ++) //������
	{
	  temp = temp >> 1;
		if(DS1302_DATA_IN)
			temp |= 0x80;
		else
			temp &= 0x7F;
		
		DS1302_SCK = 1;   //����ʱ��
		delay_us(10);
		DS1302_SCK = 0;
	}
	DS1302_RST = 0;      //ֹͣDS1302����
	return temp;
}


unsigned char BCD_Decimal_Demo(unsigned char bcd)//BCD��תʮ���ƺ���������BCD������ʮ����
{
	 unsigned char Decimal;
	 Decimal=bcd>>4;
	 return(Decimal=Decimal*10+(bcd&=0x0F));
}
/*************��Ҫ��ʱ�� ������ ��������***************/
//arry[7]
void Ds1302_Read_Time_Demo(unsigned char *arry)
{
	*arry      = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[0]));	//����
	*(arry+1)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[1]));	//����
	*(arry+2)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[2]));	//��ʱ
	*(arry+3)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[3]));	//����
	*(arry+4)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[4]));	//����
	*(arry+5)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[5]));	//����
	*(arry+6)  = BCD_Decimal_Demo(DS1302_Read_Byte_Demo(Ds1302_read_add_Demo[6]));	//������
}

void Ds1302_Save_Demo(unsigned char  po, unsigned char  dat)
{
	unsigned char  temp;
	temp=(dat)/10*16+(dat)%10;//ʮ����ת����DS1302Ҫ���DCB��
	DS1302_Write_Byte_Demo(0x8e,0x00);//����д����ֹд���� 
	DS1302_Write_Byte_Demo(po,temp);//��DS1302��д�ּĴ���82Hд�������ķ�����BCD��
	DS1302_Write_Byte_Demo(0x8e,0x80);//��д����	
}

#endif

#if CONFIG_DHT11 == ENABLED

 //////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//DHT11������ʪ�ȴ�������������	   
//�޸�����:2012/9/12
//�汾��V1.0
//��Ȩ���У�����ؾ���
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
      
//��λDHT11
void DHT11_Rst_Demo(void)	   
{                 
	  DHT11_IO_OUT(); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//����DQ
    delay_ms(20);    	//��������18ms
    DHT11_DQ_OUT=1; 	//DQ=1 
	  delay_us(30);     	//��������20~40us
}
//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
u8 DHT11_Check_Demo(void) 	   
{   
	u8 retry=0;
	DHT11_IO_IN();//SET INPUT	 
    while (DHT11_DQ_IN&&retry<100)//DHT11������40~80us
	{
		retry++;
		delay_us(1);
	};	 
	if(retry>=100)return 1;
	else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~80us
	{
		retry++;
		delay_us(1);
	};
	if(retry>=100)return 1;	    
	return 0;
}
//��DHT11��ȡһ��λ
//����ֵ��1/0
u8 DHT11_Read_Bit_Demo(void) 			 
{
 	u8 retry=0;
	while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
	{
		retry++;
		delay_us(1);
	}
	retry=0;
	while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
	{
		retry++;
		delay_us(1);
	}
	delay_us(40);//�ȴ�40us
	if(DHT11_DQ_IN)return 1;
	else return 0;		   
}
//��DHT11��ȡһ���ֽ�
//����ֵ������������
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
//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u8 DHT11_Read_Data_Demo(u8 *temp,u8 *humi)    
{        
 	u8 buf[5];
	u8 i;
	DHT11_Rst_Demo();
	if(DHT11_Check_Demo()==0)
	{
		for(i=0;i<5;i++)//��ȡ40λ����
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
//��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
//����1:������
//����0:����    	 
u8 DHT11_Init_Demo(void)
{	 
 	GPIO_InitTypeDef  GPIO_InitStructure;
 	
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PG�˿�ʱ��
	
 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				 //PG11�˿�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);				 //��ʼ��IO��
 	GPIO_SetBits(GPIOC,GPIO_Pin_13);						 //PC13 �����
			    
	DHT11_Rst_Demo();  //��λDHT11
	return DHT11_Check_Demo();//�ȴ�DHT11�Ļ�Ӧ
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
//��ȡëƤ����
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
//����
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
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PC�˿�ʱ��
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;				 //LED�˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOC
}
#endif

#if CONFIG_MP3 == ENABLED
static unsigned char Send_buf_Demo[10] = {0} ;

void MP3_uart_init_Demo(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

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
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//ʹ��PORTA,PORTEʱ��
	//MP3 BUSY jiao 
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_12;//KEY0-KEY2
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��		
}

/*****************************************************************************************************
 - �������������ڷ���һ֡����

*****************************************************************************************************/


void SendCmd_Demo(unsigned char len)
{

		MP3_USART1_Send_Data_Demo(Send_buf_Demo,len);

}

/*****************************************************************************************************
 - �������������У��
 - ����ģ�飺
 - ����˵����
 - ����˵����
 - ע��				��У���˼·����
							���͵�ָ�ȥ����ʼ�ͽ��������м��6���ֽڽ����ۼӣ����ȡ����
							���ն˾ͽ����յ���һ֡���ݣ�ȥ����ʼ�ͽ��������м�������ۼӣ��ټ��Ͻ��յ���У��
							�ֽڡ��պ�Ϊ0�������ʹ�����յ���������ȫ��ȷ
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
 - �����������������ⷢ������������ƺͲ�ѯ��
 - ����ģ�飺�ⲿ
 - ����˵����CMD����ʾ����ָ����ѯָ�����������ѯ�����ָ��
							feedback���Ƿ���ҪӦ��[0������ҪӦ��1����ҪӦ��]
							data�����͵Ĳ���
 - ����˵����
 - ע��
*****************************************************************************************************/


void Uart_SendCMD_Demo(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
		
		while(BUSY == 0){}
    Send_buf_Demo[0] = 0x7e;    //�����ֽ�
    Send_buf_Demo[1] = 0xff;    //�����ֽ�
    Send_buf_Demo[2] = 0x06;    //����
    Send_buf_Demo[3] = CMD;     //����ָ��
    Send_buf_Demo[4] = feedback;//�Ƿ���Ҫ����
    Send_buf_Demo[5] = (unsigned char)(dat >> 8);//datah
    Send_buf_Demo[6] = (unsigned char)(dat);     //datal
		Send_buf_Demo[9] = 0xef;
    DoSum_Demo(&Send_buf_Demo[1],6);        //У��
    SendCmd_Demo(10);       //���ʹ�֡����
		
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


//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif

void GPS_uart_init_Demo(u32 bound){
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}

/* ���ݿո�ָ��ַ��� */ 
int partition(char *src, char *par, int pos) 
{ 
  int i,j; 

  i = pos; 

  //ȡ����һ���ǿո��ַ� 
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
//GPS���ݽ���

//$GPRMC,055607.00,A,3959.44811,N,11625.31055,E,2.312,,300317,,,A*78
//$GPRMC,055609.00,A,3959.44931,N,11625.31260,E,0.802,,300317,,,A*79

//20180424��λ����
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
			//�ö��ŷָ���k��Ӧ��Ϊ�ĸ�λ�õĶ���
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
void USART1_IRQHandler(void)                	//����1�жϷ������
{
	u8 a;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		a =USART_ReceiveData(USART1);	//��ȡ���յ�������
		if(a == '$')
		{
			GPS_RXD_Index = 0;
			GPS_RXD[GPS_RXD_Index] = a;	
			GPS_RXD_Index++;
		}
		else if((a == '\r')&&(GPS_RXD[4]=='G')) //�յ�һ֡��������   ֻ����$GPGGA��һ֡����
		{
		

			
			GPS_States |= (1 <<GPS_RXD_END); //���GPS�������
			
			GPS_RXD[GPS_RXD_Index] = a;	
			GPS_RXD_Index++;
			GPS_RXD_Index = GPS_RXD_Index % 100;			
			GPS_Processing();	
			//����������������
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
unsigned int xlTab[5];//��������
unsigned char count=0;	//�����˲�����
unsigned int xinLater=0;//	������ʱ����
unsigned int xinLv =0;    //����ֵ
//�ⲿ�жϳ�ʼ������
void EXTIX_Init_Demo(void)
{
 
 	  EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
    GPIO_InitTypeDef GPIO_InitStructure;
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);//�ⲿ�жϣ���Ҫʹ��AFIOʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);//ʹ��PORTA,PORTCʱ��

		GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;//PA15
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //���ó���������
		GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA15	


    //GPIOA.0	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

   	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


 
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		

 
}

void EXTIX_TIM3_Int_Init_Demo(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE); //ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 ������5000Ϊ500ms
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  10Khz�ļ���Ƶ��  
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
 
	TIM_ITConfig(  //ʹ�ܻ���ʧ��ָ����TIM�ж�
		TIM3, //TIM2
		TIM_IT_Update ,
		ENABLE  //ʹ��
		);
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;  //TIM3�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  //��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  //�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; //IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIMx����
							 
}
void heart_rate_init_demo(void)
{
	EXTIX_TIM3_Int_Init_Demo(49,7199);
	EXTIX_Init_Demo();
}

void TIM3_IRQHandler(void)   //TIM3�ж�
{
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
		{
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 
		

			xinLater++;   
			if(xinLater>400)	//�˲��˵���ָδ�����
			{
				xinLv = 0; 	//�˲��˵���ָδ�����
				xinLater=0;
			}
		}
}

void EXTI0_IRQHandler(void)
{

		//OLED_ShowNum_Three_Demo(0,32,xinLater);
  if(xinLater>60)   //�˲���ֹ����300ms
  {
    if(xinLater>400)		//�˲��˵���ָδ�����
    {
      xinLater =0;		//��ʱ����Ϊ0
    }
    else
    {
      xlTab[count++]=xinLater;//��¼ǰ�������¼���� 
      xinLater=0;
      if(count>=4)		//��¼����4�ν����˲�����
      {
        xinLv =60000/((xlTab[0]+xlTab[1]+xlTab[2]+xlTab[3])/4*5);//60000��λms ��ʾ60s /4��ƽ��  *5ÿ�ζ�ʱ5ms
        count=0;		//������μ�¼
      }   
      xinLater =0;	//��ʱ����
    }
  }
	
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
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
/*����3 �������ݵ���λ�� data ��\0��β*/
void gsm_usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //�򴮿�2��������
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		i++;
	}
	i++;
}
 /*����һ���ֽ�����*/
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

//��ʼ��IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );	//ʹ��GPIOBʱ��
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD ;   //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_6|GPIO_Pin_7); 	//PB6,PB7 �����
}
//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT();     //sda�����
	IIC_SDA=1;	  	  
	IIC_SCL=1;
	delay_us(4);
 	IIC_SDA=0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT();//sda�����
	IIC_SCL=0;
	IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	IIC_SCL=1; 
	IIC_SDA=1;//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN();      //SDA����Ϊ����  
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
	IIC_SCL=0;//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT(); 	    
    IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        //IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA=1;
		else
			IIC_SDA=0;
		txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		IIC_SCL=1;
		delay_us(2); 
		IIC_SCL=0;	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN();//SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK   
    return receive;
}

#include <math.h>
_bmp180 bmp180;

//BMP180��ʼ��
//��ʹ�õ�IIC�˿ڽ��г�ʼ��
void BMP_Init(void)
{
	IIC_Init();
}

//дһ�����ݵ�BMP180
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

//��BMP180��һ���ֽ�����
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

//��BMP180��һ��16λ������
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

//��BMP180�Ļ�ȡ�������
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

//��BMP180��ȡδ�������¶�
long BMP_Read_UT(void)
{
	long temp = 0;
	BMP_WriteOneByte(0xF4,0x2E);
	
	delay_ms(5);
	temp = (long)BMP_ReadTwoByte(0xF6);
	return temp;
}

//��BMP180��ȡδ�����Ĵ���ѹ
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

//�û�ȡ�Ĳ������¶Ⱥʹ���ѹ���������������㺣��
void BMP_UncompemstatedToTrue(void)
{
	bmp180.UT = BMP_Read_UT();//��һ�ζ�ȡ����
	bmp180.UT = BMP_Read_UT();//���еڶ��ζ�ȡ��������
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
  //GPIO�˿�����
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
  
	//USART1_TX   GPIOA.9
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.9
   
  //USART1_RX	  GPIOA.10��ʼ��
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;//PA10
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.10  

  //Usart1 NVIC ����
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������

	USART_InitStructure.USART_BaudRate = bound;//���ڲ�����
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

  USART_Init(USART1, &USART_InitStructure); //��ʼ������1
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�������ڽ����ж�
  USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ���1 

}


void esp8266_UART1_Send_Byte_Demo(unsigned char a)
{

	USART_SendData(USART1,a); //��ʼ����
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET); 
	USART_ClearFlag(USART1,USART_FLAG_TXE);
}


void esp8266_UART1_Send_String_Demo(unsigned char *Index)
{

	while(*Index)//����ַ���������
	{
		esp8266_UART1_Send_Byte_Demo(*Index++);//���͵�ǰ�ַ�
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

void USART1_IRQHandler(void)                	//����1�жϷ������
{
	

	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //�����ж�(���յ������ݱ�����0x0d 0x0a��β)
	{
		a1 =USART_ReceiveData(USART1);	//��ȡ���յ�������

	} 

}
/******************************************************************** 
���ƣ�WIFIģ�����ú���  ����: ����ģ�飬�Ա����ʵ�����߽���Ϳ���  
********************************************************************/ 
void ESP8266_Set(unsigned char *puf) 
	{                        	// ����ָ��*pufָ���ַ�������
    while(*puf!='\0') 
		{  		//�����ո�����ѭ��
        esp8266_UART1_Send_Byte_Demo(*puf);  		//��WIFIģ�鷢�Ϳ���ָ�
        puf++;
    }
    delay_ms(5);
    esp8266_UART1_Send_Byte_Demo('\r'); 			//�س�
    delay_ms(5);
    esp8266_UART1_Send_Byte_Demo('\n');   			//����
}
void Esp8266_init(void)
{
		esp8266_uart1_init_Demo(9600);
		delay_ms(100);
	  ESP8266_Set((u8*)"AT+CWMODE=2"); 							//����·����ģʽ1 station,ģʽ2 AP,ģʽ3 station+AP���ģʽ   ����ǰwifi�Ĳ��������ó�9600
    delay_ms(300);
    ESP8266_Set((u8*)"AT+RST"); 									//��������wifiģ��
    delay_ms(300);
//    ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  ����ģ��SSID:WIFI, PWD:���� ����ȫ���ͼ���ģʽ��WPA2-PSK��
    ESP8266_Set((u8*)"AT+CWSAP=\"wifi_yuxia\",\"12345678\",11,4");
    delay_ms(300);
//    ESP8266_Set("AT+CIPMUX=1");								//����������ģʽ�����������ͻ��˽���
    ESP8266_Set((u8*)"AT+CIPMUX=1");								//����������ģʽ
    delay_ms(300);
    ESP8266_Set((u8*)"AT+CIPSERVER=1,5000");  					//����TCP/IP ʵ�ֻ�������//���� 	ESP8266_Set("AT+CIPSERVER=1,5000");
    delay_ms(500);
    ESP8266_Set((u8*)"AT+CIPSTO=0"); 
    delay_ms(500);	
}

#endif

#if CONFIG_MPU6050 == ENABLED

void I2C_Init1(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;	
	
	
	
	RCC_APB2PeriphClockCmd(RCC_GPIO, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
	
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

//������ʼ�ź�
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

//����ֹͣ�ź�
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

//��������Ӧ���ź�ACK
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

//����������Ӧ���ź�NACK
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
//�ȴ��ӻ�Ӧ���ź�
//����ֵ��1 ����Ӧ��ʧ��
//		  0 ����Ӧ��ɹ�
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
//I2C ����һ���ֽ�
void I2C_Send_Byte(u8 txd)
{
	u8 i=0;

	I2C_SDA_OUT();
	I2C_SCL_L;//����ʱ�ӿ�ʼ���ݴ���

	for(i=0;i<8;i++)
	{
		if((txd&0x80)>0) //0x80  1000 0000
			I2C_SDA_H;
		else
			I2C_SDA_L;

		txd<<=1;
		I2C_SCL_H;
		delay_us(2); //��������
		I2C_SCL_L;
		delay_us(2);
	}
}

//I2C ��ȡһ���ֽ�

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
	PMU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	     //�������״̬
	PMU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //�����ǲ�����
	PMU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	PMU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //���ü��ٶȴ�����������16Gģʽ
	PMU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	
	
	delay_ms(100);
//	MPU6050_PWR_MGMT_1_INIT();
	PMU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	     //�������״̬
	PMU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //�����ǲ�����
	PMU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	
	PMU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x01);	  //���ü��ٶȴ�����������16Gģʽ
	PMU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	
	
}

void MPU6050ReadID(void)
{
	unsigned char Re = 0;
    PMU6050_ReadData(MPU6050_RA_WHO_AM_I,&Re,1);    //��������ַ
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
    PMU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //��ȡ�¶�ֵ
    *tempData = (buf[0] << 8) | buf[1];
}

void MPU6050_ReturnTemp(short*Temperature)
{
	short temp3;
	u8 buf[2];
	
	PMU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //��ȡ�¶�ֵ
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

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE); 			//ʱ��ʹ��

	TIM_TimeBaseStructure.TIM_Period 		= Period-1; 			//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 	=Prescaler-1; 			//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 					//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up; 	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure); 			
 
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);   						//ʹ�ܻ���ʧ��ָ����TIM�ж�
	NVIC_InitStructure.NVIC_IRQChannel 					 = TIM2_IRQn;//TIM5�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//��ռ���ȼ�1��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority		 = 3;  		//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd 				 = ENABLE;	//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  								//����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  
	TIM_Cmd(TIM2, ENABLE);  										//ʹ��TIMx����							 
}

void TIM2_IRQHandler(void) 
{

   static unsigned char Time0_100ms_Counter = 0;	
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) 			//���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);				//���TIMx���жϴ�����λ:TIM �ж�Դ 
	  	TIM_ClearITPendingBit(TIM2, TIM_IT_Update  );  //���TIMx���жϴ�����λ:TIM �ж�Դ 

        if (UART3_RXD_Time)//20ms
        {
            if (--UART3_RXD_Time == 0) //���ڽ��ճ�ʱ
            {
                UART3_Status_Registe |= 1 << UART3_RXD_END;

            }
        }
        if (++Time0_100ms_Counter >= 5)//����ע��ļ��ʱ��
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
    UART3_Status_Registe &= ~(1 << UART3_RXD_END); //�����յ��������Ѿ�������
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

/*����3 �������ݵ���λ�� data ��\0��β*/
void gsmtxrx_usart3_SendString_Demo(unsigned char * data)
{
	u16 i=0;
	//printf("%s",data);
	while(data[i]!='\0')
	{
		USART_SendData(USART3, data[i]);         //�򴮿�2��������
		
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
		i++;
	}
	i++;
}
 /*����һ���ֽ�����*/
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
		

		UART3_RXD_Time = UART3_RXD_TIME;  //���ô��ڽ��ճ�ʱ

		UART3_RXD[UART3_RXD_Index] = a3;

		UART3_RXD_Index++;

		UART3_RXD_Index = UART3_RXD_Index % UART3_RXD_SIZE;	
		
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);        //
		while(USART_GetFlagStatus(USART3,USART_FLAG_TC) ==RESET);	  //
	}
}
void SMS_Init(void)
{
	  //�ı�ģʽ
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGF=1\r\n");
    delay_ms(200);

    //ֱ������Ϊ���Ź���ֱ����ʾ����
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //���ö�����ʾģʽ
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //���ö�����ʾģʽ
    delay_ms(200);
    gsmtxrx_usart3_SendString_Demo((u8*)"AT+CNMI=2,2,0,1\r\n");  //���ö�����ʾģʽ
    delay_ms(200);

}
void GPRS_CREG(void)
{
    
    if ((~GPRS_States_Registe) & (1 << GPRS_AT_CREG)) //û��ע��ɹ� ����ע��
    {
        if (GPRS_Time_Counter == 0)
        {

            SIM800_CMD_Register = 0;

            gsmtxrx_usart3_SendString_Demo((u8*)" AT&F\r\n"); //�ָ�����Ĭ������
            gsmtxrx_usart3_SendString_Demo((u8*)" ATE0\r\n"); //ȡ������ʾ
            gsmtxrx_usart3_SendString_Demo((u8*)" AT+CREG?\r\n");  //ģ��ע��
    
            SMS_Init();


            GPRS_Time_Counter = 100; //25s��ʱ
        }
        else
        {

            if (SIM800_CMD_Register & (1 << CMD_CREG)) //�յ�ģ�鷵������
            {
                GPRS_States_Registe |= (1 << GPRS_AT_CREG); //�յ�ģ��ظ�CREG��Ϣ
                SIM800_CMD_Register &= ~(1 << CMD_CREG); //��ձ�־
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
//AT+CNMI=2,2,0,1 �յ���������ֱ����ʾ����
//+CMT: "+8613403779870","","17/11/26,14:09:46+32"
//close

    if (hand("+CMT:")) //�յ��¶���
    {

        SMS_States_Register |= (1 << SMS_RXD_CMTI);


    }

    if (hand("+CMGR:")) //������������
    {

    }

    if (hand("+CMGS:"))  //���ŷ������
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


     //�������յ����ݣ�AT+CREG?
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
    //�޷����յ����ţ�AT+CREG?
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
        SMS_CMD_Register |= (1 << SMS_ERROR); //���մ���
        SIM800_CMD_Register |= (1 << CMD_ERROR);
    }
    if (hand("CONNECT OK"))
    {
        SIM800_CMD_Register |= (1 << CMD_CONNECT_OK);
    }
    if (hand("OPEN")) //��ȡ��������
    {

    }
    if (hand("CLOSE")) //��ȡ��������
    {
       // SIM800_CMD_Register |= (1 << CMD_CLOSE);

    }
    if (hand("DATA")) //��ȡ�������ݣ����յ����ݺ�Ҫ���ͣ���Ҫ��ʱ1�����Ҳŷ���
    {
			send_flag = 1;
      //Lcd1602_Display_String(1,5,(u8*)"DATA ");
    }		
    if (hand("SET"))  //�յ��¶���
    {


    }

    if (hand("RING") | hand("CRING")) //������
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

    if (UART3_Status_Registe & (1 << UART3_RXD_END)) //�յ���������
    {

        SIM800_CMD_Coding();//

        UART3_RXD_CLR();
        UART3_Status_Registe &= ~(1 << UART3_RXD_END);
    }


    if (SIM800_CMD_Register & (1 << CMD_RING))
    {

        //UART0_Send_String("ATH\r\n"); //ֱ�ӹҶ�

        //SMS_Retry = 5;
        SMS_States_Register |= (1 << SMS_TXD_ENA); //���Ͷ���
        SIM800_CMD_Register &= ~(1 << CMD_RING);
    }

}

void SMS_Send(u8* num,u8* data)
{
    static volatile unsigned char SMS_Step = 0;

    if (SMS_Retry == 0)
    {
        //�����������Դ���,���ٷ���
        SMS_States_Register &= ~(1 << SMS_TXD_ENA);
        return;
    }

    if (SMS_Time_Cnt) //��ʱʱ��
    {
        SMS_Time_Cnt--;
    }

    switch (SMS_Step)
    {

    case 0:
        SMS_CMD_Register = 0; //��ս���״̬

        gsmtxrx_usart3_SendString_Demo((u8*)" AT+CMGF=1\r\n"); //���ö���ģʽ
        SMS_Step++;
        SMS_Time_Cnt = 20; //1��
        if (SMS_Retry) SMS_Retry--; //���Դ���-1
        break;

    case 1:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //��ʱ��Ӧ��,����ָ�����
            SMS_Step = 0;
        }

        if (SMS_CMD_Register & (1 << SMS_RXD_OK))
        {

            SMS_CMD_Register = 0; //��ս���״̬

            gsmtxrx_usart3_SendString_Demo((u8*)"AT+CMGS=\""); //���ý��ն��ź���
            gsmtxrx_usart3_SendString_Demo(num);  //
            gsmtxrx_usart3_SendString_Demo((u8*)"\"\r\n");
            SMS_Step++;
            SMS_Time_Cnt = 60; //3��
        }

        break;

    case 2:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //��ʱ��Ӧ��,����ָ�����
            SMS_Step = 0;
            gsmtxrx_usart3_send_byte_Demo(0x1A);  //���ݽ���

        }

        if (SMS_CMD_Register & (1 << SMS_WaitData)) //�ȴ�<
        {

            SMS_CMD_Register = 0; //��ս���״̬

            gsmtxrx_usart3_SendString_Demo(data); //���Ͷ�������

            gsmtxrx_usart3_send_byte_Demo(0x1A);  //���ݽ���
            SMS_Step++;
            SMS_Time_Cnt = 180; //9.3��
        }
        break;

    case 3:
        if ((SMS_Time_Cnt == 0) || (SMS_CMD_Register & (1 << SMS_ERROR)))
        {
            //��ʱ��Ӧ��,����ָ�����
            SMS_Step = 0;
            gsmtxrx_usart3_send_byte_Demo(0x1A);  //���ݽ���
            if (SMS_Retry) SMS_Retry--; //���Դ���-1

        }

        if (SMS_CMD_Register & (1 << SMS_CMGS) || (SMS_CMD_Register & (1 << SMS_RXD_OK)))
        {
            //���ŷ��ͳɹ�
            SMS_States_Register &= ~(1 << SMS_TXD_ENA);


            SMS_CMD_Register = 0;
            SMS_Time_Cnt = 120; //6��
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
    //δע��ʱ�����ʱ���ѯע��
    GPRS_CREG();

		if ((GPRS_States_Registe) & (1 << GPRS_AT_CREG)) //ע��������������Ͷ���
		{
				if (SMS_States_Register & (1 << SMS_TXD_ENA)) //�ж�����Ҫ����
				{
					  //��������
						SMS_Send(num,data);
				}
		}
    
    //������յ�������
    UART3_Processing();

}
void gsm_txrx_init(void)
{
   GSMTXRX__USART3_ConfigDemo(9600);	
	 gsm_TIM2_Int_Init_demo(200, 7200);//20mw
}
#endif

#if CONFIG_ADXL345 == ENABLED


unsigned char BUF[8];                         //�������ݻ�����      	
unsigned char ge,shi,bai,qian,wan;           //��ʾ����
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
��ʼ�ź�
**************************************/
void ADXL345_Start(void)
{
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    SET_SDA_ADXL345();//SDA = 1;                    //����������
    SET_SCL_ADXL345();//SCL = 1;                    //����ʱ����
    delay_us(2);//Delay5us();                 //��ʱ
    CLE_SDA_ADXL345();//SDA = 0;                    //�����½���
    delay_us(2);//Delay5us();                 //��ʱ
    CLE_SCL_ADXL345();//SCL = 0;                    //����ʱ����
}

/**************************************
ֹͣ�ź�
**************************************/
void ADXL345_Stop(void)
{
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    CLE_SDA_ADXL345();//SDA = 0;                    //����������
    SET_SCL_ADXL345();//SCL = 1;                    //����ʱ����
    delay_us(2);//Delay5us();                 //��ʱ
    SET_SDA_ADXL345();//SDA = 1;                    //����������
    delay_us(2);//Delay5us();                 //��ʱ
    CLE_SCL_ADXL345();
}

/**************************************
����Ӧ���ź�
��ڲ���:ack (0:ACK 1:NAK)
**************************************/
void ADXL345_SendACK(unsigned char ack)
{   
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    if(ack==0)//SDA = ack;                  //дӦ���ź�
    {
      CLE_SDA_ADXL345();
    }
    else
    {
      SET_SDA_ADXL345();
    }
    SET_SCL_ADXL345();//SCL = 1;                    //����ʱ����
    delay_us(2);//Delay5us();                 //��ʱ
    CLE_SCL_ADXL345();//SCL = 0;                    //����ʱ����
    delay_us(5);//Delay5us();                 //��ʱ
}

/**************************************
����Ӧ���ź�
**************************************/
unsigned char ADXL345_RecvACK(void)
{
    SDA_INT_ADXL345();
    SCL_OUT_ADXL345();
    SET_SCL_ADXL345();//SCL = 1;                    //����ʱ����
    delay_us(2);//    Delay5us();                 //��ʱ
    SET_SCL_ADXL345();
    if(SDA_VAL_ADXL345()== Bit_SET)   //CY = SDA;                   //��Ӧ���ź�
    {
      err = 1;
    }
    else
    {
      err = 0;
    }
 
    CLE_SCL_ADXL345() ;//SCL = 0;                    //����ʱ����
    delay_us(5);//    Delay5us();                 //��ʱ
    SDA_OUT_ADXL345();
    return err;
}

/**************************************
��IIC���߷���һ���ֽ�����
**************************************/
void ADXL345_SendByte(unsigned char dat)
{
    unsigned char i;
    SCL_OUT_ADXL345();
    SDA_OUT_ADXL345();
    for (i=0; i<8; i++)         //8λ������
    {
        delay_us(5);             //��ʱ
        if(dat&0x80)  //SDA = CY;               //�����ݿ�
        {SET_SDA_ADXL345();}
        else
        {CLE_SDA_ADXL345();}       
        delay_us(5);             //��ʱ
        SET_SCL_ADXL345();//SCL = 1;                //����ʱ����
        delay_us(5);             //��ʱ
        CLE_SCL_ADXL345();//SCL = 0;                //����ʱ����
        dat <<= 1;              //�Ƴ����ݵ����λ
    }
    ADXL345_RecvACK();
}

/**************************************
��IIC���߽���һ���ֽ�����
**************************************/
unsigned char ADXL345_RecvByte(void)
{
    unsigned char i;
    unsigned char Mid;
    unsigned char dat = 0;
    SDA_INT_ADXL345();
    SCL_OUT_ADXL345();

    for (i=0; i<8; i++)         //8λ������
    {
        dat <<= 1;
        delay_us(5);            //��ʱ
        SET_SCL_ADXL345();

			if(SDA_VAL_ADXL345()== Bit_SET)   //CY = SDA;                   //��Ӧ���ź�
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
        CLE_SCL_ADXL345();//SCL = 0;                //����ʱ����
    }
    return dat;
}

//******���ֽ�д��*******************************************

void Single_Write_ADXL345(unsigned char REG_Address,unsigned char REG_data)
{
    ADXL345_Start();                  //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
    ADXL345_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ����ο�����pdf22ҳ 
    ADXL345_SendByte(REG_data);       //�ڲ��Ĵ������ݣ���ο�����pdf22ҳ 
    ADXL345_Stop();                   //����ֹͣ�ź�
}

//********���ֽڶ�ȡ*****************************************
unsigned char Single_Read_ADXL345(unsigned char REG_Address)
{  unsigned char REG_data;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_SendByte(REG_Address);            //���ʹ洢��Ԫ��ַ����0��ʼ	
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
    REG_data=ADXL345_RecvByte();              //�����Ĵ�������
	ADXL345_SendACK(1);   
	ADXL345_Stop();                           //ֹͣ�ź�
    return REG_data; 
}
//*********************************************************
//
//��������ADXL345�ڲ����ٶ����ݣ���ַ��Χ0x32~0x37
//
//*********************************************************
void Multiple_Read_ADXL345(void)
{   unsigned char i;
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress);           //�����豸��ַ+д�ź�
    ADXL345_SendByte(0x32);                   //���ʹ洢��Ԫ��ַ����0x32��ʼ	
    ADXL345_Start();                          //��ʼ�ź�
    ADXL345_SendByte(SlaveAddress+1);         //�����豸��ַ+���ź�
	 for (i=0; i<6; i++)                      //������ȡ6����ַ���ݣ��洢��BUF
    {
        BUF[i] = ADXL345_RecvByte();          //BUF[0]�洢0x32��ַ�е�����
        if (i == 5)
        {
           ADXL345_SendACK(1);                //���һ��������Ҫ��NOACK
        }
        else
        {
          ADXL345_SendACK(0);                //��ӦACK
       }
   }
    ADXL345_Stop();                          //ֹͣ�ź�
    delay_ms(5);
}


//*****************************************************************

//��ʼ��ADXL345��������Ҫ��ο�pdf�����޸�************************
void Init_ADXL345(void)
{
   Single_Write_ADXL345(0x31,0x0B);   //������Χ,����16g��13λģʽ
   Single_Write_ADXL345(0x2C,0x08);   //�����趨Ϊ12.5 �ο�pdf13ҳ
   Single_Write_ADXL345(0x2D,0x08);   //ѡ���Դģʽ   �ο�pdf24ҳ
   Single_Write_ADXL345(0x2E,0x80);   //ʹ�� DATA_READY �ж�
   Single_Write_ADXL345(0x1E,0x00);   //X ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
   Single_Write_ADXL345(0x1F,0x00);   //Y ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
   Single_Write_ADXL345(0x20,0x05);   //Z ƫ���� ���ݲ��Դ�������״̬д��pdf29ҳ
}
//***********************************************************************
//��ʾx��
void ReadData_x(void)
{   
  int  dis_data;                       //����
  Multiple_Read_ADXL345();       	//�����������ݣ��洢��BUF��
  dis_data=(BUF[1]<<8)+BUF[0];  //�ϳ�����   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_X=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
  dis_data=(BUF[3]<<8)+BUF[2];  //�ϳ�����   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_Y=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
  dis_data=(BUF[5]<<8)+BUF[4];    //�ϳ�����   
//  if(dis_data<0)
//  {
//    dis_data=-dis_data;
//  }
  temp_Z=(float)dis_data*3.9;  //�������ݺ���ʾ,�鿼ADXL345�������ŵ�4ҳ
}

#endif

