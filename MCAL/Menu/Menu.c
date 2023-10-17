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


unsigned char get_answer(void)
{
			unsigned char k=0xFF;
			while(k==notpressed)
			{
			k=get_key_value();
			if(k!=notpressed)
			LCD_send_data_4bit(k);
			SPI_Write(0XFF);
			_delay_ms(50);
			}
			return k;
}

void menu(void)
{	
	int Menu_flag=0;
	unsigned char choice=0xFF;
	
	while(1)
	{
	
	if(Menu_flag==0)
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("User Mode  R:1");
		LCD_Next_Line();
		LCD_send_string_4bit("Dim:2 AC:3 ~:4");
		choice=get_answer();
		
		//Main Menu
		/////////////////////////
		if(choice=='1')
		{
		Menu_flag=1;	
		}
		else if(choice=='2')
		{
		Menu_flag=2;	
		}		
		else if(choice=='3')
		{
		Menu_flag=3;	
		}
		else if(choice=='4')
		{
		Menu_flag=4;	
		}	
	}//0
	////////////////////////////
	
	if(Menu_flag==1)
	{
	LCD_Clear();
	LCD_Home();
	_delay_ms(100);
	LCD_send_string_4bit("R1:1 R2:2 R3:3");
	LCD_Next_Line();
	LCD_send_string_4bit("R4:4 R5:5 Ret.:0");		
	choice=get_answer();
	//Bulbs
	////////////////////////////
	if(choice=='1')
	{
	LCD_Clear();
	LCD_Home();	
	_delay_ms(100);
	LCD_send_string_4bit("Room1 Lights");
	LCD_Next_Line();
	LCD_send_string_4bit("On:1 Off:2 Ret:0");
	Menu_flag=5;
	}
	if(choice=='2')
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Room2 Lights");
		LCD_Next_Line();
		LCD_send_string_4bit("On:1 Off:2 Ret:0");
		Menu_flag=6;
	}	
	if(choice=='3')
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Room3 Lights");
		LCD_Next_Line();
		LCD_send_string_4bit("On:1 Off:2 Ret:0");
		Menu_flag=7;
	}
	if(choice=='4')
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Room4 Lights");
		LCD_Next_Line();
		LCD_send_string_4bit("On:1 Off:2 Ret:0");
		Menu_flag=8;
	}
	if(choice=='5')
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Room5 Lights");
		LCD_Next_Line();
		LCD_send_string_4bit("On:1 Off:2 Ret:0");
		Menu_flag=9;
	}			
	if(choice=='0')
	{
		Menu_flag=0;
	}
		
	}//1
	if(Menu_flag==5)
	{
		choice=get_answer();
		if(choice=='1')
		{
		SPI_Write(1);
		_delay_ms(100);
		}
		if(choice=='2')
		{
		SPI_Write(2);
		_delay_ms(100);
		}	
		if(choice=='0')
		{Menu_flag=1;}		
	}
	if(Menu_flag==6)
	{
		choice=get_answer();
		if(choice=='1')
		{		
			SPI_Write(3);
			_delay_ms(100);
		}
		if(choice=='2')
		{		
			SPI_Write(4);
			_delay_ms(100);
		}
		if(choice=='0')
		{Menu_flag=1;}
	}
	if(Menu_flag==7)
	{
		choice=get_answer();
		if(choice=='1')
		{		
			SPI_Write(5);
			_delay_ms(100);
		}
		if(choice=='2')
		{		
			SPI_Write(6);
			_delay_ms(100);
		}
		if(choice=='0')
		{Menu_flag=1;}
	}		
	if(Menu_flag==8)
	{
		choice=get_answer();
		if(choice=='1')
		{		
			//SPI_Write(7);
			//_delay_ms(100);
			setbit(DDRC,2);
			setbit(PORTC,2);
		}
		if(choice=='2')
		{		
			clearbit(DDRC,2);
			clearbit(PORTC,2);			
			//SPI_Write(8);
			//_delay_ms(100);
		}
		if(choice=='0')
		{Menu_flag=1;}
	}	
	if(Menu_flag==9)
	{
		choice=get_answer();
		if(choice=='1')
		{		
			setbit(DDRC,7);
			setbit(PORTC,7);						
			//SPI_Write(9);
			//_delay_ms(100);
		}
		if(choice=='2')
		{		
			clearbit(DDRC,7);
			clearbit(PORTC,7);			
			//SPI_Write(0);
			//_delay_ms(100);
		}
		if(choice=='0')
		{Menu_flag=1;}
	}
	//Dimmer
	///////////////////////////
	if(Menu_flag==2)
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Dimmer:1~5");
		LCD_Next_Line();
		LCD_send_string_4bit("Ret:0");
		choice=get_answer();
		if(choice=='1')
		{clearbit(DDRD,3);
		clearbit(PORTD,3);}
		if(choice=='2')
		{setbit(DDRD,3);
		setbit(PORTD,3);}
		if(choice=='3')
		{setbit(DDRD,3);
		setbit(PORTD,3);}
		if(choice=='4')
		{setbit(DDRD,3);
		setbit(PORTD,3);}
		if(choice=='5')
		{setbit(DDRD,3);
		setbit(PORTD,3);}	
		if(choice=='0')
		{Menu_flag=0;}
				
	}
	if(Menu_flag==3)
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Air Cond. Auto:1");
		LCD_Next_Line();
		LCD_send_string_4bit("On:2 Off:3 Ret:0");
		choice=get_answer();
		if(choice=='1')
		{
			SPI_Write(0X0F);
			_delay_ms(100);
		}
		if(choice=='2')
		{
			SPI_Write(0XA0);
			_delay_ms(100);
		}
		if(choice=='3')
		{
			SPI_Write(0XA1);
			_delay_ms(100);
		}
		if(choice=='0')
		{Menu_flag=0;}
		
	}
	if(Menu_flag==4)
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Temp:4");
		LCD_Next_Line();
		LCD_send_string_4bit("Door:5 Ret:0");
		choice=get_answer();
		if(choice=='4')
		{Menu_flag=10;}
		if(choice=='5')
		{Menu_flag=11;}
		if(choice=='0')
		{Menu_flag=0;}	
	}	
	if(Menu_flag==10)
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Temp. Set(21~27)");
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
		choice=get_answer();
		if(choice=='0')
		{Menu_flag=4;}
	}	
	if(Menu_flag==11)
	{
		LCD_Clear();
		LCD_Home();
		_delay_ms(100);
		LCD_send_string_4bit("Door:");
		LCD_Next_Line();
		LCD_send_string_4bit("Bluetooth Only");
		choice=get_answer();
		/*
		LCD_send_string_4bit("Door: Open:1");
		LCD_Next_Line();
		LCD_send_string_4bit("Close:2 Ret:0");
		choice=get_answer();
		if(choice=='1')
		{SPI_Write(0xA3);}
		if(choice=='2')
		{SPI_Write(0xA4);}*/
		if(choice=='0')
		{Menu_flag=4;}
	}	
	
		
	}//While
	
}//void
