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
void Servo(unsigned int d);
void Dimmer(unsigned int d);
void int1_init();   // INT1
void int0_init();   // INT0
void Bulb_on(int a);
void Bulb_off(int a);
void SPI_Init();
void SPI_Write(char data);
char SPI_Read();
void LCD_Next_Line(void);
void LCD_Shift_Right(void);
void LCD_Shift_Left(void);
void LCD_Clear(void);
void LCD_Home(void);
void Timer1_init();
void Timer1_start();
void Timer1_set_freq(int frequency);
void Timer1_set_direction(int angle);
void Servo_init(void);
void Servo_open(void);
void Servo_close(void);
void Buzzer(void);


void Bluetooth_Menu(void)
{
	int x=0;
		x=UART_receivechar();
		if(x=='1')
		{SPI_Write(1);
		_delay_ms(100);}
		else if(x=='2')
		{SPI_Write(2);
		_delay_ms(100);}
		else if(x=='3')
		{	
		SPI_Write(3);
		_delay_ms(100);
		
		}
		else if(x=='4')
		{
		SPI_Write(4);
		_delay_ms(100);
		}
		else if(x=='5')
		{SPI_Write(5);
		_delay_ms(100);}
		else if(x=='6')
		{SPI_Write(6);
		_delay_ms(100);}
		else if(x=='7')
		{setbit(DDRC,2);
		setbit(PORTC,2);}
		else if(x=='8')
		{clearbit(DDRC,2);
		clearbit(PORTC,2);}
		else if(x=='9')
		{setbit(DDRC,7);
		setbit(PORTC,7);}
		else if(x=='0')
		{clearbit(DDRC,7);
		clearbit(PORTC,7);}
		else if(x=='A')
		{SPI_Write(0X0F);
		_delay_ms(100);}
		else if(x=='B')
		{SPI_Write(0XA0);
		_delay_ms(100);}
		else if(x=='C')
		{SPI_Write(0XA1);
		_delay_ms(100);}
		else if(x=='D')
		{SPI_Write(0XA3);
		_delay_ms(100);}
		else if(x=='E')
		{SPI_Write(0XA4);
		_delay_ms(100);}
		else if(x=='F')
		{
		LCD_Next_Line();
		LCD_send_string_4bit("Temp.:");
		SPI_Write(0xA2);
		_delay_ms(100);
		unsigned int read=0xFF;
		read=SPI_Read();
		_delay_ms(100);
		if(read!=0xFF)
		Int_ASC(read);
		read=0xFF;
		read=SPI_Read();
		_delay_ms(100);
		if(read!=0xFF)
		Int_ASC(read);
		_delay_ms(5000);
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Bluetooth Mode");
		}
		else if(x=='g')
		{clearbit(DDRD,3);
		clearbit(PORTD,3);}									
		else if(x=='h')
		{setbit(DDRD,3);
		setbit(PORTD,3);}
		else if(x=='i')
		{setbit(DDRD,3);
		setbit(PORTD,3);}
		else if(x=='j')
		{setbit(DDRD,3);
		setbit(PORTD,3);}
		else if(x=='k')
		{setbit(DDRD,3);
		setbit(PORTD,3);}																													
}//void
