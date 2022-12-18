/*
 * P02_Ejercicio03.c
 *
 * Created: 22/02/2022 12:17:03
 * Author : DCE
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PORTS.h"
#include "PARAMETERS.h"

int main(void){
	/** ------------ SETUP ----------------------------------------*/
	/// 1) Set LED pin as output. PUSHBUTTON LED is input by default.
	GPIO_PORT_MODE |= (1<<LED_PIN_3) | ~(1<<LED_PIN_2) | (1<<LED_PIN_1) | ~(1<<LED_PIN_0);
	/// 2) Enable pull-up for the PUSHBUTTON
	GPIO_OUT |= (1<<BUTTON_RPULLUP);
	/** ------------ LOOP ----------------------------------------
	Read the state of the pushbutton and shows it onto a LED.
	Keep in mind that the read value when the PUSHBUTTON
	is released is '1' due to the pull-up resistor.
	----------------------------------------------------------*/
	while (1){
		/// 1) Read pushbutton
		/// 2) If PUSHBUTTON is not pressed
		if ((GPIO_IN & (1 << BUTTON_PIN))) {
			// ------------------------------------------------------------------
			// If (XXXX X1XX & 0000 0100 = 0000 0100) ? PIND2=’1’ (released)
			// If (XXXX X0XX & 0000 0100 = 0000 0000) ? PIND2=’0’ (pressed)
			// 0x00 -> FALSE Something non-zero ->TRUE.
			//--------------------------------------------------------------------
			/// Switch ON LED
			GPIO_OUT |= (1<<LED_PIN_3) | (1<<LED_PIN_1);
			_delay_ms(BLINK_TIME);
		} else {
	/// 3) else switch OFF LED
			GPIO_OUT &= ~((1<<LED_PIN_3) | (1<<LED_PIN_1));
			_delay_ms(BLINK_TIME);
			
			GPIO_OUT |= (1<<LED_PIN_3) | (1<<LED_PIN_1);
			_delay_ms(BLINK_TIME);
		}
	}
}

