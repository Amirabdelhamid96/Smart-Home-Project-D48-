
//keypad.h hamada.h

#ifndef KEYPAD_H_   // multi calling for header
#define KEYPAD_H_



//  header file .h not .c 
//  compiler header +++ c file 
//  c-file compilation process --> assembly --> machine lang
/*
//  #include<stdio.h>
//  

	int main()
		{
			prtf("sdfghjk");
		}
 

  */
//linker --> header stdio.h printf --> main.c --> complete compilation


/*

functions --> function body 
		  --> prototype    ==> header function 
		  proto in header file  keypad.h
		  function body c file  keypad.c
		  
		  #define x 0
		  #define s 0
		  #define a 0
		  #define z 0
header file 		  


keypad.h

keypad.c  --> calling header keypad.h

main.c

compiler main function 95% right




*/



//macro

//Rows Output
#define R1_dir DDRD
#define R2_dir DDRD
#define R3_dir DDRC
#define R4_dir DDRC
#define R1_Port PORTD
#define R2_Port PORTD
#define R3_Port PORTC
#define R4_Port PORTC
#define R1 4
#define R2 5
#define R3 0
#define R4 1

//Columns Input
#define C1_dir DDRC
#define C2_dir DDRC
#define C3_dir DDRC
#define C4_dir DDRC
#define C1_Pin PINC
#define C2_Pin PINC
#define C3_Pin PINC
#define C4_Pin PINC
#define C1_Port PORTC
#define C2_Port PORTC
#define C3_Port PORTC
#define C4_Port PORTC
#define C1 3
#define C2 4
#define C3 5
#define C4 6

void keypad_init(void);  // proto 
char get_key_value(void);


#define  notpressed 0xff // 255   0b11111111










#endif /* KEYPAD_H_ */