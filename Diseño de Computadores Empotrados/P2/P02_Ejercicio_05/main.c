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

int main(void){
	GPIO_PORT_MODE = 0x0F;
	GPIO_OUT |= (1<<BUTTON_RPULLUP);
	
	while (1){
		if (!(GPIO_IN & (1 << BUTTON_PIN))) {
			if (!(GPIO_IN & (1 << PIND3)))
				GPIO_OUT |= (1<<LED_PIN);
			else
				GPIO_OUT &= (~(1<<LED_PIN));
		}
		_delay_ms(BLINK_TIME);
	}
}

