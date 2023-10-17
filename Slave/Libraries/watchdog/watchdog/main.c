

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>

void WDT_ON()
{
	/*
	Watchdog timer enables with typical timeout period 2.1 
	second.
	*/
	//1- enable 
	//2- scale time 
	//2.1 seconds enable
	//       en     /     2 . 1 seconds      / 
	WDTCR = (1<<WDE)|(1<<WDP2)|(1<<WDP1)|(1<<WDP0);
}

void WDT_OFF()
{
	
	//This function use for disable the watchdog timer.
	
	WDTCR = (1<<WDTOE)|(1<<WDE);
	WDTCR = 0x00;
}
//auto reset for MCU 
//


int main(void)
{	
	WDT_ON();		      // 2.1 second 
	DDRD |= 255;//output	
	PORTD |= (1<<6);	// high 
	_delay_ms(500);	
	PORTD &= ~(1<<6);	// low



    while(1){
		
	}
}