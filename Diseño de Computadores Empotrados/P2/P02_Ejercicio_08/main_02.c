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
#include "PORTS.h" 
#include "LED_BUTTON.h"


typedef enum {
	STATE_LED_ON,
	STATE_LED_BLINK,
	STATE_LED_OFF,
} State_t;

static inline bool read_input(uint8_t portGPIO, uint8_t pinNumber){
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

int main(void) {
	/**---------  Local variables (Registers) -----------------*/
	/// VAriables to keep the state of the FSM
	static State_t state		= STATE_LED_ON;
	static State_t Next_state	= STATE_LED_ON;
	/// Variable to read the button and storing as TRUE/FALSE
	bool readButton				= BUTTON_NOT_PRESSED;

	/**------------ SETUP--------------------------------------*/
	/// 1) Ports are configured.
	configPorts ();

	/**---------- SUPERLOOP (FSM) -----------------------------*/
	while (1) {
		
		/// 1. Check the EVENT in each iteration
		// The value for "state" is preserved. (Static variable)
		readButton 	= read_input(GPIO_D_IN, BUTTON_PIN);
		
		//-----------------------------------------------------------
		/// 2. Set the TRANSITIONS based upon events
		switch(state){
			
			case STATE_LED_ON:
				LED_ON(GPIO_D_OUT,LED_PIN);
			
				// When the pushbutton is pressed then...
				if (readButton == BUTTON_PRESSED){
					Next_state = STATE_LED_BLINK;
				}
			break;
			
			case STATE_LED_BLINK:
			
				LED_ON(GPIO_D_OUT,LED_PIN);
				_delay_ms(BLINK_TIME);
				LED_OFF(GPIO_D_OUT,LED_PIN);
				
				if (readButton == BUTTON_PRESSED) {
					Next_state = STATE_LED_OFF;
				}
			break;
			
			case STATE_LED_OFF:		
				
				LED_OFF(GPIO_D_OUT,LED_PIN);
				// Wait until the push is released (HIGH), then...
				
				if (readButton == BUTTON_PRESSED){
					Next_state = STATE_LED_ON;
				}
			break;

			default:
			Next_state=STATE_LED_ON;
			break;
		} // Close Switch-Transitions
		
		// 4. UPDATE state
		state=Next_state;
		//--------------------------------------------------------------------------
	}		// Close While
} 		// Close Main
