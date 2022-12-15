#define F_CPU 16000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include "motor.h"

#define MODE1 1000
#define MODE2 500
#define MODE3 150

void initMotor();
void onMotor();



void initMotor(){
	DDRB=0x20;   // PB5 out 
	TCCR1A=0x82; 
	TCCR1B=0x1A; 
	OCR1A=3000; 
	ICR1=19999; // OCR1A -> OC Clear / Fast PWM TOP = ICR1 / 8╨паж
}

void onMotor(int mode){

	DDRB=0x20;   // PB5 out 
	switch(mode){
		case 1:
			OCR1A = 4000; 
			_delay_ms(MODE1);
			OCR1A = 800; 
			_delay_ms(MODE1);
			break;
		case 2:
			OCR1A = 4000; 	
			_delay_ms(MODE2);
			OCR1A = 800; 	
			_delay_ms(MODE2);
			break;
		case 3:
			OCR1A = 4000; 	
			_delay_ms(MODE3);
			OCR1A = 800; 	
			_delay_ms(MODE3);
			break;
		default:
			OCR1A = 4000; 
			_delay_ms(MODE1);
			OCR1A = 800; 
			_delay_ms(MODE1);
			break;	
	}
	
}

