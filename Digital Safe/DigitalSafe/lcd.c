#include "lcd.h"

void lcd_enable_pulse(void) {
	LCD_CTRL_PORT |= (1 << LCD_EN);
	_delay_us(1);
	LCD_CTRL_PORT &= ~(1 << LCD_EN);
	_delay_us(100);
}

void lcd_cmd(uint8_t cmd) {
	LCD_CTRL_PORT &= ~(1 << LCD_RS);  // RS = 0 for command
	LCD_DATA_PORT = (cmd & 0xF0);     // Send upper nibble
	lcd_enable_pulse();

	LCD_DATA_PORT = (cmd << 4);       // Send lower nibble
	lcd_enable_pulse();

	_delay_ms(2);
}

void lcd_putc(char c) {
	LCD_CTRL_PORT |= (1 << LCD_RS);   // RS = 1 for data
	LCD_DATA_PORT = (c & 0xF0);       // Send upper nibble
	lcd_enable_pulse();

	LCD_DATA_PORT = (c << 4);         // Send lower nibble
	lcd_enable_pulse();

	_delay_ms(2);
}

void lcd_puts(const char *str) {
	while (*str) {
		lcd_putc(*str++);
	}
}

void lcd_clrscr(void) {
	lcd_cmd(LCD_CLEAR);
	_delay_ms(2);
}

void lcd_gotoxy(uint8_t x, uint8_t y) {
	uint8_t addr = (y ? 0x40 : 0x00) + x;
	lcd_cmd(0x80 | addr);
}

void lcd_init(void) {
	LCD_CTRL_DDR |= (1 << LCD_RS) | (1 << LCD_EN);
	LCD_DATA_DDR |= 0xF0;  // Upper nibble as output

	_delay_ms(20);

	lcd_cmd(0x33);
	lcd_cmd(0x32);
	lcd_cmd(LCD_FUNCTION_SET);
	lcd_cmd(LCD_DISPLAY_ON);
	lcd_cmd(LCD_CLEAR);
	lcd_cmd(LCD_ENTRY_MODE);
}
