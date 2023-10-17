

#include <avr/io.h>
#define p0 0
#define p1 1
#define p2 2
#define p3 3
#define p4 4
#define p5 5
#define p6 6
#define p7 7

int main(void)
{
	DDRC  = (1<<p2) | (1<<p7);     // 2 7 out
	PORTC = (1<<p2) | (1<<p7);    // 2 7 high
	while (1){}
}
