#ifndef __LCD1602_H
#define __LCD1602_H
#include "delay.h"
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
/*-----------------------------------------------
  名称：LCD1602
  论坛：www.doflye.net
  编写：shifang
  日期：2009.5
  修改：无
  内容：通过标准程序静态显示字符
  引脚定义如下：1-VSS 2-VDD 3-V0 4-RS 5-R/W 6-E 7-14 DB0-DB7 15-BLA 16-BLK
------------------------------------------------*/


// D0  D1 D2 D3 D4 D5 D6 D7 E   RW RS
// A15 B3 B4 B5 B6 B7 B8 B9 A12    A11
#define RS                  PAout(11) //PB11                             
#define RW									PAout(10) //PB10	
#define EN                  PAout(12)  //PB1 

#define D0                  PAout(15) //PB0 
#define D1                  PBout(3)//PC15 
#define D2                  PBout(4)//PC14 
#define D3                  PBout(5)//PC13 
#define D4                  PBout(6) //PB0 
#define D5                  PBout(7)//PC15 
#define D6                  PBout(8)//PC14 
#define D7                  PBout(9)//PC13 
 
 
#define LCD1602_CLK  RCC_APB2Periph_GPIOA  

#define LCD1602_GPIO_PORT   GPIOA

#define LCD1602_E    GPIO_Pin_12              //定义使能引脚
//#define LCD1602_RW   GPIO_Pin_13             //定义读写引脚
#define LCD1602_RS   GPIO_Pin_11             //定义数据、命名引脚



 

void LCD1602_Init(void);  //初始化LCD602；

void LCD1602_WriteCmd(unsigned char cmd);

void LCD1602_ShowStr(uint8_t x, uint8_t y, uint8_t *str);

 void LCD_Clear(void); 
 
 void  LCD_Check_Busy(void); 
 
 void LCD_Write_Com(unsigned char com); 
 
 void LCD_Write_Data(unsigned char Data); 
 
 void LCD_Write_String(unsigned char x,unsigned char y,unsigned char *s);
	
 void LCD_Write_Char(unsigned char x,unsigned char y,unsigned char Data); 

 void LCD1602_write_long(unsigned char x,unsigned char y,u32 data,unsigned char num) ;
 
 void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date);
 void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p);
 void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date);
 /*demo
 
 int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	 // GPIO_TEST();
		//LCD_Init(); 
  	LCD1602_Init();
	  delay_ms(500);
		Lcd1602_Display_Two_bit(0,0,1);
	  Lcd1602_Display_Two_bit(1,0,1);
	
    while(1)
    {
			//LED0 = ~LED0;
			//LED1 = ~LED1;
			//LED2 = ~LED2;
			Lcd1602_Display_String(0,5,"HELLO");
			//LCD1602_ShowStr(0,16, "hello");
			delay_ms(1000);
    }
}

 
 */
#endif



