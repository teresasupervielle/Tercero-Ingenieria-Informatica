/**
	@file		main_noBlocking.c
	@author		Mirian Cifredo
	@date		10/02/2022
    @brief		Toggle a LED by means a pushbutton
    @par		Description 
				Allow toggle a LED every time a pushbutton is pressed.
				In order to avoid a bouncing in the pushbutton, the system waits for a time
				until the state of the pushbutton is stable.
*/
/// Define CPU frequency as 16 MHz 
#define  F_CPU	16000000UL
#include <avr/io.h>	 			
#include <util/delay.h>
#include <stdbool.h>
#include "functionsGPIO.h" 
#include "LED_BUTTON.h"


static bool read_input(uint8_t portGPIO, uint8_t pinNumber){
	static bool flag					= true;
	bool button_CurrentState			= true;
	
	button_CurrentState = READ_BUTTON(portGPIO, pinNumber);
	
	if (button_CurrentState == BUTTON_NOT_PRESSED){
		flag = BUTTON_NOT_PRESSED;
	}
	
	_delay_ms(DEBOUNCE_TIME); // Wait for a second reading
	
	button_CurrentState = READ_BUTTON(portGPIO, pinNumber); // Second reading
	
	if ((button_CurrentState==BUTTON_PRESSED) && (flag==BUTTON_NOT_PRESSED)){	// FAlling-edge
		_delay_ms(DEBOUNCE_TIME); // Debouncing time
		button_CurrentState = READ_BUTTON(portGPIO, pinNumber); // Third reading
		if (button_CurrentState==BUTTON_PRESSED){
			//flag=false;
			flag=BUTTON_PRESSED; // se da por buena la acción de la pulsación y se restaura para aceptar una nueva pulsación
		}
	}
	
	return button_CurrentState;
}