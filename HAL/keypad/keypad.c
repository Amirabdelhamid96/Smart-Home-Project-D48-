 
 
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
	 setbit(R1_dir,R1);    //DDRA
	 setbit(R2_dir,R2);
	 setbit(R3_dir,R3);
	 setbit(R4_dir,R4);
	 /////////////////// input pins /////////////////////////////////////
	 clearbit(C1_dir,C1);
	 clearbit(C2_dir,C2);
	 clearbit(C3_dir,C3);
	 clearbit(C4_dir,C4);
	 ///////////////// internal pull up resistor for input pins /////////////////////////////
	 //input power
	 
	 setbit(C1_Port,C1); // porta = 0000100  -- > pull up  input & port output
	 setbit(C2_Port,C2);
	 setbit(C3_Port,C3);
	 setbit(C4_Port,C4);// noise
 }





 void switch_output(int x)
 {
	 //power loop function for rows
	 
	 switch(x)
	 {   // output r0 r1 r2 r3  high to low
		 case R1:
		 clearbit(R1_Port,R1);  //r0 low
		 setbit(R2_Port,R2);
		 setbit(R3_Port,R3);
		 setbit(R4_Port,R4);
		 break;
		 case R2:
		 clearbit(R2_Port,R2); // r1 low
		 setbit(R1_Port,R1);
		 setbit(R3_Port,R3);
		 setbit(R4_Port,R4);
		 break;
		 case R3:
		 clearbit(R3_Port,R3); // r2 low
		 setbit(R1_Port,R1);
		 setbit(R2_Port,R2);
		 setbit(R4_Port,R4);
		 break;
		 case R4:
		 clearbit(R4_Port,R4); //r3 low
		 setbit(R1_Port,R1);
		 setbit(R2_Port,R2);
		 setbit(R3_Port,R3);
		 break;
		 default:
		 break;
	 }
 }






 char get_key_value(void)
 {
	 char key = notpressed; // 255 
	 int i=0;
	 while(key == notpressed && i<3)// key = '1' break condition
	 {
		 i++;
		 switch_output(R1);
		 if (readbit(C1_Pin,C1)==0)// pull up power--> low
		 {
			 key ='1';// char
			 while(readbit(C1_Pin,C1)==0);// skip loop infinte
			 // there is no pressing anymore
		 }
		 else if (readbit(C2_Pin,C2)==0)
		 {
			 key ='2';
			 while(readbit(C2_Pin,C2)==0);
		 }
		 else if (readbit(C3_Pin,C3)==0)
		 {
			 key ='3';
			 while(readbit(C3_Pin,C3)==0);
		 }
		 else if (readbit(C4_Pin,C4)==0)
		 {
			 key ='/';
			 while(readbit(C4_Pin,C4)==0);
		 }
		 switch_output(R2);
		 if (readbit(C1_Pin,C1)==0)
		 {
			 key ='4';
			 while(readbit(C1_Pin,C1)==0);
		 }
		 else if (readbit(C2_Pin,C2)==0)
		 {
			 key ='5';
			 while(readbit(C2_Pin,C2)==0);
		 }
		 else if (readbit(C3_Pin,C3)==0)
		 {
			 key ='6';
			 while(readbit(C3_Pin,C3)==0);
		 }
		 else if (readbit(C4_Pin,C4)==0)
		 {
			 key ='*';
			 while(readbit(C4_Pin,C4)==0);
		 }
		 switch_output(R3);
		 if (readbit(C1_Pin,C1)==0)
		 {
			 key ='7';
			 while(readbit(C1_Pin,C1)==0);
		 }
		 else if (readbit(C2_Pin,C2)==0)
		 {
			 key ='8';
			 while(readbit(C2_Pin,C2)==0);
		 }
		 else if (readbit(C3_Pin,C3)==0)
		 {
			 key ='9';
			 while(readbit(C3_Pin,C3)==0);
		 }
		 else if (readbit(C4_Pin,C4)==0)
		 {
			 key ='-';
			 while(readbit(C4_Pin,C4)==0);
		 }
		 switch_output(R4);
		 if (readbit(C1_Pin,C1)==0)
		 {
			 key ='C';
			 while(readbit(C1_Pin,C1)==0);
		 }
		 else if (readbit(C2_Pin,C2)==0)
		 {
			 key ='0';
			 while(readbit(C2_Pin,C2)==0);
		 }
		 else if (readbit(C3_Pin,C3)==0)
		 {
			 key ='=';
			 while(readbit(C3_Pin,C3)==0);
		 }
		 else if (readbit(C4_Pin,C4)==0)
		 {
			 key ='+';
			 while(readbit(C4_Pin,C4)==0);
		 }
	 }
	 return key;
	 
 }