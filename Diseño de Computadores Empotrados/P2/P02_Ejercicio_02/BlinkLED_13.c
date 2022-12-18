/**
	@file		BlinkLED_13.c
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Blinking the LED connected to pin 13 (Arduino's built-in LED).
    @par		Description 
				Pin 13 in Arduino is connected to pin 5 in PORTB.
				This information can be got from the picture showing Arduino UNO <--> Atmega328p
*/

/// Define CPU frequency as 16 MHz 
#define F_CPU 16000000UL	

#include <avr/io.h>
#include <util/delay.h>
#include "PORTS.h"
#include "PARAMETERS.h"


int main(void){
	uint8_t aux = CERO;
/** ------------ SETUP ------------------	*/
	///	1) Set pin 5 in PORTB as output pin 
	LED_PORT_MODE |= (1<<LED_PIN_4) | (1<<LED_PIN_3) | (1<<LED_PIN_2) | (1<<LED_PIN_1) | (1<<LED_PIN_0);

/** ------------ LOOP -------------------
			 For blinking LED 
	-------------------------------------*/
    while (1){
			/// 1) LED OFF by clearing the pin PB5
			LED_PORT = (1<<LED_PIN_4) | (aux << 2);
			aux++;
			/// 2) Delay of TIME milli-seconds
			_delay_ms(BLINK_TIME);	
		if (aux == COUNT){
			aux = CERO;
		}
    }
}

