

#include <avr/io.h>

#define setbit(reg,bit)     reg|=(1<<bit)// set 
#define clearbit(reg,bit)   reg&=(~(1<<bit)) // clear 
#define toggelbit(reg,bit)  reg ^=(1<<bit)  // toggle


#define readbit(reg,bit)    ((reg&(1<<bit))>>bit)
int main(void)
{   DDRB |= (1<<PB2);//set
	DDRC &= ~(1<<PC2);//pc2 input 
	PORTC |= (1<<PC2);  // internal pull up resistor
    while (1) 
    {	if (readbit(PINC,PC2) == 0)//button
			setbit(PORTB,PB2);//led
		else 
			clearbit(PORTB,2);//led
    }
}
	//PORTC |= (1<<2); // set bit 2 on port c high
	// pull up resistance internally
	//input pin output port
