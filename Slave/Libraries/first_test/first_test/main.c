
#include <avr/io.h>
// avr header avr families 


#define pin1 1
#define pin7 7
#define pin6 6

int main(void)
{
	//compilation process
    //registers output input 
	// output 
	//  4 PORTs 
	// PORT A B C D   Atmega32 ==> 40 pins --> 8 pins <--> 32 pins 
	// PORT --> 8 pins  PORT size ==> 8 bits --> register 8 bits
	// hardware software 
	// pin <--> bit 
	// 0-5V <--> 0-1 binary 
	// output
	// 1- config
	// 2- actual data 
	// DDR  == > register (Data Direction Reg) 
	// DDRA DDRB DDRC DDRD 
	// config port A output 
	// 8 pins output 
	//DDRA = 255;// 0b1111 1111  output portA
	//DDRA = 0; //  0b0000 0000  input  portA  
	//DDRA = 1;			0b0000 0001 = 1
	//PORTA = 1;
	
	
	//PA7 --> PA0
	//          PA7 PA6
	//   pin no  7   6 5 4 3 2 1 0
	//1<<7 == 0b 1   0 0 0 0 0 0 0
	//1<<6 == 0b 0   1 0 0 0 0 0 0
	// or  == 0b 1   1 0 0 0 0 0 0
	//          PA7 PA6
	
  //DDRA = (1<<7)|(1<<6) ; // PA7 pin output reg 
  //PORTA= (1<<7)|(1<<6) ; // PA7 pin high   reg
	DDRA = (1<<pin1)|(1<<pin7) ; // PA7 pin output reg
	PORTA= (1<<pin1)|(1<<pin7) ; // PA7 pin high   reg
	
    while (1) // super loop for MCUs 
    {
    }
}

