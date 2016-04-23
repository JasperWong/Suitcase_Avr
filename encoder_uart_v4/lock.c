#include <iom128v.h>
#include "lock.h"

void lock_open()
{
   PORTD|=(1<<0);
   delay_ms(200);
   PORTD&=~(1<<0);
}
void lock_close()
{
   PORTD|=(1<<1);
   delay_ms(200);
   PORTD&=~(1<<1);
}

