#ifndef __DS1302_H
#define __DS1302_H
#include "sys.h"

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

void DS1302_Init(void);
void DS1302_Write_Byte(u8 addr, u8 data);
u8 DS1302_Read_Byte(u8 addr);
void DS1302_Write_Time(void);
void DS1302_Read_Time(void);
void DS1302_Get_Time(u8 *time);
void Ds1302_Read_Time(unsigned char *arry);
void Ds1302_Save(unsigned char  po, unsigned char  dat);

/**demo

unsigned char arry[7];
int main(void)
{
    delay_init();	    		//延时函数初始化
    NVIC_Configuration();
	  delay_ms(500);

    LCD1602_Init();
	  Lcd1602_Display_Two_bit(0,0,1);
	  DS1302_Init( );
    while(1)
    {
			Ds1302_Read_Time(arry);
			Lcd1602_Display_Two_bit(0,0,arry[0]);
			Lcd1602_Display_Two_bit(0,3,arry[1]);
			Lcd1602_Display_Two_bit(0,6,arry[2]);
			Lcd1602_Display_Two_bit(0,9,arry[3]);
			Lcd1602_Display_Two_bit(1,0,arry[4]);
			Lcd1602_Display_Two_bit(1,3,arry[5]);		
			Lcd1602_Display_Two_bit(1,6,arry[5]);
			delay_ms(200);
    }
}

**/
#endif
