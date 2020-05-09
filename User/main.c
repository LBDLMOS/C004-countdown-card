#include "stm32f10x.h" //STM32ͷ�ļ�
#include "sys.h"
#include "delay.h"
#include "rtc.h"
#include "TM1640.h"
#include "usart.h"
#include "flash.h" 
#include "dht11.h"
#define FLASH_START_ADDR  0x0801f000

void USART2_IRQHandler(void);

int main (void){//������
	
	RCC_Configuration(); //ϵͳʱ�ӳ�ʼ�� 
	RTC_Config();  //RTC��ʼ��
	TM1640_Init(); //TM1640��ʼ��
	u8 dhterr=0;
	u8 xh=1;
	u8 dht[2];
	if(DHT11_Init()!=0){ //DHT11��ʼ��	����0�ɹ���1ʧ��
	USART2_printf("DHT11�쳣");
	dhterr=1;
	}
	u8 i;
	u8 c=0x01;
	u16 f = FLASH_R(FLASH_START_ADDR);
	void USART2_Init(115200);//����2��ʼ��������
	void USART3_Init(115200);//����3��ʼ��������
	//if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)//�жϼĴ������Ƿ�ʧ
	USART2_printf("��������ʱ����......\r\n")  ;
	USART2_printf("����ʱ�� V1.0 ���������\r\n")  ;
	delay_s(5);
	USART3_printf("wifi");
	//�ȵ�esp8266
	for (u8 p = 0; i < 30; i++)
	{
		if (USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		{
		goto USART3_printf("time");
		}
		delay_s(2);
	}
	USART3_printf("time");
	//��ʱ
	u8 t[5];
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		u16	year =USART_ReceiveData(USART3);//��ȡ���յ�������}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		t[0] =USART_ReceiveData(USART3);//��ȡ���յ�������}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		t[2] =USART_ReceiveData(USART3);//��ȡ���յ�������}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		t[3] =USART_ReceiveData(USART3);//��ȡ���յ�������}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		t[4] =USART_ReceiveData(USART3);//��ȡ���յ�������}
	delay_us(100);
	if(USART_GetFlagStatus(USART3,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
		t[5] =USART_ReceiveData(USART3)+1;//��ȡ���յ�������}
	delay_us(100);
	

	if(RTC_Set(year,t[1],t[2],t[3],t[4].t[5])!=0){
		//���ô���
		USART2_printf("����ʱ�����");
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
		while(1);
	}
	USART3_printf("weither");
	//����
	if f!=1{
		USART2_printf("��δ���õ���ʱ�����������ú�����")
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
			if(RTC_Get()==0){ //����RTCʱ��
			TM1640_display(0,ryear%100+10/10);	//��
			TM1640_display(1,ryear%10+10);
			TM1640_display(2,rmon/10); //��
			TM1640_display(3,rmon%10+10);
			TM1640_display(4,rday/10);	//��
			TM1640_display(5,rday%10+10);
			TM1640_display(6,rhour/10); //ʱ
			TM1640_display(7,rhour%10+10);
			TM1640_display(8,rmin/10); //��
			TM1640_display(9,rmin%10+10);
			TM1640_display(10,rweek); 
			delay_s(5); //��ʱ
			}
		}
		if (dhterr=0){
			DHT11_ReadData(dht);
			if (xh==1)
			{
				TM1640_display(14,b[0]/10 +0x30);//��ʾʪ��ֵ
				TM1640_display(15,b[0]%10 +0x30);//
				xh=xh+1;
			}else if (xh==2)
			{
			TM1640_display(14,b[1]/10 +0x30);//��ʾ�¶�ֵ
			TM1640_display(15,b[1]%10 +0x30);//
				xh=xh+1;
			}
			if (xh==3) xh=1;
		}
		
	}
}

void USART2_IRQHandler(void){ //����2�жϷ�����򣨹̶��ĺ����������޸ģ�	
	u8 a =USART_ReceiveData(USART2);//��ȡ���յ�������
	u8 zt=0;
	if (a=="get_time")
	{
		RTC_Get();
		USART2_printf(ryear) USART2_printf(rmon) USART2_printf(rday) USART2_printf(rhour) USART2_printf(rmin) USART2_printf(rday) USART2_printf(rweek) ;
	}else if (a=="set_time"){
		
	}else if(a=="return"){
		flash_w(FLASH_START_ADDR);
		USART2_printf("�����ɹ���������");
		GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
		while(1);
	}else if(a=="set_count"){
			USART2_printf("������Ҫ����ʱ��ʱ�䣺")
			zt=1;
			if(USART_GetFlagStatus(USART2,USART_FLAG_RXNE) != RESET){  //��ѯ���ڴ������־λ
			x =USART_ReceiveData(USART2);//��ȡ���յ�������
			RTC_Get();
			FLASH_W(0x08040000,x);
			FLASH_W(0x08020000,rday);
			flash_w(FLASH_START_ADDR,1)
			USART2_printf("���óɹ�����ػ�")
			GPIO_WriteBit(LEDPORT,LED2,(BitAction)(0));
			while(1);
	}else if (a=="info"){
		u8 f =FLASH_R(0x08040000,x);
		u8 b=FLASH_R(0x08020000,rday);
		u8 g=FLASH_R(FLASH_START_ADDR,1)
		USART2_printf("����ʱ���򡪡������԰�\r\n���������  GitHub.com/cuishuhao123/ct\r\n�汾v1.0\r\n����״̬:����ʱ��������¼�����ڣ��Ƿ�����\r\n")��
		USART2_printf(f);
		USART2_printf(b);
		USART2_printf(g);
	}else{
		if (zt==0)
		{
			USART2_printf("�Ҳ�����");
			USART2_printf(a);
		}
	}
	
	
	
} 

/*

���������塿
u32     a; //����32λ�޷��ű���a
u16     a; //����16λ�޷��ű���a
u8     a; //����8λ�޷��ű���a
vu32     a; //�����ױ��32λ�޷��ű���a
vu16     a; //�����ױ�� 16λ�޷��ű���a
vu8     a; //�����ױ�� 8λ�޷��ű���a
uc32     a; //����ֻ����32λ�޷��ű���a
uc16     a; //����ֻ�� ��16λ�޷��ű���a
uc8     a; //����ֻ�� ��8λ�޷��ű���a

#define ONE  1   //�궨��

delay_us(1); //��ʱ1΢��
delay_ms(1); //��ʱ1����
delay_s(1); //��ʱ1��

GPIO_WriteBit(LEDPORT,LED1,(BitAction)(1)); //LED����

*/



