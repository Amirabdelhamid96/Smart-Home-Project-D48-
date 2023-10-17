

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


int main ()
{
	DDRB=255;
	
		while(1){
			PORTB=0;
			_delay_ms(1000);
			PORTB=255;
			_delay_ms(1000);
		}
		
}


















/*
	//(COM01 non inverting) cs00 prescaler 1    (wgm01 wgm00 fastpwm)
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	// init
	DDRB|=(1<<PB3);
	//OC0 = output
	OCR0=10;
	*/
