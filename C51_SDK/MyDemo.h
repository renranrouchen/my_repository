#ifndef _MYDEMO_H_
#define _MYDEMO_H_
#include <reg52.h>
#include "MyConfig.h"

#define TRUE 1
#define FALSE 0

#if CONFIG_UTRL == ENABLED
#define uchar unsigned char		 
#define uint unsigned int
void DelayMs_utrl(unsigned int time);
#endif

#if CONFIG_LCD1602 == ENABLED

/****修改的点*****
***套用别的1602的com及data，只需要把Lcd1602_write_com及Lcd1602_write_data替换成对应
***要用这套1602，只需要修改相应的引脚
***/
#define Lcd1602_Demo_write_com Lcd1602_write_com
#define Lcd1602_Demo_write_data Lcd1602_write_data

sbit Lcd1602_rs=P2^5;	 //1602数据/命令选择引脚 H:数据      	L:命令
sbit Lcd1602_rw=P2^6;	 //1602读写引脚	         H:数据寄存器  	L:指令寄存器
sbit Lcd1602_e =P2^7;	 //1602使能引脚          下降沿触发


void Lcd1602_Display_Two_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_Three_bit(unsigned char hang,unsigned char add,unsigned int date);
void Lcd1602_Display_String(unsigned char hang,unsigned char add,unsigned char *p);
void Lcd1602_Display_guanbiao(unsigned char hang,unsigned char add,unsigned char date);
void Lcd1602_Display_Init();
#if CONFIG_DS1302 == ENABLED
void Ds13b02_DisPlay(unsigned char hang,unsigned char add,unsigned char yue,unsigned char ri,unsigned char shi,unsigned char fen,unsigned char miao);
void Ds13b02_DisPlay_Min(unsigned char hang,unsigned char add,unsigned char shi,unsigned char fen,unsigned char miao);
#endif

#if CONFIG_DS18b02 == ENABLED
void Lcd1602_Display_Ds18b02(unsigned char hang,unsigned char add,unsigned int date);
#endif
/******LCD1602 Demo******
void main()
{
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,"hello world");
	while(1);
}

*/
#endif


#if CONFIG_KEY == ENABLED

sbit Demo_KEY1 = P1^3;
sbit Demo_KEY2 = P1^2;
sbit Demo_KEY3 = P2^3;
sbit Demo_KEY4 = P1^0;
sbit Demo_KEY5 =  P3^6;
sbit Demo_KEY6 =  P3^7;
#define KEY_COUNT 3 //定义需要几个按键，最多6个
typedef void (*pKey_Process)(unsigned char );
void Key_value_Demo(pKey_Process key_Process);	

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

void main()
{
	
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
	}
}
***/
#endif

#if CONFIG_ADC0832 == ENABLED

sbit ADCS = P2^4;	//adc0832 时钟引脚定义
sbit ADCLK =P2^3;
sbit ADDI = P2^2;	//adc0832  数据引脚定义
sbit ADDO = P2^2;	//adc0832  片选引脚定义

unsigned char ADC0832_Demo(bit mode,bit channel); 

/******ADC0832 Demo******

//雨滴值是反的
long value;

unsigned char cs;
unsigned int sum;
unsigned char Ad_dat=0;
void main()
{
	while(1)
	{
		//烟雾demo
		value = ADC0832_Demo(1,0);//通道0 	
		//value = ADC0832_Demo(1,1);//通道1 	
		//value = value * 486 / 256; //486对应的为范围
		value = (256-value) * 486 / 256;//对值反相
		
		//水位demo
		if(cs<10)		 		//
		{
			cs++;
			sum+=ADC0832_Demo(1,0);		
			DelayMs_utrl(10);	
		}
		else					//
		{
			cs=0;				//
			Ad_dat=(uchar)(sum/10);	
			if(Ad_dat>2)
				Ad_dat=(float)((Ad_dat-2)/2.4); //范围100 
			else
				Ad_dat=0;	
				
			sum=0;
			
		}
	}
}

*/
#endif

#if CONFIG_DS1302 == ENABLED

sbit clk = P2^1;	  //ds1302时钟线定义
sbit io =  P2^2;	  //数据线
sbit rst = P2^0;	  //复位线
void DelayMs_Ds1302(unsigned int time);
void Ds1302_Write_Demo(unsigned char add,unsigned char dat);
unsigned char Ds1302_Read_Demo(unsigned char add);
unsigned char BCD_Decimal(unsigned char bcd);
void Ds1302_Read_Time(unsigned char *arry);
void Ds1302_Write_Time(unsigned char *arry);
void Ds1302_Save(unsigned char  po, unsigned char  dat);
void Ds1302_Write_ram(unsigned char add,unsigned char dat);
unsigned char Ds1302_Read_ds1302ram(unsigned char add);
void Ds1302_Set_time(unsigned char num,unsigned char *shi,unsigned char dat);
void Ds1302_Init();

