
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>

#define setbit(reg,bit)     reg|=(1<<bit)
//   setbit (reg , bit )
//   reg |= (1 << bit) 
#define clearbit(reg,bit)   reg&=(~(1<<bit))
#define toggelbit(reg,bit)  reg ^=(1<<bit)
//toggle(reg,bit)     
// reg ^=(1<<bit);
#define readbit(reg,bit)    ((reg&(1<<bit))>>bit)


int main(void)
{
   setbit(DDRC,2);
   
    while (1) 
    {
		toggelbit(PORTC , 2);
		_delay_ms(1000);
		
    }
}

