//Slave
#define F_CPU 16000000ul
#include <avr/io.h>
#include <avr/interrupt.h> // header interrupt
#include <util/delay.h>
#include "keypad.h"

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)

void LCD_send_command(unsigned char cmd);
void LCD_send_data(unsigned char data);
void LCD_INIT(void);
void LCD_send_string( char str[]);
void LCD_send_data_4bit(unsigned char data);
void LCD_send_command_4bit(unsigned char cmd);
void LCD_INIT_4bit(void);
void LCD_send_string_4bit( char* str);
void Int_ASC(int ab);
void motor_start(void);
void motor_stop(void);
void ADC_init();
int ADC_read(int ADC_chanel);
void UART_INIT(unsigned int baud);
void UART_sendchar(unsigned char data);
unsigned char UART_receivechar();
void UART_sendString(char *str);
//void Dimmer(unsigned int d);
void int1_init();   // INT1
void int0_init();   // INT0
void Bulb_on(int a);
void Bulb_off(int a);
void SPI_Init();
void SPI_Write(char data);
char SPI_Read();
void Timer1_init();
void Timer1_start();
void Timer1_set_freq(int frequency);
void Timer1_set_direction(int angle);
void Servo_init(void);
void Servo_open(void);
void Servo_close(void);
void Int_SPI(int ab);
void Timer2_init();
void Timer2_start();
void Dimmer(int level);
void Dimmer_init(void);

int main(void)
{
	//Initialization
	ADC_init();
	SPI_Init();
	Servo_init();
	//Dimmer_init();
	
	//adc2 input
	unsigned int x =0;
	clearbit(DDRA,1);
	
	char AC_Flag=0;
	char signal=0xFF;	
	
	while(1)
	{
		
		//SPI Signal from Master
		signal=SPI_Read();
		x=ADC_read(1);
		
		if(signal==1)
		{Bulb_on(1);}
		if(signal==2)
		{Bulb_off(1);}		
		if(signal==3)
		{Bulb_on(2);}
		if(signal==4)
		{Bulb_off(2);}
		if(signal==5)
		{Bulb_on(3);}
		if(signal==6)
		{Bulb_off(3);}
		if(signal==7)
		{Bulb_on(4);}
		if(signal==8)
		{Bulb_off(4);}
		if(signal==9)
		{Bulb_on(5);}
		if(signal==0)
		{Bulb_off(5);}	
		/*
		if(signal==0X0A)
		{OCR2=0;}
		if(signal==0X0B)
		{Dimmer(0);}
		if(signal==0X0C)
		{Dimmer(90);}
		if(signal==0X0D)
		{Dimmer(180);}
		if(signal==0X0E)
		{OCR2=10;}
		*/		
		if(signal==0X0F)
		{AC_Flag=0;}
		if(signal==0XA0)
		{motor_start();AC_Flag=1;}
		if(signal==0XA1)
		{motor_stop();AC_Flag=1;}		
		if(signal==0XA2)
		{
			Int_SPI(x*500/1023);
		}		
		if(signal==0XA3)
		{
			Servo_open();
		}
		if(signal==0XA4)
		{
			Servo_close();
		}			
	
		if (AC_Flag==0)
		{			
	 
	       if ((x*500/1023)>28)
	       {
		     motor_start();
	       }
	       if ((x*500/1023)<21)
	       {
		     motor_stop();
	       }
		}

			
	}
}