/******DS1302 Demo******
unsigned char Time_arry[7];

void main()
{
	while(1)
	{
		Ds1302_Read_Time(Time_arry);
		Ds13b02_DisPlay(0,6,Time_arry[2],Time_arry[1],Time_arry[0]);	//使能1602
		DelayMs_utrl(100);
		
		//设置时月秒
		//Ds1302_Save(0x84,arry[2]);
		//Ds1302_Save(0x82,arry[1]);
		//Ds1302_Save(0x80,arry[0]);	
	}
}
unsigned char Menu_Count =0;
void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //设置键
	{
		Menu_Count ++;

		if(Menu_Count >= 4)
		{
			//处理返回界面
			Lcd1602_Display_guanbiao(0,9,0);
			Lcd1602_Display_String(0,0,"T:     OVER:    ");
			Lcd1602_Display_String(1,0,"                ");
			Menu_Count = 0;
		}

		switch(Menu_Count)
		{
			case 1:
				Lcd1602_Display_String(0,0,"Ts:             ");
			  Lcd1602_Display_String(1,0,"                ");
			  Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);
			  Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 2:
				Lcd1602_Display_guanbiao(0,7,1);
				break;
			case 3:
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			
		}
	}

	if(Key_value == 2)	 //
	{
		switch(Menu_Count)
		{
			case 1:
				if(Time_arry[2]<24)
					Time_arry[2]++;
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
				Ds1302_Save(0x84,Time_arry[2]);				
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 2:
				if(Time_arry[1]<60)
					Time_arry[1]++;
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
				Ds1302_Save(0x82,Time_arry[1]);					
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 3:
				if(Time_arry[0]<60)
					Time_arry[0]++;
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
				Ds1302_Save(0x80,Time_arry[0]);				
				Lcd1602_Display_guanbiao(0,10,1);
				break;

		}
	}
	
	if(Key_value == 3)	 //
	{
		switch(Menu_Count)
		{
			case 0:
				over_time=0;
				RELAY=1;
				break;
			case 1:
				if(Time_arry[2]>0)
					Time_arry[2]--;
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
				Ds1302_Save(0x84,Time_arry[2]);				
				Lcd1602_Display_guanbiao(0,4,1);
				break;
			case 2:
				if(Time_arry[1]>0)
					Time_arry[1]--;
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
				Ds1302_Save(0x82,Time_arry[1]);					
				Lcd1602_Display_guanbiao(0,7,1);
				break;	
			case 3:
				if(Time_arry[0]>0)
					Time_arry[0]--;
				Ds13b02_DisPlay(0,3,Time_arry[2],Time_arry[1],Time_arry[0]);	
				Ds1302_Save(0x80,Time_arry[0]);				
				Lcd1602_Display_guanbiao(0,10,1);
				break;
			
		}
	}		
		
}

*/
#endif


#if CONFIG_DS18b02 == ENABLED
sbit dq   = P3^7;	//18b20 IO口的定义
unsigned int Ds18b20_Read_temp();
/******Ds18b20 Demo******
uint temp;
void main()
{
	
	while(1)
	{
	  //读出来的是三位数，第三位是小数
		temp=Ds18b20_Read_temp();
		DelayMs_utrl(100);
	}
}

*/

#endif

#if CONFIG_EEPROM == ENABLED
void SectorErase_Demo(unsigned int sector_addr);
void byte_write_Demo(unsigned int byte_addr, unsigned char original_data);
unsigned char byte_read_Demo(unsigned int byte_addr);

//demo
//读int类型的数据  dat1 = byte_read(0x2000);dat2 = byte_read(0x2001);dat1*100+dat2;
//写int类型的数据 	dat1=yanwu/100; dat2=yanwu%100;  SectorErase(0x2000); byte_write(0x2000,dat1); byte_write(0x2001,dat2);

/******EEPROM Demo******
uchar dat1;
void main()
{
	SectorErase_Demo(0x2000);
	byte_write_Demo(0x2000,dat1);
	DelayMs_utrl(100);
	dat1 = byte_read_Demo(0x2000);
	
	while(1)
	{

	}
}

*/
#endif

#if CONFIG_24C02 == ENABLED

//模拟I2C 总线的引脚定义
sbit SCL = P2^1;
sbit SDA = P2^0;
void DELAY_24C02_Demo(unsigned int t);          //延时函数
void IICStart_24C02_Demo(void);         //I2C开始函数
void IICStop_24C02_Demo(void);          //I2C结束函数
void Ack_24C02_Demo(void);              //I2C应答函数
void NOAck_24C02_Demo(void);            //I2C应答非函数
bit Check_Ack_24C02_Demo(void);         //I2C应答检测函数
void SEND0_24C02_Demo(void);            //I2C发送0函数
void SEND1_24C02_Demo(void);            //I2C发送1函数 
void Write_byte_24C02_Demo(unsigned char dat);  //I2C发送字节函数
unsigned char Read_byte_24C02_Demo(void);//I2C读取字节函数
unsigned char rdeeprom_24C02_Demo(unsigned char addr);    //读AT2402函数
void wrteeprom_24C02_Demo(unsigned char addr,unsigned char dat);  //写AT2402函数

/****** Demo******
void main()
{
	wrteeprom_24C02_Demo(3,1);
	DelayMs_utrl(10);//连续写入时多个10ms左右的延时
	wrteeprom_24C02_Demo(4,1);
	DelayMs_utrl(100);
	Lcd1602_Display_Three_bit(0,0,rdeeprom_24C02_Demo(3));
	Lcd1602_Display_Three_bit(1,0,rdeeprom_24C02_Demo(4));
	while(1)
	{
	
	}
}

*/

