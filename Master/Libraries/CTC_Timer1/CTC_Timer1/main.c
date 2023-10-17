

#include <avr/io.h>

int main ( )
{
	DDRB |= (1<<3);		/*PB3 (OC0) as output */
	
	while (1)
	{
		OCR0 = 69; // first value ocr 0-->69 
		// CS00 COM00 COM01 WGM01
		TCCR0 = 0x39;		/* CTC, set on match, no prescaler */
/**/	while ((TIFR&(1<<OCF0)) == 0);  /* monitor OCF0 flag */
		TIFR = (1<<OCF0);	/* Clear OCF0 by writing 1 */
		//OCF0 1 
		OCR0 = 220;// 0--> 220
		// CS00 COM01 WGM01
		TCCR0 = 0x29;	  // CTC, clear on match, no prescaler 
		while ((TIFR&(1<<OCF0)) == 0);
		TIFR = (1<<OCF0);  // Clear OCF0 by writing 1 
	}
}
