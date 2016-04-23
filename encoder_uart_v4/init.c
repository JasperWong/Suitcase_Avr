#include <iom128v.h>
#include "init.h"
void ICP_1_init(void)
{
	TCCR1B |= (1<< ICNC1 );			//输入捕捉噪声抑制器
	TCCR1B &= ~(1 << ICES1);		//下降沿触发
	//TCCR1B  |= (1 << CS10) | (1<<CS11);			//64分频
	TCCR1B  |= (1 << CS12);			//256分频
	//TCNT1 = 0;
	/////////TCNT1 = 34285;					//片内8M 1s
	TCNT1 = 64285;					//片内8M 40ms
	//TCNT1 = 62410;					//片内8M 100ms
	//TCNT1 = 49911;					//片内1M 1s
	//TCNT1 = 15625;					//片内1M 1s
	
	TIMSK |= (1 << TICIE1);			//捕捉中断有效					
	TIMSK &= ~(1 << TOIE1);			//溢出中断关闭					

	TIFR |= (1 << ICF1);			//捕捉中断标志清除				
	
	/*IO设置*/
	PORTD &= ~(1<<PD4);
	DDRD &= ~(1<<PD4);
	 
}

void ICP_2_init(void)
{
    TCCR2|=(1<<CS22)|(1<<CS20);//1024分频普通模式
	TIMSK|=(1<<TOIE2);//定时计数器2溢出中断 
	TCNT2=55;
	
}

void ICP_3_init(void)
{
	TCCR3B |= (1<< ICNC3 );			//输入捕捉噪声抑制器
	TCCR3B &= ~(1 << ICES3);		//下降沿触发
	//TCCR1B  |= (1 << CS10) | (1<<CS11);			//64分频
	TCCR1B  |= (1 << CS32);			//256分频
	//TCNT1 = 0;
	/////////TCNT1 = 34285;					//片内8M 1s
	TCNT1 = 64285;					//片内8M 40ms
	//TCNT1 = 62410;					//片内8M 100ms
	//TCNT1 = 49911;					//片内1M 1s
	//TCNT1 = 15625;					//片内1M 1s
	
	ETIMSK |= (1 << TICIE3);			//捕捉中断有效					
	ETIMSK &= ~(1 << TOIE3);			//溢出中断关闭					

	ETIFR |= (1 << ICF3);			//捕捉中断标志清除				
	
	/*IO设置*/
	PORTE &= ~(1<<PE7);
	DDRE &= ~(1<<PE7);
	 
}


