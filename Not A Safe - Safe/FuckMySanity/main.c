#define F_CPU 1000000UL
#include <avr/io.h>
#include "keypad.h"
#include "lcd.h"
#include <util/delay.h>
#include <string.h>

#define MAX_PASSWORD_LENGTH 4
#define MAX_TRIALS 3
const char correct_password[MAX_PASSWORD_LENGTH + 1] = "1234";

int main(void)
{
	uint8_t data_from_keypad;
	char entered_password[MAX_PASSWORD_LENGTH + 1] = "";
	uint8_t entered_index = 0;
	uint8_t trial_count = 0;

	keypad_init();
	lcd_init();

	lcd_write_string("Hello!");
	_delay_ms(500);
	lcd_clearDisplay();
	lcd_write_string("Enter Password");
	_delay_ms(1000);
	lcd_clearDisplay();

	while (1)
	{
		if (trial_count >= MAX_TRIALS)  // Lock out after exceeding maximum trials
		{
			lcd_clearDisplay();
			lcd_write_string("Locked Out");
			while (1);  // Stop further input
		}

		data_from_keypad = keypad_scan();

		if (data_from_keypad == 'C')  // Check if 'C' (Enter) is pressed
		{
			entered_password[entered_index] = '\0';  // Null-terminate the entered password
			lcd_clearDisplay();

			if (strcmp(entered_password, correct_password) == 0)  // Password matches
			{
				lcd_write_string("Access Granted");
				_delay_ms(2000);
				lcd_clearDisplay();

				// Activate the motor when access is granted
				PORTA = 0b11111110;
				_delay_ms(3000);

				lcd_write_string("Motor Stopped");
				_delay_ms(2000);
				lcd_clearDisplay();

				// Reset password and allow for the next input
				entered_index = 0;
				entered_password[0] = '\0';  // Clear entered password
			}
			else  // Incorrect password
			{
				trial_count++;  
				lcd_write_string("Access Denied");
				_delay_ms(2000);
				lcd_clearDisplay();

				lcd_write_string("Tries Left: ");
				lcd_write_character('0' + (MAX_TRIALS - trial_count));
				_delay_ms(2000);
				lcd_clearDisplay();

				
				entered_index = 0;
				entered_password[0] = '\0';
			}
		}
		else if (data_from_keypad == '*')  // Handle backspace (delete last character)
		{
			if (entered_index > 0)
			{
				entered_index--;  // Move back to previous character
				entered_password[entered_index] = '\0';  // Null-terminate the string

				lcd_clearDisplay();
				for (uint8_t i = 0; i < entered_index; i++)
				{
					lcd_write_character(entered_password[i]);
				}
			}
		}
		else if (data_from_keypad != 0 && entered_index < MAX_PASSWORD_LENGTH)  // Valid key pressed
		{
			lcd_write_character(data_from_keypad);  // Display entered character
			entered_password[entered_index++] = data_from_keypad;  // Store character in password array
		}
	}
}
