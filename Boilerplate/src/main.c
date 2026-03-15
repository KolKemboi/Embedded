#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

int main(void) {
  DDRB |= (1 << PB5);

  while (1) {
    PORTB ^= (1 << PB5);
    _delay_ms(500);
  }
}
