#ifndef LCD_H
#define LCD_H
#ifndef F_CPU
#define F_CPU 8000000UL  // Define the CPU frequency (8 MHz in this case)
#endif
#include <avr/io.h>
#include <util/delay.h>

// Define LCD control pins
#define LCD_RS PD4
#define LCD_EN PD5
#define LCD_CTRL_PORT PORTD
#define LCD_CTRL_DDR DDRD

// Define LCD data port
#define LCD_DATA_PORT PORTC
#define LCD_DATA_DDR DDRC

// LCD commands
#define LCD_CLEAR 0x01
#define LCD_HOME 0x02
#define LCD_ENTRY_MODE 0x06
#define LCD_DISPLAY_ON 0x0C
#define LCD_FUNCTION_SET 0x28

void lcd_init(void);
void lcd_cmd(uint8_t cmd);
void lcd_putc(char c);
void lcd_puts(const char *str);
void lcd_clrscr(void);
void lcd_gotoxy(uint8_t x, uint8_t y);

#endif
