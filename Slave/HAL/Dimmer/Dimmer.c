
#include <avr/io.h>
#include <util/delay.h>

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)

/*
void Dimmer(unsigned int d)
{
	// IN1 IN4 high	
	DDRC  |= (1<<PC5 ) | (1<<PC6);// IN1 IN0
	PORTC |= (1<<PC5);// IN1 IN4 high
		
	//(COM01 non inverting) cs00 prescaler 1    (wgm01 wgm00 fastpwm)
	TCCR2 = (1<<WGM00) | (1<<WGM01) | (1<<COM21) | (1<<CS00);
	DDRD|=(1<<PD7);// PIN OC0 output Enable1 pwm
	OCR2=d;// duty
}
*/

void Timer2_init()
{
	//select PWM mode 14
	clearbit(TCCR2,0);
	setbit(TCCR2,1);
	setbit(TCCR2,3);
	setbit(TCCR2,4);

	//non-inverting
	clearbit(TCCR2,6);
	setbit(TCCR2,7);

	//user manual says PD5 and Kit says PD7 so i make the two
	//set OC1A Pin to be output: it has PWM
	setbit(DDRD,7);

	//set OC1A Pin to be output: it has PWM
	//setbit(DDRD,7);
}

void Timer2_start()
{
	//select 64 prescaller
	setbit(TCCR2,0);
	setbit(TCCR2,1);
	clearbit(TCCR2,2);
}

void Dimmer(int level){
	//Ton = (OCR+1)*4u;
	//(OCR+1) = Ton/4;
	//OCR = (Ton/4)-1;
	//OCR = (angle/4)-1;

	//------ 0 degree: Ton = 1.5ms i.e. 1500u (0 degree of servo is 45 degree in reality) --------------------
	switch(level){
		case 90:   OCR2 = 170;
		break;
		//-------------------- 90 degree: Ton = 2ms i.e. 2000u --------------------
		case 180:   OCR2 = 220;
		break;
		//-------------------- 180 degree: Ton = 1ms i.e. 1000u --------------------
		case 0:   OCR2 = 70;
		break;
	}
}

void Dimmer_init(void)
{
		Timer2_init();
		Timer2_start();

}

/*int main(void)
{
   int direction=1;
    LCD_INIT_4bit(); // init lcd 
	int x =0;
	clearbit(DDRA,4);//adc4 input
	setbit(DDRA,7);//led output
	ADC_init();// calling init
			clearbit(DDRD,4);
			clearbit(DDRD,5);
    while (1)
    {
		if(((PIND>>4)&1)==1)
		direction=0;
		if(((PIND>>5)&1)==1)
		direction=1;		
		x =ADC_read(4);//adc_value
		motor(x/4,direction);
	    if (x>511)
	    setbit(PORTA,7);//led on
	    else
	    clearbit(PORTA,7);//led off
		LCD_send_command_4bit(0x02);// return home
		Int_ASC(x);
		//_delay_us(10);
				
    }
}*/

/*int main(void)
{
   int direction=1;
    LCD_INIT_4bit(); // init lcd 
	int x =0;
	clearbit(DDRA,4);//adc4 input
	setbit(DDRA,7);//led output
	ADC_init();// calling init
			clearbit(DDRD,4);
			clearbit(DDRD,5);
    while (1)
    {
		if(((PIND>>4)&1)==1)
		direction=0;
		if(((PIND>>5)&1)==1)
		direction=1;		
		x =ADC_read(4);//adc_value
		motor(x/4,direction);
	    if (x>511)
	    setbit(PORTA,7);//led on
	    else
	    clearbit(PORTA,7);//led off
		LCD_send_command_4bit(0x02);// return home
		Int_ASC(x);
		//_delay_us(10);
				
    }
}*/