#include <avr/io.h>
#include <avr/interrupt.h>
#define LED PD6
char counter =0;

void timer_init()
{
	TCNT0=189;
	TCCR0 |=  (1<<CS02);//256  prescaler
}

//1/(256*(256/1000000))
//15.2587
//16                 .2587
//1-.2587= .7413
//.7413*256 = 189.77
//fraction size 189
//  delay (no of seconds)
//  256 no counts 15

void delay_sec(int sec)
{
	int i ;
	int counts = sec *16 ;  //15 --> 1
	
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
