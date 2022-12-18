#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "PORTS.h"
#include "PARAMETERS.h"
#include "TMR0.h"
#include "TMR1.h"
#include "FUNCTIONS.h"
#include "ADC.h"
#include "m_usb.h"


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
	uint16_t value;
	
	m_usb_init(); // USB peripheral setup
	ADC_Init_Single();
	while(!m_usb_isconnected()); // Wait for a USB connection
	
	for (int i = 0; i < 3; i++) {
		playSoundTIMERS (DURACION_SHORT, STARTING_SOUND);
		_delay_ms(2000);
	}
	
	_delay_ms(3000);

	while(1){
		value = 0;
		for (int i = 0; i < 30; i++) {
			value = value + ADC_Read_Single_Poll(ADC7D);
		}
		value = value / 30;
		m_usb_tx_uint(value); // Print the ASCII character
		m_usb_tx_char('\t');
		_delay_ms(3000);
		
		if (value > 300 && value < 450) playSoundTIMERS(DURACION_SHORT, MATCH_SOUND); //Negro
		else if (value > 1000 && value < 850) playSoundTIMERS(DURACION_SHORT, FAIL_SOUND); //Blanco
		_delay_ms (2000);
	}
}