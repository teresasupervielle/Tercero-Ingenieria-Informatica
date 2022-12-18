#ifndef WHEELS_H_
#define WHEELS_H_

#include <avr/io.h>
#include <util/delay.h>
#include "TMR4.h"

static inline void setupWheels (void) {
	DDRD |= (1 << DDD6);
	DDRE |= (1 << DDE6);
	
	TMR4_PWM_Phase_Init ();
}

void Robot_FWD(uint8_t speedLeft, uint8_t speedRight);
void Robot_BWD(uint8_t speedLeft, uint8_t speedRight);
void Robot_STOP();
void Robot_RIGHT(uint8_t speedLeft, uint8_t speedRight);
void Robot_LEFT(uint8_t speedLeft, uint8_t speedRight);void Robot_Test();

#endif /* TMR1_H_ */