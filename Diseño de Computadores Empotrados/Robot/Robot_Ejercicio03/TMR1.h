/**
	@file		TMR1.h
	@author		Mirian Cifredo
	@date		22/04/2022
    @brief		Header file including macros to configure the Timer 1.
    @par		Description 
				The configuration can be modified changing the macros.
				For other MCU only this header file will need be modified.
*/



#ifndef TMR1_H_
#define TMR1_H_

#define DIV_CLK_1		1
#define DIV_CLK_8		2
#define DIV_CLK_64		3
#define DIV_CLK_256		4
#define DIV_CLK_1024	5

static inline void TMR1_CTC_Init(void){
	/// 1.- Clear a previous configuration
	TCCR1A &= ~((1 << WGM11) | (1 << WGM10));
	TCCR1B &= ~((1 << WGM13) | (1 << WGM12));
	/// 2.- Set TMR1 Mode as CTC on OCR1A
	TCCR1B |= (1 << WGM12);
	/// 3.- Enable interrupt on compare match
	TIMSK1 |= (1 << OCIE1A);
}

static inline void TMR1_CTC_enaInterrupt(){
	/// 3.- Enable interrupt on compare match
	TIMSK1 |= (1 << OCIE1A);
}

static inline void TMR1_CTC_disInterrupt(){
	/// 3.- Enable interrupt on compare match
	TIMSK1 &= ~(1 << OCIE1A);
}


static inline void TMR1_CTC_Start(uint8_t divClock){
	// 1.- Clear the flag (not necessary in cTC with ISR)
	 TIFR1 |= (1<<OCF1A);
	 TCNT1=0;
	// 2.- Set the prescaler and start
	TCCR1B |= (divClock << CS10);
}


static inline void TMR1_CTC_Stop(void){
	TCCR1B &= ~((1 << CS12)|(1 << CS11)|(1 << CS10));
}

static inline void TMR1_CTC_Set(uint16_t valueCounterA){
	/// 1.- Set the matching value in OCR1A
	OCR1A = valueCounterA; 	
	
		
		//---- @ 1024 ------------------//
		//OCR1A = 1000;	// 64ms
		//OCR1A = 10000;	// 640ms
		//OCR1A = 20000;	// 1250ms
		//OCR1A = 25000;	// 1600ms
		
		//---- @ 64 ------------------//
		//OCR1A = 1000;		// 4ms
		//OCR1A = 10000;	// 40ms
		//OCR1A = 20000;	// 80ms
		//OCR1A = 25000;	// 100ms			
}

#endif /* TMR1_H_ */