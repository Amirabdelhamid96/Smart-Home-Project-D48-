
#define F_CPU 1000000ul
#include <avr/io.h>
#include <util/delay.h>


//LCD drivers
//POT ADC driver 
//Timer ==>PWM drivers


#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)

// macros control pins
#define RS 1
#define RW 2
#define EN 3

// direction registers
#define LCD_DATA_DIR DDRC
#define LCD_control_DIR DDRD

//port registers
#define LCD_DATA_PORT PORTC
#define LCD_control_PORT PORTD





void LCD_send_data_4bit(unsigned char data)
{
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(data & 0xf0);//send high nibble
	setbit(LCD_control_PORT,RS);// rs 1
	clearbit(LCD_control_PORT,RW);
	setbit(LCD_control_PORT,EN);//en 1
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);// en 0
	_delay_us(200);
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(data<<4);//send low nibble
	setbit(LCD_control_PORT,EN);
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);
	_delay_ms(1);
	
}



void LCD_send_command_4bit(unsigned char cmd)
{
	//  7 6 5 4 3 2 1 0  Data pins no 8 bit
	//					 4bit 8/2 upper higher --> lower
	//	higher .lower
	//  0 1 0 1.0 1 0 1
	//EN=1 --> 0. --> 1 --> 0
	
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(cmd & 0xf0);//send high nibble
	
	// portd pd0 --> pd7
	// pd4 --> pd7   ==> pd4 pd5 pd6 pd7
	// not connected pd0 pd1 pd2 pd3
	// PORTD = 0b11110000
	// PORT = (PORT ==>0b1010.1010 & 0b0000.1111) | (cmd = 1010.0000 & 0b1111.0000)
	//        port = 0000.1010					|		1010.0000
	//							1010 . 0101
	//                          cmd  . old data
		
	clearbit(LCD_control_PORT,RS);
	clearbit(LCD_control_PORT,RW);
	setbit(LCD_control_PORT,EN);// en 1
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);// en 0
	_delay_us(200);// higher to lower nipple
	
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(cmd<<4);//send low nibble
	//									lower.shifted
	//cmd 1010.1010    cmd << 4 ==>      1010.0000
	//port = 1010.0101 & 0x0f == 0000.1010
	// cmd | port == 1010.1010
	// lcd port = 1010.1010
	
	// lcd operats on higher
	//8bits
	// 1111 0000
	// 1111
	// 0000
	
	//////////////// not the lcd operation ////////////////////
	// d0 d1 d2 d3
	// port & 0xf0   |   cmd & 0x0f lower
	// port & 0xf0   |   cmd >> 4 higher nibble
	///////////////////////////////////////////////////////
	
	setbit(LCD_control_PORT,EN);//en 1
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);//en 0
	_delay_ms(1); // time command
}

void LCD_INIT_4bit(void)
{
	LCD_DATA_DIR|= 0xf0;
	setbit(LCD_control_DIR,EN);
	setbit(LCD_control_DIR,RS);
	setbit(LCD_control_DIR,RW);
	LCD_send_command_4bit(0x02);// return home
	LCD_send_command_4bit(0x28);// 2 line  and 4 bit mode
	LCD_send_command_4bit(0x0c);// display on
	LCD_send_command_4bit(0x06);// auto increment
	LCD_send_command_4bit(0x01);// clear screen
	_delay_ms(20);
	
}

void LCD_send_string_4bit( char* str)
{
	int count =0;
	while(str[count]!=0)
	{
		LCD_send_data_4bit(str[count]);
		count++;
	}
}


void ADC_init() // init
{
/*	setbit(ADMUX,REFS0);  // external v refrance
	setbit(ADCSRA,ADEN);  // ADC enable
	setbit(ADCSRA,ADPS2);	// pres caller 16 ADC f = 62500 with the range of ADC (50k:200k)Hz
*/
    ADMUX|=(1<<REFS0);//AVCC with external capacitor at AREF pin
	ADCSRA |=(1<<ADEN);//ADC Enable
	//ADC speed must be in range of 50k to 200k HZ
	ADCSRA |=(1<<ADPS2);//PRESCALER 16 --> freq = 62500 Hz
// 1- external refrence cap
// 2- enable
// 3- prescaler        1000,000 /  = 50-200 KH ==>62500

}

