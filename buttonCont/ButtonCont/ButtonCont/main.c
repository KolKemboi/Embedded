/*
 * main.c
 *
 * Created: 8/17/2024 9:39:04 PM
 *  Author: kolke
 */ 
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define __DELAY_BACKWARD_COMPATIBILE__


int main(void)
{
	DDRB = DDRB | (1<<PB3);
	DDRB = DDRB & (~(1<<PB2));
	PORTB = PORTB | (1<<PB2);
	
	int input_status;
    while(1)
    {
		input_status = ~PINB & (1<<PB2);
		if (input_status)
		{
			PORTB = PORTB | (1<<PB3);
		}
		else
		{
			PORTB = PORTB & (~(1<<PB3));
		}
    }
	return 0;
}