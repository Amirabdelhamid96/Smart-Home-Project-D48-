
#define F_CPU 1000000ul
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>


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

// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read


// command function 
void LCD_send_command(unsigned char cmd)
{
	// rs rw d7 d6 d5 d4 d3 d2 d1 d0
	// cmd = d7 d6 d5 d4 d3 d2 d1 d0= binary to hex
	//port data ==> cmd 
	//port = cmd
	//lcd_data_port = cmd
	//pd0 --> pd7
	//
	
	
	LCD_DATA_PORT = cmd;   //command
	// mesh active till enable opend
	
	clearbit(LCD_control_PORT,RS);  // rs = 0
	clearbit(LCD_control_PORT,RW);  // rw = 0
	setbit(LCD_control_PORT,EN);    // EN = 1
	_delay_us(1);					// micro second
	clearbit(LCD_control_PORT,EN);  // EN = 0
	_delay_ms(3);                   //milli  lcd command <+> command
}




void LCD_send_data(unsigned char data)
{
	
	LCD_DATA_PORT = data ;  // port == data 
	
	
	setbit(LCD_control_PORT,RS);    // RS = 1 --> lcd command--> 0 data-->1 
	clearbit(LCD_control_PORT,RW);	// write ==> 0
	setbit(LCD_control_PORT,EN);	//EN = 1
	_delay_us(1);					// delay 1 us
	clearbit(LCD_control_PORT,EN);  // en =0
	_delay_ms(1);					// lcd to separate from two data sending operations
}




void LCD_INIT(void)
{
	LCD_DATA_DIR =0xff;		//all output DDRC = 255 or 0xff
	
	
	setbit(LCD_control_DIR,EN);  // EN pin output
	setbit(LCD_control_DIR,RS);	 // RS pin out
	setbit(LCD_control_DIR,RW);	 // RW output
	_delay_ms(20);				// to make sure power is on for lcd 4.5v
								// > 15 ms
								
	LCD_send_command(0x38);		// LCD in 8 bit mode and 2 lines  5*8 dots
	LCD_send_command(0x0C);		// LCD DISPLY ON CURSER OFF
	LCD_send_command(0x06);		// LCD AUTO INCRMENT
	LCD_send_command(0X01);		// LCD CLEAR SCREAN 00000001
								// make sure there is nothing on lcd
								
	LCD_send_command(0X80);		// HOME POSITION
	
	//   0 1 2 3 4 5                   15
	//  *- - - - - - - - - - - - - - - -   line 1
	//   - - - - - - - - - - - - - - - -   line 2
}




void LCD_send_string( char str[])
{
	//          01234567\0
  //char * p = "asdfghjk";
	
	int count =0;
	
	while(str[count]!=0)
	{
		LCD_send_data(str[count]);
		count++;
	}
}










int main()
{
	LCD_INIT(); // init lcd 
	
	
	/*LCD_send_data('A');
	LCD_send_data('s');
	LCD_send_data('d');
	LCD_send_data('w');*/
	
	
	LCD_send_string("ha llo");
	_delay_ms(2000);
	LCD_send_command(0X01);
	LCD_send_string("AM IT");
	
	
	
	
	
	
	
	
	
	//ASCII  num 1 ==> nothing
	//ASCII  char '1' ==> 49
	
	
	//LCD_send_data('C');
	
	
	
	
	
	
//	_delay_ms(1000);
//	LCD_send_command(0X01);
	//LCD_send_string("hallo");
}























































/*
void LCD_send_data_4bit(unsigned char data)
{
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(data & 0xf0);//send high nibble
	setbit(LCD_control_PORT,RS);
	clearbit(LCD_control_PORT,RW);
	setbit(LCD_control_PORT,EN);
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);
	_delay_us(200);
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(data<<4);//send low nibble
	setbit(LCD_control_PORT,EN);
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);
	_delay_ms(1);
	
}
void LCD_send_command_4bit(unsigned char cmd)
{
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(cmd & 0xf0);//send high nibble
	clearbit(LCD_control_PORT,RS);
	clearbit(LCD_control_PORT,RW);
	setbit(LCD_control_PORT,EN);
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);
	_delay_us(200);
	LCD_DATA_PORT = (LCD_DATA_PORT &0x0f) |(cmd<<4);//send low nibble
	setbit(LCD_control_PORT,EN);
	_delay_us(1);
	clearbit(LCD_control_PORT,EN);
	_delay_ms(1);
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

*/