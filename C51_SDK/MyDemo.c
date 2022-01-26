
#include "MyConfig.h"
#include "MyDemo.h"
#include <intrins.h>


#if CONFIG_UTRL == ENABLED

void DelayMs_utrl(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}

#endif
/*********************LCD1602*********************/
#if CONFIG_LCD1602 == ENABLED

void Lcd1602_Demo_write_com(unsigned char com);
void Lcd1602_Demo_write_data(unsigned char dat);


/********************************************************************
* 名称 : delay_uint()
* 功能 : 小延时。
* 输入 : 无
* 输出 : 无
***********************************************************************/
void Lcd1602_delay_uint(unsigned int q)
{
	while(q--);
}

/********************************************************************
* 名称 : write_com(uchar com)
* 功能 : 1602命令函数
* 输入 : 输入的命令值
* 输出 : 无
***********************************************************************/
void Lcd1602_write_com(unsigned char com)
{
	Lcd1602_e=0;
	Lcd1602_rs=0;
	Lcd1602_rw=0;
	P0=com;
	Lcd1602_delay_uint(3);
	Lcd1602_e=1;
	Lcd1602_delay_uint(25);
	Lcd1602_e=0;
}

/********************************************************************
* 名称 : write_data(uchar dat)
* 功能 : 1602写数据函数
* 输入 : 需要写入1602的数据
* 输出 : 无
***********************************************************************/
void Lcd1602_write_data(unsigned char dat)
{
	Lcd1602_e=0;
	Lcd1602_rs=1;
	Lcd1602_rw=0;
	P0=dat;
	Lcd1602_delay_uint(3);
	Lcd1602_e=1;
	Lcd1602_delay_uint(25);
	Lcd1602_e=0;	
}

void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	Lcd1602_Demo_write_data(0x30+date/10%10);
	Lcd1602_Demo_write_data(0x30+date%10);	
}

void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	Lcd1602_Demo_write_data(0x30+date/100%10);
	Lcd1602_Demo_write_data(0x30+date/10%10);
	Lcd1602_Demo_write_data(0x30+date%10);	
}

void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
		while(1)
		{
			if(*p == '\0')  break;
			Lcd1602_Demo_write_data(*p);
			p++;
		}	
}


/*****************控制光标函数********************/
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date)
{		
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	if(date == 1)
		Lcd1602_Demo_write_com(0x0f);     //显示光标并且闪烁	
	else 
		Lcd1602_Demo_write_com(0x0c);   //关闭光标
}

void Lcd1602_Display_Init()
{
	Lcd1602_Demo_write_com(0x38);
	Lcd1602_Demo_write_com(0x38);
	Lcd1602_Demo_write_com(0x0c);
	Lcd1602_Demo_write_com(0x06);
}
#if CONFIG_DS1302 == ENABLED
/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add); 
	
	Lcd1602_Demo_write_data(yue%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(yue%10+0x30);				// 个位
	Lcd1602_Demo_write_data('-');
	Lcd1602_Demo_write_data(ri%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(ri%10+0x30);				// 个位
	Lcd1602_Demo_write_data(' ');	
	Lcd1602_Demo_write_data(shi%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(shi%10+0x30);				// 个位
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(fen%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(fen%10+0x30);				// 个位
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(miao%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(miao%10+0x30);				// 个位

}

/*********************************************************/
// 液晶输出数字
/*********************************************************/
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add); 
	

	Lcd1602_Demo_write_data(shi%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(shi%10+0x30);				// 个位
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(fen%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(fen%10+0x30);				// 个位
	Lcd1602_Demo_write_data(':');
	Lcd1602_Demo_write_data(miao%100/10+0x30);		// 十位
	Lcd1602_Demo_write_data(miao%10+0x30);				// 个位

}
#endif
#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date)
{
	if(hang==0)   
		Lcd1602_Demo_write_com(0x80+add);
	else
		Lcd1602_Demo_write_com(0x80+0x40+add);
	Lcd1602_Demo_write_data(0x30+date/100%10);
	Lcd1602_Demo_write_data(0x30+date/10%10);
	Lcd1602_Demo_write_data('.');
	Lcd1602_Demo_write_data(0x30+date%10);	
}
#endif
#endif

/********************独立按键程序*****************/
#if CONFIG_KEY == ENABLED


void Key_value_Demo(pKey_Process key_Process)	 //独立按键程序
{
	unsigned char Key_value;
#if KEY_COUNT == 1
	if((Demo_KEY1 == 0))
	{
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



#endif


/*********************ADC0832********************/
#if CONFIG_ADC0832 == ENABLED

  

unsigned char ADC0832_Demo(bit mode,bit channel)    //AD转换，返回结果
{
	unsigned char i,dat,ndat;
	
	ADCS = 0;//拉低CS端
	_nop_();
	_nop_();
	
	ADDI = 1;	//第1个下降沿为高电平
	ADCLK = 1;//拉高CLK端
	_nop_();
	_nop_();
	ADCLK = 0;//拉低CLK端,形成下降沿1
	_nop_();
	_nop_();
	
	ADDI = mode;	//低电平为差分模式，高电平为单通道模式。	
	ADCLK = 1;//拉高CLK端
	_nop_();
	_nop_();
	ADCLK = 0;//拉低CLK端,形成下降沿2
	_nop_();
	_nop_();
	
	ADDI = channel;	//低电平为CH0，高电平为CH1	
	ADCLK = 1;//拉高CLK端
	_nop_();
	_nop_();
	ADCLK = 0;//拉低CLK端,形成下降沿3
	
	ADDI = 1;//控制命令结束(经试验必需)
	dat = 0;
	//下面开始读取转换后的数据，从最高位开始依次输出（D7~D0）
	for(i = 0;i < 8;i++)
	{
		dat <<= 1;
		ADCLK=1;//拉高时钟端
		_nop_();
		_nop_();
		ADCLK=0;//拉低时钟端形成一次时钟脉冲
		_nop_();
		_nop_();
		dat |= ADDO;
	}
	ndat = 0; 	   //记录D0
	if(ADDO == 1)
	ndat |= 0x80;
	//下面开始继续读取反序的数据（从D1到D7） 
	for(i = 0;i < 7;i++)
	{
		ndat >>= 1;
		ADCLK = 1;//拉高时钟端
		_nop_();
		_nop_();
		ADCLK=0;//拉低时钟端形成一次时钟脉冲
		_nop_();
		_nop_();
		if(ADDO==1)
		ndat |= 0x80;
	}	  
	ADCS=1;//拉高CS端,结束转换
	ADCLK=0;//拉低CLK端
	ADDI=1;//拉高数据端,回到初始状态
	if(dat==ndat)
	return(dat);
	else
	return 0;   
}

#endif

/*********************DS1302********************/
#if CONFIG_DS1302 == ENABLED

/******************
	ds1302 内部RAM   RAM0  1100 000R/W   1读 0写
					 RAM1  1100 001R/W  
					       ....... 
					 RAM30 1111 110R/W   
********************/

unsigned char code Ds1302_write_add[]={0x80,0x82,0x84,0x86,0x88,0x8c,0x8a};   //写地址
unsigned char code Ds1302_read_add[] ={0x81,0x83,0x85,0x87,0x89,0x8d,0x8b};   //读地址
unsigned char code Ds1302_init_ds[]  ={0x58,0x29,0x07,0x05,0x10,0x14,0x1}; 

void DelayMs_Ds1302(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}

/*************写一个数据到对应的地址里***************/
void Ds1302_Write_Demo(unsigned char add,unsigned char dat)
{
	unsigned char i;
	rst = 1;			 //把复位线拿高
	for(i=0;i<8;i++)
	{				     //低位在前

		io = add & 0x01;    	
		add >>= 1;		 //把地址右移一位
		clk = 1;		 //时钟线拿高	 
		clk = 0;		 //时钟线拿低开始写数据
	}									 
	for(i=0;i<8;i++)
	{

		io = dat & 0x01;
		dat >>= 1;		 //把数据右移一位	
		clk = 1;		 //时钟线拿高
		clk = 0;		 //时钟线拿低开始写数据
	}
	rst = 0;			 //复位线合低
}


/*************从对应的地址读一个数据出来***************/
unsigned char Ds1302_Read_Demo(unsigned char add)
{
	unsigned char value,i;
	rst = 1;			 //把复位线拿高
	for(i=0;i<8;i++)
	{				     //低位在前
		clk = 0;		 //时钟线拿低开始写数据
		io = add & 0x01;    	
		add >>= 1;		 //把地址右移一位
		clk = 1;		 //时钟线拿高
	}		
	for(i=0;i<8;i++)
	{
		clk = 1;		 //时钟线拿高
		clk = 0;		 //时钟线拿低开始读数据
		value >>= 1;
		if(io == 1)
			value |= 0x80;
	}
	rst = 0;			 //复位线合低
	clk = 0;
	io = 0;
	return value;		 //返回读出来的数据
}

unsigned char BCD_Decimal(unsigned char bcd)//BCD码转十进制函数，输入BCD，返回十进制
{
	 unsigned char Decimal;
	 Decimal=bcd>>4;
	 return(Decimal=Decimal*10+(bcd&=0x0F));
}

/*************把要的时间 年月日 都读出来***************/
//arry[7]
void Ds1302_Read_Time(unsigned char *arry)
{
	*arry      = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[0]));	//读秒
	*(arry+1)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[1]));	//读分
	*(arry+2)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[2]));	//读时
	*(arry+3)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[3]));	//读日
	*(arry+4)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[4]));	//读月
	*(arry+5)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[5]));	//读年
	*(arry+6)  = BCD_Decimal(Ds1302_Read_Demo(Ds1302_read_add[6]));	//读星期
}

void Ds1302_Save(unsigned char  po, unsigned char  dat)
{
	unsigned char  temp;
	temp=(dat)/10*16+(dat)%10;//十进制转换成DS1302要求的DCB码
	Ds1302_Write_Demo(0x8e,0x00);//允许写，禁止写保护 
	Ds1302_Write_Demo(po,temp);//向DS1302内写分寄存器82H写入调整后的分数据BCD码
	Ds1302_Write_Demo(0x8e,0x80);//打开写保护	
}

/*************把要写的时间 年月日 都写入ds1302里***************/
void Ds1302_Write_Time(unsigned char *arry)
{
	Ds1302_Write_Demo(0x8e,0x00);			//打开写保护

	Ds1302_Write_Demo(Ds1302_write_add[0],0x80);	

	Ds1302_Write_Demo(Ds1302_write_add[0],arry[0]);	//写秒
	Ds1302_Write_Demo(Ds1302_write_add[1],arry[1]);		//写分
	Ds1302_Write_Demo(Ds1302_write_add[2],arry[2]);		//写时
	Ds1302_Write_Demo(Ds1302_write_add[3],arry[3]);		//写日
	Ds1302_Write_Demo(Ds1302_write_add[4],arry[4]);		//写月
	Ds1302_Write_Demo(Ds1302_write_add[5],arry[5]);	//写星期
	Ds1302_Write_Demo(Ds1302_write_add[6],arry[6]);	//写年
	Ds1302_Write_Demo(0x8e,0x80);			//关闭写保护
}

/*************把数据保存到ds1302 RAM中**0-31*************/
void Ds1302_Write_ram(unsigned char add,unsigned char dat)
{
	add <<= 1;     //地址是从第二位开始的
	add &= 0xfe;   //把最低位清零  是写的命令
	add |= 0xc0;   //地址最高两位为 1  
	Ds1302_Write_Demo(0x8e,0x00);
	Ds1302_Write_Demo(add,dat);	
	Ds1302_Write_Demo(0x8e,0x80);
}


/*************把数据从ds1302 RAM读出来**0-31*************/
unsigned char Ds1302_Read_ds1302ram(unsigned char add)
{
	add <<= 1;     //地址是从第二位开始的
	add |= 0x01;   //把最高位置1  是读命令
	add |= 0xc0;   //地址最高两位为 1  
	return(Ds1302_Read_Demo(add));	
}

/**********************设置ds1302时间函数**********************/
void Ds1302_Set_time(unsigned char num,unsigned char *shi,unsigned char dat)	 //调时
{
  	if(num == 1)
    {
    	*shi+=0x01;
		if((*shi & 0x0f) >= 0x0a)
			*shi = (*shi & 0xf0) + 0x10;
		if(*shi >= dat)
			*shi = 0;
    }
    else
    {
		if(*shi == 0x00)
			*shi = dat;
		if((*shi & 0x0f) == 0x00)
			*shi = (*shi | 0x0a) - 0x10;
		*shi -=0x01 ; 
    }  
}

/*************初始化ds1302时间***************/
void Ds1302_Init()
{
	unsigned char i;
	rst = 0;	//第一次读写数据时要把IO品拿低
	clk = 0;
	io = 0;
	i = Ds1302_Read_ds1302ram(30);   
	if(i != 3)
	{	
		i = 3;
		Ds1302_Write_ram(30,i);			 //4050   4100		 3080

		Ds1302_Write_Demo(0x8e,0x00);	            //打开写保护
		for(i=0;i<7;i++)
			Ds1302_Write_Demo(Ds1302_write_add[i],Ds1302_init_ds[i]);	//把最高位值0 允许ds1302工作
		Ds1302_Write_Demo(0x8e,0x80);	//关写保护
	}

	//read_time();		  //读时间
	//if(miao >= 0x60)
	{
		Ds1302_Write_Demo(0x8e,0x00);	            //打开写保护
		Ds1302_Write_Demo(Ds1302_write_add[0],0x01);	//把最高位值0 允许ds1302工作
		Ds1302_Write_Demo(0x8e,0x80);	//关写保护
		
	}

}

/*demo
uchar arry[7];
Ds1302_Read_Time(arry);
*/
#endif

/*********************DS18b02********************/
#if CONFIG_DS18b02 == ENABLED
/***********************18b20初始化函数*****************************/

/********************************************************************
* 名称 : delay_uint()
* 功能 : 小延时。
* 输入 : 无
* 输出 : 无
***********************************************************************/


void delay_18B20(unsigned int q)
{
	while(q--);
}

void Ds18b02_Init()
{
	bit q;
	dq = 1;				//把总线拿高
	delay_18B20(1);	    //15us
	dq = 0;				//给复位脉冲
	delay_18B20(80);		//750us
	dq = 1;				//把总线拿高 等待
	delay_18B20(10);		//110us
	q = dq;				//读取18b20初始化信号
	delay_18B20(20);		//200us
	dq = 1;				//把总线拿高 释放总线
}

/*************写18b20内的数据***************/
void DS18b20_Write(unsigned char dat)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{					 //写数据是低位开始
		dq = 0;			 //把总线拿低写时间隙开始 
		dq = dat & 0x01; //向18b20总线写数据了
		delay_18B20(5);	 // 60us
		dq = 1;			 //释放总线
		dat >>= 1;
	}	
}

/*************读取18b20内的数据***************/
unsigned char Ds18b20_Read()
{
	unsigned char i,value;
	for(i=0;i<8;i++)
	{
		dq = 0;			 //把总线拿低读时间隙开始 
		value >>= 1;	 //读数据是低位开始
		dq = 1;			 //释放总线
		if(dq == 1)		 //开始读写数据 
			value |= 0x80;
		delay_18B20(5);	 //60us	读一个时间隙最少要保持60us的时间
	}
	return value;		 //返回数据
}

/*************读取温度的值 值为3位数，第三位为小数***************/
unsigned int Ds18b20_Read_temp()
{
	unsigned int value;
	unsigned char low;			   //在读取温度的时候如果中断的太频繁了，就应该把中断给关了，否则会影响到18b20的时序
	float tt=0;
	Ds18b02_Init();		   //初始化18b20
	DS18b20_Write(0xcc);	   //跳过64位ROM
	DS18b20_Write(0x44);	   //启动一次温度转换命令

	Ds18b02_Init();		   //初始化18b20
	
	DS18b20_Write(0xcc);	   //跳过64位ROM
	DS18b20_Write(0xbe);	   //发出读取暂存器命令
	
	low = Ds18b20_Read();	   //读温度低字节
	value = Ds18b20_Read();  //读温度高字节
	value <<= 8;		   //把温度的高位左移8位
	value |= low;		   //把读出的温度低位放到value的低八位中
	tt =value * 0.0625;	       //转换到温度值 
  value= tt*10+0.5;     //放大10倍输出并四舍五入	
	return value;		   //返回读出的温度 
}

#endif


/*********************EEPROM********************/
#if CONFIG_EEPROM == ENABLED

/********STC89C51扇区分布*******
第一扇区：1000H--11FF
第二扇区：1200H--13FF
第三扇区：1400H--15FF
第四扇区：1600H--17FF
第五扇区：1800H--19FF
第六扇区：1A00H--1BFF
第七扇区：1C00H--1DFF
第八扇区：1E00H--1FFF
*****************/

/********STC89C52扇区分布*******
第一扇区：2000H--21FF
第二扇区：2200H--23FF
第三扇区：2400H--25FF
第四扇区：2600H--27FF
第五扇区：2800H--29FF
第六扇区：2A00H--2BFF
第七扇区：2C00H--2DFF
第八扇区：2E00H--2FFF
*****************/


#define RdCommand 0x01 //定义ISP的操作命令
#define PrgCommand 0x02
#define EraseCommand 0x03 
#define Error 1
#define Ok 0
#define WaitTime 0x01 //定义CPU的等待时间
sfr ISP_DATA=0xe2;  //寄存器申明
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;


	

