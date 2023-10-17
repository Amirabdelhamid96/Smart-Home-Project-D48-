/*
0x30  PIND
0x31  DDRD
0x32  PORTD
0x33  PINC
0x34  DDRC
0x35  PORTC
0x36  PINB
0x37  DDRB
0x38  PORTB
0x39  PINA
0x3A  DDRA
0x3B  PORTA
*/
//memory mapping c language
//port mapping   assembly 

//unsigned char * x =0x3A ;  // DDRA
//*x = 1;                    // DDRA = 1 ;





/*#define DIOC *((unsigned char*)0x34)
#define OUTPUTC *((unsigned char*)0x35)
*/


#define F_CPU 1000000ul

#include<util/delay.h>
//delay functions

typedef unsigned char u8;

#define p0 0
#define p1 1
#define p2 2
#define p3 3

///////////portA/////////////
#define Dir_A  *((u8*)0x3A)
#define Data_A *((u8*)0x3B)

int main(void)
{
    Dir_A  =(1<<p0)|(1<<p2);
	while (1) 
    {	  
		Data_A ^=(1<<p0)|(1<<p2);
		_delay_ms(1000);
	  }
}



 //DIOC |=  1 ;  //DDRc = 1;// address to ==> int short 
  /* unsigned char * x =(unsigned char*)0x3A ;    // DDRA
   *x = (1<<0)|(1<<1);							// DDRA = 1 ;
   unsigned char * y =(unsigned char*)0x3B ;    // PORTA
   *y = (1<<0)|(1<<1);                          // PORTA = 1;   
   */

