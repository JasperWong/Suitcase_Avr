#include <iom128v.h>
#include "data_get.h"
#include "usart0.h"
extern unsigned char data[2000];
extern unsigned char data_rec_done_flag;
void clean_data()
{
  unsigned int i;
  for(i=0;i<2000;i++)
    data[i]=0;
}
void data_get()
{
  unsigned int n;
  for(n=0;n<1999;n++)
    data[n]=uart0_receive();
}

/*void data_return()
{
  unsigned int n;
  for(n=0;n<1999;n++)
    usart0_sent_char(data[n]);
}*/