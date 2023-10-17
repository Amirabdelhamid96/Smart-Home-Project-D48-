
#define F_CPU 1000000ul
#define SCL_CLK 10000
#include <avr/io.h>
#include <math.h>      //power
#include <util/delay.h>
//scl line clock     mcu clock
//SCL frequency =  (CPU CLK frequency)/(16+2(TWBR)*4^TWPS )

//cpuf/sf =16+2(TWBR)*4^TWPS

//cpuf/sf-16 =2(TWBR)*4^TWPS
//((cpuf/sf)-16)/2*(4^TWPS) = TWBR
/* Define bit rate */
/*1-init    func 
2-start   func
3-write   func*/
// twsr = twps0 twps1  ==> 11
#define BITRATE(TWSR)	((F_CPU/SCL_CLK)-16)/(2*pow(4,(TWSR&((1<<TWPS0)|(1<<TWPS1)))))
void I2C_Init()			
{   // clock configuration 
	TWBR = BITRATE(TWSR=0x00);	// Get bit rate register value by formula 
}//TWSR  ==> TWPS0 prescale

char I2C_Start(char address)  // input address 
{
	char status;		
	TWCR=(1<<TWSTA)|(1<<TWEN)|(1<<TWINT);	/* Enable TWI, generate START					*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	//TWSR & 0b1111 1000 =
	//reg = 10101 000 & 11111 000
	// status = 10101
	status=TWSR&0xF8;						/* Read TWI status register						*/
	if(status!=0x08)						/* Check weather START transmitted or not?		*/
	return 0;								/* Return 0 to indicate start condition fail	*/
	TWDR= address;							/* Write SLA+W in TWI data register				*/
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI & clear interrupt flag			*/
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job		*/
	status=TWSR&0xF8;						/* Read TWI status register */
	if(status==0x18)	//ACK				/* Check for SLA+W transmitted &ack received	*/
	return 1;								/* Return 1 to indicate ack received			*/
	if(status==0x20)	//Not ACK			/* Check for SLA+W transmitted &nack received	*/
	return 2;								/* Return 2 to indicate nack received			*/
	else
	return 3;		// bus fault						/* Else return 3 to indicate SLA+W failed		*/
}

char I2C_Write(char data)					/* I2C write function */
{
	char status;							/* Declare variable */
	TWDR=data;								/* Copy data in TWI data register */
	TWCR=(1<<TWEN)|(1<<TWINT);				/* Enable TWI and clear interrupt flag */
	while(!(TWCR&(1<<TWINT)));				/* Wait until TWI finish its current job */
	status=TWSR&0xF8;						/* Read TWI status register */
	if(status==0x28)						/* Check for data transmitted &ack received */
	return 0;								/* Return 0 to indicate ack received */
	if(status==0x30)						/* Check for data transmitted &nack received */
	return 1;								/* Return 1 to indicate nack received */
	else
	return 2;	// data fault							/* Else return 2 for data transmission failure */
}

void I2C_Stop()								/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);	/* Enable TWI, generate stop */
	while(TWCR&(1<<TWSTO));					/* Wait until stop condition execution */
}
int main(void)
{
	I2C_Init();
    while (1) 
    {
		I2C_Start(0x20);   //address
		I2C_Write(0x05);   //data
		I2C_Stop();        //stop
		_delay_ms(3000);
    }
}

