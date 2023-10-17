

//delay function
//ms delay function
//us delay function

//     second delay function












#include <avr/io.h>
#include <avr/interrupt.h>
#define LED PD6





void wait_ms(int ms)// ==> _delay_ms
{
	///////////initialization zone ///////
	TCNT0=0;
	TCCR0 |=  (1<<CS00);
	//prescale 1 no prescaler

	float i ;
	//int counts = ms *3.9 ;  //4 --> 1ms
	
	float counts = ms *3.9 ;
	
	//1 * 3.9 =3.9 
	//2 * 3.9 =7.8
	
	
	// time / (res * (pre / clk))
	// .001 / (256 * (1 / 1000000)
	// 
	
	
	for(i=0;i<counts;i++)
	{
		while ((TIFR&(1<<TOV0))==0)
		{		}// check over or not
		TIFR =  0x01; // clear flag
	}
}


void delay_sec(int sec)
{
	///////////initialization zone ///////
	TCNT0=0;
	TCCR0 |=  (1<<CS02);  //prescaler
	
	/////////////////////////////
	int i ;
	int counts = sec *15 ;  //15 --> 1 second
	for(i=0;i<counts;i++)
	{
		while ((TIFR&(1<<TOV0))==0)
		{		}// check over or not
			
		TIFR =  0x01; // clear flag
	}
}



int main()
{
	DDRD=0xff;				//configure PORTD as output
	while(1)
		{
			//delay_sec(3);	
			//delay function(seconds)
			int i;
			for(i=0;i<200;i++)
			wait_ms(5);// 1000 ms = 1 second
			
			PORTD ^= (1 << LED);
		}
}



//3.9  15.2   14.3 

/*15 = 16          
.2
(1-fraction ) * 256
1-.2 =.8
.8*256 = 204

register = 204  
fraction from 16 mesh 16 15 and (204 ==>.2)
 
*/

////////////////////////////////////////////
// delay ms
// count ==> .001 
// count ==> 1    pre 256 clock 1,000,000 
// time /( res * (pre/clk) )


// pre =256,, clk= 1,000,000,, res =256,, time 0.001
// count =  

/*0.001/.065535 =0.0152     0 one ms
0.001/(256 * 64/1000000) = 0.061
1/0.0655535 = 15.2    == 15 one second
.001/(256 *8/1000000)= 0.5
.001/(256 *1/1000000)=3.9 ~= 4


8 64 256 1024 1*/



