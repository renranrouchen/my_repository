

#ifndef _ADC_H
#define _ADC_H





 
#define Channel_Num  4			//
#define Sample_Num  10			//
 
extern vu16 ADC_ConvertedValue[Sample_Num][Channel_Num];
 
void ADC1_Config(void);
uint16_t ReadADCAverageValue(uint16_t Channel);
 
 





/*DEMO


volatile u16 PH0_Value = 0;
volatile u16 PH1_Value = 0;
volatile u16 PH2_Value = 0;
int main(void)
{
    delay_init();	    		//—” ±∫Ø ˝≥ı ºªØ
    NVIC_Configuration();
	 // GPIO_TEST();
	  delay_ms(500);
		//ADC1_Init();
	  ADC1_Config();
		OLED_Init3();
	

		OLED_ShowStr_ENCH(0,0,(unsigned char *)"01ª∂”≠ π”√√‹¬Î",1);
		//OLED_ShowStr_ENCH(0,16,(unsigned char *)" 02ª∂”≠",1);
		//OLED_ShowStr_ENCH(0,32,(unsigned char *)"  03ª∂”≠",1);
		//OLED_ShowStr_ENCH(0,48,(unsigned char *)"   04ª∂”≠",1);
	  //OLED_ShowNum(16,48,3,1,16);
		OLED_Refresh_Gram();	
    while(1)
    {
			PH0_Value = ReadADCAverageValue(0);
			PH1_Value = ReadADCAverageValue(1);
			PH2_Value = ReadADCAverageValue(2);
			OLED_ShowNum(0,16,PH0_Value,4,16);
			OLED_ShowNum(0,32,PH1_Value,4,16);
			OLED_ShowNum(0,48,PH2_Value,4,16);
			OLED_Refresh_Gram();	
			//LED0 = ~LED0;
			//LED1 = ~LED1;
			//LED2 = ~LED2;
			//Lcd1602_Display_String(0,5,"HELLO");
			//LCD1602_ShowStr(0,16, "hello");
			delay_ms(1000);
    }
}

*/





#endif


