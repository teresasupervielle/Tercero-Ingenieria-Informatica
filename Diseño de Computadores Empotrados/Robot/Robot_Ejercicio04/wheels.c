#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "wheels.h"
#include "TMR4.h"

void Robot_FWD(uint8_t speedLeft, uint8_t speedRight) {
	PORTD &= ~(1 << PORTD6);
	PORTE &= ~(1 << PORTE6);
	
	TMR4_PWM_Phase_Duty(speedLeft, speedRight);
}

void Robot_BWD(uint8_t speedLeft, uint8_t speedRight) {
	PORTD |= (1 << PORTD6);
	PORTE |= (1 << PORTE6);
	
	TMR4_PWM_Phase_Duty(speedLeft, speedRight);
}

void Robot_STOP() {
	PORTD |= (1 << PORTD6);
	PORTE |= (1 << PORTE6);
	
	TMR4_PWM_Phase_Duty(255,0);
}

void Robot_RIGHT(uint8_t speedLeft, uint8_t speedRight) {
	PORTD &= ~(1 << PORTD6);
	PORTE |= (1 << PORTE6);
	
	TMR4_PWM_Phase_Duty(speedLeft, speedRight);
}

void Robot_LEFT(uint8_t speedLeft, uint8_t speedRight) {
	PORTD |= (1 << PORTD6);
	PORTE &= ~(1 << PORTE6);
	
	TMR4_PWM_Phase_Duty(speedLeft, speedRight);
}