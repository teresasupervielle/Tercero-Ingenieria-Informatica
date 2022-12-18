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

/**-------- Interrupt Service Routines --------------------------*/
/// If INT0 interrupt is enabled, each time the pushbutton is
/// pressed, the int interrupt is triggered. Then all the actions
/// written into the ISR are executed. When it finishes, the flag is
/// cleared and the main program continues.
ISR(INT0_vect) {
	LED_TOGGLE (GPIO_D_OUT, RED_LED_PIN); // Toggle the RED_LED
}

int main(void) {
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Configure ports
	configPorts();
	/// 2) Configure external interrupt
	EICRA |= (1<<ISC01); // INT0 is triggered by a falling edge
	EICRA &= ~(1<<ISC00); // ISC01-00 = "10"
	EIMSK |= (1<<INT0); // Enable the ISR of INT0;
	/// 3) Enable global interrupts
	sei(); // Equivalent to SREG |=(1<<I);
	/** ------------ LOOP ----------------------------------------*/
	while (1){
		LED_TOGGLE(GPIO_D_OUT,GREEN_LED_PIN);
		_delay_ms(BLINK_TIME);
	}
}