/*********
verson3
pidֱ��
*******/
#include"encoder.h"
#include"uart.h"
#include"pwm.h"
#include"pid.h"
#include<iom128v.h>

#include "usart0.h"  
#include "gps.h"
#include <string.h>
#include "sim900a.h"

#include "lock.h"
#include "data_get.h"
#include "alarm_message.h"
#include "init.h"
/*
*ICP_init
*��׽���뺯����ʼ��
*�������:��
*���ز���:��
*/
#define bell_open() PORTA|=(1<<1)
#define bell_close() PORTA&=~(1<<1)
#define move() p->Vsp = 90
#define stop() {p->Vsp = 0;}


unsigned char data_rec_done_flag=0;
unsigned char data[3000];
unsigned char app_data[5]={0,1,0,0,0};
unsigned char gps_data[200]={1};
unsigned char uart1_receive_flag=0;
unsigned char lock_flag=0;
unsigned char sec_time=0;
unsigned int  now_time=0;
int num_pulse_1 = 0;
int get_num_pulse_1 = 0;

int num_pulse_3 = 0;
int get_num_pulse_3 = 0;
//int flag;
int vino = 0;

//double dError;
//double Error;
//double Pwm;

nmea_msg gpsx; 											//GPS��Ϣ
unsigned char longitude[50];   								//��ӡ������
unsigned char latitude[50]; 

void Gps_Msg_Show(void)
{
 	float tp;		     	 
	tp=gpsx.longitude;	   
	sprintf((char *)longitude,"%.3f %1c-",tp/10000,gpsx.ewhemi);	//�õ������ַ��� 	
	tp=gpsx.latitude;
	sprintf((char *)latitude,"%.3f %1c-",tp/10000,gpsx.nshemi);	//�õ�γ���ַ���	 
}

/*void Gps_Msg_Show(void)
{
 	float tp;		     	    
	sprintf((char *)longitude,"%.5f %1c-",gpsx.longitude/100000,gpsx.ewhemi);	//�õ������ַ��� 	
	sprintf((char *)latitude,"%.5f %1c-",gpsx.latitude/100000,gpsx.nshemi);	//�õ�γ���ַ���	 
}*/

void delay_ms(unsigned int i) {

	unsigned int a;
	unsigned char b;
	for (a = 0; a < i; a++) {
		for (b = 1; b; b++) {
			;
			}
		}
}


		
/*
*ICP_1�жϺ���
*��λ��ʱ������ֵ
*��������ź�,�������жϣ�������֡������
*�����źţ�����ֹ����������յ�����ֵ�
*/

//�ж������� 12    T1���벶׽�¼��ж�

#pragma interrupt_handler INT_T1_ICP: 12
void INT_T1_ICP(void)
{
	TIMSK &= ~(1 << TOIE1);						//�ر�����ж�	
	num_pulse_1++;
	
	//TIMSK |= (1 << TOIE1);						//����ж���Ч					
	//TIFR |= (1 << TOV1);						//����жϱ�־���		
	//flag = TCNT1;
	TIMSK |= (1 << TOIE1);						//������ж�		
}

/*
*ICP_3�жϺ���
*��λ��ʱ������ֵ
*��������ź�,�������жϣ�������֡������
*�����źţ�����ֹ����������յ�����ֵ�
*/

//�ж������� 12    T1���벶׽�¼��ж�

#pragma interrupt_handler INT_T3_ICP: 26
void INT_T3_ICP(void)
{
	TIMSK &= ~(1 << TOIE1);						//�ر�����ж�	
	num_pulse_3++;
	
	//TIMSK |= (1 << TOIE1);						//����ж���Ч					
	//TIFR |= (1 << TOV1);						//����жϱ�־���		
	//flag = TCNT1;
	TIMSK |= (1 << TOIE1);						//������ж�		
}

