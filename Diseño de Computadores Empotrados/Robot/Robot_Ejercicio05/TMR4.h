/**
	@file		TMR1.h
	@author		Mirian Cifredo
	@date		22/04/2022
    @brief		Header file including macros to configure the Timer 1.
    @par		Description 
				The configuration can be modified changing the macros.
				For other MCU only this header file will need be modified.
*/



#ifndef TMR4_H_
#define TMR4_H_

#define DIV_CLK_1		0
#define DIV_CLK_2		1
#define DIV_CLK_4		2
#define DIV_CLK_8		3
#define DIV_CLK_16		4
#define DIV_CLK_32		5
#define DIV_CLK_64		6
#define DIV_CLK_128		7
#define DIV_CLK_256		8
#define DIV_CLK_512		9
#define DIV_CLK_1024	10
#define DIV_CLK_2048	11
#define DIV_CLK_4096	12
#define DIV_CLK_8192	13
#define DIV_CLK_16384	14

static inline void TMR4_PWM_Phase_Init(void) {
	DDRC |= (1 << DDC6);
	DDRD |= (1 << DDD7);
	
	TCCR4A &= ~((1 << COM4A1) | (1 << COM4A0) | (1 << PWM4A) | (1 << PWM4B));
	TCCR4C &= ~((1 << COM4D1) | (1 << COM4D0) | (1 << PWM4D));
	
	TCCR4A |= (1 << COM4A0) | (1 << PWM4A);	 
	TCCR4C |= (1 << COM4D1) | (1 << PWM4D);
	
	TCCR4D &= ~(1 << WGM41); 
	TCCR4D |= (1 <<  WGM40);
}

static inline void TMR4_PWM_Phase_Start (uint8_t divClock) {
	TCNT4 = 0;
	TCCR4B |= (divClock << CS40);
}

static inline void TMR4_PWM_Phase_Duty(uint8_t valueOCR4A, uint8_t valueOCR4D){
	OCR4A = valueOCR4A;
	OCR4D = valueOCR4D;
}

#endif /* TMR1_H_ */