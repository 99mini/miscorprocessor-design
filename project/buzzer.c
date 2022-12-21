#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

void startBuuzor();

void startBuzzor() {
	DDRB = 0x10; 

    PORTB = 0x10;
    _delay_ms(1);
    PORTB = 0x00;
	_delay_ms(1);

}
