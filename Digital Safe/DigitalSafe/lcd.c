#include "lcd.h"

void lcd_command(unsigned char cmd) {
	LCD_PORT = (LCD_PORT & 0x0F) | (cmd & 0xF0); // Send higher nibble
	LCD_PORT &= ~(1 << RS); // RS = 0 for command
	LCD_PORT |= (1 << EN); // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (cmd << 4); // Send lower nibble
	LCD_PORT |= (1 << EN); // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_data(unsigned char data) {
	LCD_PORT = (LCD_PORT & 0x0F) | (data & 0xF0); // Send higher nibble
	LCD_PORT |= (1 << RS); // RS = 1 for data
	LCD_PORT |= (1 << EN); // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_us(200);

	LCD_PORT = (LCD_PORT & 0x0F) | (data << 4); // Send lower nibble
	LCD_PORT |= (1 << EN); // Enable pulse
	_delay_us(1);
	LCD_PORT &= ~(1 << EN);
	_delay_ms(2);
}

void lcd_init(unsigned char disp_attr) {
	LCD_DDR = 0xFF; // Set LCD port as output
	_delay_ms(15);
	lcd_command(0x02); // Initialize LCD in 4-bit mode
	lcd_command(0x28); // 2 lines, 5x7 matrix
	lcd_command(0x0C); // Display ON, Cursor OFF
	lcd_command(0x06); // Auto-increment cursor
	lcd_command(0x01); // Clear display
	_delay_ms(2);
}

void lcd_clrscr() {
	lcd_command(0x01); // Clear display
	_delay_ms(2);
}

void lcd_puts(const char *str) {
	while (*str) {
		lcd_data(*str++);
	}
}

void lcd_gotoxy(unsigned char x, unsigned char y) {
	unsigned char pos[] = {0x80, 0xC0};
	lcd_command(pos[y] + x);
}

void lcd_putc(char c) {
	lcd_data(c);
}
