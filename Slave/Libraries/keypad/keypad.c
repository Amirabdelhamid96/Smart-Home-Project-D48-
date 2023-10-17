 
 
 // keypad.c
 
#include <avr/io.h>  // DDRA PIN PORT

// macros
#define setbit(reg,bit) reg|=(1<<bit)		// set bit 1
#define clearbit(reg,bit) reg&=~(1<<bit)	// clear bit 0
#define toggelbit(reg,bit) reg^=(1<<bit)	// toggle
#define readbit(reg,bit) ((reg>>bit)&1)		// input read


#include "keypad.h"

void keypad_init(void)   // 1st step
{
	
	// 8 bits p0 --> p7
	// 8 pins  4 / 4  4 rows --> power loop --> output   4 columns --> inputs 
	// 4rows p0 p1 p2 p3    output power
	//columns p4 p5 p6 p7   input  reading pin
	
	
	///////////////////////  output pins //////////////////////////////
	setbit(keypad_out_dir,7);    //DDRA
	setbit(keypad_out_dir,4);
	setbit(keypad_out_dir,5);
	setbit(keypad_out_dir,6);
	/////////////////// input pins /////////////////////////////////////
	clearbit(keypad_in_dir,2);
	clearbit(keypad_in_dir,3);
	clearbit(keypad_in_dir,6);
	clearbit(DDRC,2);
	///////////////// internal pull up resistor for input pins /////////////////////////////
	//input power 
	
	clearbit(keypad_in_pin,2); // porta = 0000100  -- > pull up  input & port output
	clearbit(keypad_in_pin,3);
	clearbit(keypad_in_pin,6);
	clearbit(PINC,2);// noise 
}	





void switch_output(int x)
{ 
	//power loop function for rows 
		
	switch(x)
	{   // output r0 r1 r2 r3  high to low
		case 0:
		setbit(keypad_out_port,4);  //r0 low
		clearbit(keypad_out_port,5);
		clearbit(keypad_out_port,6);
		clearbit(keypad_out_port,7);
		break;
		case 1:
		setbit(keypad_out_port,5); // r1 low
		clearbit(keypad_out_port,4);
		clearbit(keypad_out_port,6);
		clearbit(keypad_out_port,7);
		break;
		case 2:
		setbit(keypad_out_port,6); // r2 low
		clearbit(keypad_out_port,4);
		clearbit(keypad_out_port,5);
		clearbit(keypad_out_port,7);
		break;
		case 3:
		setbit(keypad_out_port,7); //r3 low
		clearbit(keypad_out_port,4);
		clearbit(keypad_out_port,5);
		clearbit(keypad_out_port,6);
		break;
		default:
		break;
	}
}






char get_key_value(void)
{
	char key = notpressed; // 255 
	
	
	while(key == notpressed)// key = '1' break condition 
	{
		switch_output(0);
		if (readbit(keypad_in_pin,2)==1)// pull up power--> low 
		{
			key ='1';// char 
			while(readbit(keypad_in_pin,2)==1);// skip loop infinte 
			// there is no pressing anymore 
		}
		else if (readbit(keypad_in_pin,3)==1)
		{
			key ='4';
			while(readbit(keypad_in_pin,3)==1);
		}
		else if (readbit(keypad_in_pin,6)==1)
		{
			key ='7';
			while(readbit(keypad_in_pin,6)==1);
		}
		else if (readbit(PINC,2)==1)
		{
			key ='*';
			while(readbit(PINC,2)==1);
		}
		switch_output(1);
		if (readbit(keypad_in_pin,2)==1)
		{
			key ='2';
			while(readbit(keypad_in_pin,2)==1);
		}
		else if (readbit(keypad_in_pin,3)==1)
		{
			key ='5';
			while(readbit(keypad_in_pin,3)==1);
		}
		else if (readbit(keypad_in_pin,6)==1)
		{
			key ='8';
			while(readbit(keypad_in_pin,6)==1);
		}
		else if (readbit(PINC,2)==1)
		{
			key ='0';
			while(readbit(PINC,2)==1);
		}
		switch_output(2);
		if (readbit(keypad_in_pin,2)==1)
		{
			key ='3';
			while(readbit(keypad_in_pin,2)==1);
		}
		else if (readbit(keypad_in_pin,3)==1)
		{
			key ='6';
			while(readbit(keypad_in_pin,3)==1);
		}
		else if (readbit(keypad_in_pin,6)==1)
		{
			key ='9';
			while(readbit(keypad_in_pin,6)==1);
		}
		else if (readbit(PINC,2)==1)
		{
			key ='=';
			while(readbit(PINC,2)==1);
		}
		switch_output(3);
		if (readbit(keypad_in_pin,2)==1)
		{
			key ='/';
			while(readbit(keypad_in_pin,2)==1);
		}
		else if (readbit(keypad_in_pin,3)==1)
		{
			key ='+';
			while(readbit(keypad_in_pin,3)==1);
		}
		else if (readbit(keypad_in_pin,6)==1)
		{
			key ='-';
			while(readbit(keypad_in_pin,6)==1);
		}
		else if (readbit(PINC,2)==1)
		{
			key ='C';
			while(readbit(PINC,2)==1);
		}
	}
	return key;
	
}