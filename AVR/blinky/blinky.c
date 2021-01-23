#include <avr/io.h>
#include <util/delay.h>

#define MS_DELAY 3000

int main (void) {
    /*Set to one the zeroth bit of DDRB to one
    **Set digital PB0 to output mode */
    DDRB |= _BV(DDB0);

    while(1) {
        /*Set to one the zeroth bit of PORTB to one
        **Set to HIGH the PB0 */
        PORTB |= _BV(PORTB0);

        /*Wait 3000 ms */
        _delay_ms(MS_DELAY);

        /*Set to zero the zeroth bit of PORTB
        **Set to LOW the PB0 */
        PORTB &= ~_BV(PORTB0);

        /*Wait 3000 ms */
        _delay_ms(MS_DELAY);
    }
}
