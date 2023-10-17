
#define F_CPU 16000000ul
#include <avr/io.h>
#include <util/delay.h>


void UART_INIT(unsigned int baud);
void UART_sendchar(unsigned char data);
unsigned char UART_receivechar();
void UART_sendString(char *str);

void LCD_send_data_4bit(unsigned char data);
void LCD_send_command_4bit(unsigned char cmd);
void LCD_INIT_4bit(void);
void LCD_send_string_4bit( char* str);

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)





int main(void)
{
    UART_INIT(103);
    unsigned char x;
    DDRA = 255;
    while (1)
    {		
			x=UART_receivechar();
			UART_sendchar(x);
				if(x=='A')
					{
						PORTA =255; 
					}
				
				else
					{
						PORTA =0;
					}
				 
    }
}



void UART_INIT(unsigned int baud)
{
	UCSRB |= (1 << RXEN) | (1 << TXEN);				// Enable UART transmitter and receiver
	UCSRC |= (1 << URSEL)| (1 << UCSZ0) | (1 << UCSZ1);	//8 bit data and 1 stop bit
	UBRRL = baud;
	UBRRH = (baud >> 8);
}
void UART_sendchar(unsigned char data)
{
	while(readbit(UCSRA,UDRE)==0)// wait the reg to be empty
	{	;	}
	UDR = data; // send  data
	while(readbit(UCSRA,TXC)==0)// wait till the data to be send
	{	;	}
}
unsigned char UART_receivechar()
{
	while ((UCSRA & (1 << RXC)) == 0);/* Wait till data is received */
	return(UDR);			/* Return the byte*/
}
void UART_sendString(char *str)
{
	int count =0 ;
	while (str[count]  != 0)
	{
		UART_sendchar(str[count]);
		count ++;
	}
}