#endif

#if CONFIG_Timer2 == ENABLED
#define Time_count 20 //20为1s
typedef void (*Timer2_Process)();
void Timer2_init_Demo(Timer2_Process T_Process);

/****** Demo******
//跟串口会冲突？使用串口后，定时器2就无法使用

void Timer2_Process2()
{

}
void main()
{
	Timer2_init_Demo(Timer2_Process2);
	while(1)
	{
	
	}
}

*/
#endif

#if CONFIG_Timer0 == ENABLED
typedef void (*Timer0_Process)();
void Timer0_Init_demo(Timer0_Process T_Process);

/****** Demo******
void Timer0_Process2()
{

}
void main()
{
	Timer0_Init_demo(Timer0_Process2);
	while(1)
	{
	
	}
}

*/
#endif

#if CONFIG_UART0 == ENABLED
#define CRC 0XFF
#define REV_NUM 2 //数量从0开始算
typedef void (*UART0_RX_Process_T)(unsigned char *RxDate);
void UART0_Init_Demo(UART0_RX_Process_T RX_Process);
void UART0_Send_Byte_Demo(unsigned char a);

/****** Demo******
void UART0_Recv_Process(unsigned char *RxDate)//接收到数据的处理
{
	Lcd1602_Display_Three_bit(0,0,RxDate[1]));
}
void main()
{
	UART0_Init_Demo(UART0_Recv_Process);
	DelayMs_utrl(500);
	UART0_Send_Byte_Demo(0xFF);
	UART0_Send_Byte_Demo(1);	
	while(1)
	{
		
	}
}

*/
#endif

#if CONFIG_KEY_MAP == ENABLED

sbit ROW1=P3^0;
sbit ROW2=P3^1;
sbit ROW3=P3^2;
sbit ROW4=P3^3;
sbit COL1=P3^4;
sbit COL2=P3^5;
sbit COL3=P3^6;
sbit COL4=P3^7;
unsigned char Getkeyboard(void);
#endif

#if CONFIG_HX711 == ENABLED
extern unsigned long Weight_Maopi;
//IO设置
sbit HX711_DOUT=P1^2; 
sbit HX711_SCK=P1^3; 

long Get_Weight();
void Get_Maopi();

/****** Demo******
long KgValue;
void main()
{
	Get_Maopi();
	while(1)
	{
		KgValue = Get_Weight();
	}
}
*****/
#endif

#if CONFIG_HRSR04 == ENABLED
sbit Trig_P    = P2^2;		// 超声波模块的Trig管脚
sbit Echo_P    = P2^3;		// 超声波模块的Echo管脚
void HRSR04_Timer_init();
unsigned int GetDistance(void);
/****** Demo******
volatile uint Distanc;
void main()
{
	HRSR04_Timer_init();
	while(1)
	{
			Distanc = GetDistance();
	}
}
***/
#endif

#if CONFIG_MP3_TF == ENABLED
sbit voice_busy = P2^0;
void uart_init();
void Delay_ms(unsigned int n);
void Uart_SendCMD(unsigned char CMD ,unsigned char feedback , unsigned int dat);

/* demo****
#define VOICE_INIT 13
void main()
{
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
}

*/
#endif

#if CONFIG_SHT11 == ENABLED

sbit DATA = P2^7;		//位定义
sbit SCK  = P2^6;

enum {TEMP,HUMI};

typedef union 				//定义共用同类型
{ 	
	unsigned int i;
	float f;
} value;

void s_connectionreset(void);
char s_measure(unsigned char *p_value, unsigned char *p_checksum, unsigned char mode);
void calc_sth10(float *p_humidity ,float *p_temperature);

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

#if CONFIG_DHT11 == ENABLED

sbit DTH_PIN=P3^7;// 温湿度模块信号脚
char DHT11_RH(unsigned char* arry);
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



#if CONFIG_LCD12864_LIB == ENABLED

sbit lcd_RS =    P2^5; 
sbit Lcd_Rw	=	 P2^6;
sbit Lcd_En	=	 P2^7;

void LCDInit();
void Lcd_String(const unsigned char  *str);
void Lcd_Display2data(unsigned char line,unsigned char list,unsigned char Date);
void Lcd_Display3data(unsigned char line,unsigned char list,unsigned int Date);
void  Lcd_ShowSring(unsigned char line,unsigned char list,unsigned char *p);

/*demo

  LCDInit();	//lcd12864初始化
	Lcd_ShowSring(1,0,"棚内温湿度光照");
  Lcd_ShowSring(2,0,"温度:");
	Lcd_ShowSring(3,0,"湿度:");
	Lcd_ShowSring(4,0,"光度:");
	while(1);

*/
#endif

#if CONFIG_ESP8266 == ENABLED
extern unsigned char a;
void Uart_Init();
void ESP8266_Set(unsigned char *puf);
void Esp8266_Delay_Ms(int cnt);
void Esp8266_init();
void UartSendString(unsigned char *string);

