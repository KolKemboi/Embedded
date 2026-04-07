#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <avr/interrupt.h>
#include <util/delay.h>

ISR(INT0_vect) {
  PORTC ^= (1 << PC0);
  _delay_ms(50);
}

int main(void) {
  DDRC = 0x07;
  DDRD = 1 << PD0;
  DDRB = 0;

  PORTB = 1 << PB1;

  EIMSK = 1 << INT0;
  EICRA = (1 << ISC01) | (1 << ISC00);
  sei();
  int delay = 300;

  while (1) {
    PORTC = 1 << PC0;
    _delay_ms(delay);
    PORTC = 1 << PC1;
    _delay_ms(delay);
    PORTC = 1 << PC2;
    _delay_ms(delay);
  }
}
