#ifndef KEYPAD_H
#define KEYPAD_H

#include <avr/io.h>
#include <util/delay.h>

#define KEYPAD_PORT PORTD
#define KEYPAD_PIN PIND
#define KEYPAD_DDR DDRD

void keypad_init();
char keypad_getkey();

#endif
