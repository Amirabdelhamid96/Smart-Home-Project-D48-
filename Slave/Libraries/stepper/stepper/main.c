
#define F_CPU 1000000UL  //frequency speed of execution clock rate
#include<avr/io.h>
#include<util/delay.h>
void step(char x);
int main()
{
	DDRC=0XFF;              // 255 0b11111111
	int x =0;
	while(1)
	{						
			step(x++);
			_delay_ms(1000);
			if(x==4)x=0;	
    }
}



void step(char x)
{
	PORTC=1<<x;			//1  0  0  0  //1<<PC3
}