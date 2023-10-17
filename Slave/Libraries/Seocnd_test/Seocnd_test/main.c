
#define F_CPU 1000000ul 
#include <avr/io.h>
#include <util/delay.h>
//1-sequential power connection A B C D   OUTPUT --> key
//2-loop detect pin no 1 2 3 4            key --> Input 
#define A 0
#define B 1
#define C 2
#define D 3

int main(void)
{
	DDRD = 255; // port D direction  output A B C D
	DDRC = 0;   // port c			 input 1 2 3 4
    while (1) 
    {	PORTD=(1<<A);
		_delay_ms(100);
		PORTD=(1<<B);
		_delay_ms(100);
		PORTD=(1<<C);
		_delay_ms(100);
		PORTD=(1<<D);
		_delay_ms(100);
		
    }
}





// portc
// 7 6 5 4 3 2 1 0
// 1 0 0 0 0 1 0 0  ==> decimeal 
//portc2
//portc7

//portd3
// 7 6 5 4 3 2 1 0
// 0 0 0 0 1 0 0 0  ==> decimal
