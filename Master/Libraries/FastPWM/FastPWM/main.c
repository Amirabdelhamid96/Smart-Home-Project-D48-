

#include <avr/io.h>


int main(void)
{
    // fast PWM mode , non-inverted output
    TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
    DDRB|=(1<<PB3);  // OC0 pin as output
	OCR0 =50;		 //fast PWM compare value
	
    
}

