#ifndef KEYPAD_H
#define KEYPAD_H

#ifndef F_CPU
#define F_CPU 8000000UL  // Define the CPU frequency (8 MHz in this case)
#endif
#include <avr/io.h>
#include <util/delay.h>

// Define keypad port and pins
#define KEYPAD_PORT PORTB
#define KEYPAD_DDR DDRB
#define KEYPAD_PIN PINB

void keypad_init(void);
char keypad_get_key(void);

#endif
