

/*
unsigned char segment (char NO )
{
	switch(NO)
	{
		case 0:
		return 0b00111111;
		break;
		case 1:
		return 0b00000110;
		break;
		case 2:
		return 0b01011011;
		break;
		case 3:
		return 0b01001111;
		break;
		
	}
}*/




#define F_CPU 1000000ul

#include <avr/io.h>
#include<util/delay.h>
void segment (char no);
int main(void)
{
	DDRC = 255; // port c output segment  0b11111111 0xff
    int x=1;
	while (1) 
    {  
		segment(x++);
		_delay_ms(1000);
		if(x == 4)
		x=1;
    }
}



void segment (char no){
	if(no == 1)
	PORTC =(1<<PC1)|(1<<PC2);
	else if(no == 2 )
	PORTC=(1<<PC0)|(1<<PC1)|(1<<PC6)|(1<<PC4)|(1<<PC3);
	else if(no == 3 )
	PORTC=(1<<PC0)|(1<<PC1)|(1<<PC6)|(1<<PC2)|(1<<PC3);
}




// task no 1 implement all the numbers and the characters 


