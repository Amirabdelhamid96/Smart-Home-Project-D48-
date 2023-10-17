
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>
//1-sequential power connection A B C D   OUTPUT --> key
//2-loop detect pin no 1 2 3 4            key --> Input
#define A 0
#define B 1
#define C 2
#define D 3

#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit)    ((reg&(1<<bit))>>bit)	// input read

int main(void)
{
	DDRD = 255; // port D direction  output A B C D
	DDRC = 0;   // port c			 input 1 2 3 4
	DDRA = 255;
	char x = 0;
	while (1)
	{	//---------A------------//
		PORTD=(1<<A);
		if(readbit(PINC,PC0)==1)		x = 7;
		if(readbit(PINC,PC1)==1)		x = 8;
		if(readbit(PINC,PC2)==1)		x = 9;
		if(readbit(PINC,PC3)==1)		x = '/';
		_delay_ms(1);
		//---------B------------//
		PORTD=(1<<B);
		if(readbit(PINC,PC0)==1)		x = 4;
		if(readbit(PINC,PC1)==1)		x = 5;
		if(readbit(PINC,PC2)==1)		x = 6;
		if(readbit(PINC,PC3)==1)		x = '*';
		_delay_ms(1);
		//---------C------------//
		PORTD=(1<<C);
		if(readbit(PINC,PC0)==1)		x = 1;
		if(readbit(PINC,PC1)==1)		x = 2;
		if(readbit(PINC,PC2)==1)		x = 3;
		if(readbit(PINC,PC3)==1)		x = '-';
		_delay_ms(1);
		//---------D------------//
		PORTD=(1<<D);
		if(readbit(PINC,PC0)==1)		x = 'o';
		if(readbit(PINC,PC1)==1)		x = 0;
		if(readbit(PINC,PC2)==1)		x = '=';
		if(readbit(PINC,PC3)==1)		x = '+';
		_delay_ms(1);
		
		PORTA=x;
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