/**demo

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
		Cnt1 = 0;
		Cnt1 = 0;
		buff[0]= 'H';
		buff[1]= ':';
		buff[2]= count/100%10+0x30;
		buff[3]= count/10%10+0x30;
		buff[4]= count%10+0x30;
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
		UartSendString(buff);		
	}	
}
void main()
{
	Esp8266_init();
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
      EPS	
		EPS8266_Send();
		DelayMs_utrl(100);
	}
}


**/
#endif

#if CONFIG_ISD4004 == ENABLED
#define ISDPOWERUP      0X25           //ISD4004上电
#define ISDSTOP         0X10           //ISD4004下电
#define OPERSTOP        0X30           //ISD4004停止当前操作
#define PLAYSET         0XE0//0XE7           //ISD4004从指定地址开始放音
#define PLAYCUR         0XF0           //ISD4004从当前地址开始放音
#define RECSET          0XA0//0XA5           //ISD4004从指定地址开始录音
#define RECCUR          0XB0           //ISD4004从当前地址开始录音

#define ADDR1STR        0x0000//0X020           //第一首的起始地址 
#define ADDR2STR        0x012d//0X240           //第二首的起始地址 
#define ADDR3STR        0x0259//0X180           //第三首的起始地址 
#define ADDR4STR        0x0385//0X720           //第四首的起始地址 
sbit   SS=P1^5;            //LOW IS ACTIVELY
sbit   MOSI=P1^4;
sbit   MISO=P1^3;
sbit   SCLK=P1^6;

extern void stop();
extern void rec(unsigned int addr);
extern void play(unsigned int addr);
extern bit flag_xh;

/*demo
play(ADDR4STR);

*/
#endif


#if CONFIG_FUZZIFY == ENABLED
void fuzzy_engine(unsigned char input);
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
#if CONFIG_EX0_EX1 == ENABLED
typedef void (*EX0_1_Process)();
void EX0_INIT(EX0_1_Process T_Process);
void EX1_INIT(EX0_1_Process T_Process);
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

#if CONFIG_LCD12864 == ENABLED

#define Disp_On  0x3f//开显示
#define Disp_Off 0x3e//关显示
#define Col_Add  0x40//地址基准
#define Page_Add 0xb8
#define Start_Line 0xc0
#define REGULATE 0      //校准
#define SPACE 1    //刷新温度时间间隔（s）
//各种引脚定义
sbit cs1=P2^4; 		//CS1=1
sbit cs2=P2^3; 		//CS2=1
sbit Enable=P2^2; 	//使能端
sbit Di=P2^0;  		//数据命令选择端
sbit RW=P2^1;  		//读写选择端
void Lcd_Init();
void hz_disp16(unsigned char pag,unsigned char col, unsigned char code *hzk);
void hz_disp8(unsigned char pag,unsigned char col, unsigned char code *hzk);
#endif

#if CONFIG_IRSEND == ENABLED
//红外管脚接口
sbit HL=P3^4;
void SendIRdata(char p_irdata);
void IR_SEND_INIT();
/**demo

void Key_Process_Demo(unsigned char Key_value)
{

	if(Key_value == 1)	 //设置键
	{
		SendIRdata(0x45);
	}

	if(Key_value == 2)	 //
	{
    SendIRdata(0x46);
	}
	
	if(Key_value == 3)	 //
	{
		SendIRdata(0x47);
	}		
		
}


	
void main()
{
	IR_SEND_INIT();
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
		DelayMs_utrl(100);
	}
}
**/
#endif

#if CONFIG_IR_REVICE == ENABLED
extern unsigned char ir_num;	
void IR_Init(void);
//接外部中断0 P32 ,使用定时器0
/*demo

void main()
{

	IR_Init();
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,"hello world");
	while(1)
	{
 
		if(ir_num>0)
		{
			Lcd1602_Display_Two_bit(1,0,ir_num);
			ir_num=0;
		}
			
			
		
	}
}
*/
#endif
#if CONFIG_DS18B20_MULT== ENABLED
#define MAXNUM 5 //定义最多有8个 DS18B02
sbit DQ=P3^5;    //定义数据线
void DS18B20_Processing(unsigned char *Temp_Value);
void search_rom(void);//搜索ROM

/****** Demo******
unsigned char Temp_Value[5];
void main()
{
	search_rom();
	while(1)
	{
		DS18B20_Processing(Temp_Value);
	}
}
*****/
#endif

#if CONFIG_LCD12864_PLUS== ENABLED

#define lcdDat P0  /* LCD12864 数据线 */
sbit cs2= P1^4;    /* 右屏片选，高电平有效 */
sbit cs1= P1^3;    /* 左屏片选，高电平有效 */
sbit en = P1^2;    /* 读,写使能,高电平有效，下沿锁定数据 */
sbit rw = P1^1;    /* 1读\0写 */
sbit rs = P1^0;    /* 1数据\0指令 */
#define addX0 0xB8       /* x地址（0页） */
#define addY0 0x40       /* y地址（0列） */
#define addZ0 0xC0       /* Z地址（0行开始显示） */
void Init12864();
void showStr(unsigned char row,unsigned char col,unsigned char *s);
void showXY(unsigned char row,unsigned char col,unsigned char x,unsigned char y,unsigned char *tab);
void showThreeNum(unsigned char row,unsigned char col,unsigned int s);
void showDS18B02Num(unsigned char row,unsigned char col,unsigned int s);
void Ds13b02_DisPlay_12864(unsigned char row,unsigned char col,unsigned char shi,unsigned char fen,unsigned char miao);
/****** Demo******

void main()
{
	Init12864();
	showStr(0,0," 欢迎使用密码锁 ");
	showStr(2,0,"12  请输入密码   ");
	showThreeNum(4,64,123);
	while(1)
	{

	}
}

*/
#endif

