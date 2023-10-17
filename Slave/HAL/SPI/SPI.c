
#include <avr/io.h>
#include <util/delay.h>

#define setbit(reg,bit) reg|=(1<<bit)
#define clearbit(reg,bit) reg&=~(1<<bit)
#define toggelbit(reg,bit) reg^=(1<<bit)
#define readbit(reg,bit) ((reg>>bit)&1)

#define MOSI 5 //master out
#define SCK 7 //clock
#define SS  4 //sel
#define MISO 6 //master in
//1-init
//2-function send
//3-function recive
void SPI_Init()					/* SPI Initialize function */
{
	clearbit(DDRB,MOSI);
	clearbit(DDRB,SCK);
	clearbit(DDRB,SS);
	setbit(DDRB,MISO);
	
	clearbit(PINB,SS);
	
	setbit(SPCR,SPE);
	clearbit(SPCR,MSTR);
	setbit(SPCR,SPR0);
	
	setbit(PINB,SS);
	/*
	DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	//Make MOSI, SCK, SS as Output pin
	DDRB &= ~(1<<MISO);			// Make MISO pin as input pin
	PORTB |= (1<<SS);			// Make high on SS pin
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);	// Enable SPI in master mode with Fosc/16
	SPSR &= ~(1<<SPI2X);			// Disable speed doubler
	PORTB &=~(1<<SS);  //Deselect
	*/

}


void SPI_Write(char data)		/* SPI write data function */
{
	
	SPDR = data;			/* Write data to SPI data register */
	while(!(SPSR & (1<<SPIF)));	/* Wait till transmission complete */
	
	
}


char SPI_Read()				/* SPI read data function */
{
	SPDR = 0xFF;
	while(!(SPSR & (1<<SPIF)));	/* Wait till reception complete */
	return(SPDR);			/* Return received data */
}

void Int_SPI(int ab)
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
	int k=4;
	for(i=3; i>=0; i--)
	{
		if(array[i]!=0 || i==0)
		{k=i;i=0;}

	}
	
	for(i=k; i>=0; i--)
	{
		SPI_Write(array[i]);
		_delay_ms(100);
		// '0' --> 48
		// array[3]---->array[0]
		// 0 0 1 0
		// sending no : 48 ====> '0'
		// 0 1 2 3 ---> 9
		// 48 49 50 ---> end
	}
}

/*
int main(void)
{
	SPI_Init();

	PORTB &=~(1<<SS);
	while (1)
	{
		SPI_Write('A');//char 0 ascii
		_delay_ms(2000);
		//2 --> 0x02
		SPI_Write('B');//char 0 ascii
		_delay_ms(2000);
		SPI_Write('C');//char 0 ascii
		_delay_ms(2000);
	}
}*/