/* ================ 打开 ISP,IAP 功能 ================= */
void ISP_IAP_enable_Demo(void)
{
	 EA = 0;       /* 关中断   */
	 ISP_CONTR = ISP_CONTR & 0x18;       /* 0001,1000 */
	 ISP_CONTR = ISP_CONTR | WaitTime; /* 写入硬件延时 */
	 ISP_CONTR = ISP_CONTR | 0x80;       /* ISPEN=1  */
}
/* =============== 关闭 ISP,IAP 功能 ================== */
void ISP_IAP_disable_Demo(void)
{
	 ISP_CONTR = ISP_CONTR & 0x7f; /* ISPEN = 0 */
	 ISP_TRIG = 0x00;
	 EA   =   1;   /* 开中断 */
}
/* ================ 公用的触发代码 ==================== */
void ISPgoon_Demo(void)
{
	 ISP_IAP_enable_Demo();   /* 打开 ISP,IAP 功能 */
	 ISP_TRIG = 0x46;  /* 触发ISP_IAP命令字节1 */
	 ISP_TRIG = 0xb9;  /* 触发ISP_IAP命令字节2 */
	 _nop_();
}
/* ==================== 字节读 ======================== */
unsigned char byte_read_Demo(unsigned int byte_addr)
{
	EA = 0;
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);/* 地址赋值 */
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	 ISP_CMD   = ISP_CMD & 0xf8;   /* 清除低3位  */
	 ISP_CMD   = ISP_CMD | RdCommand; /* 写入读命令 */
	 ISPgoon_Demo();       /* 触发执行  */
	 ISP_IAP_disable_Demo();    /* 关闭ISP,IAP功能 */
	 EA  = 1;
	 return (ISP_DATA);    /* 返回读到的数据 */
}
/* ================== 扇区擦除 ======================== */
void SectorErase_Demo(unsigned int sector_addr)
{
	 unsigned int iSectorAddr;
	 iSectorAddr = (sector_addr & 0xfe00); /* 取扇区地址 */
	 ISP_ADDRH = (unsigned char)(iSectorAddr >> 8);
	 ISP_ADDRL = 0x00;
	 ISP_CMD = ISP_CMD & 0xf8;   /* 清空低3位  */
	 ISP_CMD = ISP_CMD | EraseCommand; /* 擦除命令3  */
	 ISPgoon_Demo();       /* 触发执行  */
	 ISP_IAP_disable_Demo();    /* 关闭ISP,IAP功能 */
}
/* ==================== 字节写 ======================== */
void byte_write_Demo(unsigned int byte_addr, unsigned char original_data)
{
	 EA  = 0;
//	 SectorErase(byte_addr);
	 ISP_ADDRH = (unsigned char)(byte_addr >> 8);  /* 取地址  */
	 ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	 ISP_CMD  = ISP_CMD & 0xf8;    /* 清低3位 */
	 ISP_CMD  = ISP_CMD | PrgCommand;  /* 写命令2 */
	 ISP_DATA = original_data;   /* 写入数据准备 */
	 ISPgoon_Demo();       /* 触发执行  */
	 ISP_IAP_disable_Demo();     /* 关闭IAP功能 */
	 EA =1;
}
#endif


/*********************24C02********************/
#if CONFIG_24C02 == ENABLED

/*********************************
      BASE  DRIVE
**********************************/
void DELAY_24C02_Demo(unsigned int t)
{
	while(t!=0)
	t--;
}

/******************************
      IIC  DRIVE
******************************/
void IICStart_24C02_Demo(void)
{
     SCL=0;  
 	 DELAY_24C02_Demo(1);
     SDA=1; SCL=1; DELAY_24C02_Demo(1);
     SDA=0; DELAY_24C02_Demo(1);
     SCL=0; 
}

void IICStop_24C02_Demo(void)
{
	 SDA=0;SCL=1; DELAY_24C02_Demo(1);
     SDA=1; DELAY_24C02_Demo(1);
     SCL=0; 	
}
void SEND0_24C02_Demo(void)
{
	SDA=0;
	SCL=1;
	DELAY_24C02_Demo(1);
	SCL=0;
}

void SEND1_24C02_Demo(void)
{
	SDA=1;
	DELAY_24C02_Demo(1);
	SCL=1;
	DELAY_24C02_Demo(1);
	SCL=0;
}

bit Check_Ack_24C02_Demo(void)
{
   unsigned char errtime=250;
   DELAY_24C02_Demo(1);
   SCL=1; 
   DELAY_24C02_Demo(1);
   CY=SDA;
   while(CY)
   {
    errtime--; 
    CY=SDA;
    if (!errtime)
     {
     IICStop_24C02_Demo();
    
     return 1;
     }
}
 DELAY_24C02_Demo(1);
 SCL=0; 
 return 0;
}


void Write_byte_24C02_Demo(unsigned char dat) 
{
    unsigned char i;
	for(i=0;i<8;i++)
	{	
		if((dat<<i)&0x80)
		SEND1_24C02_Demo();
		else
		SEND0_24C02_Demo();
	}
}


unsigned char Read_byte_24C02_Demo(void)
{
	unsigned char i,temp=0;     
	for(i=0;i<8;i++)
	{
        SDA=1;
	    SCL=1;
	    DELAY_24C02_Demo(1);  
		if(SDA==1)
		{
			temp=temp<<1;
			temp=temp|0x01;
		}
		else
			temp=temp<<1;
		 SCL=0;	
	  }
	  return temp;
}

/************************************
      EEPROM  DRIVE
	  Addr:from 0x00-->
*************************************/
unsigned char rdeeprom_24C02_Demo(unsigned char addr)
{ 
        unsigned char temp=0;
		bit flag=0;
		IICStart_24C02_Demo();
		Write_byte_24C02_Demo(0xa0);
        Check_Ack_24C02_Demo();
		Write_byte_24C02_Demo(addr);
		Check_Ack_24C02_Demo();
		IICStart_24C02_Demo();
		Write_byte_24C02_Demo(0xa1);
		Check_Ack_24C02_Demo();
		temp=Read_byte_24C02_Demo();
		SEND1_24C02_Demo();
		IICStop_24C02_Demo();
 	    return temp;   
}  
    
   
void wrteeprom_24C02_Demo(unsigned char addr,unsigned char dat)
{
    IICStart_24C02_Demo();
		Write_byte_24C02_Demo(0xa0);
		Check_Ack_24C02_Demo();
		Write_byte_24C02_Demo(addr);
		Check_Ack_24C02_Demo();
		Write_byte_24C02_Demo(dat);
		Check_Ack_24C02_Demo();
		IICStop_24C02_Demo();
} 
#endif

/*********************Timer2********************/
#if CONFIG_Timer2 == ENABLED
static Timer2_Process  Interrp_Process;

unsigned char TimeCtr;

void Timer2_init_Demo(Timer2_Process T_Process)
{
	RCAP2H = (0XFFFF - 50000)/256;
	RCAP2L = (0XFFFF - 50000)%256;
	T2CON =0;
	//T2MOD = 0;
	IE |=0xA0;
	
	Interrp_Process = T_Process;
	TR2 = 1;
}

void timer2() interrupt 5
{
	TF2 = 0;
	TimeCtr++;
	if(TimeCtr >= Time_count)//1秒
	{
		TimeCtr =0;
		Interrp_Process();
		//Buzzer_P = ~Buzzer_P;
	}
		
}

#endif

/*********************Timer0定时********************/
#if CONFIG_Timer0 == ENABLED

//	TMOD=0x21;             //定时器T1工作于计数模式1，定时器T0工作于计时模式1；
//	TH1=(65536-46083)/256;    //定时器T0的高8位设置初值，每50ms产生一次中断
//	TL1=(65536-46083)%256;    //定时器T0的低8位设置初值，每50ms产生一次中断
//	TH0=(65536-20000)/256;    //定时器T0的高8位设置初值，每50ms产生一次中断
//	TL0=(65536-20000)%256;    //定时器T0的低8位设置初值，每50ms产生一次中断
static Timer0_Process  Timer_Process;
unsigned char RHCounter;
//定时器0初始化
void Timer0_Init_demo(Timer0_Process T_Process) 
{
    ET0 = 1;        //允许定时器0中断
    TMOD = 0x01;       //定时器工作方式选择
    TL0 = 0xFF;
    TH0 = 0x4B;     //定时器赋予初值
    TR0 = 1;        //启动定时器
	  EA = 1;
		Timer_Process = T_Process;
}

//定时器0中断
void Timer0_ISR (void) interrupt 1 using 0 {
    TL0 = 0xFF;
    TH0 = 0x4B;     //定时器赋予初值
    RHCounter++;

    if (RHCounter >= 40) //2秒
		{
				Timer_Process();
        RHCounter = 0;
    }
}
#endif


/********************UART0 *********************/
#if CONFIG_UART0 == ENABLED
bit UART0_TXD_BUSY = 0;
static UART0_RX_Process_T  UART0_RX_Process;
void UART0_Send_Byte_Demo(unsigned char a)
{

	SBUF = a;
  UART0_TXD_BUSY = 1;	
	while(UART0_TXD_BUSY);	//等待发送成功

}




/*----------------------------
UART1 发送字符串
-----------------------------*/
void UART0_Send_String_Demo(char *s)
{
	while(*s)//检测字符串结束符
	{
		UART0_Send_Byte_Demo(*s++);//发送当前字符
	}
}


void UART0_Init_Demo(UART0_RX_Process_T RX_Process)
{
	
	TMOD|= 0X20;		//T1  方式2  ，8位   自动重装   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600
	TR1=1; 		    // 定时器1启动  


	SM0=0;	    // 设置串口的工作模式
	SM1=1; 	    //方式1


	REN=1; 		 // 允许串口接收数据 	 

  TI=1;
	ES=1; 	     // 串口中断应许 
	EA=1;		 // 开启中断 
	UART0_RX_Process = RX_Process;
	
}
unsigned char UART0_RXD[3];
unsigned char UART0_RXD_Index =0;
void UART0_ISR(void) interrupt 4
{
	unsigned char a;
	
	if(RI)
	{
		RI = 0;
		
		a = SBUF;
		//接收多数据
		UART0_RXD[UART0_RXD_Index] = a;
		UART0_RXD_Index++;
		if(UART0_RXD[0] != CRC)//校验帧
		{
			UART0_RXD_Index =0;
		}
		if(UART0_RXD_Index>REV_NUM)//要接收的数量
		{
			UART0_RX_Process(UART0_RXD);
			UART0_RXD[1] = 0;
			UART0_RXD_Index =0;	
		}			
				
	}
	else if(TI)
	{
		TI = 0;
		UART0_TXD_BUSY = 0;
	}
	else
	{
		RI = 0;
		TI = 0;
	}
	
}
#endif



/********************KEY_MAP *********************/
#if CONFIG_KEY_MAP == ENABLED

//按键扫描函数 :    
//功能；只扫描一个按键，按键为号小优先  
//返回键值：
//         7    8    9    10	   //10:清除单价并且清除重量	
//         4    5    6    11	   //11:清除单价最后一位
//         1    2    3    12	   //12:去皮
//         14   0    15   13	   //14:无功能（用于扩展）15：小数点  13：确定

unsigned char Getkeyboard(void)
{
    unsigned char number = 0;
    unsigned char i;
	
	//行输入低电平
    ROW1=ROW2=ROW3=ROW4=0;
	//如果列输出不全为高，则说明有键按下
	if ((COL1!=1)||(COL2!=1)||(COL3!=1)||(COL4!=1))
	{
	   //输入0111
	   ROW1=0;
	   ROW2=ROW3=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 1;	   // 7
	   else if (COL2==0) return 2;	//	 8
	   else if (COL3==0) return 3;	 //	9
	   else if (COL4==0) return 10;	 //	 10
	   //输入1011
	   ROW2=0;
	   ROW1=ROW3=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 4;	  //4
	   else if (COL2==0) return 5; //  5
	   else if (COL3==0) return 6;	// 6
	   else if (COL4==0) return 11;	 //	11
	   //输入1101
	   ROW3=0;
	   ROW1=ROW2=ROW4=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 7;  //1
	   else if (COL2==0) return 8;	  // 2
	   else if (COL3==0) return 9;	  //   3
	   else if (COL4==0) return 12;	  //   12
	   //输入0111
	   ROW4=0;
	   ROW1=ROW2=ROW3=1;
	   for (i=0;i<20;i++);
	   if (COL1==0) return 14;
	   else if (COL2==0) return 0;
	   else if (COL3==0) return 15;
	   else if (COL4==0) return 13;
	   //没有检测到列低电平
	   return 99;
	}
	return 99;
}

#endif

/********************HX711 *********************/
#if CONFIG_HX711 == ENABLED

unsigned long Weight_Maopi;

void Delay__hx711_us(void)
{
	_nop_();
	_nop_();
}

//校准参数
//因为不同的传感器特性曲线不是很一致，因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
//当发现测试出来的重量偏大时，增加该数值。
//如果测试出来的重量偏小时，减小改数值。
//该值可以为小数
unsigned int GapValue=245;
void Delay_ms_HX711(unsigned int n)
{
	unsigned int  i,j;
	for(i=0;i<n;i++)
		for(j=0;j<123;j++);
}

unsigned long HX711_Read(void)	//增益128
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	Delay__hx711_us();
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
	} 
 	HX711_SCK=1; 
    count=count^0x800000;//第25个脉冲下降沿来时，转换数据
	Delay__hx711_us();
	HX711_SCK=0;  
	return(count);
}
//****************************************************
//获取毛皮重量
//****************************************************
void Get_Maopi()
{
	unsigned long Weight_Maopi_0 = 0;
mm:	Weight_Maopi_0 = HX711_Read();
	Delay_ms_HX711(500);
	Weight_Maopi = HX711_Read();
	if(Weight_Maopi/GapValue!=Weight_Maopi_0/GapValue)
	goto mm;

} 

//****************************************************
//称重
//****************************************************
long Get_Weight()
{
	long Weight_Shiwu;
	Weight_Shiwu = HX711_Read();
	Weight_Shiwu = Weight_Shiwu - Weight_Maopi;		//获取净重
	
	Weight_Shiwu = (unsigned int)((float)Weight_Shiwu/GapValue); 	//计算实物的实际重量																
  return Weight_Shiwu;
}
#endif

/********************HRSR04 *********************/
#if CONFIG_HRSR04 == ENABLED

/*********************************************************/
// 毫秒级的延时函数，time是要延时的毫秒数
/*********************************************************/
void HRSR04_DelayMs(unsigned int time)
{
	unsigned int i,j;
	for(i=0;i<time;i++)
		for(j=0;j<112;j++);
}
void HRSR04_Timer_init()
{
		TMOD = 0x01;											// 选择定时器0，并且确定是工作方式1（为了超声波模块测量距离计时用的）
}

unsigned int GetDistance(void)
{
	unsigned int ss;					// 用于记录测得的距离
	//uart那边开启了TR0不知道为什么
	TR0=0;
	TH0=0;
	TL0=0;

	Trig_P=1;					// 给超声波模块一个开始脉冲
	HRSR04_DelayMs(1);
	Trig_P=0;

	while(!Echo_P);		// 等待超声波模块的返回脉冲
	TR0=1;						// 启动定时器，开始计时
	while(Echo_P);		// 等待超声波模块的返回脉冲结束
	TR0=0;						// 停止定时器，停止计时

	ss=((TH0*256+TL0)*0.034)/2;		// 距离cm=（时间us * 速度cm/us）/2

	return ss;
}

/* 
HRSR04_Timer_init();  
while(1)
{
	...
	Distanc = GetDistance();
}
*/
#endif

/********************MP3_TF_16P *********************/
#if CONFIG_MP3_TF == ENABLED

unsigned char a;

//9600bps
void uart_init()
{
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
	TI = 1;
	
	//TH0=0x4c;
	//TL0=0x00;	  //装载定时器1数据
	//TR0=1;		  //开始定时
	//ET0=1;		  //是能定时器1

}

void UartSendByte(unsigned char byte)
{
	SBUF = byte;
	while(!TI);
		TI = 0;
}


void UartSendString(unsigned char *string)
{
	while(*string)
	{
		UartSendByte(*string++);
	}
}


void ser() interrupt 4
{
	RI = 0;
	a = SBUF;
}

static unsigned char Send_buf[10] = {0} ;
static unsigned char Recv_buf[10] = {0} ;

static unsigned char SendDataLen = 0 ;
static unsigned char ResendDataLen = 0 ;


/*****************************************************************************************************
 - 功能描述：
 - 隶属模块：
 - 参数说明：
 - 返回说明：
 - 注：
*****************************************************************************************************/

/*****************************************************************************************************
 - 功能描述：串口发送一帧数据

*****************************************************************************************************/


void SendCmd(unsigned char len)
{
    unsigned char i = 0 ;

    //UartSendByte(0x7E); //??
    //UartSendByte(0xff); //??	
		//UartSendByte(0x7e);
    for(i=0; i<len; i++)//??
    {
		UartSendByte(Send_buf[i]) ;
    }
    //UartSendByte(0xEF) ;//??
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

void DoSum( unsigned char *Str, unsigned char len)
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


void Uart_SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat)
{
		//TR0 = 0;
		while(voice_busy == 0);
    Send_buf[0] = 0x7e;    //保留字节
    Send_buf[1] = 0xff;    //保留字节
    Send_buf[2] = 0x06;    //长度
    Send_buf[3] = CMD;     //控制指令
    Send_buf[4] = feedback;//是否需要反馈
    Send_buf[5] = (unsigned char)(dat >> 8);//datah
    Send_buf[6] = (unsigned char)(dat);     //datal
		Send_buf[9] = 0xef;
    DoSum(&Send_buf[1],6);        //校验
    SendCmd(10);       //发送此帧数据
		//TR0 =1;
}
//****************************************************
//MS延时函数(12M晶振下测试)
//****************************************************
void Delay_ms(unsigned int n) {
    unsigned int  i,j;
    for(i=0; i<n; i++)
        for(j=0; j<123; j++);
}
/* demo
	//串口初始化
	uart_init();
	EA = 1;
		//语音提示
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x06,0,30);
	Delay_ms(500);
	Uart_SendCMD(0x03,0,VOICE_INIT);//欢迎使用语音电子称
	Delay_ms(500);
	while(1)
	{
		...
		Uart_SendCMD(0x03,0,(dat/100));//百位
		Delay_ms(100);
		Uart_SendCMD(0x03,0,12);//百
		Delay_ms(100);		
	}
*/
#endif

/********************SHT11 *********************/
#if CONFIG_SHT11 == ENABLED
#define noACK 0				//继续传输数据，用于判断是否结束通讯
#define ACK   1             //结束数据传输；
							//地址  命令  读/写
