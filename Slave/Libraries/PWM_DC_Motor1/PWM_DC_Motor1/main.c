

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>


void motor(unsigned char d,unsigned char r);

int main ()
{
	while (1)
	{
		//1- duty 
		//2- direction
		//3- break PA1 PA0 high
			motor(100,1);//R
			_delay_ms(5000);
			motor(50,0);//L
			_delay_ms(5000);
	}
}




void motor(unsigned char d,unsigned char r)
{
	
	
	DDRA  |= (1<<PA0 ) | (1<<PA1);// IN1 IN0
	if (r>=1)
		PORTA = 1<<PA0;// PA0 IN1 high
	else
		PORTA = 1<<PA1;// PA1 IN2 high
	
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);// PIN OC0 output Enable1 pwm
	OCR0=((d*255)/100);// duty
}