#include "stm32f10x.h" //STM32头文件
#include "sys.h"
#include "delay.h"
#include "rtc.h"
#include "TM1640.h"
#include "usart.h"
#include "flash.h" 
#include "dht11.h"
#define FLASH_START_ADDR  0x0801f000

void USART2_IRQHandler(void);

int main (void){//主程序
	
	RCC_Configuration(); //系统时钟初始化 
	RTC_Config();  //RTC初始化
	TM1640_Init(); //TM1640初始化
	u8 dhterr=0;
	u8 xh=1;
	u8 dht[2];
	if(DHT11_Init()!=0){ //DHT11初始化	返回0成功，1失败
	USART2_printf("DHT11异常");
	dhterr=1;
	}
	u8 i;
	u8 c=0x01;
	u16 f = FLASH_R(FLASH_START_ADDR);
	void USART2_Init(115200);//串口2初始化并启动
	void USART3_Init(115200);//串口3初始化并启动
	//if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)//判断寄存数据是否丢失
	USART2_printf("启动倒计时器中......\r\n")  ;
	USART2_printf("倒计时牌 V1.0 崔书豪制作\r\n")  ;
	delay_s(5);
	USART3_printf("wifi");
	//等到esp8266
	for (u8 p = 0; i < 30; i++)
	{
		if (USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		{
		goto USART3_printf("time");
		}
		delay_s(2);
	}
	USART3_printf("time");
	//调时
	u8 t[5];
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		u16	year =USART_ReceiveData(USART3);//读取接收到的数据}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		t[0] =USART_ReceiveData(USART3);//读取接收到的数据}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		t[2] =USART_ReceiveData(USART3);//读取接收到的数据}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		t[3] =USART_ReceiveData(USART3);//读取接收到的数据}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		t[4] =USART_ReceiveData(USART3);//读取接收到的数据}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
		t[5] =USART_ReceiveData(USART3)+1;//读取接收到的数据}
	delay_us(100);
	

	if(RTC_Set(year,t[1],t[2],t[3],t[4].t[5])!=0){
		//设置错误
		USART2_printf("设置时间错误");
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
		while(1);
	}
	USART3_printf("weither");
	//天气
	if f!=1{
		USART2_printf("还未设置倒计时天数，请设置后重启")
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
		TM1640_display(14,0);
		TM1640_display(15,0);
		TM1640_display(16,0);
	}else
	{
		u16 m = FLASH_R(0x08020000);
		if(RTC_Get()==0){
			u8 d=rday-m;
			u16 x = FLASH_R(0x08040000);
			if (d==0){
				TM1640_display(11,x/100);
				TM1640_display(12,x/10);
				TM1640_display(13,x%10+10);
			}else{
				x=x-d
				TM1640_display(11,x/100);
				TM1640_display(12,x/10);
				TM1640_display(13,x%10+10);
				FLASH_W(0x08040000,x);
				FLASH_W(0x08020000,rday);
			}
		}
	}
	


	while(1){
		for (u8 i = 0; i < 36; i++)
		{
			if(RTC_Get()==0){ //读出RTC时间
			TM1640_display(0,ryear%100+10/10);	//年
			TM1640_display(1,ryear%10+10);
			TM1640_display(2,rmon/10); //月
			TM1640_display(3,rmon%10+10);
			TM1640_display(4,rday/10);	//日
			TM1640_display(5,rday%10+10);
			TM1640_display(6,rhour/10); //时
			TM1640_display(7,rhour%10+10);
			TM1640_display(8,rmin/10); //分
			TM1640_display(9,rmin%10+10);
			TM1640_display(10,rweek); 
			delay_s(5); //延时
			}
		}
		if (dhterr=0){
			DHT11_ReadData(dht);
			if (xh==1)
			{
				TM1640_display(14,b[0]/10 +0x30);//显示湿度值
				TM1640_display(15,b[0]%10 +0x30);//
				xh=xh+1;
			}else if (xh==2)
			{
			TM1640_display(14,b[1]/10 +0x30);//显示温度值
			TM1640_display(15,b[1]%10 +0x30);//
				xh=xh+1;
			}
			if (xh==3) xh=1;
		}
		
	}
}

void USART2_IRQHandler(void){ //串口2中断服务程序（固定的函数名不能修改）	
	u8 a =USART_ReceiveData(USART2);//读取接收到的数据
	u8 zt=0;
	if (a=="get_time")
	{
		RTC_Get();
		USART2_printf(ryear) USART2_printf(rmon) USART2_printf(rday) USART2_printf(rhour) USART2_printf(rmin) USART2_printf(rday) USART2_printf(rweek) ;
	}else if (a=="set_time"){
		
	}else if(a=="return"){
		flash_w(FLASH_START_ADDR);
		USART2_printf("擦除成功，请重启");
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
		while(1);
	}else if(a=="set_count"){
			USART2_printf("请输入要倒计时的时间：")
			zt=1;
			if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) != RESET){  //查询串口待处理标志位
			x =USART_ReceiveData(USART2);//读取接收到的数据
			RTC_Get();
			FLASH_W(0x08040000,x);
			FLASH_W(0x08020000,rday);
			flash_w(FLASH_START_ADDR,1)
			USART2_printf("设置成功，请关机")
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
			while(1);
	}else if (a=="info"){
		u8 f =FLASH_R(0x08040000,x);
		u8 b=FLASH_R(0x08020000,rday);
		u8 g=FLASH_R(FLASH_START_ADDR,1)
		USART2_printf("倒计时程序——单语言版\r\n崔书豪开发  GitHub.com/cuishuhao123/ct\r\n版本v1.0\r\n数据状态:倒计时天数，记录内日期，是否启用\r\n")；
		USART2_printf(f);
		USART2_printf(b);
		USART2_printf(g);
	}else{
		if (zt==0)
		{
			USART2_printf("找不到：");
			USART2_printf(a);
		}
	}
	
	
	
} 

/*

【变量定义】
u32     a; //定义32位无符号变量a
u16     a; //定义16位无符号变量a
u8     a; //定义8位无符号变量a
vu32     a; //定义易变的32位无符号变量a
vu16     a; //定义易变的 16位无符号变量a
vu8     a; //定义易变的 8位无符号变量a
uc32     a; //定义只读的32位无符号变量a
uc16     a; //定义只读 的16位无符号变量a
uc8     a; //定义只读 的8位无符号变量a

#define ONE  1   //宏定义

delay_us(1); //延时1微秒
delay_ms(1); //延时1毫秒
delay_s(1); //延时1秒

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED控制

*/