#define STATUS_REG_W 0x06   //000   0011    0
#define STATUS_REG_R 0x07   //000   0011    1
#define MEASURE_TEMP 0x03   //000   0001    1
#define MEASURE_HUMI 0x05   //000   0010    1
#define RESET        0x1e   //000   1111    0
//写字节程序
char s_write_byte(unsigned char value)   
{ 
	unsigned char i,error=0; 
	for (i=0x80;i>0;i>>=1)             //高位为1，循环右移
	{ 
		if (i&value) DATA=1;          //和要发送的数相与，结果为发送的位
    	else DATA=0;                        
    	SCK=1;                          
    	_nop_();_nop_();_nop_();        //延时3us 
    	SCK=0;
	}
	DATA=1;                           //释放数据线
	SCK=1;                            
	error=DATA;                       //检查应答信号，确认通讯正常
	_nop_();_nop_();_nop_();
	SCK=0;        
	DATA=1;
	return error;                     //error=1 通讯错误
}
//读字节程序
char s_read_byte(unsigned char ack)
{ 
	unsigned char i,val=0;
	DATA=1;                           //释放数据线
	for(i=0x80;i>0;i>>=1)             //高位为1，循环右移
	{ 
		SCK=1;                         
    	if(DATA) val=(val|i);        //读一位数据线的值 
    	SCK=0;       
	}
	DATA=!ack;                        //如果是校验，读取完后结束通讯；
	SCK=1;                            
	_nop_();_nop_();_nop_();          //延时3us 
	SCK=0;   
	_nop_();_nop_();_nop_();       
	DATA=1;                           //释放数据线
	return val;
}
//启动传输
void s_transstart(void)
// generates a transmission start 
//       _____         ________
// DATA:      |_______|
//           ___     ___
// SCK : ___|   |___|   |______
{ 
   	DATA=1; SCK=0;                   //准备
   	_nop_();
  	SCK=1;
   	_nop_();
   	DATA=0;
   	_nop_();
  	SCK=0; 
  	 _nop_();_nop_();_nop_();
   	SCK=1;
   	_nop_();
  	DATA=1;     
  	_nop_();
   	SCK=0;     
}
//连接复位
void s_connectionreset(void)
// communication reset: DATA-line=1 and at least 9 SCK cycles followed by transstart
//       _____________________________________________________         ________
// DATA:                                                      |_______|
//          _    _    _    _    _    _    _    _    _        ___     ___
// SCK : __| |__| |__| |__| |__| |__| |__| |__| |__| |______|   |___|   |______
{ 
	unsigned char i; 
	DATA=1; SCK=0;                    //准备
	for(i=0;i<9;i++)                  //DATA保持高，SCK时钟触发9次，发送启动传输，通迅即复位
	{ 
		SCK=1;
    	SCK=0;
	}
	s_transstart();                   //启动传输
}
//软复位程序
char s_softreset(void)
// resets the sensor by a softreset 
{ 
	unsigned char error=0; 
	s_connectionreset();              //启动连接复位
	error+=s_write_byte(RESET);       //发送复位命令
	return error;                     //error=1 通讯错误
}          
//温湿度测量
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode)
// 进行温度或者湿度转换，由参数mode决定转换内容；
{ 
//	enum {TEMP,HUMI};		 //已经在头文件中定义
	unsigned error=0;
	unsigned int i;

	s_transstart();                   //启动传输
	switch(mode)                     //选择发送命令
    {	
		case TEMP : error+=s_write_byte(MEASURE_TEMP); break;		   //测量温度
    	case HUMI : error+=s_write_byte(MEASURE_HUMI); break;		   //测量湿度
    	default     : break; 
	}
	for (i=0;i<65535;i++) if(DATA==0) break; //等待测量结束
	if(DATA) error+=1;                // 如果长时间数据线没有拉低，说明测量错误 
	*(p_value) =s_read_byte(ACK);    //读第一个字节，高字节 (MSB)
	*(p_value+1)=s_read_byte(ACK);    //读第二个字节，低字节 (LSB)
	*p_checksum =s_read_byte(noACK); //read CRC校验码
	return error;					 // error=1 通讯错误
}
//温湿度值标度变换及温度补偿
void calc_sth10(float *p_humidity ,float *p_temperature)
{ 
	
	const float C1=-8.0;              // 12位湿度精度 修正公式
	const float C2=+0.0405;           // 12位湿度精度 修正公式
	const float C3=-0.0000028;        // 12位湿度精度 修正公式
	const float T1=+0.01;             // 14位温度精度 5V条件  修正公式
	const float T2=+0.00008;          // 14位温度精度 5V条件  修正公式
	
	float rh=*p_humidity;             // rh:      12位 湿度 
	float t=*p_temperature;           // t:       14位 温度
	float rh_lin;                     // rh_lin: 湿度 linear值
	float rh_true;                    // rh_true: 湿度 ture值
	float t_C;                        // t_C   : 温度 ℃
	
	t_C=t*0.01 - 40;                  //补偿温度
	rh_lin=C3*rh*rh + C2*rh + C1;     //相对湿度非线性补偿
	rh_true=1*(T1+T2*rh)+rh_lin;   //相对湿度对于温度依赖性补偿
	if(rh_true>100)rh_true=100;       //湿度最大修正
	if(rh_true<0.1)rh_true=0.1;       //湿度最小修正

	*p_temperature=t_C;               //返回温度结果
	*p_humidity=rh_true;              //返回湿度结果
}

/*demo
void main()
{
	unsigned int temp,humi;		//定义温度和湿度变量
	value humi_val,temp_val;		//定义两个共同体，一个用于湿度，一个用于温度
	unsigned char error;		    //用于检验是否出现错误
	unsigned char checksum;			//CRC			 
	uchar wendu[6];				 	//用于记录温度
	uchar shidu[6];				 	//用于记录湿度	
	value humi_val,temp_val;		//定义两个共同体，一个用于湿度，一个用于温度
	while(1)
	{
		error=0;					   //初始化error=0，即没有错误
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //温度测量
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //湿度测量
    if(error!=0) 
			s_connectionreset();                 ////如果发生错误，系统复位		
		else
		{
				humi_val.f=(float)humi_val.i;                   //转换为浮点数
     		temp_val.f=(float)temp_val.i;                   //转换为浮点数
     		calc_sth10(&humi_val.f,&temp_val.f);            //修正相对湿度及温度
//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //计算e dew_point
   			temp=temp_val.f*10;
     		humi=humi_val.f*10;		
		}
	}

}


*/

#endif

/********************DHT11 *********************/
#if CONFIG_DHT11 == ENABLED

unsigned char U8FLAG,U8temp,U8comdata;

void Delay(unsigned int j)
{      
	unsigned char i;
	for(;j>0;j--)
	{ 	
		for(i=0;i<27;i++);
	}
}
void  Delay_10us(void)
{
	unsigned char i;
	i--;
	i--;
	i--;
	i--;
	i--;
	i--;
}
	
void  COM(void)			//
{

	unsigned char i;

	for(i=0;i<8;i++)	   
	{

		U8FLAG=2;	
		while((!DTH_PIN)&&U8FLAG++);
		Delay_10us();
		Delay_10us();
		Delay_10us();
		U8temp=0;
		if(DTH_PIN)U8temp=1;
		U8FLAG=2;
		while((DTH_PIN)&&U8FLAG++);
		//超时则跳出for循环		  
		if(U8FLAG==1)break;
		//判断数据位是0还是1	 

		// 如果高电平高过预定0高电平值则数据位为 1 

		U8comdata<<=1;
		U8comdata|=U8temp;        //0
	}//rof

}

	//--------------------------------
	//-----湿度读取子程序 ------------
	//--------------------------------
	//----以下变量均为全局变量--------
	//----温度高8位== U8T_data_H------
	//----温度低8位== U8T_data_L------
	//----湿度高8位== U8RH_data_H-----
	//----湿度低8位== U8RH_data_L-----
	//----校验 8位 == U8checkdata-----
	//----调用相关子程序如下----------
	//---- Delay();, Delay_10us();,COM(); 
	//--------------------------------

char DHT11_RH(unsigned char* arry)
{
	unsigned char U8T_data_H_temp,U8T_data_L_temp,U8RH_data_H_temp,U8RH_data_L_temp,U8checkdata_temp;
	//主机拉低18ms 
	DTH_PIN=0;
	Delay(180);
	DTH_PIN=1;
	//总线由上拉电阻拉高 主机延时20us
	Delay_10us();
	Delay_10us();
	Delay_10us();
	Delay_10us();
	//主机设为输入 判断从机响应信号 
	DTH_PIN=1;
	//判断从机是否有低电平响应信号 如不响应则跳出，响应则向下运行	  
	if(!DTH_PIN)		 //T !	  
	{
		U8FLAG=2;
		//判断从机是否发出 80us 的低电平响应信号是否结束	 
		while((!DTH_PIN)&&U8FLAG++);
		U8FLAG=2;
		//判断从机是否发出 80us 的高电平，如发出则进入数据接收状态
		while((DTH_PIN)&&U8FLAG++);
		//数据接收状态		 
		COM();
		U8RH_data_H_temp=U8comdata;
		COM();
		U8RH_data_L_temp=U8comdata;
		COM();
		U8T_data_H_temp=U8comdata;
		COM();
		U8T_data_L_temp=U8comdata;
		COM();
		U8checkdata_temp=U8comdata;
		DTH_PIN=1;
		//数据校验 

		U8temp=(U8T_data_H_temp+U8T_data_L_temp+U8RH_data_H_temp+U8RH_data_L_temp);
		if(U8temp==U8checkdata_temp)
		{
			arry[0]=U8RH_data_H_temp;
			arry[1]=U8RH_data_L_temp;
			arry[2]=U8T_data_H_temp;
			arry[3]=U8T_data_L_temp;
			return TRUE;
		//U8checkdata=U8checkdata_temp;
		}else
			return FALSE;
	}//fi
	return FALSE;
}
/*Demo	
unsigned char RH_Value[4];
while(1)
{
	if(DHT11_RH(RH_Value) == TRUE)
	{
		Lcd1602_Display_Three_bit(0,0,RH_Value[0]);//读出温湿度，只取整数部分
		Lcd1602_Display_Three_bit(1,0,RH_Value[2]);
	}
}
*/
#endif


/********************LCD12864 *********************/
#if CONFIG_LCD12864_LIB == ENABLED

/********************************************
Description:  LCD12864 驱动 ,采用串行方式,
********************************************/ 


#define BIT(n)	(1<<(n))
#define SID_0   Lcd_Rw=0;
#define SID_1   Lcd_Rw=1; 
#define SCLK_0  Lcd_En=0;
#define SCLK_1  Lcd_En=1; 
//15脚 PSB 接低电平

//函数  delay(uchar z)
//功能能  延时

void Delay1(unsigned char z)
{
	unsigned char a,b;
	for(a=z;a>0;a--)
	 for(b=200;b>0;b--);	
} 

void SendByte(unsigned char bye)
{
	unsigned char i;
	for(i=0;i<8;i++)
	{
		if((bye<<i)&0x80){SID_1;}
		else {SID_0;}
		SCLK_1;

		SCLK_0;

	}
}

void Lcd_WriteCom(unsigned char CMD)
{
	SendByte(0xf8);
	SendByte(CMD&0xf0);
	SendByte((CMD<<4)&0xf0);
      Delay1(20);
	  Delay1(20);
	  Delay1(20);
}

void Lcd_WriteDate(unsigned char Data)
{	SendByte(0xf8+2);
	SendByte(Data&0xf0);
	SendByte((Data<<4)&0xf0);
}

void LCDInit()
{/*	RST=0;
	delay1MS(50);
	RST=1;          */
	lcd_RS=1;
    Lcd_WriteCom(0x34);//功能设置，一次送8位数据，基本指令集
    Lcd_WriteCom(0x30);//0000,1100  整体显示，游标off，游标位置off
    Lcd_WriteCom(0x01);//0000,0001 清DDRAM
    Lcd_WriteCom(0x06);//0000,0010 DDRAM地址归位
    Lcd_WriteCom(0x0c);//1000,0000 设定DDRAM 7位地址000，0000到地址计数器AC//     
}

/*****************************
发送字符串
*****************************/
//void show_str(uchar const *s)//改AVR去掉const
void  Lcd_String(const unsigned char  *str)
{
 while(*str !='\0')
   { 
   		Lcd_WriteDate(*str++);

   }
}

void Lcd_Display2data(unsigned char line,unsigned char list,unsigned char Date)
{
		unsigned char i;
		 unsigned char ta[]={0,0,'\0'};	  //用一个数组来装数
	   list=list &0x07;			       //限制在 0-7列
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }
	 for(i=2;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 
void Lcd_Display3data(unsigned char line,unsigned char list,unsigned int Date)
{
		unsigned char i;
		 unsigned char ta[]={0,0,0,0,'\0'};	  //用一个数组来装数
	   list=list &0x07;			       //限制在 0-7列
	   switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }
	 for(i=3;i>0;i--)
	 {							  //循环四次把四个数从高到低装入ta
	 	ta[i-1]=Date%10+48;
		Date=Date/10;
	 }
	  Lcd_String(ta);
} 


 

 ////////////////////////////////////////////////////////////////////
//函数	  Lcd_init(uchar com)
//功能    精确屏幕显示字符串
//参数    line  液晶屏的第几行  list  第几个位置开始写 （最多8个列）  *p要写的字符串
void  Lcd_ShowSring(unsigned char line,unsigned char list,unsigned char *p)
{
	 switch(line){
				case 1:   Lcd_WriteCom(0x80+list);break;	//第一行
				case 2:   Lcd_WriteCom(0x90+list);break;	//第二行
				case 3:   Lcd_WriteCom(0x88+list);break;	//第三行
				case 4:   Lcd_WriteCom(0x98+list);break;	//第四行
				default : break;
	
	   }

	    Lcd_String(p);

}

/*demo

  LCDInit();	//lcd12864初始化
	Lcd_ShowSring(1,0,"棚内温湿度光照");
  Lcd_ShowSring(2,0,"温度:");
	Lcd_ShowSring(3,0,"湿度:");
	Lcd_ShowSring(4,0,"光度:");
	while(1);

*/
#endif


/********************ESP8266*********************/
#if CONFIG_ESP8266 == ENABLED
unsigned char a;
void us_delay(unsigned char t) 
{  
	while(t--); 
}  

