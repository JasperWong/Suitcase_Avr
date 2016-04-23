#include"iom128v.h"

#define uchar unsigned char
#define uint unsigned int

#define pi 3.1415926

/*串口初始化函数*/
void uart0_init(void);

/*数据发送，查询方式*/
void uart0_transmit(unsigned char i);

/*数据发送,分解每位数据*/
void sent(int number);

/*数据发送，字符串输出*/
void uart0_str(unsigned char *p);

/*数据接收，等待查询方式*/
unsigned char uart0_receive(void);