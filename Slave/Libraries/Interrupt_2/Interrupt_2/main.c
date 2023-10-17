#define F_CPU 1000000ul
#include <avr/io.h>
#include <avr/interrupt.h> // header interrupt
#include <util/delay.h>


#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)

void int1_init();   // INT1
void int0_init();   // INT0

int main(void)
{
	setbit(DDRA,5);		// make LED as OUTPUT
	int1_init();        // calling
	int0_init();
	setbit(DDRB,6);     // toggle pin LED
	while (1) 
	{
		toggelbit(PORTB,6); // toggling
		_delay_ms(500);     // delay 500ms
	}
}

void int1_init() 
{
	clearbit(DDRD,3);    // set pin as INPUT
	setbit(MCUCR,ISC11); // The rising edge of INT1 generates an interrupt request.
	setbit(MCUCR,ISC10); // The rising edge of INT1 generates an interrupt request.
	setbit(GICR,INT1);   // external interrupt  EN  INT1
	sei();               // global interrupt EN
}

void int0_init()
{
	clearbit(DDRD,2);    // set pin as INPUT
	setbit(MCUCR,ISC01); // The rising edge of INT1 generates an interrupt request.
	setbit(MCUCR,ISC00); //The rising edge of INT1 generates an interrupt request.
	setbit(GICR,INT0);   // external interrupt  EN INT0
	sei();               // global interrupt EN
}

ISR(INT1_vect)  
{	DDRC=0XFF;// output
	int x;
	for(x=0;x<10;x++)
	{
		PORTC=0x08;			//1  0  0  0
		_delay_ms(100);
		PORTC=0x04;			//0  1  0  0
		_delay_ms(100);
		PORTC=0x02;			//0  0  1  0
		_delay_ms(100);
		PORTC=0x01;			//0  0  0  1
		_delay_ms(100);

	}
}


ISR(INT0_vect)
{
	DDRC=0XFF;
	int x;
	for(x=0;x<10;x++)
	{
		PORTC=0x01;			
		_delay_ms(100);
		PORTC=0x02;			
		_delay_ms(100);
		PORTC=0x04;			
		_delay_ms(100);
		PORTC=0x08;			
		_delay_ms(100);

	}
}