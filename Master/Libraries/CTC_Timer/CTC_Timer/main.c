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







/*

normal timers
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
*/

//TCNT0   ==> 255  over flow --> count++ 
//OCR0    ==> 50   0  --> 50
// pins   : OC0 --> set clear toggle
//  pin_OC0 : 1 or 0
// pulses depends OCR0 value 
// 1- scale 
// 2- action type set 
// pin OC0  set forever 0 --> 50  counter timer TCNT0
//			clear 
// pin OC0  toggle
// scale prescaler   
// CTC only ==> pulses 
// fast PWM  == > pulses 
// Duty ==> 50 10 30 90 100



//compare match CTC mode
/*
  TCNT0 becomes equal to the OCR0,
  a compare match occurs, and then the timer
  will get cleared and the OCF0 flag will get set
*/

#include <avr/io.h>

int main ( )
{
	
	DDRB = DDRB|(1<<3);	/* PB3 (OC0) as output */	
  /*TCCR0 |= (1<<WGM01);  
	TCCR0 |= (1<<CS00);
	TCCR0 |= (1<<COM00);
	TCCR0 |= (1<<COM00)|(1<<CS00)|(1<<WGM01);
	TCCR0 |= 0b00011001;*/
	
	TCCR0 = 0x19;		// CTC mode, toggle ,no pre-scaling 1
	OCR0 = 200;  		// compare value 
	//tcnt= 200   action on or off
	
	
	
	while (1);
}

