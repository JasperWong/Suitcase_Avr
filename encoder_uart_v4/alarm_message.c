#include<iom128v.h>
#include "gps.h"
#include "alarm_message.h"
#include "encoder.h"
#include "data_get.h"
#include "sim900a.h"
#include "usart0.h"

extern unsigned char data[3000];
extern nmea_msg gpsx; 		

extern unsigned char longitude[50];

void clean_data()
{
  unsigned int i;
  for(i=0;i<2999;i++)
    data[i]=0;
}

void data_get()
{
  unsigned int n;
  for(n=0;n<2999;n++)
    data[n]=uart0_receive();
}

void alarm_mes()
{
   unsigned int n;
	data_get();
	GPS_Analysis(&gpsx,(unsigned char*)data);//�����ַ���
	Gps_Msg_Show();				//��ʾ��Ϣ	
	sim900a_sms_test();
	clean_data();
}