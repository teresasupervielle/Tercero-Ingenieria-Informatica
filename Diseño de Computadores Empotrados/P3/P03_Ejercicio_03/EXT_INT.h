/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/

#ifndef EXT_INT_H_
#define EXT_INT_H_

#define LOW_LEVEL 0		//ISC01 = 0		ISC00 = 0
#define CHANGE 1		//ISC01 = 0		ISC00 = 1
#define FALLING 2		//ISC01 = 1		ISC00 = 0
#define RISING 3		//ISC01 = 1		ISC00 = 1

#define MAX_INCREMENT 4

#define PINCHANGE0 0
#define PINCHANGE1 1
#define PINCHANGE2 2

//INT0 -> pin 2
static inline void INT0_config(uint8_t typeTrigger){
	EICRA &= 11111100;
	EICRA |= typeTrigger;
}

static inline void INT0_enable() {
	EIMSK |= (1 << INT0);	// Enable INT0;
}

static inline void INT0_disable(){
	EIMSK |= ~(1 << INT0);	// Enable INT0;
}

//INT1 -> pin 3
static inline void INT1_config(uint8_t typeTrigger){
	EICRA &= 11110011;
	EICRA |= (2 << typeTrigger);
}

static inline void INT1_enable() {
	EIMSK |= (1 << INT1);	// Enable INT0;
}

static inline void INT1_disable(){
	EIMSK |= ~(1 << INT1);	// Enable INT0;
}

//PCINT
static inline void PCINT_enable(uint8_t numberPINCHANGE) {
	PCICR |= (1 << numberPINCHANGE);	// Enable INT0;
}

static inline void PCINT0_pinSelect(uint8_t numberPIN) {
	PCMSK0 |= (1 << numberPIN);	// Enable INT0;
}

static inline void PCINT1_pinSelect(uint8_t numberPIN) {
	PCMSK1 |= (1 << numberPIN);	// Enable INT0;
}

static inline void PCINT2_pinSelect(uint8_t numberPIN) {
	PCMSK2 |= (1 << numberPIN);	// Enable INT0;
}

#endif /* LED_BUTTON_H_ */