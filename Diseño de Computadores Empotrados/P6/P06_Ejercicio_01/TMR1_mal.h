/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/

#ifndef TMR1_H_
#define TMR1_H_

#define c_0			0b000
#define c_1			0b001
#define c_8			0b010
#define c_64		0b011
#define c_256		0b100
#define c_1024		5

static inline void TMR_CTC_Init () {
	TCCR1A |= (1 << WGM11) ;
	TCCR1B &= ~(1 << WGM12);
	TCCR1A &= ~(1 << WGM10);
}

static inline void TMR_CTC_EnaInterrup () {
	TIMSK1 |= (1 << OCIE1A);
}

static inline void TMR_CTC_Start (uint8_t diuclk) {
	TCCR1B &= 0xf8;
	TCCR1B |= diuclk;
}

static inline void TMR_CTC_Stop () {
	TIMSK1 &= ~(1 << OCIE1A);
}

static inline void TMR_CTC_Set (uint16_t value) {
	TCNT1 = 0;
	OCR1A = value;
}


#endif /* LED_BUTTON_H_ */