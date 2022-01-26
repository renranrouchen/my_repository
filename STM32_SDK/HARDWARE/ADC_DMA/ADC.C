
#include "sys.h"
#include "ADC.H"
#include "stm32f10x_adc.h"





 
 
//内存中存储转换结果
vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];
 
 
//DMA??:ADC1->CR --> ADC_ConvertedValue
void ADC_DMA_Config(void)
{
	 DMA_InitTypeDef DMA_InitStructure;
				   
	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	 DMA_DeInit(DMA1_Channel1);												//DMA的通道1寄存器设为缺省值
	 DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;		//DMA外设ADC基地址
	 DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&ADC_ConvertedValue;		//DMA内存基地址
	 DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;						//内存作为数据传输的目的地
	 DMA_InitStructure.DMA_BufferSize = Sample_Num*Channel_Num;				//DMA通道的DMA缓存大小
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
 
 
void ADC1_Config(void)
{
	 GPIO_InitTypeDef GPIO_InitStructure;
	 ADC_InitTypeDef ADC_InitStructure;
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	   
	//PA0 通道0 PA1 通道1 PA2 通道2
	 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;		
	 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;			//模拟输入
	 GPIO_Init(GPIOA, &GPIO_InitStructure);
	 ADC_DMA_Config();
	   
	 RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	 RCC_ADCCLKConfig(RCC_PCLK2_Div6); 		//设置ADC分频因子6 72M/6=12M，ADC最大时间不能超过14M
	
	// ADC_DeInit(ADC1);
	 ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;						//ADC1和ADC2工作在独立模式
	 ADC_InitStructure.ADC_ScanConvMode = ENABLE;							//多通道
	 ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;						//连续转换
	 ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//软件启动转换
	 ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;					//转换结果右对齐
	 ADC_InitStructure.ADC_NbrOfChannel = Channel_Num;						//通道数
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
 
 
uint16_t ReadADCAverageValue(uint16_t Channel)
{
	uint8_t i;
	uint32_t sum = 0;
	for(i=0; i<Sample_Num; i++)
	{
		sum+=ADC_ConvertedValue[i][Channel];		//
	}
	return (sum/Sample_Num);
}