#if CONFIG_KEY_MAP_2== ENABLED
sbit col3=P0^0;sbit col2=P0^1;sbit col1=P0^2;sbit col0=P0^3;
sbit row0=P2^0;sbit row1=P2^1;sbit row2=P1^0;sbit row3=P1^1;
typedef void (*pKey_Map_Process)(unsigned char );
unsigned char key_get();
void Key_Map(pKey_Map_Process key_Map_Process);


/****** Demo******
void Key_Process_Demo(unsigned char Key_value)
{
	showThreeNum(6,0,Key_value);
}
void main()
{
	Init12864();
	showStr(0,0," 欢迎使用密码锁 ");
	showStr(2,0,"12  请输入密码   ");
	showThreeNum(4,64,126);
	while(1)
	{
			//showThreeNum(6,0,key_get());
		Key_Map(Key_Process_Demo);
		DelayMs_utrl(100);
	}
}

*/
#endif

#if CONFIG_MAX6675== ENABLED

sbit  SO  = P1^5;  				//P3.6口与SO相连
sbit  MAX6675_SCK = P1^6; 				//P3.4口与SCK相连
sbit  CS1 = P1^7;  				//P3.5口与CS相连

sbit  CS2  = P1^7;   				//P3.5口与CS相连
sbit  CS3  = P1^7;   				//P3.5口与CS相连
sbit  CS4  = P1^7;  				//P3.5口与CS相连
void MAX6675_Processing(unsigned char CH,unsigned short *MAX6675_Temp);

/**demo**
idata  unsigned short MAX6675_Temp[4] = {0,0,0,0};
void main()
{
	while(1)
	{
		MAX6675_Processing(0,MAX6675_Temp);
	}
		
}
			
**/
#endif

#if CONFIG_GSM== ENABLED

//#define RsBuf_N			250
void Uart_init();
void SendASC(unsigned char d);
void SendString(unsigned char *str)	;
void Gsm_init();
void GSM_delay_ms(unsigned int z);
unsigned char strsearch(unsigned char *ptr2,unsigned char *ptr1_at);
void SendTwoNum(unsigned char num);
void SendNum(unsigned char num);
void SendNum_char(unsigned char num);
/***demo

uchar stauts=0;
unsigned char  dianhuahaoma[12]="18459195135";
void Send_SMS_CH(unsigned char *sta,unsigned char option)
{
	
		unsigned char _Data[1];
		static unsigned char Step = 0;
		uchar send_number;
			
			if(*sta!=0)
			{
				switch(Step)
				{
					case 0:
								SendString("AT\r\n"); Step++;
								break;
					
					case 1: SendString("ATE0\r\n");  Step++;  break;

					
					case 2:SendString("AT+CMGF=1\r\n");Step++;break;
			 
					case 3:SendString("AT+CSCS=\"UCS2\"\r\n");Step++;break;
			 

					case 4: SendString("AT+CSMP=17,0,2,25\r\n");Step++;  break;
			 
					case 5: SendString("AT+CMGS=\"");Step++; 
									for(send_number=0;send_number<11;send_number++)//在每位号码前加003
									{
										SendNum_char(dianhuahaoma[send_number]);
									} 								
									SendString("\"\r\n");

					break;

					case 6: 
									switch(option)
									{
										case 0:
											SendString("52305403836F65F695F48BF753CA65F65403836F"); 
										break;
									}
									
									SendString("0020");			//发送空格
									_Data[0] = 0x1A;
									SendASC(*_Data);
									Step = 0;
									*sta=0;
									break;
					default: Step = 0;
					break;
				}
				DelayMs_utrl(100);
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
								SendString("AT\r\n"); Step++;
								break;
					
					case 1: SendString("ATE0\r\n");  Step++;  break;

					
					case 2:SendString("AT+CMGF=1\r\n");Step++;break;
			 
					case 3:SendString((uchar*)"AT+CSCS=\"GSM\"\r\n");Step++;break;
			 
			 
					case 4: SendString("AT+CMGS=\"");Step++; 
									SendString(dianhuahaoma);  								
									SendString("\"\r\n");
					break;

					case 5: 
									switch(option)
									{
										case 0:
											SendString("HELLO"); 
										break;
									}
									
									_Data[0] = 0x1A;
									SendASC(*_Data);
									Step = 0;
									*sta=0;
									break;
					default: Step = 0;
					break;
				}
				DelayMs_utrl(100);
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
    Lcd1602_Display_String(0,0,dianhuahaoma);
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
    Lcd1602_Display_String(0,0,dianhuahaoma);
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
void main()
{
	Gsm_init();
	Lcd1602_Display_Init();
	Lcd1602_Display_String(0,0,dianhuahaoma);
	while(1)
	{
		Key_value_Demo(Key_Process_Demo);
		if(stauts==0)
		{
			//判断发送的条件,成功stauts=1;
			//stauts=1;
			
		}
		//发送完成后stauts消除
		Send_SMS_EN(&stauts,0);
		DelayMs_utrl(100);
	}
}

unsigned char  dianhuahaoma[12]={1,3,7,5,5,1,0,0,5,0,4};
void TransmitText(unsigned char Status)
{
	uchar send_number;
	SendString("AT+CMGF=1\r\n"); //设置文本模式
  GSM_delay_ms(1000);	
	SendString("AT+CSCS=\"UCS2\"\r\n");//设置短信格式，发送汉字模式
	GSM_delay_ms(1000);
	SendString("AT+CSMP=17,0,2,25\r\n");//设置短信文本模式参数（具体内容参考开发资料内的模块资料）
	GSM_delay_ms(1000);
	
	SendString("AT+CMGS=");	//信息发送指令 AT+CMGS=//
	SendASC('"');
	for(send_number=0;send_number<11;send_number++)//在每位号码前加003
	{
		SendNum(dianhuahaoma[send_number]);
	}   
	SendASC('"');
	SendASC('\r');			//发送回车指令//
	SendASC('\n');			//发送换行指令//
	//该延时会影响下一个发送的第一个字节的数据	
//	GSM_delay_ms(1000);			
			
	
  //确保数据完整，不然会发送失败	

	SendString("002C8BF753CA65F6590474060021");//,请及时处理！
	SendString("0020");			//发送空格
	GSM_delay_ms(1000);	
	SendASC(0x1a);  //确定发送短信
	
	SendASC('\r');
	SendASC('\n');					
	GSM_delay_ms(1000);
}
//英文 
unsigned char  PhoneNO[]= "13755100504";//接收方号码
void GSM_SENT()
{
		SendString((uchar*)" AT+CMGF=1\r\n");	
		
		GSM_delay_ms(1000);
		
		SendString((uchar*)"AT+CSCS=\"GSM\"\r\n");	
		
		GSM_delay_ms(1000);
		
		SendString((uchar*)"AT+CMGS=");	//信息发送指令 AT+CMGS=//
		SendASC('"');
		SendString(PhoneNO);   
		SendASC('"');
		SendASC('\r');			//发送回车指令//
		SendASC('\n');			//发送回车指令//
		
		GSM_delay_ms(1000);
		
    SendString("system fall down");
		GSM_delay_ms(1000);
		
		SendASC(0x1a);		
}

void main()
{
	Gsm_init();
	while(1)
	{
		TransmitText(2);
		DelayMs_utrl(100);
	}
}

***/
#endif

