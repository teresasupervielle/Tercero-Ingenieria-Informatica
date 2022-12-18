#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

#include "PARAMETERS.h"
#include "TMR1.h"
#include "TMR0.h"
#include "PORTS.h"
/*
static inline void Buzzer_ON () {
	for (int i = 0; i < 250; i++){
		/// 1) LED OFF by clearing the pin PB5
		BUZZER_PORT &=~(1<<BUZZER_PIN);
		/// 2) Delay of TIME milli-seconds
		_delay_ms(BLINK_TIME);
		/// 3) LED ON by setting the pin PB5
		BUZZER_PORT |=(1<<BUZZER_PIN);
		/// 4) Delay of TIME milli-seconds
		_delay_ms(BLINK_TIME);
	}
}

static inline void Buzzer_BLACK () {
	for (int i = 0; i < 250; i++){
		/// 1) LED OFF by clearing the pin PB5
		BUZZER_PORT &=~(1<<BUZZER_PIN);
		/// 2) Delay of TIME milli-seconds
		_delay_ms(BLINK_TIME2);
		/// 3) LED ON by setting the pin PB5
		BUZZER_PORT |=(1<<BUZZER_PIN);
		/// 4) Delay of TIME milli-seconds
		_delay_ms(BLINK_TIME2);
	}
}

static inline void Buzzer_WHITE () {
	for (int i = 0; i < 250; i++){
		/// 1) LED OFF by clearing the pin PB5
		BUZZER_PORT &=~(1<<BUZZER_PIN);
		/// 2) Delay of TIME milli-seconds
		_delay_ms(BLINK_TIME3);
		/// 3) LED ON by setting the pin PB5
		BUZZER_PORT |=(1<<BUZZER_PIN);
		/// 4) Delay of TIME milli-seconds
		_delay_ms(BLINK_TIME3);
	}
}*/

static inline void playSoundTIMERS (uint16_t dur, uint8_t frec) {
	TMR0_CTC_Set(frec);
	TMR0_CTC_Init();
	TMR0_CTC_enaInterrupt();
	
	TMR1_CTC_Set(dur);
	TMR1_CTC_Init();
	TMR1_CTC_enaInterrupt();
	
	sei();
	
	TMR0_CTC_Start(T0_DIV_CLK_1024);
	TMR1_CTC_Start(T1_DIV_CLK_1024);
}
#endif