void Esp8266_Delay_Ms(int cnt)
{
	unsigned char i, j;

	while(cnt--)
	{

		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
//*********主函数*****************
//9600bps
void ESP8266_uart_init()
{
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
	TI = 1;
}
void UartSendByte(unsigned char byte)
{
	SBUF = byte;
	while(!TI);
		TI = 0;
}


void UartSendString(unsigned char *string)
{
	while(*string)
	{
		UartSendByte(*string++);
	}
}


void ser() interrupt 4
{
	if(RI)
	{
		RI = 0;
		a = SBUF;
	}
}


/******************************************************************** 
名称：WIFI模块设置函数  作用: 启动模块，以便可以实现无线接入和控制  
********************************************************************/ 
void ESP8266_Set(unsigned char *puf) 
	{                        	// 数组指针*puf指向字符串数组
    while(*puf!='\0') 
		{  		//遇到空格跳出循环
        UartSendByte(*puf);  		//向WIFI模块发送控制指令。
        Esp8266_Delay_Ms(5);
        puf++;
    }
    Esp8266_Delay_Ms(5);
    UartSendByte('\r'); 			//回车
    Esp8266_Delay_Ms(5);
    UartSendByte('\n');   			//换行
}
void Esp8266_init()
{
		ESP8266_uart_init();
		Esp8266_Delay_Ms(100);
	  ESP8266_Set("AT+CWMODE=2"); 							//设置路由器模式1 station,模式2 AP,模式3 station+AP混合模式   设置前wifi的波特率设置成9600
    Esp8266_Delay_Ms(300);
    ESP8266_Set("AT+RST"); 									//重新启动wifi模块
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+CWSAP=\"wifi\",\"12345678\",11,4");  	//AT+CWSAP="wifi_yuan","12345678",11,4  设置模块SSID:WIFI, PWD:密码 及安全类型加密模式（WPA2-PSK）
    ESP8266_Set("AT+CWSAP=\"wifi_yuxia\",\"12345678\",11,4");
    Esp8266_Delay_Ms(300);
//    ESP8266_Set("AT+CIPMUX=1");								//开启多连接模式，允许多个各客户端接入
    ESP8266_Set("AT+CIPMUX=1");								//开启单连接模式
    Esp8266_Delay_Ms(300);
    ESP8266_Set("AT+CIPSERVER=1,5000");  					//启动TCP/IP 实现基于网络//控制 	ESP8266_Set("AT+CIPSERVER=1,5000");
    Esp8266_Delay_Ms(500);
    ESP8266_Set("AT+CIPSTO=0"); 
    Esp8266_Delay_Ms(500);	
}
/**demo

unsigned char buff[30];
void EPS8266_Send(void)
{
	static unsigned char Cnt1 = 1;
  if(++Cnt1 == 20)
	{
		ESP8266_Set("AT+CIPSEND=0,34\r\n");	   ////发送字符长度  
	}else if(Cnt1 >= 40)
	{
		Cnt1 = 0;
		buff[0]= 'H';
		buff[1]= ':';
		buff[2]= Temp_Value/100%10+0x30;
		buff[3]= Temp_Value/10%10+0x30;
		buff[4]= Temp_Value%10+0x30;
		buff[5]= ',';
		buff[6]= RH/100%10+0x30;
		buff[7]= RH/10%10+0x30;
		buff[8]= ',';
		buff[9]= RH%10+0x30;
		buff[10]= ',';
		buff[11]= PH_Value/100%10+0x30;
		buff[12]= PH_Value/10%10+0x30;
		buff[13]= PH_Value%10+0x30;
		buff[14]= ',';
   	buff[15]= zt+0x30;
		buff[16]= ',';
   	buff[17]= tempH+0x30;
		buff[18]= ',';	
   	buff[19]= tempL+0x30;
		buff[20]= ',';	
   	buff[21]= waterH+0x30;
		buff[22]= ',';	
   	buff[23]= waterR+0x30;
		buff[24]= ',';			
		buff[25]= 'E';	
		UartSendString(buff);		
	}	
}

	Esp8266_init();
	while(1)
	{
		EPS8266_Send();
	}

**/
#endif

/********************ISD4004*********************/
#if CONFIG_ISD4004 == ENABLED

void delayms(unsigned char ms)// 延时子程序 
{      
	unsigned char j;
	while(ms--)
	{
		for(j = 0; j < 120; j++);
	}
}
bit flag_xh = 0;
////////////////放音部分子程序，放音地址由ADDR决定////
void play(unsigned int addr)
{
	unsigned char y;
	flag_xh = 0;
	SS=0;
	MOSI=0;//发送开始
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x20>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送结束
	SS=1;//上电结束
	delayms(50);
	SS=0;
	MOSI=0;//发送地址
	SCLK=0;
	for(y=0;y<16;y++)
	{
	SCLK=0;
	if((addr>>y)&0x01)MOSI=1;
	else MOSI=0;
	_nop_();
	_nop_();
	_nop_();
	SCLK=1;
	_nop_();
	_nop_();
	_nop_();
	}//发送地址结束
	MOSI=0;//放音
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xe0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
	SS=0;
	MOSI=0;//放音
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xf0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
	//	flag_xh = 1;	 
}	
//////////////////////////lu音部分子程序，地址由ADDR决定/////////////////////////
void rec(unsigned int addr)                
{
 	unsigned int y;	
	SS=0;
	MOSI=0;//发送开始
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x20>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送结束
	SS=1;//上电结束
	delayms(50);
	SS=0;
	MOSI=0;//发送开始
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x20>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送结束
	SS=1;//上电结束
	delayms(50);
	delayms(50);
	SS=0;
	MOSI=0;//发送地址
	SCLK=0;
	for(y=0;y<16;y++)
	{
		SCLK=0;
		if((addr>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}//发送地址结束
	MOSI=0;
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xa0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
	SS=0;
	MOSI=0;
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0xb0>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;	  }

////////////////////////////////////
////////////////////////////////
void stop()
{ 
  unsigned char y;
	SS=1;
	SS=0;
	MOSI=0;//放音
	SCLK=0;
	for(y=0;y<8;y++)
	{
		SCLK=0;
		if((0x30>>y)&0x01)MOSI=1;
		else MOSI=0;
		_nop_();
		_nop_();
		_nop_();
		SCLK=1;
		_nop_();
		_nop_();
		_nop_();
	}
	SS=1;
}

/*demo
play(ADDR4STR);

*/
#endif

/********************fuzzify*********************/
#if CONFIG_FUZZIFY == ENABLED
//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
// 定义差距输入常量
#define GAP_ZERO     0x00
#define GAP_VSMALL   0x01
#define GAP_SMALL    0x02
#define GAP_MEDIUM   0x03
#define GAP_BIG      0x04
// 定义控制输出常量
#define TURN_ZERO    0x80
#define TURN_VSMALL  0x81
#define TURN_SMALL   0x82
#define TURN_MEDIUM  0x83
#define TURN_BIG     0x84



//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
//unsigned char Temp_H,Temp_L;

//unsigned int sum;			  //10次AD值的综合变量
//unsigned char RH,RH_H=12,RH_L=8,state,ms,cs;  //当前水位，  水位上限，下限，  设置项变量，50ms变量   ，cs 为计次数变量    ，
//bit beep1,zt,s1;	  //报警标志位，   工作模式标志位，   闪烁标志位

//int Temperature;
 


//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
//-------------定义常量----------------------------------------------------------------
#define MU_MAX 0XFF            //模糊度的最大值为0XFF代表面1
#define RULE_TOT 10            //规则数个数
#define MF_TOT 5               //成员函数的个数
#define IO_NUM 0x07
#define LABEL_NUM 0x70
#define DEFAULT_VALUE 0x00
//----------------定义数据库-----------------------------------------------------------
unsigned char code output_memf[MF_TOT]={0, 15, 35, 60, 102};// OUTPUT TURNING NUMBER:
                                                            // ZERO, VSMALL, SMALL, MEDIUM, BIG
                                                            // 输入功能函数以点斜式方式存储. 第一维成员函数标号第二维是点斜式数据
unsigned char code input_memf[MF_TOT][4]={                  //距离功能函数
                                            { 0x00, 0x00, 0x00, 0x0d }, // VSLOW
                                            { 0x00, 0x0d, 0x14, 0x0d }, // SLOW
                                            { 0x1e, 0x0d, 0x32, 0x0d }, // MEDIUM
                                            { 0x3C, 0x0d, 0x50, 0x0d }, // FAST
                                            { 0x50, 0x09, 0x6e, 0x00 }  // VFAST
                                          };

//-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
//-----------定义模糊系统规则-----------------------------------------------------------
unsigned char code rules[RULE_TOT]={ 
                                        // if...  then...
                                        GAP_ZERO,TURN_ZERO,
                                        GAP_VSMALL,TURN_VSMALL,
                                        GAP_SMALL,TURN_SMALL,
                                        GAP_MEDIUM,TURN_MEDIUM,
                                        GAP_BIG,TURN_BIG
                                   };


 //-----------定义模糊系统参数-----------------------------------------------------------
//------------------------------------------------------------------------------------
 //-----------定义各变量-----------------------------------------------------------------
unsigned char outputs[MF_TOT],fuzzy_out;  //模糊输出mu值
//-----------子程序函数头申明-----------------------------------------------------------
void fuzzy_engine(unsigned char);
unsigned char compute_memval(unsigned char,unsigned char);
void defuzzify(void);

/***************************************************************************************************************/
unsigned char compute_memval(unsigned char input,unsigned char label)
 {
    int data temp;
    if (input < input_memf[label][0])
    {                                 // 如果输入不在曲线下u值为0
         return 0;
    }
    else
    {
        if (input < input_memf[label][2])
        {
             temp=input;              // 用点斜式计算mu
             temp-=input_memf[label][0];
             if (!input_memf[label][1])
             {
                temp=MU_MAX;
             }
             else
             {
                temp*=input_memf[label][1];
             }
             if (temp < 0x100)
             {                     // 如果结果不超过1
                return temp;       // 返回计算结果
             }
             else
             {
                return MU_MAX;     // 确保mu值在范围内
             }
        }
        else
        {                           // 输入落在第二条斜线上
            temp=input;               // 用点斜式方法计算 mu
            temp-=input_memf[label][2];
            temp*=input_memf[label][3];
            temp=MU_MAX-temp;
            if (temp < 0)
            {                      // 确保结果不小于0
                  return 0;
            }
            else
            {
                  return temp;        // mu为正 – 返回结果
            }
        }
    }
    return 0;
}
/*******************************************************************************
Function: defuzzify
Description: 计算模糊输出的重心并调用函数把它
             转换成可被系统使用的输出量
Parameters: 无.
Returns: 无.
Side Effects: outputs[][] 数组被清零.
*******************************************************************************/
void defuzzify(void)
{
    unsigned long numerator, denominator;
    unsigned char j;
    numerator=0;                         // 恢复总数值
    denominator=0;
    for (j=0; j<MF_TOT; j++)
    {                                // 计算总和值
        numerator+=(outputs[j]*output_memf[j]);
        denominator+=outputs[j];
        outputs[j]=0;                        // 清零输出作为参考使用
        if (denominator)
        {                                     // 确保分母是0的情况不发生
            fuzzy_out=numerator/denominator;  // 确定 COG
        }
        else
        {
            fuzzy_out=DEFAULT_VALUE;         // 没有规则被触发
        }
    }
}
/*******************************************************************************
Function: fuzzy_engine
Description: 实施规则基中的规则
Parameters: 无
Returns: 无.
Side Effects: 无
********************************************************************************/
unsigned char bdata clause_val;                        // 保存当前的分支进行快速访问
sbit clause_type = clause_val^7;                       // 表示分支是否是条件分支或者是结果分支
void fuzzy_engine(unsigned char input)
{
    bit then;                                       // 当正在分析结果时置位
    unsigned char if_val,                           // 保存当前规则中条件分支中的值
                  clause,                           // 规则基中当前的分支
                      mu,                           // 保存当前分支中的值
                 label=0;                           // 被条件使用的成员函数
                  then=0;                           // 设第一个分支是条件分支
           if_val=MU_MAX;                           // max out mu for the first rule
    for (clause=0; clause<RULE_TOT; clause++)
    {                                               // 遍历每条规则
        clause_val=rules[clause];                   // 读入当前的分支
        if (!clause_type)
        {                                           // 当前的分支是不是条件分支
            if (then)
            {                                       // 是否正在分析结果...
                then=0;
                if_val=MU_MAX;                      // 复位mu
            }
            mu=compute_memval(input, label);        // 得到条件分支的值
            if_val=mu;
            label++;
        }
        else
        {                                       // 当前分支是结果
            then=1;            // 置位标志位,如果当前规则的mu比参考的值要大,保存这个值作为新的模糊输出
            if (outputs[clause_val&0x07] < if_val)
            {
                outputs[clause_val&0x07]=if_val;
            }
        }
    }
    defuzzify(); // 用COG方法计算模糊输出和反模糊输出
 }

/*demo
		if(Temperature <= Temp_L)//小于设定值时，采用模糊计算
		{
						
		 //模糊计算
			fuzzy_engine((Temp_L - Temperature)*10);
		 
		 if(fuzzy_out)  //根据模糊计算结果，处理输出状态
		 {
				LED_3_BUF = led_3=0;		//显示对应的指示灯
		 }
		 else
		 {
			 LED_3_BUF = led_3=0;		//显示对应的指示灯 
		 }		
			
		} 
 
 */
#endif

/********************EX0_EX1*********************/
#if CONFIG_EX0_EX1 == ENABLED

static EX0_1_Process EX0_Process;
static EX0_1_Process EX1_Process;
void EX0_INIT(EX0_1_Process T_Process)
{
	EX0=1;     //开中断0
	IT0=1;     //中断0为边沿触发
	EA=1;     //开总中断
	EX0_Process = T_Process;
}

void EX1_INIT(EX0_1_Process T_Process)
{
	EX1=1;     //开中断0
	IT1=1;     //中断0为边沿触发
	EA=1;     //开总中断
	EX1_Process = T_Process;
}


//外部0中断子函数
void wb0() interrupt 0  //比赛时间开始/暂停
{
	EX0_Process();
}
//外部1中断子函数
void wb1() interrupt 2   //24s倒计时重新开始
{
	EX1_Process();
}
/*DEMO

sbit LED0 = P1^1;
sbit LED1 = P1^2;
void Ex0_Process()
{
	LED0 = ~LED0;
}
void Ex1_Process()
{
	LED1 = ~LED1;
}
void main()
{
	EX0_INIT(Ex0_Process);
	EX1_INIT(Ex1_Process);
	while(1)
	{

	}
}

*/
#endif

/********************LCD12864*********************/
#if CONFIG_LCD12864 == ENABLED



//延时函数
void delay(unsigned char t)
{
	unsigned char i,j;
	for(i=0;i<t;i++)
		for(j=0;j<10;j++);
}

//写命令函数
void write_com(unsigned char cmdcode)
{
	Di=0;
	RW=0;
	P0=cmdcode;		
	delay(2);
	Enable=1;
	delay(2);
	Enable=0;
}
//写数据函数
void write_data(unsigned char Dispdata)
{
	Di=1;
	RW=0;
	P0=Dispdata;
	delay(2);
	Enable=1;
	delay(2);
	Enable=0;
}

//清屏函数
void Lcd_Clr()
{
	unsigned char j,k;
	cs1=1;cs2=1;
 	write_com(Page_Add+0);
 	write_com(Col_Add+0);
 	for(k=0;k<8;k++)
 	{
		write_com(Page_Add+k);
  		for(j=0;j<64;j++)write_data(0x00);
	}
	cs1=0;cs2=0;
}

/****************************************
定位函数，定位一个字，
其中pag为行数0~3，
col为列数，col=16i，i=0~8
*hzk为要显示的内容；
****************************************/
void hz_disp16(unsigned char pag,unsigned char col, unsigned char code *hzk)
{
	unsigned char j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+pag+j);
		write_com(Col_Add+col);
		for(i=0;i<16;i++) 
		write_data(hzk[16*j+i]);
	}
}

/****************************************
定位函数，定位一个字节，
其中pag为行数0~3，
col为列数，col=8i，i=0~16
*hzk为要显示的内容；
****************************************/
void hz_disp8(unsigned char pag,unsigned char col, unsigned char code *hzk)
{
	unsigned char j=0,i=0;
	for(j=0;j<2;j++)
	{
		write_com(Page_Add+pag+j);
		write_com(Col_Add+col);
		for(i=0;i<8;i++) 
		write_data(hzk[8*j+i]);
	}
			
}

//lcd初始化函数
void Lcd_Init()
{
	delay(100);
	cs1=1;
	cs2=1;
	delay(100);
	write_com(0x83);
	write_com(Disp_Off);
	write_com(Page_Add+0);
	write_com(Start_Line+0);
	write_com(Col_Add+0);
	write_com(Disp_On);

}

/*demo

//盆花自动浇水系统
char code pen[]={
0x20,0x20,0x10,0x08,0x94,0x72,0x10,0x90,0x13,0xF4,0x08,0x10,0x20,0x60,0x20,0x00,
0x40,0x40,0x7D,0x45,0x44,0x7C,0x44,0x44,0x45,0x7C,0x44,0x44,0x7E,0x44,0x40,0x00
};

char code jiao[]={
0x10,0x21,0x62,0x06,0x80,0x08,0x88,0x8B,0x5C,0x24,0x54,0x84,0x86,0xE4,0x00,0x00,
0x04,0x04,0xFE,0x01,0x80,0x82,0x42,0x3E,0x02,0x02,0x7E,0x82,0x82,0x82,0xE0,0x00
};


//显示‘0’，‘1’，‘2’，‘3’，‘4’，‘5’，‘6’，‘7’，‘8’，‘9’
char code base_num[][16]={
//'0'
{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00},
//'1'
{0x00,0x10,0x10,0xF8,0x00,0x00,0x00,0x00,0x00,0x20,0x20,0x3F,0x20,0x20,0x00,0x00},
//'2'
{0x00,0x70,0x08,0x08,0x08,0x88,0x70,0x00,0x00,0x30,0x28,0x24,0x22,0x21,0x30,0x00},
//'3'
{0x00,0x30,0x08,0x88,0x88,0x48,0x30,0x00,0x00,0x18,0x20,0x20,0x20,0x11,0x0E,0x00},
//'4'
{0x00,0x00,0xC0,0x20,0x10,0xF8,0x00,0x00,0x00,0x07,0x04,0x24,0x24,0x3F,0x24,0x00},
//'5'
{0x00,0xF8,0x08,0x88,0x88,0x08,0x08,0x00,0x00,0x19,0x21,0x20,0x20,0x11,0x0E,0x00},
//'6'
{0x00,0xE0,0x10,0x88,0x88,0x18,0x00,0x00,0x00,0x0F,0x11,0x20,0x20,0x11,0x0E,0x00},
//'7'
{0x00,0x38,0x08,0x08,0xC8,0x38,0x08,0x00,0x00,0x00,0x00,0x3F,0x00,0x00,0x00,0x00},
//'8'
{0x00,0x70,0x88,0x08,0x08,0x88,0x70,0x00,0x00,0x1C,0x22,0x21,0x21,0x22,0x1C,0x00},
//'9'
{0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x00,0x31,0x22,0x22,0x11,0x0F,0x00},

{0xE0,0x10,0x08,0x08,0x08,0x10,0xE0,0x00,0x0F,0x18,0x24,0x24,0x38,0x50,0x4F,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x37,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01},

{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0C,0x0C,0x00,0x00,0x00,0x00},

};
	unsigned int temp,humi;		//定义温度和湿度变量
	value humi_val,temp_val;		//定义两个共同体，一个用于湿度，一个用于温度
	unsigned char error;		    //用于检验是否出现错误
	unsigned char checksum;			//CRC			 
	unsigned char  wendu[6];				 	//用于记录温度
	unsigned char  shidu[6];				 	//用于记录湿度		
void System_Show()		//信息显示
{
	cs1=1;cs2=0;
	hz_disp16(0,0,pen);		//盆花自动

			 
	cs1=0;cs2=1;
	hz_disp16(0,0,jiao);	//浇水系统


}
void main()
{
	Lcd_Init();
	
	while(1)
	{
		error=0;					   //初始化error=0，即没有错误
		error+=s_measure((unsigned char*)&temp_val.i,&checksum,TEMP); //温度测量
		error+=s_measure((unsigned char*)&humi_val.i,&checksum,HUMI); //湿度测量
		if(error!=0)
			s_connectionreset();                 ////如果发生错误，系统复位
		else
		{ 		
		humi_val.f=(float)humi_val.i;                   //转换为浮点数
		temp_val.f=(float)temp_val.i;                   //转换为浮点数
		calc_sth10(&humi_val.f,&temp_val.f);            //修正相对湿度及温度
		//   		dew_point=calc_dewpoint(humi_val.f,temp_val.f); //计算e dew_point
		temp=temp_val.f*10;
		humi=humi_val.f*10;	

      		wendu[0]=(temp/1000)/1000;     		//温度百位 
      		wendu[1]=(temp%1000)/100;     	//温度十位	
   			  wendu[2]=(temp%100)/10;			//温度个位
      		wendu[3]=0x2E;						//小数点
   			  wendu[4]=temp%10;				//温度小数点后第一位		
			 
			    shidu[0]=(humi/1000)/1000;     		//湿度百位
      		shidu[1]=(humi%1000)/100;     	//湿度十位	
   			  shidu[2]=(humi%100)/10;			//湿度个位
      		shidu[3]=0x2E;						//小数点
   			  shidu[4]=humi%10;				//湿度小数点后第一位	 

					cs1=0;cs2=1;
					hz_disp8(2,0,base_num[wendu[0]]);	//显示温度
					hz_disp8(2,8,base_num[wendu[1]]);
					hz_disp8(2,16,base_num[wendu[2]]);
					hz_disp8(2,24,base_num[14]);
					hz_disp8(2,32,base_num[wendu[4]]);
					hz_disp8(2,40,base_num[12]);

					hz_disp8(4,0,base_num[shidu[0]]);	//显示湿度
					hz_disp8(4,8,base_num[shidu[1]]);
					hz_disp8(4,16,base_num[shidu[2]]);
					hz_disp8(4,24,base_num[14]);
					hz_disp8(4,32,base_num[shidu[4]]);
					hz_disp8(4 ,40,base_num[12]);

			
		System_Show();
		}
	}
}

*/
#endif

/********************IR_SEND*********************/
#if CONFIG_IRSEND == ENABLED


//红外发射管的亮灭控制
static bit OP;
//延时计数器
static unsigned int count;
//终止延时计数器
static unsigned int  endcount;
//红外发送标志
static unsigned char flag;
//16位地址 第一字节
char iraddr1;
//16位地址 第二字节
char iraddr2;

unsigned char Menu_Count =0;

//定时器0中断处理函数
void timeint(void) interrupt 1
{
	//设定定时器初值
	TH0=0xff;
	TL0=0xe6;
	
	//中断计数累加
	count++;
	if(flag==1)
	{
		OP=~OP;
	}
	else
	{
		OP=0;
	}
	HL=OP;
}

//发送数据函数
//发送的延时时间参数即(endcount)都是在12MHZ的值
void SendIRdata(char p_irdata)
{
	int i;
	char irdata=p_irdata;
	
	//发送9ms的起始码
	endcount=223;
	flag=1;
	count=0;
	while(count<endcount);

	//发送4.5ms的结果码
	endcount=117;
	flag=0;
	count=0;
	do{}while(count<endcount);

	//发送16位地址的前八位
	irdata=iraddr1;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}

	//发送16位地址的后八位
	irdata=iraddr2;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}


	//发送8位数据
	irdata=p_irdata;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}


	//发送8位数据反码
	irdata=~p_irdata;
	for(i=0;i<8;i++)
	{
		//先发送0.56ms的38K红外波(即编码中的0.56ms的低电平）
		endcount=13;
		flag=1;
		count=0;
		do{}while(count<endcount);

		//停止发送红外信号(即编码中的高电平)
		if(irdata-(irdata/2)*2)//判断二进制的个位是1还是0
		{
			endcount=41;//1
		}
		else
		{
			endcount=13;//0
		}
		flag=0;
		count=0;
		do{}while(count<endcount);
		irdata=irdata>>1;
	}
	//结束信息
	endcount=13;
	flag=1;
	count=0;
	do{}while(count<endcount);
	flag=0;
}


