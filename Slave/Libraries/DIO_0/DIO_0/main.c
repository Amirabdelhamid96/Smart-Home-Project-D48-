
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRC |= (1<<PC2);
	while (1) 
    {
		PORTC |= (1<<PC2); 
		_delay_ms(1000);
		PORTC &= ~(1<<PC2);  //logic and & with inv//   ~000000001  ====  111111110 & port ==> 10101110 
		_delay_ms(1000);
    }
}

