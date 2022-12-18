/**
	@file		TMR1.h
	@author		Mirian Cifredo
	@date		22/04/2022
    @brief		Header file including macros to configure the Timer 1.
    @par		Description 
				The configuration can be modified changing the macros.
				For other MCU only this header file will need be modified.
*/



#ifndef TMR0_H_
#define TMR0_H_

#define DIV_CLK_1		1
#define DIV_CLK_8		2
#define DIV_CLK_64		3
#define DIV_CLK_256		4
#define DIV_CLK_1024	5


static inline void TMR0_PWM_Phase_Init(void) {
	DDRD|= (1 << DDD5) | (1 << DDD6);
	
	//TCCR0A &= ~((1<<COM0A1) | (1<<WGM01)|(1<<WGM00));
	//TCCR0B &= ~(1 << WGM02);
	
	TCCR0A |= (1 << COM0A1);
	TCCR0A |= (1 << WGM00);
}

static inline void TMR0_PWM_Phase_Start (uint8_t divClock) {
	TCNT0 = 0;
	TCCR0B |= (divClock << CS00);
}

static inline void TMR0_PWM_Phase_Duty(uint8_t valueOCR0A, uint8_t valueOCR0B){
	OCR0A = valueOCR0A;
	OCR0B = valueOCR0B; 				
}

#endif /* TMR1_H_ */