#define F_CPU 16000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include "switch.h"

#define ON 1
#define OFF 0

void initSwitch(){
	DDRA = 0xff; // Port A output
	DDRE = 0x00; // Port E input
}

int startSwitch(int state){
	if((PINE & 0x10) == 0x00){
		if (state == OFF){
			state = ON;
		}
		else {
			PORTA = 0x00;
			state = OFF;
		}
		_delay_ms(300);
		return state;
	}
	return -1;
}

