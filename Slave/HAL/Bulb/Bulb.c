
#include <avr/io.h>
#include <util/delay.h>

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)


void Bulb_on(int a)
{
		if(a==1)
		{
		setbit(DDRC,2);
		setbit(PORTC,2);	
		}
		if(a==2)
		{
			setbit(DDRC,7);
			setbit(PORTC,7);
		}
		if(a==3)
		{
			setbit(DDRD,3);
			setbit(PORTD,3);
		}
		if(a==4)
		{
			setbit(DDRA,6);
			setbit(PORTA,6);
		}
		if(a==5)
		{
			setbit(DDRA,7);
			setbit(PORTA,7);
		}
}

void Bulb_off(int a)
{
		if(a==1)
		{
			clearbit(DDRC,2);
			clearbit(PORTC,2);
		}
		if(a==2)
		{
			clearbit(DDRC,7);
			clearbit(PORTC,7);
		}
		if(a==3)
		{
			clearbit(DDRD,3);
			clearbit(PORTD,3);
		}
		if(a==4)
		{
			clearbit(DDRA,6);
			clearbit(PORTA,6);
		}
		if(a==5)
		{
			clearbit(DDRA,7);
			clearbit(PORTA,7);
		}
}