//  DIO interface ==> lcd motor s7 keypad key&lcd leds P.Bs
//  interrupt 
//  operational process == led toggle 
//  ext interrupt == > pause process , cpu process  another process
//  old process continue 
//  interrupt process subroutine
//   


#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h> // header interrupt
#include <util/delay.h>

// macros for DIO
#define setbit(reg,bit) reg|=(1<<bit)    // one 
#define clearbit(reg,bit) reg&=~(1<<bit) // zero
#define toggelbit(reg,bit) reg^=(1<<bit) // toggle
#define readbit(reg,bit) ((reg>>bit)&1)  //read

// prototype
void int1_init();   // INT1
void int0_init();   // INT0

int main(void)
{
	setbit(DDRA,5);		// make LED as OUTPUT
	int1_init();        // calling
	int0_init();
	
	setbit(DDRB,6);     // toggle pin LED
    
	while (1) // super loop main_routine 
    {
		toggelbit(PORTB,6); // toggling 
		_delay_ms(500);     // delay 500ms
    }
}

void int1_init() // int1 intialization 
{
	clearbit(DDRD,3);    // set pin as INPUT
	clearbit(MCUCR,ISC11); // The rising edge of INT1 generates an interrupt request.
	setbit(MCUCR,ISC10); // The rising edge of INT1 generates an interrupt request.	
	setbit(GICR,INT1);   // external interrupt  EN  INT1
	sei();               // global interrupt EN
}



// pulse
//   R  ____  F     High level  5v
//     |    |
// ____|    |____   low level   0v
 
// Push button --> pulse  --> define wich part of the pulse
//
// 



void int0_init()
{
	clearbit(DDRD,2);    // set pin as INPUT
	setbit(MCUCR,ISC01); // The rising edge of INT1 generates an interrupt request.
	setbit(MCUCR,ISC00); //The rising edge of INT1 generates an interrupt request.
	setbit(GICR,INT0);   // external interrupt  EN INT0    
	sei();               // global interrupt EN
}

// handler : function --> subroutine other code for interrupt   
// 






// int1 --> set bit 5
ISR(INT1_vect)  // interrupt service routine ISR handler --> vetor name ==>table--> address to the function --> process subroutine
{	// the code needed
	int x;
	for(x=0;x<7;x++)
	{	
		toggelbit(PORTA,5);
		_delay_ms(500);
	}
}

// int0 --> clear bit 5
ISR(INT0_vect)
{
	clearbit(PORTA,5);
}