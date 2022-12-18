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

volatile uint8_t cont = 0x00;

ISR(INT0_vect) {
	cont++;
	if (cont == 0x0F) cont = 0x00;
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
		_delay_ms(BLINK_TIME);
		GPIO_D_OUT = 0b00000100 | (cont << 3);
	}
}