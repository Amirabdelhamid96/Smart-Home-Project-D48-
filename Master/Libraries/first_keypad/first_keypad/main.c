
#define F_CPU 1000000ul
#include <avr/io.h>
#include<util/delay.h>

#define setbit(reg,bit)     reg|=(1<<bit)
#define clearbit(reg,bit)   reg&=(~(1<<bit))
#define toggelbit(reg,bit)  reg ^=(1<<bit)
#define readbit(reg,bit)    ((reg&(1<<bit))>>bit)

int keypad(void);

int main(void)
{
	DDRC = 0b11111111; //output
   
    while (1) 
    {
		PORTC = 1<<PC0;
		
	}
}






		
		//  Data direction register DDR A B C D
		// DDRA Control data direction in out
		// DDRA = 0b11111111; output
		// PORT output data
		// PORTA = 0b11111111; PORTA = 0b00000001;
		// DDRA = 0b000000000 input
		// PINA == 0b00000001; --> input no input
		//  PORT
		//  PIN
		// DDRA = 0b00001111;

		
		
		
		
		
		
		/*
		
		int z;
		z = keypad();
		
		if (z == 7)
		{
			PORTA = 255;
		}
		else if(z == 3)
		{
			PORTB = 255;
		}
		else {
			PORTB = 0;
			PORTA = 0;
		}
		*/
		
		
		
		/*PORTC = (1<<0); // 7 8 9 /  
			if(readbit(PIND,0))
				{
					setbit(PORTB,0);
				}
			else if(readbit(PIND,1))
				{
					setbit(PORTB,1);
				}
			else if(readbit(PIND,2))
				{
					setbit(PORTB,2);
				}
			else if(readbit(PIND,3))
				{
					setbit(PORTB,3);
				}
			else
				{
					PORTB=0;
				}
				
			if(readbit(PIND,0))
				{
					setbit(PORTA,0);
				}
			else
				{
					PORTA=0;
				}
		
		_delay_ms(10);
		PORTC = (1<<1);  
		if(readbit(PIND,0))
			{
				setbit(PORTB,0);
			}
		else if(readbit(PIND,1))
			{
				setbit(PORTB,1);
			}
		else if(readbit(PIND,2))
			{
				setbit(PORTB,2);
			}
		else if(readbit(PIND,3))
			{
				setbit(PORTB,3);
			}
		else
			{
				PORTB=0;
			}
		
		_delay_ms(10);
		
		
		
		
		
		PORTC = (1<<2);
		if(readbit(PIND,0))
		{
			setbit(PORTB,0);
		}
		else if(readbit(PIND,1))
		{
			setbit(PORTB,1);
		}
		else if(readbit(PIND,2))
		{
			setbit(PORTB,2);
		}
		else if(readbit(PIND,3))
		{
			setbit(PORTB,3);
		}
		else
		{
			PORTB=0;
		}
		_delay_ms(10);
		PORTC = (1<<3);
		if(readbit(PIND,0))
		{
			setbit(PORTB,0);
		}
		else if(readbit(PIND,1))
		{
			setbit(PORTB,1);
		}
		else if(readbit(PIND,2))
		{
			setbit(PORTB,2);
		}
		else if(readbit(PIND,3))
		{
			setbit(PORTB,3);
		}
		else
		{
			PORTB=0;
		}   
		_delay_ms(10);
		
			
		
		
		
    }
}*/


	int keypad(void)
	{	int y=0;
		
			PORTC = (1<<0);  //PC0 ( 7 8 9)
			if(readbit(PIND,0))
			y = 7;
			if(readbit(PIND,1))
			y = 8;
			if(readbit(PIND,2))
			y = 9;
			_delay_ms(1);
			PORTC = (1<<1);   //PC1 ( 4 5 6)
			if(readbit(PIND,0))
			y = 4;
			if(readbit(PIND,1))
			y = 5;
			if(readbit(PIND,2))
			y = 6; 
			_delay_ms(1);
			PORTC = (1<<2);   //PC1 ( 1 2 3)
			if(readbit(PIND,0))
			y = 1;
			if(readbit(PIND,1))
			y = 2;
			if(readbit(PIND,2))
			y = 3;
			_delay_ms(1);
		
		return y;
	}