void IR_SEND_INIT()
{
	//初始化
	count=0;
	flag=0;
	OP=0;
	HL=0;
	//数码管初始化
	//总中断开
	EA=1;
	//设置定时器0和1为16位模式
	TMOD=0x11;
	//定时器0中断允许
	ET0=1;
	//设定定时大小 38K 等加于 26us中断一次             
	TH0=0xff;
	TL0=0xe6;
	//开始计数
	TR0=1;
	
	//写16位地址
	iraddr1=0;
	iraddr2=255;
}



#endif

#if CONFIG_IR_REVICE == ENABLED

unsigned char ir_num;	
#define Imax 14000    //此处为晶振为11.0592时的取值, 
#define Imin 8000    //如用其它频率的晶振时,没
#define Inum1 1450    //要改变相应的取值。
#define Inum2 700 
#define Inum3 3000 

unsigned long f=0;
unsigned long m,Tc;	  // 变量申明
unsigned char IrOK;		// 变量申明
unsigned char Im[4]={0x00,0x00,0x00,0x00};	 //IRCOM[0]~IRCOM[3]：地址码、地址反码、按键码、按键反码(都是十六进制)

/*******************************************************************/
void IR_Init(void)
{
	TMOD|=0x01;		//定时器0和定时器1都是方式1,16位定时器
	TL0 = 0xb0;     
	TH0 = 0x3c;     //定时器赋予初值
	IT0=1,//下降沿触发
	EX0=1;//外部中断0     使能位	
	TR0=1;
	//ET0 = 1;        //允许定时器0中
	EA=1;//	总中断
} 



void Timer0_ISR (void) interrupt 1 using 1
{

	TH0=0X3C;							//重赋初值
	TL0=0XBA;

}
void int0() interrupt 0	using 1  		//外部中断0 服务
{
	Tc=TH0*256+TL0; //定时器清空只记TC 值                                              //提取中断时间间隔时长
	TH0=0; 
	TL0=0;              //定时中断重新置零

	if((Tc>Imin)&&(Tc<Imax))//启动码判定 两个时间对比0.9MS	
	{  
		m=0;
		f=1;
		//ET0 = 1;

		return;
	}       //找到启始码

	if(f==1)
	{
		if(Tc>Inum1&&Tc<Inum3) //判定是0该还是1 是0 1.125MS 是1  2.25MS
		{
		Im[m/8]=Im[m/8]>>1|0x80; m++;  //存0
		}
		if(Tc>Inum2&&Tc<Inum1) 
		{
		Im[m/8]=Im[m/8]>>1; m++; //	存1
		}
		if(m==32) 	//32位存储完毕
		{
		m=0;  
		f=0;
		if(Im[2]==~Im[3])  //反码检查
		{	 
		IrOK=1; 	//OK 完成
		}
		else IrOK=0;   //取码完成后判断读码是否正确
		}
		//准备读下一码
	}
	if(IrOK)
	{
		switch(Im[2])
		{
			case (0x45): ir_num=1;break;
			case (0x46): ir_num=2;break;
			case (0x47): ir_num=3;break;
			case (0x44): ir_num=4;break;	 //
			case (0x40): ir_num=5;break;		
			case (0x43): ir_num=6;break;
			case (0x07): ir_num=7;break;	  
		}
	}	

}


#endif

#if CONFIG_DS18B20_MULT== ENABLED

bit first =1;
idata unsigned char ID[MAXNUM][8];
unsigned char num=0;
unsigned char temp_l,temp_h,temp_over,t; 
bit negetiveflag=0;
signed char tempalarm=0;
void delay_nus(unsigned int n)//?? ?? ??8+6(??)=14us
{
	while(n--);
}

void reset(void)  //ds18b20???????
{
	 unsigned char x=0;
	 DQ = 1;          	//DQ??
	 delay_nus(8);  	//????
	 DQ = 0;          	//????DQ??
	 delay_nus(80); 	//???? ?? 480us
	 DQ = 1;          	//????
	 delay_nus(10);
	 x=DQ;            	//????? ??x=0?????? x=1??????
	 delay_nus(5);
}

void write_bit(unsigned char dat)	//DS18B20 ??? ??
{
  	DQ = 0;
	_nop_();
    _nop_();
 	DQ = dat&0x01;
    delay_nus(5);
 	DQ = 1;
}

void write_byte(unsigned char dat)//?????
{
 	unsigned char i,j;
 	for (i=8; i>0; i--)
 	{
		j=dat&0x01;
  		write_bit(j);
		dat>>=1;
    }
}

unsigned char read_2bit(void)//??? ???
{
	unsigned char i;
	unsigned char dat = 0;
	for (i=2;i>0;i--)
	{
		DQ = 0; // ?????
		dat<<=1;
		DQ = 1; // ?????
		if(DQ)
		dat|=0x01;
		delay_nus(4);
	}
 	return(dat);
}

unsigned char read_byte(void)//????? ???
{
	unsigned char i=0;
	unsigned char dat = 0;
	for (i=8;i>0;i--)
	{
		DQ = 0; // ?????
		dat>>=1;
		DQ = 1; // ?????
		if(DQ)
		dat|=0x80;
		delay_nus(4);
	}
 	return(dat);  
}
void delay_nms(unsigned int n)
{
	unsigned int j=0;
	unsigned char i=0;
	for(j=0;j<n;j++)
	{
		for(i=0;i<120;i++)
		{
			_nop_();
		}
	}
}


void read_temp(unsigned char num_data)//???? ??? ???????????
{
	unsigned char f;	
	reset();
	write_byte(0xcc);//????ROM???
	write_byte(0x44);//????????
	if(first)
	{
		first =0;
		delay_nms(2000);
	}
	else
		delay_nms(100);		
	reset();
	write_byte(0x55);//????ROM???
	for(f=0;f<8;f++) //8??ROM?
	{
		write_byte(ID[num_data][f]);//???ROM
	}
	
	delay_nus(100);
	write_byte(0xbe);//??????
	delay_nus(100);
	temp_l=read_byte();
	temp_h=read_byte();
}

 
void temp_convert(void)//????
{
	negetiveflag=0;
	negetiveflag=temp_h&0x80;
	if(negetiveflag)
	{
		negetiveflag=1;
		temp_h=~temp_h;
  		if(temp_l==0)
		{
		 	temp_h++;  //??8???0?????,?????????1
		}
  		temp_l=~temp_l+1; 
	}
	temp_h<<=4;
	temp_l>>=4;
	temp_over=temp_h|temp_l;
	tempalarm=temp_over;
	if(negetiveflag==1)
	{
		 tempalarm=tempalarm*(-1);
	}
}
void display_total(void)	  //??????DS18B20?????
{
	//Lcd1602_Display_String(0,0,"total num :");
	//Lcd1602_Display_Two_bit(0,10,num);
}
/***********************????ROM*****************************/
void search_rom(void)//??ROM
{ 
	unsigned char k=0,l=0,chongtuwei=0,m=0,n=0;
	unsigned char s=0;
	unsigned char zhan[MAXNUM];
	unsigned char ss[64];
	do
	{
		reset();
		write_byte(0xf0);  //??ROM??	
		for(m=0;m<8;m++)
		{
			for(n=0;n<8;n++)
			{
				k=read_2bit();//?????
				k=k&0x03;   
				s>>=1;
				if(k==0x01)//01??????0 ?0 ???0?????
				{   		
					write_bit (0);
	    			ss[(m*8+n)]=0;
				}
				else if(k==0x02)//??????1 ?1 ???1?????
				{
					s=s|0x80;
					write_bit (1);
					ss[(m*8+n)]=1;
				}
				else if(k==0x00)//??????0  ???? ????? 
				{				//??????????0 ????????? ?????1
					chongtuwei=m*8+n+1;					
					if(chongtuwei>zhan[l])
					{						
						write_bit (0);
						ss[(m*8+n)]=0;												
						zhan[++l]=chongtuwei;						
					}
					else if(chongtuwei<zhan[l])
					{
						s=s|((ss[(m*8+n)]&0x01)<<7);
						write_bit (ss[(m*8+n)]);
					}
					else if(chongtuwei==zhan[l])
					{
						s=s|0x80;
						write_bit (1);
						ss[(m*8+n)]=1;
						l=l-1;
					}
				}
				else
				{
					goto loop;
				}
			}
			ID[num][m]=s;		
		}
		num++;
	}
	while(zhan[l]!=0&&(num<MAXNUM));		
loop:
	//search_cartoon();
	display_total();

}

void DS18B20_Processing(unsigned char *Temp_Value)
{
	static unsigned char i=0;

	ET0 = 0;					
	read_temp(i);   //??? i ?ds18b20 ???
	ET0 = 1;

	temp_convert(); //??????

	switch(i)
	{
		case 0:
			Temp_Value[0] = tempalarm;					
		break;

		case 1:
			Temp_Value[1] = tempalarm;

						
		break;			
		case 2:
			Temp_Value[2] = tempalarm;

		break;	

		case 3:
			Temp_Value[3] = tempalarm;

		break;	
		case 4:
			Temp_Value[4] = tempalarm;	

		break;							
	}
	i++;
	if(i >= num)
	i = 0;
}
#endif

#if CONFIG_LCD12864_PLUS== ENABLED



unsigned char code zm8x16_index[]="0123456789: |-+.";//字串索引
unsigned char code zm8x16_Table[][16]={
	0xF8,0xFC,0x04,0xC4,0x24,0xFC,0xF8,0x00,0x07,0x0F,0x09,0x08,0x08,0x0F,0x07,0x00, // -0-
	//0x00,0xE0,0x10,0x08,0x08,0x10,0xE0,0x00,0x00,0x0F,0x10,0x20,0x20,0x10,0x0F,0x00,
	0x00,0x10,0x18,0xFC,0xFC,0x00,0x00,0x00,0x00,0x08,0x08,0x0F,0x0F,0x08,0x08,0x00, // -1-
	0x08,0x0C,0x84,0xC4,0x64,0x3C,0x18,0x00,0x0E,0x0F,0x09,0x08,0x08,0x0C,0x0C,0x00, // -2-
	0x08,0x0C,0x44,0x44,0x44,0xFC,0xB8,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00, // -3-
	0xC0,0xE0,0xB0,0x98,0xFC,0xFC,0x80,0x00,0x00,0x00,0x00,0x08,0x0F,0x0F,0x08,0x00, // -4-
	0x7C,0x7C,0x44,0x44,0xC4,0xC4,0x84,0x00,0x04,0x0C,0x08,0x08,0x08,0x0F,0x07,0x00, // -5-
	0xF0,0xF8,0x4C,0x44,0x44,0xC0,0x80,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00, // -6-
	0x0C,0x0C,0x04,0x84,0xC4,0x7C,0x3C,0x00,0x00,0x00,0x0F,0x0F,0x00,0x00,0x00,0x00, // -7-
	0xB8,0xFC,0x44,0x44,0x44,0xFC,0xB8,0x00,0x07,0x0F,0x08,0x08,0x08,0x0F,0x07,0x00, // -8-
	0x38,0x7C,0x44,0x44,0x44,0xFC,0xF8,0x00,0x00,0x08,0x08,0x08,0x0C,0x07,0x03,0x00, // -9-
	0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x06,0x00,0x00,0x00, // -:-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, // - -
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00, // -|-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01, // ---
	0x00,0x00,0x00,0x00,0xFF,0x00,0x00,0x00,0x01,0x01,0x01,0x01,0xFF,0x01,0x01,0x01, // -+-
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00,0x00,0x00,0x00,/*".",0*/	
};
unsigned char code zm16x16_index[]="  欢迎使用密码锁请输入密码";//字串索引
unsigned char code zm16x16_Table[][32]={
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",0*/

0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,/*" ",1*/

0x04,0x24,0x44,0x84,0x64,0x9C,0x40,0x30,0x0F,0xC8,0x08,0x08,0x28,0x18,0x00,0x00,
0x10,0x08,0x06,0x01,0x82,0x4C,0x20,0x18,0x06,0x01,0x06,0x18,0x20,0x40,0x80,0x00,/*"?",2*/

0x40,0x40,0x42,0xCC,0x00,0x00,0xFC,0x04,0x02,0x00,0xFC,0x04,0x04,0xFC,0x00,0x00,
0x00,0x40,0x20,0x1F,0x20,0x40,0x4F,0x44,0x42,0x40,0x7F,0x42,0x44,0x43,0x40,0x00,/*"?",3*/

0x80,0x60,0xF8,0x07,0x04,0xE4,0x24,0x24,0x24,0xFF,0x24,0x24,0x24,0xE4,0x04,0x00,
0x00,0x00,0xFF,0x00,0x80,0x81,0x45,0x29,0x11,0x2F,0x41,0x41,0x81,0x81,0x80,0x00,/*"?",4*/

0x00,0x00,0xFE,0x22,0x22,0x22,0x22,0xFE,0x22,0x22,0x22,0x22,0xFE,0x00,0x00,0x00,
0x80,0x60,0x1F,0x02,0x02,0x02,0x02,0x7F,0x02,0x02,0x42,0x82,0x7F,0x00,0x00,0x00,/*"?",5*/

0x10,0x8C,0x44,0x04,0xE4,0x04,0x95,0xA6,0x44,0x24,0x14,0x84,0x44,0x94,0x0C,0x00,
0x02,0x02,0x7A,0x41,0x41,0x43,0x42,0x7E,0x42,0x42,0x42,0x43,0xF8,0x00,0x00,0x00,/*"?",6*/

0x04,0x84,0xE4,0x5C,0x44,0xC4,0x00,0x02,0xF2,0x82,0x82,0x82,0xFE,0x80,0x80,0x00,
0x02,0x01,0x7F,0x10,0x10,0x3F,0x00,0x08,0x08,0x08,0x08,0x48,0x88,0x40,0x3F,0x00,/*"?",7*/

0x20,0x10,0x2C,0xE7,0x24,0x24,0x00,0xE2,0x2C,0x20,0xBF,0x20,0x28,0xE6,0x00,0x00,
0x01,0x01,0x01,0x7F,0x21,0x11,0x80,0x4F,0x20,0x10,0x0F,0x10,0x20,0x4F,0x80,0x00,/*"?",8*/

0x40,0x42,0xCC,0x00,0x00,0x44,0x54,0x54,0x54,0x7F,0x54,0x54,0x54,0x44,0x40,0x00,
0x00,0x00,0x7F,0x20,0x10,0x00,0xFF,0x15,0x15,0x15,0x55,0x95,0x7F,0x00,0x00,0x00,/*"?",9*/

0x88,0x68,0x1F,0xC8,0x08,0x10,0xC8,0x54,0x52,0xD1,0x12,0x94,0x08,0xD0,0x10,0x00,
0x09,0x19,0x09,0xFF,0x05,0x00,0xFF,0x12,0x92,0xFF,0x00,0x5F,0x80,0x7F,0x00,0x00,/*"?",10*/

0x00,0x00,0x00,0x00,0x00,0x01,0xE2,0x1C,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x80,0x40,0x20,0x10,0x0C,0x03,0x00,0x00,0x00,0x03,0x0C,0x30,0x40,0x80,0x80,0x00,/*"?",11*/

0x10,0x8C,0x44,0x04,0xE4,0x04,0x95,0xA6,0x44,0x24,0x14,0x84,0x44,0x94,0x0C,0x00,
0x02,0x02,0x7A,0x41,0x41,0x43,0x42,0x7E,0x42,0x42,0x42,0x43,0xF8,0x00,0x00,0x00,/*"?",12*/

0x04,0x84,0xE4,0x5C,0x44,0xC4,0x00,0x02,0xF2,0x82,0x82,0x82,0xFE,0x80,0x80,0x00,
0x02,0x01,0x7F,0x10,0x10,0x3F,0x00,0x08,0x08,0x08,0x08,0x48,0x88,0x40,0x3F,0x00,/*"?",13*/

			
};
/** LCM忙检测 **/
void busy12864(){
	lcdDat=0xff;    //口线置1，防止干扰
	rs=0; rw=1;	   //置“命令、读”模式
	//en=1; while(lcdDat&0x80); en=0;//忙等待
}
/** 写命令 参数：comDat为要发送的命令 **/
void WriteCom(unsigned char comDat){  
    busy12864();     		//忙，则等待
	rs=0;rw=0;				//置“命令、写”模式
    lcdDat=comDat;en=1;en=0;//送出命令，并使之有效
}
/** 写数据 参数：dat为要发送的数据 **/
void WriteDat(unsigned char dat){  
    busy12864();  		 	//忙，则等待
	rs=1;rw=0;			  	//置“数据、写”模式
    lcdDat=dat;en=1;en=0;	//送出数据，并使之有效
}
/** 初始化12864 **/
void Init12864(){
	lcdDat=0xff;   //口线置1，防止干扰
	rs=0; rw=1;	   //置“命令、读”模式
	//en=1; while(lcdDat&0x10); en=0;//等待复位完成
	WriteCom(0x3f);	  //开显示
	WriteCom(addZ0);	  //设置显示起始行
}

