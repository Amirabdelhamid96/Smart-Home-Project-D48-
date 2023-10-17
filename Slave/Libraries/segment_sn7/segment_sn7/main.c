/*
 * segment_sn7.c
 *
 * Author : Mohamed
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

#define LED_Directions DDRD
#define LED_Direction DDRC
#define LED_PORT1 PORTD
#define LED_PORT2 PORTC

char array[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
int k, j, i;

void set_brightness(int brightness)
{
	while (0 < brightness)
	{
		_delay_us(1);
		--brightness;
	}
}

void SevenSeg_SetNumber(int num)
{
	k = num % 10;
	num = num / 10;

	j = num % 10;
	num = num / 10;

	i = num % 10;
}

void sevseg_refreshDisplay(char refvalue)
{
	LED_PORT2 = 0x01;
	LED_PORT1 = array[k];
	set_brightness(refvalue);

	LED_PORT2 = 0x02;
	LED_PORT1 = array[j];
	set_brightness(refvalue);

	LED_PORT2 = 0x04;
	LED_PORT1 = array[i];
	set_brightness(refvalue);
}

int main(void)
{
	LED_Directions = 0xFF;
	LED_Direction = 0xFF;
	LED_PORT1 = 0xFF;
	LED_PORT2 = 0xFF;

	int brightvalue = 1000;

	while (1)
	{
		SevenSeg_SetNumber(456);
		sevseg_refreshDisplay(brightvalue);
		_delay_ms(1000);

		SevenSeg_SetNumber(789);
		sevseg_refreshDisplay(brightvalue);
		_delay_ms(1000);
	}
	return 0;
}
