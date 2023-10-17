

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main ()
{
	unsigned char d;
	//(COM01 non inverting) cs00 prescaler 1    (wgm01 wgm00 fastpwm)
 	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	// init
	DDRB|=(1<<PB3);
	//OC0 = output
	
	while (1)
	{					// OCR0= variable
		for(d=0; d<255; d++)
		{
			OCR0=d;  //increase 
			_delay_ms(10);
		}
	//255 ==> 100
	//0   ==> 0
		for(d=255; d>1; d--)
		{
			OCR0=d;  //decrease 
			_delay_ms(10);
		}
	}
}