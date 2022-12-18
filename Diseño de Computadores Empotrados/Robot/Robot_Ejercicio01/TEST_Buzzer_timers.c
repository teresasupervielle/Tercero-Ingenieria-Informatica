/// Define CPU frequency as 16 MHz 
#define F_CPU 16000000UL	

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "PORTS.h"
#include "PARAMETERS.h"
#include "TMR0.h"
#include "TMR1.h"
#include "FUNCTIONS.h"

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

int main(void){
/** ------------ SETUP ------------------	*/
	///	1) Set pin 5 in PORTB as output pin 
	BUZZER_PORT_MODE |=(1<<BUZZER_PIN);

	playSoundTIMERS(DURACION, STARTING_SOUND);
	_delay_ms(3000);
	playSoundTIMERS(DURACION, MATCH_SOUND);
	_delay_ms(3000);
	playSoundTIMERS(DURACION, FAIL_SOUND);
	_delay_ms(3000);
	
	while (1)  {

	}
}