/******** 任意尺寸点阵显示函数 ***********|
|参数：显示位置：row页数，col列号，		  |
|	   字符大小：x横向像素，y纵向页数	  |
|	   显示内容：tab字模表          ******/
void showXY(unsigned char row,unsigned char col,unsigned char x,unsigned char y,unsigned char *tab){
	unsigned char i,j;
	bit right;
	if(col<64){right=0;} //置左右屏标志
	else {col-=64;right=1;}	
	for(i=0;i<y;i++){
		if(right)cs2=0,cs1=1;
		else  cs2=1,cs1=0;
		WriteCom(addX0+row+i); //行
		WriteCom(addY0+col);   //列
		for(j=0;j<x;j++){
			if(col+j<64)WriteDat(tab[i*x+j]); //未跨屏
			else if(right==0){		  //从左屏跨右屏
				 cs2=0,cs1=1;		  //选中右屏
				 WriteCom(addX0+row+i);	   //设置行
				 WriteCom(addY0+(col+j-64));
				 WriteDat(tab[i*x+j]);
			}						 //在右屏越界不显示
		}
	}
}

/* 返回一个8*16字符索引位置 */					
unsigned char enN(unsigned char *s){
	unsigned char i;
	for(i=0;zm8x16_index[i]!=0;i++)if(zm8x16_index[i]==s[0])break;
	return i;	
}
/* 返回一个16*16字符索引位置 */
unsigned char cnN(unsigned char *s){
	unsigned char i;
	for(i=0;zm16x16_index[i]!=0;i+=2)
		if(zm16x16_index[i]==*s&&zm16x16_index[i+1]==*(s+1))break ;
	return i/2;
}
/* 显示中英文字符串 */
void showStr(unsigned char row,unsigned char col,unsigned char *s){
	 unsigned char i;
	 for(i=0;s[i]!=0;i++){
	 	if(s[i]<0x80){ 	//英文
			showXY(row,col,8,2,zm8x16_Table[enN(&s[i])]);
			col+=8;
		}else{			
			showXY(row,col,16,2,zm16x16_Table[cnN(&s[i])]);	
			col+=16;i+=1;		
		}
		if(col>120){	 //换行处理
			col=0;
			row+=2;
		}
	 }
}
/* 显示数字 */
void showNum(unsigned char row,unsigned char col,unsigned char s){
	showXY(row,col,8,2,zm8x16_Table[s]);
}
void showThreeNum(unsigned char row,unsigned char col,unsigned int s)
{
	showNum(row,col,s/100%10);
	showNum(row,col+8,s/10%10);
	showNum(row,col+16,s%10);
}
#if CONFIG_DS18b02 == ENABLED
void showDS18B02Num(unsigned char row,unsigned char col,unsigned int s)
{
	showNum(row,col,s/100%10);
	showNum(row,col+8,s/10%10);
	showStr(row,col+16,".");
	showNum(row,col+24,s%10);
}
#endif
#if CONFIG_DS1302 == ENABLED
void Ds13b02_DisPlay_12864(unsigned char row,unsigned char col,unsigned char shi,unsigned char fen,unsigned char miao)
{

	showNum(row,col,shi%100/10);		// 十位
	showNum(row,col+8,shi%10);				// 个位
	showStr(row,col+8*2,":");
	showNum(row,col+8*3,fen%100/10);		// 十位
	showNum(row,col+8*4,fen%10);				// 个位
	showStr(row,col+8*5,":");
	showNum(row,col+8*6,miao%100/10);		// 十位
	showNum(row,col+8*7,miao%10);				// 个位

}
#endif
#endif

#if CONFIG_KEY_MAP_2== ENABLED

void key_Map_delay(unsigned int i){ while(i--);}
unsigned char key_get(){
    unsigned char k=16;
    col0=col1=col2=col3=row0=row1=row2=row3=1;
    row0=0; k=col0==0?0:col1==0?1:col2==0?2:col3==0?3:k; row0=1;
    row1=0; k=col0==0?4:col1==0?5:col2==0?6:col3==0?7:k; row1=1;
		row2=0; k=col0==0?8:col1==0?9:col2==0?10:col3==0?11:k; row2=1;
		row3=0; k=col0==0?12:col1==0?13:col2==0?14:col3==0?15:k; row3=1;
    return k;  //返回键值
}
bit keyFlag=0;
void Key_Map(pKey_Map_Process key_Map_Process)
{
	if(key_get()!=16&&keyFlag==0)
	{
		key_Map_delay(200);
		if(key_get()!=16)
		{
			keyFlag=1;
			key_Map_Process(key_get());
		}
	}
	if(key_get()==16&&keyFlag==1)keyFlag=0;	//键释放
}
#endif

#if CONFIG_MAX6675== ENABLED

void MAX6675_Delay(void)
{
	_nop_();	
	_nop_();	
	_nop_();	
}

//volatile unsigned short MAX6675_Temp[4] = {0,0,0,0};

void MAX6675_Processing(unsigned char CH,unsigned short *MAX6675_Temp)
{
	
	unsigned char i;   
	unsigned int dat;
	unsigned int t;
	
	unsigned char Flag_connect;
	
	i   = 0;   
	dat = 0;   
	
	switch(CH)
	{
		case 0:	CS1 = 0;break;
		case 1: CS2 = 0;break;
		case 2: CS3 = 0;break;
		case 3: CS4 = 0;break;
	}

	MAX6675_Delay();
	MAX6675_SCK = 0;     
	MAX6675_Delay();
	
	for(i=0; i<16; i++)		//get D15-D0 from 6675  
	{      
		MAX6675_SCK = 1; 
		MAX6675_Delay();    
		dat = dat<<1;  
		
		if(  SO == 1 )   
			dat = dat|0x01;  
		
		MAX6675_SCK = 0;   
		MAX6675_Delay();		
	} 
	
	switch(CH){case 0:CS1  = 1; break;case 1: CS2 = 1;break;case 2: CS3 = 1;break;case 3: CS4 = 1;break;}
	
	MAX6675_Delay();  
	
	t = dat;
	

  Flag_connect = t&0x04;		 	//读出数据的D2位是热电偶掉线标志位，该位为1表示掉线，该位为0表示连接
  Flag_connect = Flag_connect>>2; 	//MAX6675是否在线

	t = t<<1;					   	//读出来的数据的D3~D14是温度值
	t = t>>4;
	
	MAX6675_Temp[CH] = (t/4)-5;				//测得的温度单位是0.25，所以要乘以0.25（即除以4）才能得到以度为单位的温度值
		
}
#endif

#if CONFIG_GSM== ENABLED

void GSM_delay_ms(unsigned int z)
{
	unsigned int i1,j1;
		for(i1=z;i1>0;i1--)
			for(j1=110;j1>0;j1--);
}
void Uart_init()
{
	TMOD|= 0X21;		//T1  方式2  ，8位   自动重装   
	TH1=0Xfd;
	TL1=0Xfd;	    //9600

	ET0=1;
	TR1=1; 		    // 定时器1启动  
	SM0=0;	    // 设置串口的工作模式
	SM1=1; 	    //方式1
	REN=1; 		 // 允许串口接收数据 	 
	ES=1; 	     // 串口中断应许 
	EA=1;		 // 开启中断
}

void SendASC(unsigned char d)
{
	
	SBUF=d;
	while(!TI);

	TI=0;
}
void SendString(unsigned char *str)	
{
	while(*str)
	{
		SendASC(*str) ;
		str++;
	}
}
void SendNum(unsigned char num)
{
	SendASC('0');
	SendASC('0');
	SendASC('3');
	SendASC(0x30+num);	
}
void SendNum_char(unsigned char num)
{
	SendASC('0');
	SendASC('0');
	SendASC('3');
	SendASC(num);	
}
void SendTwoNum(unsigned char num)
{
		if(num>=100)
		   num = 99;
		SendNum(num/10);
		SendNum(num%10);	
}
void Gsm_init()
{
	Uart_init();
	GSM_delay_ms(500);
}
#if 0
/*********************************************************************
 *                  C51中字符串函数的扩充                            *
 ** 函数名称    : strsearch ()
 ** 函数功能    : 在指定的数组里连续找到相同的内容
 ** 入口参数   ： ptr2=要找的内容, ptr1 当前数组
 **** 出口参数 ： 0-没有 找到   >1 查找到
 *********************************************************************/
//本函数是用来检查字符串*ptr2是否完全包含在*ptr1中
//返回:  0  没有找到
//       1-255 从第N个字符开始相同
unsigned char strsearch(unsigned char *ptr2,unsigned char *ptr1_at)//查字符串*ptr2在*ptr1中的位置

{
	unsigned int i2,j2,k2;
	if(ptr2[0]==0)
	return(0);

	for(i2=0,j2=0;i2<RsBuf_N;i2++)
	{
		if(ptr1_at[i2]==ptr2[j2])
		{//第一个字符相同
			k2=i2;
			do {
			if(ptr2[j2]=='\0')//比较正确
			return(i2+1);               //返回值是整数，不含0
			if(ptr1_at[k2]!=ptr2[j2])
			break;
			k2++;j2++ ;	 
			}
			while(k2<RsBuf_N) ;
			j2=0;
		}
	}
	return(0);
}
#endif
//  通讯中断接收程序   中断函数无返回值
void uart_rx()  interrupt 4	using 3	  //放在这里 和放在main（）里面是一样的
{
	RI=0;
}
#endif

#if CONFIG_STEPMOTO== ENABLED

static MotoTimer2_Process  Moto_Interrp_Process;

unsigned char MotoTimeCtr;

void MotoTimer2_init_Demo(MotoTimer2_Process T_Process)
{
	RCAP2H = (0XFFFF - TIME_HAPPEND)/256;
	RCAP2L = (0XFFFF - TIME_HAPPEND)%256;
	T2CON =0;
	IE |=0xA0;
	
	Moto_Interrp_Process = T_Process;
	TR2 = 1;
}

void timer2() interrupt 5
{
	TF2 = 0;
	MotoTimeCtr++;
	if(MotoTimeCtr >= TIME_COUNT)
	{
		MotoTimeCtr =0;
		Moto_Interrp_Process();
	}
		
}


void DelayMoto(unsigned int i)//延时
{
	while(--i);
}
/***********************正转****************************/
void zheng(unsigned char dat)
{
	switch(dat)
	{
		case 0: dj1=1;dj2=0;dj3=0;dj4=0; break;
		case 1: dj1=0;dj2=1;dj3=0;dj4=0; break;
		case 2: dj1=0;dj2=0;dj3=1;dj4=0; break;
		case 3: dj1=0;dj2=0;dj3=0;dj4=1; break;
	}
}

/***********************正转****************************/
void fan(unsigned char dat)
{
	switch(dat)
	{
		case 0: dj1=0;dj2=0;dj3=0;dj4=1; break;
		case 1: dj1=0;dj2=0;dj3=1;dj4=0; break;
		case 2: dj1=0;dj2=1;dj3=0;dj4=0; break;
		case 3: dj1=1;dj2=0;dj3=0;dj4=0; break;
	}
}
void stop()
{
	dj1=0;dj2=0;dj3=0;dj4=0;
}
void MotoStepSpeed(unsigned char status,unsigned int speed,unsigned int count)
{
	unsigned char i;
	unsigned int j;
	if(status == 0)
	{
		for(j=0;j<count;j++)
		{
			for(i=0;i<4;i++)
			{
				zheng(i);
				DelayMoto(speed);
			}			
		}

	}else
	{
		for(j=0;j<count;j++)
		{
			for(i=0;i<4;i++)
			{
				fan(i);
				DelayMoto(speed);
			}			
		}		
	}
}

#endif

#if CONFIG_7BIT_4_LED== ENABLED
#if 0
typedef void (*Num_Process)();
sbit LED_A = P0^0;
sbit LED_B = P0^1;
sbit LED_C = P0^2;
sbit LED_D = P0^3;
sbit LED_E = P0^4;
sbit LED_F = P0^5;
sbit LED_G = P0^6;
sbit LED_H = P0^7;
sbit LED_S1 = P2^0;
sbit LED_S2 = P2^1;
sbit LED_S3 = P2^2;
sbit LED_S4 = P2^3;
#define NUM_0 {LED_A=0;LED_B=0;LED_C=0;LED_D=0;LED_E=0;LED_F=0;LED_G=1;LED_H=1;}
#define NUM_1 {LED_A=1;LED_B=0;LED_C=0;LED_D=1;LED_E=1;LED_F=1;LED_G=1;LED_H=1;}

void numProcess_0(){NUM_0}
Num_Process numProcess[10]={numProcess_0};
#endif
/**demo

static Timer2_Process  Interrp_Process;


void Timer2_init_Demo(Timer2_Process T_Process)
{
	RCAP2H = (0XFFFF - 5000)/256;
	RCAP2L = (0XFFFF - 5000)%256;
	T2CON =0;
	IE |=0xA0;
	TR2 = 1;
	Interrp_Process = T_Process;
}

void timer2() interrupt 5
{
	TF2 = 0;
	Interrp_Process();
	}
		
}

//P0~7,对应数码管的abcdefgh
//uchar code  LEDData[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90,0xff,0xc6,0x88,0x86};//0123456789CAE
//p0~7,对应数据管的afbedhcg,且需要取反~LEDData[]
uchar code  LEDData[]={0x5F,0x44,0x9D,0xD5,0xC6,0xD3,0xDB,0x47,0xDF,0xD7,0xCF,0xDA,0x9B,0xDC,0x9B,0x8B,};//0123456789ABCDE
void Timer2_Process2()
{
	P2=0xff;
	P0 = DisplayNum[DisplayBit];
	switch(DisplayBit)
	{
		case 0:
			P2 = 0XFD;//相应的数码管片选拉低拉高
		break;
		case 1:
			P2 = 0XF7;
		break;
		case 2:
			P2 = 0xDF;
		break;
		case 3:
			P2 = 0x7F;
		break;			
	}	
	DisplayBit++;
	if(DisplayBit>=4)
	{	
		DisplayBit=0;
	}
		
	
}
void main()
{
	Timer2_init_Demo(Timer2_Process2);
	DisplayNum[0] = ~LEDData[10];
	DisplayNum[1] = ~LEDData[1];
	DisplayNum[2] = ~LEDData[0];
	DisplayNum[3] = ~LEDData[12];	
	while(1);
}
**/
#endif

#if CONFIG_BULETOOTH == ENABLED
unsigned char *a;
void Bluetooth_Delay_Ms(int cnt)
{
	unsigned char i, j;

	while(cnt--)
	{

		i = 2;
		j = 199;
		do
		{
			while (--j);
		} while (--i);
	}
}
//*********主函数*****************
//9600bps
void Bluetooth_uart_init(unsigned char *buff)
{
	TMOD |= 0x20;
	TH1 = 0xfd;
	TL1 = 0xfd;
	TR1 = 1;
	SM0 = 0;
	SM1 = 1;
	REN = 1;
	EA = 1;
	ES = 1;
	TI = 1;
	a= buff;
}
void Bluetooth_UartSendByte(unsigned char byte)
{
	SBUF = byte;
	while(!TI);
		TI = 0;
}


void Bluetooth_UartSendString(unsigned char *string)
{
	while(*string)
	{
		Bluetooth_UartSendByte(*string++);
	}
}


void ser() interrupt 4
{
	if(RI)
	{
		RI = 0;
		*a = SBUF;
	}
}
 
/**demo 

//接收到的数据
unsigned char revbuff;
unsigned char buff[20];
void bluetooth_send()
{
	
	static unsigned int Cnt1 = 1;
	Cnt1++;
  if(Cnt1 >= 40)
	{
			Cnt1 = 0;
			buff[0]= 'H';
			buff[1]= ':';
			buff[2]= Length_Value/100%10+0x30;
			buff[3]= Length_Value/10%10+0x30;
			buff[4]= Length_Value%10+0x30;
			buff[5]= ',';
			buff[6]= adcx/1000%10+0x30;
			buff[7]= adcx/100%10+0x30;
			buff[8]= adcx/10%10+0x30;
			buff[9]= adcx%10+0x30;	
			buff[10]= ',';
			buff[11]= autoFlag+0x30;
			buff[12]= ',';			
			buff[13]= 'E';	
			Bluetooth_UartSendString(buff);		
	}
	

}
void main()
{
	Bluetooth_uart_init(&revbuff);
	while(1)
	{
		bluetooth_send();
		
	}
}
**/
#endif

#if CONFIG_PCF8591 == ENABLED
bit PCF859_ack;                 /*应答标志位*/
   
