#include"iom128v.h"

#define uchar unsigned char
#define uint unsigned int

#define pi 3.1415926

/*���ڳ�ʼ������*/
void uart0_init(void);

/*���ݷ��ͣ���ѯ��ʽ*/
void uart0_transmit(unsigned char i);

/*���ݷ���,�ֽ�ÿλ����*/
void sent(int number);

/*���ݷ��ͣ��ַ������*/
void uart0_str(unsigned char *p);

/*���ݽ��գ��ȴ���ѯ��ʽ*/
unsigned char uart0_receive(void);