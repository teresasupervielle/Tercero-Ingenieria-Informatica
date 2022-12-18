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
#include "EXT_INT.h"

/**-------- Interrupt Service Routines --------------------------*/
/// If INT0 interrupt is enabled, each time the pushbutton is
/// pressed, the int interrupt is triggered. Then all the actions
/// written into the ISR are executed. When it finishes, the flag is
/// cleared and the main program continues.

volatile uint8_t incremento = 1;

ISR(INT0_vect) {
	if (incremento == MAX_INCREMENT) incremento = 1;
	else incremento++;
}

int main(void) {
	uint8_t cont = 0x00;
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Configure ports
	configPorts();
	initINT0();
	sei(); // Equivalent to SREG |=(1<<I);
	/** ------------ LOOP ----------------------------------------*/
	while (1){		
		cont = cont + incremento;
		if (cont == 0x0F) cont = 0x00;
		
		GPIO_D_OUT = 0b00000100 | (cont << 4);
		
		_delay_ms(300);
	}
}