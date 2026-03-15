#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

int main(void) {
  DDRB = DDRB | (1 << PB3);
  DDRB = DDRB & (~(1 << PB2));
  PORTB = PORTB | (1 << PB2);
  int pin_status;
  while (1) {
    pin_status = ~PINB & (1 << PB2);
    if (pin_status) {
      PORTB = PORTB | (1 << PB3);

    } else {
      PORTB = PORTB & (~(1 << PB3));
    }
  }return 0;
}
