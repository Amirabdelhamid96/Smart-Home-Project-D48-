

//delay function  
//ms delay function 
//us delay function 

//second delay function 












#include <avr/io.h>
#include <avr/interrupt.h>
#define LED PD6
char counter =0;

void timer_init()
{
	TCNT0=0;
	TCCR0 |=  (1<<CS02);//256  prescaler
}


//  delay (no of seconds)
//  256 no counts 15

void delay_sec(int sec)
{
	int i ;
	int counts = sec *15 ;  //15 --> 1 
	
	for(i=0;i<counts;i++)   //little bug
	{
		while ((TIFR&(1<<TOV0))==0)
		{		}// check over or not
		TIFR =  0x01; // clear flag
	}
}



int main()
{
	timer_init();  //calling
	DDRD=0xff;     //configure PORTD as output
	while(1)
	{
		delay_sec(3); //delay function
		PORTD ^= (1 << LED);
	}
}