#if CONFIG_STEPMOTO== ENABLED
sbit dj1 = P2^0;   //电机IO口定义
sbit dj2 = P2^1;   //电机IO口定义
sbit dj3 = P2^2;   //电机IO口定义
sbit dj4 = P2^3;   //电机IO口定义
enum moto_statu
{
	STOP,
	OPEN,
	CLOSE,
};
#define TIME_COUNT 1 //
#define TIME_HAPPEND 10000 //10000为10ms
typedef void (*MotoTimer2_Process)();
void MotoStepSpeed(unsigned char status,unsigned int speed,unsigned int count);
void stop();
void zheng(unsigned char dat);
void fan(unsigned char dat);
void MotoTimer2_init_Demo(MotoTimer2_Process T_Process);
/**denmo

#define MOTO_COUNT 250
uchar motostatu=OPEN;
uint MotoPoint=0;

void Timer2_Process2()
{
	 static uchar i;
   switch(motostatu)
	 {
		 case STOP:
			 stop();
			 break;
		 case OPEN:
			if(MotoPoint<MOTO_COUNT)
			{
				i++;
				if(i>=4)
				{
					i=0;
					MotoPoint++;
				}
				
				zheng(i);
				
			}else
				stop();			 
		 
			 break;
		 case CLOSE:
			 
			if(MotoPoint>0)
			{
				i++;
				if(i>=4)
				{
					i=0;
					MotoPoint--;
				}
				
				fan(i);
				
			}else
				stop();		 
			 break;		 
	 }

}
void main()
{
  MotoTimer2_init_Demo(Timer2_Process2);
	while(1)
	{
		DelayMs_utrl(100);
	}
}
**/
#endif

#if CONFIG_7BIT_4_LED== ENABLED

#endif

#if CONFIG_BULETOOTH == ENABLED
void Bluetooth_uart_init(unsigned char *buff);
void Bluetooth_UartSendString(unsigned char *string);

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

#if CONFIG_PCF8591== ENABLED
#define  NOP()   _nop_()   /* 定义空指令 */
#define  _Nop()  _nop_()   /*定义空指令*/

 
sbit     PCF8591_SCL=P1^1;       //I2C  时钟 
sbit     PCF8591_SDA=P1^0;       //I2C  数据 

//起动总线函数
void PCF8591_Start();
//结束总线函数  
void PCF8591_Stop();
//应答子函数
void PCF8591_Ack(bit a);
//字节数据发送函数
void PCF8591_SendByte(unsigned char  c);
//有子地址发送多字节数据函数               
bit PCF8591_ISendStr(unsigned char sla,unsigned char suba,unsigned char *s,unsigned char no) ;
//无子地址发送多字节数据函数   
bit PCF8591_ISendStrExt(unsigned char sla,unsigned char *s,unsigned char no);
//无子地址读字节数据函数               
unsigned char PCF8591_RcvByte();
/////////////////////////////////////////////////
bit PCF8591_DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit PCF8591_ISendByte(unsigned char sla,unsigned char c);
unsigned char PCF8591_IRcvByte(unsigned char sla);