// return value int 0-255
// input selection for channel 
// ADC0-->ADC7
// 100  --> 4 

// analoge to digital
int ADC_read(int ADC_chanel)
{
	int adc_value=0;
	//0b01000000 &
	//0b11100000 |
	//0b00000100
//==> 0b01000100
	ADMUX = (ADMUX&0xE0)|ADC_chanel;//choose which ADC will work channel
	//0xE0 ==> 0b11100000
	ADCSRA |=(1<<ADSC);//ADC Start Conversion
	while(readbit(ADCSRA,ADIF)==0) //wait until Conversion complete using polling not int
	{    // 0 lessah or 1 tamam
	}
	//safty code for make sure conversion is ended 
	_delay_us(10);//wait until the value store in ADC REG.
	//decimal max 1023
	//2.5v == 512
	//1.25 == 256
	//5    == 1023
	adc_value =(int)ADCL+(int)ADCH*256;//calculate the ADC value
	// ADCL 8 bit lower 
	// ADCH 2 bit higher  0b01 =1
	// x = (ADCL =256 )+(ADCH =1*256 )= 512
	//10-bit 11 1111 1111 => 1023 
	return adc_value ;
}


// value ==> lcd
// 1- lcd ascii 16541 to characters
// 2- 0  --> 48
// 0 --> 1023
//           1000    500   650
// no within  //////1023 to character/// display 
void Int_ASC(int ab)
{
	int i;
	int array[4]; // array arrange data 
	for(i=0; i<=3; i++)                  /* Convert decimal to ASCII                     */
	{	// 35% 10 ==> 5
		array[i] = ab%10; // remainder  500   10 % 10 ==> 0  --> 
		//array[0]  last ab = 1 (1 % 10)==> 1 --> array[1]
		// 0 % 10 = 0 --> 0%10 = 0   
		ab       = ab/10; // ab = 10/10 = 1 --> 1/10 ==> 0 int 
		//array[]={0 , 1 , 0 ,0 };
			// 0100
			// 0010
			//  5300
	}
	
	
	for(i=3; i>=0; i--)
	{
		LCD_send_data_4bit(array[i]+'0');               
		// '0' --> 48 
		// array[3]---->array[0]
		// 0 0 1 0
		// sending no : 48 ====> '0'
		// 0 1 2 3 ---> 9
		// 48 49 50 ---> end
	}
}




void motor(unsigned int d,unsigned char r)
{
	//IN1 --> IN4
	DDRA  |= (1<<PA0 ) | (1<<PA1)| (1<<PA2)| (1<<PA3);// output IN1 IN2 IN3 IN4
	
	if (r>=1)// IN1 IN3
	PORTA = (1<<PA0) | (1<<PA3);// IN1 IN4 high   
	else
	PORTA = (1<<PA1) | (1<<PA2);             //  IN2 IN3 high
	
	//(COM01 non inverting) cs00 prescaler 1    (wgm01 wgm00 fastpwm)
	TCCR0 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRB|=(1<<PB3);// PIN OC0 output Enable1 pwm
	OCR0=((d*255)/100);// duty  d ==> 10*255/100
}

// adc 0--> 1023  max 512    
// pwm 0--> 255   max 127
// 1023 <========> 255
//  adc/4

int main(void)
{
    LCD_INIT_4bit(); // init lcd 
	int x =0;
	clearbit(DDRA,4);//adc4 input
	setbit(DDRA,7);//led output
	ADC_init();// calling init
	
    while (1)
    {
	    x =ADC_read(4);//adc_value
		motor(x/4,1);// adc 512   ==> 50%   255/2  127   512/127 =4
		
	    if (x>511)
	    setbit(PORTA,7);//led on
	    else
	    clearbit(PORTA,7);//led off
		
		LCD_send_command_4bit(0x02);		// return home
		Int_ASC(x);// no lcd 
		//_delay_us(10);
		
    }
}

