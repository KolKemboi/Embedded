#include <avr/io.h>
#define __DELAY_BACKWARD_COMPATIBLE__
#include <util/delay.h>

#define LEDC_Port PORTC
#define LEDC_Dir DDRC

#define LEDB_Port PORTB
#define LEDB_Dir DDRB

#define LEDD_Port PORTD
#define LEDD_Dir DDRD

void display(int digit) {
  char nums[] = {0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f};
  if (digit < 10) {
    LEDC_Port = nums[digit];
    LEDB_Port = nums[digit];
    LEDD_Port = nums[digit];
  }
}

int main(void) {
  LEDC_Dir |= 0xff;
  LEDC_Port |= 0xff;

  LEDB_Dir |= 0xff;
  LEDB_Port |= 0xff;

  LEDD_Dir |= 0xff;
  LEDD_Port |= 0xff;
  while (1) {
    for (int i = 0; i < 10; i++) {
      display(i);
      _delay_ms(1000);
    }
  }
}
