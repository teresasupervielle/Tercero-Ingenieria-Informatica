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
#include "FUNCTIONS.h"

int main(void){
/** ------------ SETUP ------------------	*/
	///	1) Set pin 5 in PORTB as output pin 
	BUZZER_PORT_MODE |=(1<<BUZZER_PIN_MODE);
	
/** ------------ LOOP -------------------
			 For blinking LED 
	-------------------------------------*/
    while (1){
		Buzzer_ON();
		
		_delay_ms(5);
		
		Buzzer_BLACK();
		
		_delay_ms(5);
		
		Buzzer_WHITE();
		
		_delay_ms(5);
	}
}

