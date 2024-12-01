#include "keypad.h"

const char keys[4][4] = {
	{'1', '2', '3', 'A'},
	{'4', '5', '6', 'B'},
	{'7', '8', '9', 'C'},
	{'*', '0', '#', 'D'}
};

void keypad_init() {
	KEYPAD_DDR = 0xF0; // Upper nibble output, lower nibble input
	KEYPAD_PORT = 0xFF; // Enable pull-ups
}

char keypad_getkey() {
	for (uint8_t row = 0; row < 4; row++) {
		KEYPAD_PORT = ~(1 << (row + 4)); // Set one row low
		_delay_us(1); // Small delay

		for (uint8_t col = 0; col < 4; col++) {
			if (!(KEYPAD_PIN & (1 << col))) {
				return keys[row][col]; // Return pressed key
			}
		}
	}
	return '\0'; // No key pressed
}
