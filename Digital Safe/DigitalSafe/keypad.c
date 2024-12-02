#include "keypad.h"
#include <util/delay.h>

const char keypad_map[4][4] = {
	{'7', '8', '9', '/'},
	{'4', '5', '6', 'x'},
	{'1', '2', '3', '-'},
	{'C', '0', '=', '+'}
};

void keypad_init(void) {
	KEYPAD_DDR = 0xF0;   // Upper nibble as output, lower nibble as input
	KEYPAD_PORT = 0xFF;  // Enable pull-up resistors on lower nibble
}

char keypad_get_key(void) {
	for (uint8_t row = 0; row < 4; row++) {
		KEYPAD_PORT = ~(1 << (row + 4));  // Set one row low at a time

		_delay_us(10);  // Small delay for stabilization
		for (uint8_t col = 0; col < 4; col++) {
			if (!(KEYPAD_PIN & (1 << col))) {
				_delay_ms(50);  // Debounce delay
				while (!(KEYPAD_PIN & (1 << col)));  // Wait for key release
				return keypad_map[row][col];
			}
		}
	}
	return '\0';  // No key pressed
}
