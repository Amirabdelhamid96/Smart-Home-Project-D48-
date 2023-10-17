
#include <avr/io.h>
#include <util/delay.h>

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)


void Buzzer_on(void)
{
	//buzzer
	setbit(DDRA,3);
	setbit(PORTA,3);
}

void Buzzer_off(void)
{
	//buzzer
	setbit(DDRA,3);
	clearbit(PORTA,3);
}