/*******************************************************************
                     起动总线函数               
函数原型: void  Start_I2c();  
功能:     启动I2C总线,即发送I2C起始条件.  
********************************************************************/
void PCF8591_Start()
{
	PCF8591_SDA=1;         /*发送起始条件的数据信号*/
	_Nop();
	PCF8591_SCL=1;
	_Nop();        /*起始条件建立时间大于4.7us,延时*/
	_Nop();_Nop();_Nop();_Nop();    
	PCF8591_SDA=0;         /*发送起始信号*/
	_Nop();        /* 起始条件锁定时间大于4μs*/
	_Nop();_Nop();_Nop();_Nop();       
	PCF8591_SCL=0;       /*钳住I2C总线，准备发送或接收数据 */
	_Nop();_Nop();
}
/*******************************************************************
                      结束总线函数               
函数原型: void  Stop_I2c();  
功能:     结束I2C总线,即发送I2C结束条件.  
********************************************************************/
void PCF8591_Stop()
{
  PCF8591_SDA=0;      /*发送结束条件的数据信号*/
  _Nop();       /*发送结束条件的时钟信号*/
  PCF8591_SCL=1;      /*结束条件建立时间大于4μs*/
  _Nop();_Nop();_Nop();_Nop();_Nop();
  PCF8591_SDA=1;      /*发送I2C总线结束信号*/
  _Nop();_Nop();_Nop();_Nop();
}
/*******************************************************************
                 字节数据发送函数               
函数原型: void  SendByte(UCHAR c);
功能:     将数据c发送出去,可以是地址,也可以是数据,发完后等待应答,并对
          此状态位进行操作.(不应答或非应答都使ack=0)     
           发送数据正常，ack=1; ack=0表示被控器无应答或损坏。
********************************************************************/
void  PCF8591_SendByte(unsigned char  c)
{
 unsigned char  BitCnt; 
 for(BitCnt=0;BitCnt<8;BitCnt++)  /*要传送的数据长度为8位*/
    {
     if((c<<BitCnt)&0x80)PCF8591_SDA=1;   /*判断发送位*/
       else  PCF8591_SDA=0;                
     _Nop();
     PCF8591_SCL=1;               /*置时钟线为高，通知被控器开始接收数据位*/
      _Nop(); _Nop();             /*保证时钟高电平周期大于4μs*/
      _Nop();_Nop();_Nop();         
     PCF8591_SCL=0; 
    } 
    _Nop();_Nop();
    PCF8591_SDA=1;                /*8位发送完后释放数据线，准备接收应答位*/
    _Nop();_Nop();   
    PCF8591_SCL=1;
    _Nop();_Nop();_Nop();
    if(PCF8591_SDA==1)PCF859_ack=0;     
       else PCF859_ack=1;        /*判断是否接收到应答信号*/
    PCF8591_SCL=0;
    _Nop();_Nop();
}
/*******************************************************************
                 字节数据接收函数               
函数原型: UCHAR  RcvByte();
功能:        用来接收从器件传来的数据,并判断总线错误(不发应答信号)，
          发完后请用应答函数应答从机。  
********************************************************************/    
unsigned char  PCF8591_RcvByte()
{
  unsigned char  retc;
  unsigned char  BitCnt;
  
  retc=0; 
  PCF8591_SDA=1;                     /*置数据线为输入方式*/
  for(BitCnt=0;BitCnt<8;BitCnt++)
      {
        _Nop();           
        PCF8591_SCL=0;                  /*置时钟线为低，准备接收数据位*/
        _Nop();_Nop();                 /*时钟低电平周期大于4.7μs*/
        _Nop();_Nop();_Nop();
        PCF8591_SCL=1;                  /*置时钟线为高使数据线上数据有效*/
        _Nop();_Nop();
        retc=retc<<1;
        if(PCF8591_SDA==1)retc=retc+1;  /*读数据位,接收的数据位放入retc中 */
        _Nop();_Nop(); 
      }
  PCF8591_SCL=0;    
  _Nop();_Nop();
  return(retc);
}
/********************************************************************
                     应答子函数
函数原型:  void Ack_I2c(bit a);
功能:      主控器进行应答信号(可以是应答或非应答信号，由位参数a决定)
********************************************************************/
void PCF8591_Ack(bit a)
{
  
  if(a==0)PCF8591_SDA=0;              /*在此发出应答或非应答信号 */
  else PCF8591_SDA=1;
  _Nop();_Nop();_Nop();      
  PCF8591_SCL=1;
  _Nop();_Nop();                    /*时钟低电平周期大于4μs*/
  _Nop();_Nop();_Nop();  
  PCF8591_SCL=0;                     /*清时钟线，钳住I2C总线以便继续接收*/
  _Nop();_Nop();    
}

///////////////////////////////
/*******************************************************************
DAC 变换, 转化函数               
*******************************************************************/
bit PCF8591_DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   PCF8591_Start();              //启动总线
   PCF8591_SendByte(sla);            //发送器件地址
   if(PCF859_ack==0)return(0);
   PCF8591_SendByte(c);              //发送控制字节
   if(PCF859_ack==0)return(0);
   PCF8591_SendByte(Val);            //发送DAC的数值  
   if(PCF859_ack==0)return(0);
   PCF8591_Stop();               //结束总线
   return(1);
}

/*******************************************************************
ADC发送字节[命令]数据函数               
*******************************************************************/
bit PCF8591_ISendByte(unsigned char sla,unsigned char c)
{
   PCF8591_Start();              //启动总线
   PCF8591_SendByte(sla);            //发送器件地址
   if(PCF859_ack==0)return(0);
   PCF8591_SendByte(c);              //发送数据
   if(PCF859_ack==0)return(0);
   PCF8591_Stop();               //结束总线
   return(1);
}

/*******************************************************************
ADC读字节数据函数               
*******************************************************************/
unsigned char PCF8591_IRcvByte(unsigned char sla)
{  unsigned char c;

   PCF8591_Start();          //启动总线
   PCF8591_SendByte(sla+1);      //发送器件地址
   if(PCF859_ack==0)return(0);
   c=PCF8591_RcvByte();          //读取数据0

   PCF8591_Ack(1);           //发送非就答位
   PCF8591_Stop();           //结束总线
   return(c);
}


#endif

#if CONFIG_SPEAK_RING == ENABLED



//////////////////////////////////////////////
unsigned char timer0h,timer0l,time;//timer0h,timer0l为定时器T0的高低位初值,time为对应的节拍时间
signed char fre;                   //对应频率数据表的地址
unsigned char music_num,num;       //music_num为歌曲编号,music_num=0表示刚开机时的状态,num是查找歌曲数据表的地址
//《烟花易冷》
unsigned char code song1[]={
     5,2,1, 3,2,1, 2,2,2, 2,2,4, 3,2,1, 1,2,1, 2,2,1, 3,2,4, 
	 5,2,1, 3,2,1, 2,2,2, 2,2,2, 5,1,1, 3,2,1, 4,2,1, 3,2,4, 
	 3,2,1, 3,2,1, 7,2,1, 3,2,1, 2,2,2, 1,2,1, 7,1,1, 1,2,1, 
	 2,2,1, 3,2,1, 6,2,3, 6,1,1, 1,2,1, 3,2,1, 2,2,1, 6,1,1, 
	 1,2,1, 7,1,1, 5,1,1, 6,1,6, 5,2,1, 3,2,1, 2,2,2, 2,2,1, 
	 2,2,1, 3,2,1, 1,2,1, 2,2,1, 3,2,4, 5,2,1, 3,2,1, 2,2,2, 
	 2,2,1, 2,2,1, 5,1,1, 3,2,1, 4,2,1, 3,2,4, 3,2,1, 3,2,1, 
	 7,2,3, 3,2,1, 2,2,2, 1,2,1, 7,1,1, 1,2,1, 2,2,1, 3,2,1, 
	 6,2,3, 6,1,1, 1,2,1, 3,2,1, 2,2,1, 6,1,1, 1,2,1, 7,1,2, 
	 5,1,2, 6,1,6, 0,0,0 };

//《发如雪》
unsigned char code song2[]={
     5,1,1, 2,2,1, 3,2,2, 2,2,1, 3,2,1, 5,2,1, 6,2,1, 5,2,3, 1,2,1, 2,2,1, 
	 3,2,1, 6,2,1, 5,2,1, 3,2,1, 5,2,3, 5,2,1, 6,2,1, 1,3,2, 6,2,1, 5,2,1, 
	 3,2,1, 5,2,1, 3,2,2, 1,2,1, 2,2,1, 3,2,1, 1,2,1, 6,1,1, 3,2,1, 2,2,1, 
	 5,1,1, 2,2,1, 3,2,2, 2,2,1, 3,2,1, 5,2,1, 6,2,1, 5,2,3, 1,2,1, 2,2,1, 
	 3,2,1, 6,2,1, 5,2,3, 5,2,1, 6,2,1, 1,3,2, 6,2,1, 
	 5,2,1, 3,2,1, 5,2,1, 3,2,2, 1,2,1, 6,1,1, 3,2,1, 2,2,1, 1,2,1, 6,1,1, 
	 1,2,1, 2,2,1, 2,2,1, 1,2,4, 0,0,0 };

//《简单爱》
unsigned char code song3[]={
     5,1,1, 1,2,1, 2,2,1, 3,2,1, 2,2,1, 3,2,1, 4,2,1, 5,2,1, 5,2,1, 5,2,1, 
	 4,2,1, 3,2,1, 2,2,3, 5,1,1, 1,2,1, 2,2,1, 3,2,1, 4,2,1, 5,2,1, 5,2,1, 
	 5,2,1, 6,2,1, 5,2,2, 2,2,1, 3,2,1, 1,2,2, 1,2,1, 6,1,1, 2,2,1, 2,2,1, 
	 3,2,1, 3,2,1, 1,2,1, 5,2,1, 1,2,1, 5,2,1, 1,2,1, 7,1,1, 1,2,1, 1,2,1, 6,1,1, 
	 2,2,1, 2,2,1, 3,2,1, 3,2,1, 5,2,1, 5,2,1, 
	 5,2,1, 6,2,1, 5,2,2, 2,2,1, 3,2,1, 1,2,2,  
	 5,1,1, 1,2,1, 2,1,2, 3,2,1, 2,2,1, 3,2,1, 4,2,1, 5,2,1, 5,2,1, 5,2,1, 
	 4,2,1, 3,2,1, 2,2,3, 5,1,1, 1,2,1, 2,2,1, 3,2,1, 2,2,1, 3,2,1, 4,2,1, 
	 5,2,1, 5,2,1, 5,2,2, 2,2,1, 3,2,1, 1,2,2, 1,2,1, 6,1,1, 2,2,1, 2,2,1, 
	 3,2,1, 3,2,1, 1,2,2, 5,2,1, 1,2,1, 5,2,1, 5,2,1, 7,1,1, 1,2,1, 0,0,0 };

//《世上只有妈妈好》
unsigned char code song4[]={
     6,2,3, 5,2,1, 3,2,2, 5,2,2, 1,3,2, 6,2,1,
	 //6,2,3代表6,中音,3个半拍;
	 //5,2,1代表5,中音,1个半拍;
	 //3,2,2代表3,中音,2个半拍;
	 //5,2,2代表5,中音,2个半拍;
	 //1,3,2代表1,高音,2个半拍;
	 //...
     5,2,1,6,2,4, 3,2,2, 5,2,1, 6,2,1, 5,2,2, 3,2,2, 1,2,1,6,1,1, 5,2,1, 
	 3,2,1, 2,2,4, 2,2,3, 3,2,1, 5,2,2, 5,2,1, 6,2,1, 3,2,2, 2,2,2, 
	 1,2,4, 5,2,3, 3,2,1,2,2,1, 1,2,1, 6,1,1, 1,2,1, 5,1,6, 0,0,0};

//《当你孤单你会想起谁》
unsigned char code song5[]={
     3,2,2, 3,2,1, 4,2,1, 3,2,2, 2,2,1, 1,2,1,  2,2,2, 5,2,2, 2,2,2, 2,2,3,
	 1,2,2, 1,2,1, 2,2,1, 1,2,2, 7,1,1, 6,1,1, 7,1,2, 3,2,2, 7,1,2, 7,1,3, 
	 6,1,2, 2,2,1, 3,2,1, 2,2,1, 1,2,1, 6,1,2, 5,1,2, 2,2,1, 3,2,1, 2,2,1, 
	 1,2,1, 6,1,2, 6,1,2, 2,2,1, 3,2,1, 2,2,1, 1,2,1, 6,1,1, 7,1,1, 1,2,6, 0,0,0 };

//《乡间小路》
unsigned char code song6[]={
     3,1,2, 3,1,1, 3,1,1, 6,0,1, 6,0,1, 1,1,2,
     6,0,1, 5,0,1, 6,0,4, 6,0,2, 6,0,1 ,6,0,1, 6,0,2, 6,0,1, 1,1,1, 
     2,1,2, 2,1,1, 3,1,1, 2,1,4, 3,1,1, 3,1,1, 3,1,1, 2,1,1, 4,1,2,
     4,1,2, 3,1,2, 2,1,1, 1,1,1, 2,1,4, 7,0,1, 7,0,1, 7,0,1, 6,0,1, 
     5,0,1, 5,0,1, 6,0,1, 7,0,1, 7,0,1, 6,0,1, 5,0,1, 6,0,4, 6,1,2,
     3,1,1, 6,1,1, 7,1,1, 6,1,1, 5,1,1, 5,1,2, 5,1,1, 2,1,1, 5,1,1, 
     6,1,1, 5,1,1, 4,1,1, 4,1,2, 4,1,1, 3,1,1, 2,1,2, 1,1,1, 2,1,1, 
     3,1,1, 2,1,1, 1,1,1, 2,1,1, 3,1,4, 6,1,2, 3,1,1, 6,1,1, 7,1,1, 
	 6,1,1, 5,1,1, 5,1,2, 2,1,1, 5,1,1, 6,1,1, 5,1,1, 4,1,1, 0,0,0};     

//《送别》
unsigned char code song7[]={
     5,1,2, 3,1,3, 5,1,1, 1,2,3, 6,1,2, 1,2,2, 
     5,1,4, 5,1,2, 1,1,1, 2,1,1, 3,1,2, 2,1,1, 1,1,1, 2,1,4, 5,1,2, 
	 3,1,1, 5,1,1, 1,2,2, 7,1,1, 6,1,2, 1,2,2, 5,1,4, 5,1,2, 2,1,1, 
	 3,1,1, 4,1,2, 7,0,1, 1,1,4, 6,1,2, 1,2,2, 1,2,4, 7,1,2, 6,1,1,
	 7,1,1, 1,2,4, 6,1,1, 7,1,1, 1,2,1, 6,1,1, 6,1,1, 5,1,1, 3,1,1, 
	 1,1,1, 2,1,8, 5,1,2, 3,1,1, 5,1,1, 1,2,2, 7,1,1, 6,1,2, 1,2,2, 
	 5,1,4, 5,1,2, 2,1,1, 3,1,1, 4,1,2, 7,0,2, 1,1,4, 0,0,0};

//《最浪漫的事》
unsigned char code song8[]={
     5,1,1, 6,1,1, 1,2,1, 6,1,2, 6,1,1, 5,1,1, 6,1,1, 5,1,1, 3,1,1, 5,1,5, 
	 5,1,1, 6,1,1, 1,2,1, 6,1,2, 6,1,1, 5,1,1, 6,1,1, 5,1,1, 6,1,1, 1,1,5, 
	 1,1,1, 2,1,1, 3,1,1, 2,1,1, 2,1,1, 2,1,1, 1,1,1, 2,1,1, 1,1,1, 6,1,1, 
	 3,1,2, 2,1,3, 5,1,1, 6,1,1, 1,2,1, 6,1,2, 6,1,1, 5,1,1, 6,1,1, 5,1,1, 
	 6,1,1, 1,1,5, 1,1,1, 2,1,1, 3,1,1, 4,1,2, 4,1,1, 5,1,1, 6,1,1, 6,1,1, 
	 5,1,1, 6,1,2, 1,2,1, 6,1,3, 1,2,1, 6,1,1, 5,1,1, 5,1,4, 1,1,1, 6,1,1, 
	 5,1,5, 5,1,1, 6,1,1, 1,2,1, 3,1,1, 2,1,1, 3,1,1, 1,1,6, 0,0,0}; 

// 频率-半周期数据表 高八位  共保存了四个八度的28个频率数据
unsigned char code FREQH[]={
    0xF2, 0xF3, 0xF5, 0xF5, 0xF6, 0xF7, 0xF8,    //低音1234567
    0xF9, 0xF9, 0xFA, 0xFA, 0xFB, 0xFB, 0xFC, 0xFC,//1,2,3,4,5,6,7,i
    0xFC, 0xFD, 0xFD, 0xFD, 0xFD, 0xFE,            //高音 234567
    0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFE, 0xFF};   //超高音 1234567

// 频率-半周期数据表 低八位
unsigned char code FREQL[]={
    0x42, 0xC1, 0x17, 0xB6, 0xD0, 0xD1, 0xB6,    //低音1234567
    0x21, 0xE1, 0x8C, 0xD8, 0x68, 0xE9, 0x5B, 0x8F, //1,2,3,4,5,6,7,i
    0xEE, 0x44, 0x6B, 0xB4, 0xF4, 0x2D,             //高音 234567
    0x47, 0x77, 0xA2, 0xB6, 0xDA, 0xFA, 0x16};   //超高音 1234567  
	
void timer0(void) interrupt 1  //T0中断程序,控制发音的音调
{
	speaker=!speaker;//输出方波, 发音
	TH0=timer0h;	 //下次的中断时间,这个时间控制音调高低
	TL0=timer0l;
 }



void delay(unsigned char t)	    //延时子函数,控制发音的时间长度,每个节拍0.4S
{
	unsigned char t1;
	unsigned long t2;
	for(t1=0;t1<t;t1++)	       //嵌套循环, 共延时t个半拍
	{
		for(t2=0;t2<8000;t2++) //延时期间, 可进入T0中断去发音
		{
			;
		}
	}
	TR0=0;		               //关闭T0, 停止发音
}
void song(void)  	//演奏一个音符
{
	TH0=timer0h;    //控制音调
	TL0=timer0l;
	TR0=1;		    //启动T0, 由T0输出方波发音
	delay(time);    //每个音符的演奏时间
}
 
void speak_ring_init()
{
	TMOD|=0x11; //T0 T1 均在工作方式1
	ET0=1;  //T0开中断
	EA=1;   //CPU开中断	 
}
void speak_play()
{
	fre=song6[num]+7*song6[num+1]-1;
	timer0h=FREQH[fre];
		timer0l=FREQL[fre];
		time=song6[num+2];
		num+=3;
	if(fre==-1)
	{

		num=0;
	}
	song();		
}
#endif

