
#include <avr/io.h>
#define  F_CPU 8000000UL
#include <util/delay.h>
#include <stdio.h>

void lcd_init();			//----LCD Initializing Function
void toggle();				//----Latching function of LCD
void lcd_send_cmd (char cmd);		//----Function to send Command to LCD
void lcd_send_hf_cmd(char cmd);      //----Function to send half Command to LCD
void lcd_send_data (char data);		//----Function to send data to LCD
void lcd_clear (void);			//----Function to clear LCD
void lcd_put_cur(int row, int col);		//----Function to change Cursor of Lcd
void lcd_send_string(char *str);		//----Function to Send String to LCD
void i2c_init();
void i2c_start();
void i2c_write(char x);
char i2c_read();

// Declare i2c addrees
#define LCD_1   0x76
#define LCD_2   0x72
#define LCD_3   0x7A

// Declare your global variables here
int count1, count2, count3;
char data[16];

//Declare Display 
void Display();

int main(void)
{

	// Bit-Banged I2C Bus initialization
	// I2C Port: PORTC
	// I2C SDA bit: 1
	// I2C SCL bit: 0
	// Bit Rate: 100 kHz.
	
	i2c_init();
	i2c_start();
	
	i2c_write(LCD_1);
	lcd_init();
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("LCD_1 init :)");
	_delay_ms(1000);
	lcd_clear();
	
	i2c_write(LCD_2);
	i2c_start();
	lcd_init();
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("LCD_2 init :)");
	_delay_ms(1000);
	lcd_clear();
	
	i2c_write(LCD_3);
	i2c_start();
	lcd_init();
	lcd_clear();
	lcd_put_cur(0, 0);
	lcd_send_string("LCD_3 init :)");
	_delay_ms(1000);
	lcd_clear();

	while (1)
	{
		count1++;
		if (count1%2==0)
		{
			count2++;
			if(count2%2 == 0) count3++;
		}
		Display();
		_delay_ms(1000);
		
	}
}








void toggle ()
{
	TWDR |= 0x02;					//---PIN En de la LCD en = 1;  -----Latching data in to LCD data register using High to Low signal
	TWCR = (1<<TWINT) | (1<<TWEN);	//---Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));	
	_delay_ms(1);
	TWDR &= ~0x02;					//---PIN del Enable de la LCD en = 0;
	TWCR = (1<<TWINT) | (1<<TWEN);	//---Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
}

void lcd_send_cmd (char cmd)
{
	TWDR&=~0x01;                    //rs = 0; ----Selecting register as command register
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;                   //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (cmd & 0xF0);            //----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
	TWDR &= 0x0F;                    //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= ((cmd & 0x0F)<<4);        //----Masking lower 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcd_send_hf_cmd(char cmd)
{
	TWDR &=~0x01;					//PIN RS de la LCD rs = 0; ----Selecting register as Command register
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;					//----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (cmd & 0xF0);			//----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}


void lcd_send_data (char data)
{
	TWDR|=0x01;                        //rs = 1; ----Selecting register as command register
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR &= 0x0F;                    //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= (data & 0xF0);            //----Masking higher 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
	
	TWDR &= 0x0F;                    //----clearing the Higher 4 bits
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	TWDR |= ((data & 0x0F)<<4);        //----Masking lower 4 bits and sending to LCD
	TWCR = (1<<TWINT) | (1<<TWEN);    //Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
	toggle();
}

void lcd_init ()
{
	lcd_send_hf_cmd(0x30);       //-----Sequence for initializing LCD
	lcd_send_hf_cmd(0x30);       //-----     "            "              "               "
	lcd_send_hf_cmd(0x20);       //-----     "            "              "               "
	lcd_send_cmd(0x28);          //-----Selecting 16 x 2 LCD in 4Bit mode
	lcd_send_cmd(0x0C);          //-----Display ON Cursor OFF
	lcd_send_cmd(0x01);          //-----Clear display
	lcd_send_cmd(0x06);          //-----Cursor Auto Increment
	lcd_send_cmd(0x80);          //-----1st line 1st location of LCD
}


void lcd_send_string (char *str)
{
	while (*str) lcd_send_data (*str++);
}

void lcd_put_cur(int row, int col)
{
	switch (row)
	{
		case 0:
		col |= 0x80;
		break;
		case 1:
		col |= 0xC0;
		break;
	}

	lcd_send_cmd (col);
}

void lcd_clear (void)
{
	int i;
	lcd_send_cmd (0x80);
	for (i=0; i<70; i++)
	{
		lcd_send_data (' ');
	}
}

void i2c_init(){
	TWBR = 0x62;		//	Baud rate is set by calculating
	TWCR = (1<<TWEN);	//Enable I2C
	TWSR = 0x00;		//Prescaler set to 1

}
//Start condition
void i2c_start(){
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTA);	//start condition
	while (!(TWCR & (1<<TWINT)));				//check for start condition

}
//I2C stop condition
void i2c_write(char x){				
	TWDR = x;						//Move value to I2C
	TWCR = (1<<TWINT) | (1<<TWEN);	//Enable I2C and clear interrupt
	while  (!(TWCR &(1<<TWINT)));
}

char i2c_read(){
	TWCR  = (1<<TWEN) | (1<<TWINT);	//Enable I2C and clear interrupt
	while (!(TWCR & (1<<TWINT)));	//Read successful with all data received in TWDR
	return TWDR;
}
void Display()
{
	//LCD1
	i2c_write(LCD_1);
	i2c_start();
	lcd_put_cur(0, 0);
	lcd_send_string("Lcd_1");
	lcd_put_cur(1, 0);
	lcd_send_string("Count = ");
	lcd_put_cur(1, 8);
	sprintf(data, "%d", count1);
	lcd_send_string(data);
	//LCD2
	i2c_write(LCD_2);
	i2c_start();
	lcd_put_cur(0, 0);
	lcd_send_string("Lcd_2");
	lcd_put_cur(1, 0);
	lcd_send_string("Count = ");
	lcd_put_cur(1, 8);
	sprintf(data, "%d", count2);
	lcd_send_string(data);
	//LCD3
	i2c_write(LCD_3);
	i2c_start();
	lcd_put_cur(0, 0);
	lcd_send_string("Lcd_3");
	lcd_put_cur(1, 0);
	lcd_send_string("Count = ");
	lcd_put_cur(1, 8);
	sprintf(data, "%d", count3);
	lcd_send_string(data);
}
