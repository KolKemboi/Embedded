#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

int main(void) {
  DDRB = 0xFF;

	int delay = 100;
  while (1) {
    PORTB = PORTB | (1 << PB3);
    _delay_ms(delay);
    PORTB = PORTB & (~(1 << PB3));
    _delay_ms(delay * 20);
  }
  return 0;
}
