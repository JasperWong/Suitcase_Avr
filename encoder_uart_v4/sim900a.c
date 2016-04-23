#include "sim900a.h"		
#include "delay.h"	
#include "usart0.h"
#include "string.h"
#include <iom128v.h>

extern unsigned char longitude[50];
extern unsigned char latitude[50]; 

unsigned char sim900a_sms_test()
{

    usart0_sent_string("AT+CMGF=1-");
	usart0_sent_char('\r');
    usart0_sent_char('\n');
	delay_ms(1000);
	usart0_sent_string("AT+CSCS=\"GSM\"-");
	usart0_sent_char('\r');
    usart0_sent_char('\n');
	delay_ms(1000);
	usart0_sent_string("AT+CMGS=\"18520287074\"-");
	usart0_sent_char('\r');
    usart0_sent_char('\n');
	delay_ms(1000);
	//usart0_sent_string(longitude);
	//usart0_sent_char(',');
	//usart0_sent_string(latitude);
	usart0_sent_string("23.05299 N , 113.39370 E");
	usart0_sent_char(0x1a);
	usart0_sent_char('\r');
    usart0_sent_char('\n');
	
	
	return 0;
} 