#if CONFIG_RC522 == ENABLED


void delay_ns(unsigned int ns)
{
	unsigned int i;
	for(i=0;i<ns;i++)
	{	   
		_nop_();
		_nop_();
		_nop_();
	}
}

//------------------------------------------
// 读SPI数据 
//------------------------------------------
unsigned char SPIReadByte(void)
{
	unsigned char SPICount;                                       // Counter used to clock out the data
	unsigned char SPIData; 
	                 
	SPIData = 0;
	for (SPICount = 0; SPICount < 8; SPICount++)                  // Prepare to clock in the data to be read
	{
		SPIData <<=1;                                               // Rotate the data
		CLR_SPI_CK; //nop();//nop();                                         // Raise the clock to clock the data out of the MAX7456
		if(STU_SPI_MISO)
		{
 			SPIData|=0x01;
		}
		SET_SPI_CK;   //nop();//nop();                                               // Drop the clock ready for the next bit
	}                                                             // and loop back
	return (SPIData);                              // Finally return the read data
} 
//------------------------------------------
// 写SPI数据 
//------------------------------------------
void SPIWriteByte(unsigned char SPIData)
{
	unsigned char SPICount;                                       // Counter used to clock out the data
	for (SPICount = 0; SPICount < 8; SPICount++)
	{
		if (SPIData & 0x80)
		{
			SET_SPI_MOSI;
		}
		else
		{
			CLR_SPI_MOSI;
		} 
		_nop_();_nop_();
		CLR_SPI_CK;nop();nop();
		SET_SPI_CK;nop();nop();
		SPIData <<= 1;
	}         	
}

/////////////////////////////////////////////////////////////////////
//功    能：读RC632寄存器
//参数说明：Address[IN]:寄存器地址
//返    回：读出的值
/////////////////////////////////////////////////////////////////////
unsigned char ReadRawRC(unsigned char Address)
{
	unsigned char ucAddr;
    unsigned char ucResult=0;
	CLR_SPI_CS;
    ucAddr = ((Address<<1)&0x7E)|0x80;
	SPIWriteByte(ucAddr);
	ucResult=SPIReadByte();
	SET_SPI_CS;
	return ucResult;
}

/////////////////////////////////////////////////////////////////////
//功    能：写RC632寄存器
//参数说明：Address[IN]:寄存器地址
//          value[IN]:写入的值
/////////////////////////////////////////////////////////////////////
void WriteRawRC(unsigned char Address, unsigned char value)
{  
    unsigned char ucAddr;

	CLR_SPI_CS;
    ucAddr = ((Address<<1)&0x7E);
	SPIWriteByte(ucAddr);
	SPIWriteByte(value);
	SET_SPI_CS;
}   

/////////////////////////////////////////////////////////////////////
//功    能：清RC522寄存器位
//参数说明：reg[IN]:寄存器地址
//          mask[IN]:清位值
/////////////////////////////////////////////////////////////////////
void ClearBitMask(unsigned char reg,unsigned char mask)  
{
    char tmp = 0x00;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg, tmp & ~mask);  // clear bit mask
} 


/////////////////////////////////////////////////////////////////////
//功    能：置RC522寄存器位
//参数说明：reg[IN]:寄存器地址
//          mask[IN]:置位值
/////////////////////////////////////////////////////////////////////
void SetBitMask(unsigned char reg,unsigned char mask)  
{
    char tmp = 0x00;
    tmp = ReadRawRC(reg);
    WriteRawRC(reg,tmp | mask);  // set bit mask
}

/////////////////////////////////////////////////////////////////////
//用MF522计算CRC16函数
/////////////////////////////////////////////////////////////////////
void CalulateCRC(unsigned char *pIndata,unsigned char len,unsigned char *pOutData)
{
    unsigned char i,n;
    ClearBitMask(DivIrqReg,0x04);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    for (i=0; i<len; i++)
    {   WriteRawRC(FIFODataReg, *(pIndata+i));   }
    WriteRawRC(CommandReg, PCD_CALCCRC);
    i = 0xFF;
    do 
    {
        n = ReadRawRC(DivIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x04));
    pOutData[0] = ReadRawRC(CRCResultRegL);
    pOutData[1] = ReadRawRC(CRCResultRegM);
}

/////////////////////////////////////////////////////////////////////
//功    能：通过RC522和ISO14443卡通讯
//参数说明：Command[IN]:RC522命令字
//          pInData[IN]:通过RC522发送到卡片的数据
//          InLenByte[IN]:发送数据的字节长度
//          pOutData[OUT]:接收到的卡片返回数据
//          *pOutLenBit[OUT]:返回数据的位长度
/////////////////////////////////////////////////////////////////////
char PcdComMF522(unsigned char idata Command, 
                 unsigned char idata *pInData, 
                 unsigned char idata InLenByte,
                 unsigned char idata *pOutData, 
                 unsigned int idata *pOutLenBit)
{
    char idata status = MI_ERR;
    unsigned char idata irqEn   = 0x00;
    unsigned char idata waitFor = 0x00;
    unsigned char idata lastBits;
    unsigned char idata n;
    unsigned int idata i;
    switch (Command)
    {
        case PCD_AUTHENT:
			irqEn   = 0x12;
			waitFor = 0x10;
			break;
		case PCD_TRANSCEIVE:
			irqEn   = 0x77;
			waitFor = 0x30;
			break;
		default:
			break;
    }
   
    WriteRawRC(ComIEnReg,irqEn|0x80);
    ClearBitMask(ComIrqReg,0x80);
    WriteRawRC(CommandReg,PCD_IDLE);
    SetBitMask(FIFOLevelReg,0x80);
    
    for (i=0; i<InLenByte; i++)
    {   
		WriteRawRC(FIFODataReg, pInData[i]);    
	}
    WriteRawRC(CommandReg, Command);
   
    if (Command == PCD_TRANSCEIVE)
    {    
		SetBitMask(BitFramingReg,0x80);  
	}
    
    //i = 600;//根据时钟频率调整，操作M1卡最大等待时间25ms
	i = 2000;
    do 
    {
        n = ReadRawRC(ComIrqReg);
        i--;
    }
    while ((i!=0) && !(n&0x01) && !(n&waitFor));
    ClearBitMask(BitFramingReg,0x80);

    if (i!=0)
    {    
        if(!(ReadRawRC(ErrorReg)&0x1B))
        {
            status = MI_OK;
            if (n & irqEn & 0x01)
            {   status = MI_NOTAGERR;   }
            if (Command == PCD_TRANSCEIVE)
            {
               	n = ReadRawRC(FIFOLevelReg);
              	lastBits = ReadRawRC(ControlReg) & 0x07;
                if (lastBits)
                {   
					*pOutLenBit = (n-1)*8 + lastBits;   
				}
                else
                {   
					*pOutLenBit = n*8;   
				}
                if (n == 0)
                {   
					n = 1;    
				}
                if (n > MAXRLEN)
                {   
					n = MAXRLEN;   
				}
                for (i=0; i<n; i++)
                {   
					pOutData[i] = ReadRawRC(FIFODataReg);    
				}
            }
        }
        else
        {   
			status = MI_ERR;   
		}
        
    }
   
    SetBitMask(ControlReg,0x80);           // stop timer now
    WriteRawRC(CommandReg,PCD_IDLE); 
    return status;
}
                      
/////////////////////////////////////////////////////////////////////
//功    能：寻卡
//参数说明: req_code[IN]:寻卡方式
//                0x52 = 寻感应区内所有符合14443A标准的卡
//                0x26 = 寻未进入休眠状态的卡
//          pTagType[OUT]：卡片类型代码
//                0x4400 = Mifare_UltraLight
//                0x0400 = Mifare_One(S50)
//                0x0200 = Mifare_One(S70)
//                0x0800 = Mifare_Pro(X)
//                0x4403 = Mifare_DESFire
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////
char PcdRequest(unsigned char req_code,unsigned char *pTagType)
{
	char status;  
	unsigned int unLen;
	unsigned char ucComMF522Buf[MAXRLEN]; 

	ClearBitMask(Status2Reg,0x08);
	WriteRawRC(BitFramingReg,0x07);
	SetBitMask(TxControlReg,0x03);
 
	ucComMF522Buf[0] = req_code;

	status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,1,ucComMF522Buf,&unLen);

	if ((status == MI_OK) && (unLen == 0x10))
	{    
		*pTagType     = ucComMF522Buf[0];
		*(pTagType+1) = ucComMF522Buf[1];
	}
	else
	{   
		status = MI_ERR;   
	}
   
	return status;
}


/////////////////////////////////////////////////////////////////////
//功    能：防冲撞
//参数说明: pSnr[OUT]:卡片序列号，4字节
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////  
char PcdAnticoll(unsigned char *pSnr)
{
    char status;
    unsigned char i,snr_check=0;
    unsigned int unLen;
    unsigned char ucComMF522Buf[MAXRLEN]; 
    

    ClearBitMask(Status2Reg,0x08);
    WriteRawRC(BitFramingReg,0x00);
    ClearBitMask(CollReg,0x80);
 
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x20;

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,2,ucComMF522Buf,&unLen);

    if (status == MI_OK)
	{
		for (i=0; i<4; i++)
		{   
			*(pSnr+i)  = ucComMF522Buf[i];
			snr_check ^= ucComMF522Buf[i];
		}
		if (snr_check != ucComMF522Buf[i])
   		{   
			status = MI_ERR;    
		}
    }
    
    SetBitMask(CollReg,0x80);
    return status;
}

/////////////////////////////////////////////////////////////////////
//功    能：选定卡片
//参数说明: pSnr[IN]:卡片序列号，4字节
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////
char PcdSelect(unsigned char *pSnr)
{
    char idata status;
    unsigned idata   i;
    unsigned int idata unLen;
    unsigned char idata ucComMF522Buf[MAXRLEN]; 
    
    ucComMF522Buf[0] = PICC_ANTICOLL1;
    ucComMF522Buf[1] = 0x70;
    ucComMF522Buf[6] = 0;
    for (i=0; i<4; i++)
    {
    	ucComMF522Buf[i+2] = *(pSnr+i);
    	ucComMF522Buf[6]  ^= *(pSnr+i);
    }
    CalulateCRC(ucComMF522Buf,7,&ucComMF522Buf[7]);
  
    ClearBitMask(Status2Reg,0x08);

    status = PcdComMF522(PCD_TRANSCEIVE,ucComMF522Buf,9,ucComMF522Buf,&unLen);
    
    if ((status == MI_OK) && (unLen == 0x18))
    {   
		status = MI_OK;  
	}
    else
    {   
		status = MI_ERR;    
	}

    return status;
}


/////////////////////////////////////////////////////////////////////
//功    能：复位RC522
//返    回: 成功返回MI_OK
/////////////////////////////////////////////////////////////////////
char PcdReset(void)
{
	SET_RC522RST;
    delay_ns(10);
	CLR_RC522RST;
    delay_ns(10);
	SET_RC522RST;
    delay_ns(10);
    WriteRawRC(CommandReg,PCD_RESETPHASE);
    delay_ns(10);
    
    WriteRawRC(ModeReg,0x3D);            //和Mifare卡通讯，CRC初始值0x6363
    WriteRawRC(TReloadRegL,30);           
    WriteRawRC(TReloadRegH,0);
    WriteRawRC(TModeReg,0x8D);
    WriteRawRC(TPrescalerReg,0x3E);
	
	WriteRawRC(TxAutoReg,0x40);//必须要
   
    return MI_OK;
}
//////////////////////////////////////////////////////////////////////
//设置RC632的工作方式 
//////////////////////////////////////////////////////////////////////
char M500PcdConfigISOType(unsigned char type)
{
   if (type == 'A')                     //ISO14443_A
   { 
       ClearBitMask(Status2Reg,0x08);
       WriteRawRC(ModeReg,0x3D);//3F
       WriteRawRC(RxSelReg,0x86);//84
       WriteRawRC(RFCfgReg,0x7F);   //4F
   	   WriteRawRC(TReloadRegL,30);//tmoLength);// TReloadVal = 'h6a =tmoLength(dec) 
	   WriteRawRC(TReloadRegH,0);
       WriteRawRC(TModeReg,0x8D);
	   WriteRawRC(TPrescalerReg,0x3E);
	   delay_ns(1000);
       PcdAntennaOn();
   }
   else{ return -1; }
   
   return MI_OK;
}

/////////////////////////////////////////////////////////////////////
//开启天线  
//每次启动或关闭天险发射之间应至少有1ms的间隔
/////////////////////////////////////////////////////////////////////
void PcdAntennaOn(void)
{
    unsigned char i;
    i = ReadRawRC(TxControlReg);
    if (!(i & 0x03))
    {
        SetBitMask(TxControlReg, 0x03);
    }
}


/////////////////////////////////////////////////////////////////////
//关闭天线
/////////////////////////////////////////////////////////////////////
void PcdAntennaOff(void)
{
	ClearBitMask(TxControlReg, 0x03);
}

void init_rc522(void)
{
  PcdReset();
  PcdAntennaOff();  
  PcdAntennaOn();
  M500PcdConfigISOType( 'A' );
}

char read_id(unsigned char *pTagType)
{

	if( PcdRequest( PICC_REQIDL, &pTagType[0] ) != MI_OK )//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节	
	{
		if( PcdRequest( PICC_REQIDL, &pTagType[0] ) != MI_OK )//寻天线区内未进入休眠状态的卡，返回卡片类型 2字节	
		{
	 	
			return 0;
		}	
	}

	if( PcdAnticoll( &pTagType[2] ) != MI_OK ) //防冲撞，返回卡的序列号 4字节 
	{
		return 0;	
	}

	if( PcdSelect( &pTagType[2] ) != MI_OK )//选卡
	{
		return 0;
	}
  return 1;	
}
#endif

#if CONFIG_MPU6050 == ENABLED



//************************************************************************************************
//延时5微秒(STC90C52RC@12M)
//不同的工作环境,需要调整此函数
//注意当改用1T的MCU时,请调整此延时函数
//************************************************************************************************
void Delay5us()
{
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
	_nop_();_nop_();_nop_();_nop_();
}
//*************************************************************************************************
//I2C起始信号
//*************************************************************************************************
void I2C_Start()
{
    SDA = 1;                    //拉高数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 0;                    //产生下降沿
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
}
//*************************************************************************************************
//I2C停止信号
//*************************************************************************************************
void I2C_Stop()
{
    SDA = 0;                    //拉低数据线
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SDA = 1;                    //产生上升沿
    Delay5us();                 //延时
}
//**************************************************************************************************
//I2C发送应答信号
//入口参数:ack (0:ACK 1:NAK)
//**************************************************************************************************
void I2C_SendACK(bit ack)
{
    SDA = ack;                  //写应答信号
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
}
//****************************************************************************************************
//I2C接收应答信号
//****************************************************************************************************
bit I2C_RecvACK()
{
    SCL = 1;                    //拉高时钟线
    Delay5us();                 //延时
    CY = SDA;                   //读应答信号
    SCL = 0;                    //拉低时钟线
    Delay5us();                 //延时
    return CY;
}
//*****************************************************************************************************
//向I2C总线发送一个字节数据
//*****************************************************************************************************
void I2C_SendByte(unsigned char dat)
{
    unsigned char i;
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;              //移出数据的最高位
        SDA = CY;               //送数据口
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    I2C_RecvACK();
}
//*****************************************************************************************************
//从I2C总线接收一个字节数据
//******************************************************************************************************
unsigned char I2C_RecvByte()
{
    unsigned char i;
    unsigned char dat = 0;
    SDA = 1;                    //使能内部上拉,准备读取数据,
    for (i=0; i<8; i++)         //8位计数器
    {
        dat <<= 1;
        SCL = 1;                //拉高时钟线
        Delay5us();             //延时
        dat |= SDA;             //读数据               
        SCL = 0;                //拉低时钟线
        Delay5us();             //延时
    }
    return dat;
}
//*****************************************************************************************************
//向I2C设备写入一个字节数据
//*****************************************************************************************************
void Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data)
{
    I2C_Start();                  //起始信号
    I2C_SendByte(SlaveAddress);   //发送设备地址+写信号
    I2C_SendByte(REG_Address);    //内部寄存器地址，
    I2C_SendByte(REG_data);       //内部寄存器数据，
    I2C_Stop();                   //发送停止信号
}
//*******************************************************************************************************
//从I2C设备读取一个字节数据
//*******************************************************************************************************
unsigned char Single_ReadI2C(unsigned char REG_Address)
{
	unsigned char REG_data;
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress);    //发送设备地址+写信号
	I2C_SendByte(REG_Address);     //发送存储单元地址，从0开始	
	I2C_Start();                   //起始信号
	I2C_SendByte(SlaveAddress+1);  //发送设备地址+读信号
	REG_data=I2C_RecvByte();       //读出寄存器数据
	I2C_SendACK(1);                //接收应答信号
	I2C_Stop();                    //停止信号
	return REG_data;
}
//******************************************************************************************************
//初始化MPU6050
//******************************************************************************************************
void InitMPU6050()
{
	Single_WriteI2C(PWR_MGMT_1, 0x00);	//解除休眠状态
	Single_WriteI2C(SMPLRT_DIV, 0x07);
	Single_WriteI2C(CONFIG, 0x06);
	Single_WriteI2C(GYRO_CONFIG, 0x18);
	Single_WriteI2C(ACCEL_CONFIG, 0x01);
}
//******************************************************************************************************
//合成数据
//******************************************************************************************************
int GetData(unsigned char REG_Address)
{
	unsigned char H,L;
	H=Single_ReadI2C(REG_Address);
	L=Single_ReadI2C(REG_Address+1);
	return ((H<<8)+L);   //合成数据
}

//******????************
float Accel_ax;
float Accel_az;             //X???????
float Angle;         //????????
unsigned char value;                 //????????
//*********************************************************
// ????(?????)
//*********************************************************

float Angle_Calcu(void)         
{
		Accel_ax  = GetData(ACCEL_YOUT_H);          //??X????
		Accel_az  = GetData(ACCEL_ZOUT_H);          //??X????
		Angle = (int)(atan(Accel_ax/Accel_az)*180/3.14);
		return Angle;                                                                                                          
} 


#endif


