
#define F_CPU 1000000ul
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>  //std headers
#include "keypad.h"  // home made headers
                     //  

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
	clearbit(LCD_control_PORT,RW);  // rw = 0  write
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
	
	
	
	
	//   0 1 2 3 4 5                   15   col
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



int main()
{
		
	LCD_INIT_4bit(); // init lcd 
    keypad_init(); // define key pad   //1// 
	
	//LCD_send_string_4bit("hallo");
	//_delay_ms(2000);
	
	while(1)
	{
		//keypad 
/*2-*/	unsigned char k=get_key_value();
		////////////////////////////
		
		LCD_send_data_4bit(k);
	
	}
	
	
	
	
	
	//LCD_send_command_4bit(0X01); //clear
	
	
		
	//ASCII  num 1 ==> nothing
	//ASCII  char '1' ==> 49
	
	//LCD_send_data('C');
		
//	_delay_ms(1000);
//	LCD_send_command(0X01);
	//LCD_send_string("hallo");
}


