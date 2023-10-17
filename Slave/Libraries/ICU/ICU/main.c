
#include <avr/io.h>
int main ( )
{
	//ICU 
	// input capture unit
	// measure input pulses time
	// pulses 
	// event 

	unsigned int t;
	DDRA = 0xFF;	
	DDRB = 0xFF;	
	PORTD = 0xFF;	  // high 
	// timer1  16 bit  8 & 8
	TCCR1A = 0; // init 
	TIFR = (1<<ICF1);		/* clear input capture flag */
	TCCR1B = 0x41;			/* capture on rising edge */ 
	// failing edge 
	// rising edge 
	// level
	//_____    _    _    _
    ///       |__| |__| |__| |_
    // 1- capture check 
	while ((TIFR&(1<<ICF1)) == 0);  /* monitor for capture*/
	// check capture   TIFR
	t = ICR1;	// 16 bit value		
	TIFR = (1<<ICF1);		/* clear capture flag */
	//pulse time - pulse time 
	while ((TIFR&(1<<ICF1)) == 0);  /* monitor for next rising	edge capture */
    // t == count 
    // count >10000 < 500
	t = ICR1 - t;  			/* period= recent capture-previous capture */
	PORTA = t;  			// put period count on PORTA & PORTB 	
	PORTB = t>>8;
	while (1);
	return 0;
}