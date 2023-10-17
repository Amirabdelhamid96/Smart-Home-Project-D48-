

//1- initialize 
// prescale 
//2- function
//counts reach desired time

// clock 1,000,000  
// 256
// wanted 1 sec
//
//nov = (1)/(256 counts * (256/1,000,000)   )
// = 15.2 no.  == 15 ==> 1 sec
// 










#include <avr/io.h>
#include <avr/interrupt.h>
#define LED PD6
char counter =0;

void timer_init()
{
	TCNT0=0; // defines fraction <--> counting 
	TCCR0 |=  (1<<CS02); //256  prescaler
}





int main()
{
	timer_init();//calling
	DDRD|=1<<LED;   //output pd6      
	
	while(1)
	{
		while ((TIFR&(1<<TOV0))==0)
		{		} // to check tov0 bit flag TIFR 1 
				  // 0 within loop over to end
			
			
			
		counter ++;// major glass
		if (counter==15)  // 1 sec
		{
			PORTD ^= (1 << LED);//toggle
			counter =0;
		}
		TIFR = 0x01;// clear reuse for thhe next loop
	}
}








