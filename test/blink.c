#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    // Set PB5 (Arduino pin 13) as output
    DDRB |= (1 << DDB5);

    while (1) {
        // Toggle LED
        PORTB ^= (1 << PORTB5);
        _delay_ms(1000); // 1 second delay
    }
}
