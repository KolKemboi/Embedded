
#include <avr/io.h>
#include <util/delay.h>
#include "lcd.h"
#include "keypad.h"

#define LCD_DISP_ON 0x0C   // Display ON, Cursor OFF
#define LCD_DISP_ON_CURSOR 0x0E // Display ON, Cursor ON
#define LCD_DISP_ON_CURSOR_BLINK 0x0F

// Define the correct password
char correctPassword[4] = {'1', '2', '3', '4'};

// Function to control the motor
void unlockSafe() {
	// Set PB1 (OC1A) as output
	DDRB |= (1 << PB1);

	// Configure Timer1 for PWM
	TCCR1A |= (1 << COM1A1) | (1 << WGM11);
	TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Prescaler 8

	ICR1 = 19999; // Top value for 50 Hz (8 MHz / (8 * 50 Hz) - 1)

	OCR1A = 1500; // Duty cycle for "unlock" position
	_delay_ms(3000);

	OCR1A = 1000; // Duty cycle for "lock" position
	_delay_ms(500);
}

// Function to compare passwords
uint8_t comparePasswords(char *input) {
	for (uint8_t i = 0; i < 4; i++) {
		if (input[i] != correctPassword[i]) {
			return 0; // Passwords do not match
		}
	}
	return 1; // Passwords match
}

int main() {
	char enteredPassword[4];
	uint8_t index = 0;
	char key;

	// Initialize LCD and Keypad
	lcd_init(LCD_DISP_ON);
	keypad_init();

	// Display initial message
	lcd_clrscr();
	lcd_puts("Enter Password:");

	while (1) {
		// Wait for a key press
		key = keypad_getkey();

		if (key != '\0') {
			// Display the key as '*'
			lcd_gotoxy(index, 1);
			lcd_putc('*');
			enteredPassword[index] = key;  // Store the entered key
			index++;  // Move to the next position for entering password

			// Check if 4 digits have been entered
			if (index == 4) {
				index = 0;  // Reset index for the next input

				// Compare the entered password
				if (comparePasswords(enteredPassword)) {
					lcd_clrscr();
					lcd_puts("Access Granted");
					unlockSafe(); // Unlock the safe by moving the motor
					_delay_ms(2000); // Delay to keep "Access Granted" on screen for a while
					} else {
					lcd_clrscr();
					lcd_puts("Wrong Password");
					_delay_ms(2000); // Delay to show "Wrong Password"
				}

				// Reset the display after showing the result
				lcd_clrscr();
				lcd_puts("Enter Password:");
			}
		}
	}
	return 0;
}