/*demo

		for(i=0;i<8;i++)
		{
			switch(AD_CHANNEL)
			{
				case 0: PCF8591_ISendByte(PCF8591,0x41);
				AD_Up=PCF8591_IRcvByte(PCF8591)*2;  //ADC0 模数转换1
				break;  
				
				case 1: PCF8591_ISendByte(PCF8591,0x42);
				AD_Down=PCF8591_IRcvByte(PCF8591)*2;  //ADC1  模数转换2
				break;  
				case 2: PCF8591_ISendByte(PCF8591,0x43);
				AD_Left=PCF8591_IRcvByte(PCF8591)*2;  //ADC2 模数转换3
				break;  
				
				case 3: PCF8591_ISendByte(PCF8591,0x40);
				AD_Right=PCF8591_IRcvByte(PCF8591)*2;  //ADC3  模数转换4
				break; 
			}

			Send_Hex(Table,4);
			if(++AD_CHANNEL>3)
			{
					AD_CHANNEL=0;
					Table[0] = AD_Up;
					Table[1] = AD_Down;
					Table[2] = AD_Left;
					Table[3] = AD_Right;
				 Lcd1602_Display_Three_bit(0,3,AD_Up);
				 Lcd1602_Display_Three_bit(0,11,AD_Down);
				 Lcd1602_Display_Three_bit(1,3,AD_Left);
				 Lcd1602_Display_Three_bit(1,11,AD_Right);				
			 }
		}
*/
#endif

#if CONFIG_SPEAK_RING == ENABLED

sbit speaker=P3^2;     //无源蜂鸣器

void speak_ring_init();
void speak_play();

/*demo
void main()
{
	speak_ring_init();
	while(1)
	{
		speak_play();
	}
}

*/
#endif


#if CONFIG_RC522 == ENABLED

#define nop() _nop_()
/////////////////////////////////////////////////////////////////////
//MF522命令字
/////////////////////////////////////////////////////////////////////
#define PCD_IDLE              0x00               //取消当前命令
#define PCD_AUTHENT           0x0E               //验证密钥
#define PCD_RECEIVE           0x08               //接收数据
#define PCD_TRANSMIT          0x04               //发送数据
#define PCD_TRANSCEIVE        0x0C               //发送并接收数据
#define PCD_RESETPHASE        0x0F               //复位
#define PCD_CALCCRC           0x03               //CRC计算

/////////////////////////////////////////////////////////////////////
//Mifare_One卡片命令字
/////////////////////////////////////////////////////////////////////
#define PICC_REQIDL           0x26               //寻天线区内未进入休眠状态
#define PICC_REQALL           0x52               //寻天线区内全部卡
#define PICC_ANTICOLL1        0x93               //防冲撞
#define PICC_ANTICOLL2        0x95               //防冲撞
#define PICC_AUTHENT1A        0x60               //验证A密钥
#define PICC_AUTHENT1B        0x61               //验证B密钥
#define PICC_READ             0x30               //读块
#define PICC_WRITE            0xA0               //写块
#define PICC_DECREMENT        0xC0               //扣款
#define PICC_INCREMENT        0xC1               //充值
#define PICC_RESTORE          0xC2               //调块数据到缓冲区
#define PICC_TRANSFER         0xB0               //保存缓冲区中数据
#define PICC_HALT             0x50               //休眠

/////////////////////////////////////////////////////////////////////
//MF522 FIFO长度定义
/////////////////////////////////////////////////////////////////////
#define DEF_FIFO_LENGTH       64                 //FIFO size=64byte
#define MAXRLEN  18

