/*
 * P02_Ejercicio03.c
 *
 * Created: 22/02/2022 12:17:03
 * Author : DCE
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>
#include "PORTS.h"
#include "LED_BUTTON.h"

typedef enum {
	allON,
	oddON,
	evenON,
	oddOFF
} State_t;

/**-------- Interrupt Service Routines --------------------------*/
/// If INT0 interrupt is enabled, each time the pushbutton is
/// pressed, the int interrupt is triggered. Then all the actions
/// written into the ISR are executed. When it finishes, the flag is
/// cleared and the main program continues.

ISR(INT0_vect) {

}

int main(void) {
	static State_t state		= allON;
	static State_t Next_state	= allON;
	
	bool readButton				= BUTTON_NOT_PRESSED;
	
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Configure ports
	configPorts();
	EICRA |= (1<<ISC01); // INT0 is triggered by a falling edge
	EICRA &= ~(1<<ISC00); // ISC01-00 = "10"
	EIMSK |= (1<<INT0);
	sei(); // Equivalent to SREG |=(1<<I);
	/** ------------ LOOP ----------------------------------------*/
	while (1){		
		readButton 	= READ_BUTTON(GPIO_D_IN,BUTTON_PIN);
		
		switch(state){
			case allON:
			// When the pushbutton is pressed then...
			LED_ON(GPIO_D_OUT,LED_PIN_0);
			LED_ON(GPIO_D_OUT,LED_PIN_1);
			LED_ON(GPIO_D_OUT,LED_PIN_2);
			LED_ON(GPIO_D_OUT,LED_PIN_3);
			_delay_ms(BLINK_TIME);
			Next_state = oddON;
			break;
			
			case oddON:
			// Wait until timer finishes, then...
			if (readButton==BUTTON_PRESSED){
				Next_state = allON;
			} else {
				_delay_ms(BLINK_TIME);
				LED_ON(GPIO_D_OUT,LED_PIN_1);
				LED_ON(GPIO_D_OUT,LED_PIN_3);
				_delay_ms(BLINK_TIME);	
				Next_state = evenON;			
			}
			break;
			
			case evenON:
			// Wait until the push is released (HIGH), then...
			if (readButton==BUTTON_PRESSED){
				Next_state = allON;
			} else {
				_delay_ms(BLINK_TIME);
				LED_ON(GPIO_D_OUT,LED_PIN_0);
				LED_ON(GPIO_D_OUT,LED_PIN_2);
				_delay_ms(BLINK_TIME);
				Next_state = oddOFF;
			}
			break;

			case oddOFF:
			if (readButton==BUTTON_PRESSED){
				Next_state = allON;
			} else {
				LED_OFF(GPIO_D_OUT,LED_PIN_0);
				LED_OFF(GPIO_D_OUT,LED_PIN_1);
				LED_OFF(GPIO_D_OUT,LED_PIN_2);
				LED_OFF(GPIO_D_OUT,LED_PIN_3);
				_delay_ms(BLINK_TIME);
				Next_state = allON;
			}
			break;
			
			default:
			Next_state = allON;
			break;
		} // Close Switch-Transitions
		
		state=Next_state;
	}
}