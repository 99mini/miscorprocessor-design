#define F_CPU 16000000UL
#include <avr/io.h> 
#include <util/delay.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <string.h>

#include "motor.h"
#include "fnd.h"
#include "switch.h"
#include "buzzor.h"
#include "temperature.h"
#include "utils.h"

#define ON 1
#define OFF 0

#define MOTOR_MODE1 1
#define MOTOR_MODE2 2
#define MOTOR_MODE3 3

volatile int isStart = OFF;
volatile int temperature = 0;
volatile int value_int = 0;

void init(){
	initMotor();
	initSwitch();

	// fnd init
	DDRC = 0xff; 
	DDRG = 0xff;

	// �µ� ���� 
    PORTD = 3;

    temp_init();
    _delay_ms(100);	
}

void setTemp(){
	temperature = temp_read();
	value_int = ((temperature & 0x7f00) >> 8);
}


void display(){
	setTemp();
			
	set_fnd1(1,(int)(value_int/10));_delay_ms(5);
	set_fnd1(2,value_int%10);_delay_ms(5);
}

/* 
����ġ 1�� ���ͷ�Ʈ
���α׷� ����
*/
SIGNAL(SIG_INTERRUPT4){

	if(isStart == OFF){
		set_on();
	}
	else set_off();

	isStart = startSwitch(isStart);
	
}

/* 
����ġ 2�� ���ͷ�Ʈ
fnd �µ� ǥ��
*/ 

SIGNAL(SIG_INTERRUPT5){
	for (int i=0;i < 30; i++) display();

	if(isStart == ON) set_on();
	else set_off();
}


int main(void)
{
	init();

	DDRE = 0xcf; // 0b11011111, PE5(switch2)�� �Է�    

    //PORTG = 0x01;
  	EICRB = 0x0a; //falling edge
  	EIMSK = 0x30; //interrupt en
  	SREG |= 1 << 7;

    while(1)
    {	
		setTemp();
		if (isStart == ON){		
			
			// 24������ ���� ��� ��� 1
			if (value_int < 24){
				onMotor(MOTOR_MODE1);
			}
			// 24�� �̻� 30�� �̸� ��� 2
			else if (value_int >= 24 && value_int < 30){
				onMotor(MOTOR_MODE2);
			}
			// 30�� �̻� ��� 3
			// ���� �︮��
			else if (value_int >= 30){
				onMotor(MOTOR_MODE3);
				startBuzzor();
			}
			set_on();
		} 
		else if(isStart == OFF){
			set_off();	
		}
    }
}
