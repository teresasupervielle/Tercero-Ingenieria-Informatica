#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "PORTS.h"
#include "PARAMETERS.h"
#include "TMR0.h"
#include "TMR1.h"
#include "TMR4.h"
#include "FUNCTIONS.h"
#include "wheels.h"

ISR (TIMER1_COMPA_vect){
	BUZZER_PORT &= ~(1<<BUZZER_PIN);

	TMR0_CTC_disInterrupt();
	TMR0_CTC_Stop();

	TMR1_CTC_disInterrupt();
	TMR1_CTC_Stop();
}

ISR (TIMER0_COMPA_vect){
	BUZZER_PORT ^=(1<<BUZZER_PIN);
}

typedef enum {
	startSTATE,
	testSTATE,
	stopSTATE
} State_t;

int main(void){	
	static State_t state		= startSTATE;
	static State_t Next_state	= startSTATE;
	
	setupWheels();
	Robot_STOP();
	TMR4_PWM_Phase_Start(DIV_CLK_64);
	sei();
	
	while(1){
		switch(state){
			case startSTATE:
				playSoundTIMERS (DURACION_SHORT, STARTING_SOUND);
				_delay_ms(1000);
				Next_state = testSTATE;
			break;
			
			case testSTATE:
				Robot_Test();
				Next_state = stopSTATE;
			break;
			
			case stopSTATE:
				for (int i = 0; i < 3; i++) {
					playSoundTIMERS (DURACION_SHORT, STARTING_SOUND);
					_delay_ms(1000);
					playSoundTIMERS (DURACION_SHORT, 0);
				}
				Next_state = startSTATE;
			break;
		}
		state = Next_state;
	}
}