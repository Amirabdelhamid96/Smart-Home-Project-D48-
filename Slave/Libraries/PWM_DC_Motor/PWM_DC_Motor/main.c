

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>



int main ()
{
	unsigned char d;
	DDRA =255;//
	PORTA |= 1<<PA0;// PA0 IN1 high
	PORTA |= 1<<PA1;// IN2 HIGH
	//PORTA |= (1<<PA0)|(1<<PA1);
	/*     */
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);// PIN OC0 output Enable1 pwm
	while (1)
	{
		for(d=0; d<255; d++)
		{
			OCR0=d;  //increase
			_delay_ms(10);
		}
		
		for(d=255; d>1; d--)
		{
			OCR0=d;  //decrease
			_delay_ms(10);
		}
	}
}