#include"pwm.h"


void io_init(void)
{
  DDRE=0xFF;
  DDRA=0xff;
  DDRD=0xff;
  DDRD&=~(1<<2);
  PORTD|=(1<<2);
}

/************************************
������ :     t3_init
���� :       t3��ʱ��ʼ�� ,8λ����PWMģʽ ,�޷�Ƶ��OCR1A/B��Χ0-255
������� :   ��
���ز��� :   ��
*************************************/
void t3_init(void)
{
   TCCR3A |=0xa9;//10101001
   TCCR3B |=0x09;//00001001
   OCR3A=0;
   OCR3B=0;
}