/////////////////////////////////////////////////////////////////////
//MF522寄存器定义
/////////////////////////////////////////////////////////////////////
// PAGE 0
#define     RFU00                 0x00    
#define     CommandReg            0x01    
#define     ComIEnReg             0x02    
#define     DivlEnReg             0x03    
#define     ComIrqReg             0x04    
#define     DivIrqReg             0x05
#define     ErrorReg              0x06    
#define     Status1Reg            0x07    
#define     Status2Reg            0x08    
#define     FIFODataReg           0x09
#define     FIFOLevelReg          0x0A
#define     WaterLevelReg         0x0B
#define     ControlReg            0x0C
#define     BitFramingReg         0x0D
#define     CollReg               0x0E
#define     RFU0F                 0x0F
// PAGE 1     
#define     RFU10                 0x10
#define     ModeReg               0x11
#define     TxModeReg             0x12
#define     RxModeReg             0x13
#define     TxControlReg          0x14
#define     TxAutoReg             0x15
#define     TxSelReg              0x16
#define     RxSelReg              0x17
#define     RxThresholdReg        0x18
#define     DemodReg              0x19
#define     RFU1A                 0x1A
#define     RFU1B                 0x1B
#define     MifareReg             0x1C
#define     RFU1D                 0x1D
#define     RFU1E                 0x1E
#define     SerialSpeedReg        0x1F
// PAGE 2    
#define     RFU20                 0x20  
#define     CRCResultRegM         0x21
#define     CRCResultRegL         0x22
#define     RFU23                 0x23
#define     ModWidthReg           0x24
#define     RFU25                 0x25
#define     RFCfgReg              0x26
#define     GsNReg                0x27
#define     CWGsCfgReg            0x28
#define     ModGsCfgReg           0x29
#define     TModeReg              0x2A
#define     TPrescalerReg         0x2B
#define     TReloadRegH           0x2C
#define     TReloadRegL           0x2D
#define     TCounterValueRegH     0x2E
#define     TCounterValueRegL     0x2F
// PAGE 3      
#define     RFU30                 0x30
#define     TestSel1Reg           0x31
#define     TestSel2Reg           0x32
#define     TestPinEnReg          0x33
#define     TestPinValueReg       0x34
#define     TestBusReg            0x35
#define     AutoTestReg           0x36
#define     VersionReg            0x37
#define     AnalogTestReg         0x38
#define     TestDAC1Reg           0x39  
#define     TestDAC2Reg           0x3A   
#define     TestADCReg            0x3B   
#define     RFU3C                 0x3C   
#define     RFU3D                 0x3D   
#define     RFU3E                 0x3E   
#define     RFU3F		  		  0x3F

/////////////////////////////////////////////////////////////////////
//和MF522通讯时返回的错误代码
/////////////////////////////////////////////////////////////////////
#define 	MI_OK                 0
#define 	MI_NOTAGERR           (-1)
#define 	MI_ERR                (-2)

sbit  spi_cs=P1^3;
sbit  spi_ck=P1^4;
sbit  spi_mosi=P1^5;
sbit  spi_miso=P1^6;
sbit  spi_rst=P1^2;

#define SET_SPI_CS  spi_cs=1
#define CLR_SPI_CS  spi_cs=0

#define SET_SPI_CK  spi_ck=1
#define CLR_SPI_CK  spi_ck=0

#define SET_SPI_MOSI  spi_mosi=1
#define CLR_SPI_MOSI  spi_mosi=0

#define STU_SPI_MISO  spi_miso

#define SET_RC522RST  spi_rst=1
#define CLR_RC522RST  spi_rst=0

extern char PcdReset(void);
extern char PcdRequest(unsigned char req_code,unsigned char *pTagType);
extern void PcdAntennaOn(void);
extern void PcdAntennaOff(void);
extern char M500PcdConfigISOType(unsigned char type);
extern char PcdAnticoll(unsigned char *pSnr);
extern char PcdSelect(unsigned char *pSnr);
extern char PcdAuthState(unsigned char auth_mode,unsigned char addr,unsigned char *pKey,unsigned char *pSnr);
extern char PcdWrite(unsigned char addr,unsigned char *pData);
extern char PcdRead(unsigned char addr,unsigned char *pData);
extern char PcdHalt(void);
extern void init_rc522(void);
char read_id(unsigned char *pTagType);
/*demo

unsigned char xdata CardRevBuf[10] = { 0 };

void main()
{
	init_rc522();
	while(1)
	{
		if(read_id(CardRevBuf))//读卡成功
		{

		}
		DelayMs_utrl(100);
	}
}

*/
#endif


#if CONFIG_MPU6050 == ENABLED

//****************************************
// 定义51单片机端口
//****************************************
sbit    SCL=P1^4;			//IIC时钟引脚定义
sbit    SDA=P1^5;			//IIC数据引脚定义
//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	0x3B
#define	ACCEL_XOUT_L	0x3C
#define	ACCEL_YOUT_H	0x3D
#define	ACCEL_YOUT_L	0x3E
#define	ACCEL_ZOUT_H	0x3F
#define	ACCEL_ZOUT_L	0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	0xD0	//IIC写入时的地址字节数据，+1为读取



//**************************************************************************************************
void  Delay5us();
//********************************MPU6050操作函数***************************************************
void  InitMPU6050();											//初始化MPU6050
void  I2C_Start();
void  I2C_Stop();
void  I2C_SendACK(bit ack);
bit   I2C_RecvACK();
void  I2C_SendByte(unsigned char dat);
unsigned char I2C_RecvByte();
void  I2C_ReadPage();
void  I2C_WritePage();

unsigned char Single_ReadI2C(unsigned char REG_Address);						//读取I2C数据
void  Single_WriteI2C(unsigned char REG_Address,unsigned char REG_data);	    //向I2C写入数据
int GetData(unsigned char REG_Address);
float Angle_Calcu(void);
#include <math.h>

/*DEMO


unsigned int adx,ady,adz;
void main()
{
  InitMPU6050();
	while(1)
	{
		adx=GetData(ACCEL_XOUT_H);
		ady=GetData(ACCEL_YOUT_H);
		adz = GetData(ACCEL_ZOUT_H);
		adx = adx / 172;
		ady = ady / 172;
		adz = adz / 172;
		//Lcd1602_Display_Three_bit(1,4,adx);
		//Lcd1602_Display_Three_bit(1,8,ady);
		//Lcd1602_Display_Three_bit(1,4,adz);
	}
}

*/
#endif

#endif