#pragma interrupt_handler INT_T1_OV: 15
void INT_T1_OV(void)
{
	TIMSK &= ~(1 << TICIE1);			//��׽�ж�ICP1ʧ��	
	ETIMSK &= ~(1 << TICIE3);			//��׽�ж�ICP3ʧ��	
	if(TCNT1 == 0)
	{
		vino++;
		get_num_pulse_1 = num_pulse_1;					//ȥȡ��һ����ICP_1��׽��������
		get_num_pulse_3 = num_pulse_3;					//ȥȡ��һ����ICP_3��׽��������
		////////sent(get_num_pulse*3/20);
		if(vino == 25)
		{
			//flag++;
			sent((get_num_pulse_1)*5/2);
			sent((get_num_pulse_3)*5/2);
			//sent(get_num_pulse_1);
			//sent(get_num_pulse_3);
			vino = 0;
		}
		num_pulse_1 = 0;								//�����������
		num_pulse_3 = 0;								//�����������

		/**********
		*��һ��pid�ĳ���
		*�����ٶ�Ϊ�Զ���
		*pid��������pwm
		***********/
		p->Vpv = ((get_num_pulse_1)*5/2);		//��ǰ�ٶ�  r/min
		////////p->Vpv = (get_num_pulse*3/20);		//��ǰ�ٶ�  r/min
		p->Error = p->Vsp - p->Vpv;		//ƫ��
		p->Vse += p->Error;				//���� 
		p->dError = p->Vle - p->Vpe;	//��ǰ΢��
		p->Vpe = p->Vle;
		p->Vle = p->Error;
		p->Pwm = p->Kp * p->Error + p->Ki * p->Vse + p->Kd * p->dError;
		
		if((OCR3A + p->Pwm) > 255)
		{
			OCR3A = 255;
		}
		else if((OCR3A + p->Pwm) < 0)
		{
			OCR3A = 0;
		}
		else
		{
			OCR3A=OCR3A+p->Pwm;		//����PWMռ�ձȣ�ת��λ��ʽPID�㷨
			OCR3B = OCR3A;
		}
		
		/**********
		*�ڶ���pid�ĳ���
		*�����ٶ�Ϊ��һ��pid���ص���ʵ�ٶ�
		*pid����������������ٶȲ�
		***********/
		v->Vsp = ((get_num_pulse_1)*5/2);		//����ֵȡ��һ��pwm���ص���ʵ�ٶ�ֵ
		v->Vpv = ((get_num_pulse_3)*5/2);		//��ǰ�ٶ�  r/min
		////////p->Vpv = (get_num_pulse*3/20);		//��ǰ�ٶ�  r/min
		v->Error = v->Vsp - v->Vpv;		//ƫ��
		v->Vse += v->Error;				//���� 
		v->dError = v->Vle - v->Vpe;	//��ǰ΢��
		v->Vpe = v->Vle;
		v->Vle = v->Error;
		v->Pwm = v->Kp * v->Error + v->Ki * v->Vse + v->Kd * v->dError;
		
		if((OCR3B + v->Pwm) > 255)
		{
			OCR3B = 255;
		}
		else if((OCR3B + v->Pwm) < 0)
		{
			OCR3B = 0;
		}
		else
		{
			OCR3B=OCR3B+v->Pwm;		//����PWMռ�ձȣ�ת��λ��ʽPID�㷨
		}
		
		
		
		TCNT1 = 64285;
	}
	

	TIMSK |= (1 << TICIE1);			//��׽�ж���Ч	
	ETIMSK |= (1 << TICIE3);			//��׽�ж���Ч	

}
#pragma interrupt_handler stolen:11
void stolen()
{
  sec_time=(sec_time+1)%40;
  if(sec_time==0)
    now_time++;
  TCNT2=55;
}
/*
*UART1�����жϺ���
*�����ֻ��˷��������ź�
*/

#pragma interrupt_handler uart1_receive:31
void uart1_receive()
{
   static unsigned char st_bit=0;
   unsigned char n;
   n=UDR1;
  if((0!=st_bit)&&(uart1_receive_flag))
     {
	   app_data[st_bit]=n-'0';
	   st_bit++;
	 }
   else  if((uart1_receive_flag)&&('s'==n)&&(0==st_bit))
     {
	   st_bit++;
	 }
   
   if(4==st_bit)
     {
	   st_bit=0;
	   uart1_receive_flag=0;
	 }
 
	
}

void main(void)
{
   unsigned char i;
   unsigned int rxlen;
	PIDInit_1();
	PIDInit_3();
	io_init(); 
	t3_init();
	ICP_1_init();
	ICP_2_init();
	ICP_3_init();
	uart_init(9600);
    uart1_init(9600);
	while(1)
	{    
	     
		 uart1_receive_flag=1;
		 delay_ms(500);
		 if((app_data[1])&&(0==lock_flag))//����������
		   {
		     lock_close();
			 lock_flag=1;
		   }
		 else if((0==app_data[1])&&(1==lock_flag))
		   {
		     lock_open();
			 lock_flag=0;
		   }
		 
		 if(0==app_data[2])//����ǰ��
		   stop(); 
		 if(1==app_data[2])
		   move();
		 
		 if(0==app_data[3])//��ʧ�ж�
		 {
		   bell_close();
		   now_time=0;
		   TIMSK&=~(1<<TOIE2);//�ض�ʱ������2����ж� 
		 }
		 if(1==app_data[3])
		 {
		   uart1_receive_flag=1;
		   delay_ms(500);
		   uart1_receive_flag=1;
		   delay_ms(500);
		   if(1==app_data[3])
		   {
		   TIMSK|=(1<<TOIE2);//����ʱ������2����ж� 
		   bell_open();
		   }
		 }
		 if(10==now_time)//10�뱨����������
		 {
		   alarm_mes();
		   now_time=0;
		 }
		
	}
}