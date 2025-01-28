#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

//avr-gcc -mmcu=atmega328p -Os -o main.elf main.c
//avr-objcopy -O ihex -R .eeprom main.elf main.hex 

int main(void)
{
	DDRB = DDRB | (1 << PB3);
	DDRB = DDRB & (~(1 << PB2));
	PORTB = PORTB | (1 << PB2);
	int pin_status;
	while(1)
	{
		pin_status = ~PINB & (1<<PB2);
		if(pin_status)
		{
			PORTB = PORTB | (1 << PB3);
		}
		else
		{
			PORTB = PORTB & (~(1 << PB3));
		}
	}
	return 0;
}