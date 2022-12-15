#include <avr/io.h>

#define F_CPU 16000000UL
#include <util/delay.h>

void startBuuzor();

void startBuzzor() {
	DDRB = 0x10; // ��Ʈ B�� bit4 �� ��� ���·� ����

    PORTB = 0x10; // 1ms ���� ��On�� ���� ����
    _delay_ms(1);
    PORTB = 0x00; // 1ms ���� ��Off�� ���� ����
	_delay_ms(1);

}
