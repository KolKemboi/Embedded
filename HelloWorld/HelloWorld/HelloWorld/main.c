/*
 * HelloWorld.c
 *
 * Created: 7/7/2024 9:30:19 AM
 * Author : kolke
 */ 
#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	DDRB = 0xFF;
    while (1) 
    {
		PORTB = 0xFF;
		_delay_ms(1000);
		PORTB = 0x00;
		_delay_ms(1000);
    }
}

