#ifndef LCD_H
#define LCD_H

#include <avr/io.h>
#include <util/delay.h>

// Define LCD ports and pins
#define LCD_PORT PORTC
#define LCD_DDR DDRC
#define RS PC0
#define EN PC1

// Function prototypes
void lcd_command(unsigned char cmd);
void lcd_data(unsigned char data);
void lcd_init(unsigned char disp_attr);
void lcd_clrscr();
void lcd_puts(const char *str);
void lcd_gotoxy(unsigned char x, unsigned char y);
void lcd_putc(char c);

#endif
