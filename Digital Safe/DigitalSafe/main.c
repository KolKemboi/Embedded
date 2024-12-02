
#ifndef F_CPU
#define F_CPU 8000000UL  // Define the CPU frequency (8 MHz in this case)
#endif

#include <avr/io.h>
#include "lcd.h"
#include "keypad.h"
#include <string.h>  // For strcmp


#include <util/delay.h>

// Define LED and motor pins
#define BLUE_LED PD6
#define RED_LED PD7
#define MOTOR_EN PD3
#define MOTOR_CTRL1 PD2
#define MOTOR_CTRL2 PD1

// Password configuration
const char correct_password[] = "1234";
#define PASSWORD_LENGTH 4

void setup_peripherals(void) {
	// Configure LED and motor pins as output
	DDRD |= (1 << BLUE_LED) | (1 << RED_LED) | (1 << MOTOR_EN) | (1 << MOTOR_CTRL1) | (1 << MOTOR_CTRL2);

	// Initialize peripherals
	PORTD &= ~((1 << BLUE_LED) | (1 << RED_LED));  // Turn off LEDs
	PORTD &= ~((1 << MOTOR_EN) | (1 << MOTOR_CTRL1) | (1 << MOTOR_CTRL2));  // Stop motor
}

void motor_open(void) {
	PORTD |= (1 << MOTOR_EN);      // Enable motor
	PORTD |= (1 << MOTOR_CTRL1);   // Set motor direction
	PORTD &= ~(1 << MOTOR_CTRL2);  // Clear opposite direction
}

void motor_stop(void) {
	PORTD &= ~((1 << MOTOR_EN) | (1 << MOTOR_CTRL1) | (1 << MOTOR_CTRL2));
}

int main(void) {
	char entered_password[PASSWORD_LENGTH + 1];  // To store user input
	uint8_t index = 0;                           // Current index of password input

	// Initialize peripherals
	setup_peripherals();
	lcd_init();
	keypad_init();

	while (1) {
		lcd_clrscr();
		lcd_puts("Enter Password:");
		lcd_gotoxy(0, 1);  // Move cursor to the second row

		// Reset password input
		index = 0;

		// Get the password from the user
		while (index < PASSWORD_LENGTH) {
			char key = keypad_get_key();
			if (key != '\0') {  // A valid key was pressed
				entered_password[index++] = key;  // Store the key
				lcd_putc('*');                    // Show asterisk for privacy
			}
		}
		entered_password[index] = '\0';  // Null-terminate the string

		_delay_ms(500);
		lcd_clrscr();

		// Check if the entered password matches the correct one
		if (strcmp(entered_password, correct_password) == 0) {
			lcd_puts("Access Granted!");
			PORTD |= (1 << BLUE_LED);  // Turn on blue LED
			PORTD &= ~(1 << RED_LED);  // Turn off red LED
			motor_open();              // Open the motor
			} else {
			lcd_puts("Access Denied!");
			PORTD |= (1 << RED_LED);   // Turn on red LED
			PORTD &= ~(1 << BLUE_LED); // Turn off blue LED
			motor_stop();              // Keep motor closed
		}

		_delay_ms(2000);  // Delay to allow user to read the message
		PORTD &= ~((1 << BLUE_LED) | (1 << RED_LED));  // Turn off LEDs
	}
}
