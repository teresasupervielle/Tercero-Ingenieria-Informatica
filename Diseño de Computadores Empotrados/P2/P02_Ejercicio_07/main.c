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
#include "PORTS.h"
#include "LED_BUTTON.h"

//---------  User data types definitions -------------
typedef enum {
	STATE_START,
	STATE_TIMER,
	STATE_RELEASE,
	STATE_DEBOUNCED
} State_t;


int main(void) {
	/**---------  Local variables (Registers) -----------------*/
	/// VAriables to keep the state of the FSM
	static State_t state		= STATE_START;
	static State_t Next_state	= STATE_START;
	/// Variable to read the button and storing as TRUE/FALSE
	bool readButton				= BUTTON_NOT_PRESSED;

	/**------------ SETUP--------------------------------------*/
	/// 1) Ports are configured.
	configPorts ();

	/**---------- SUPERLOOP (FSM) -----------------------------*/
	while (1) {
		/// 1. Check the EVENT in each iteration
		// The value for "state" is preserved. (Static variable)
		readButton 	= READ_BUTTON(GPIO_D_IN,BUTTON_PIN);
		
		//-----------------------------------------------------------
		/// 2. Set the TRANSITIONS based upon events
		switch(state){
			case STATE_START:
			// When the pushbutton is pressed then...
			if (readButton==BUTTON_PRESSED){
				Next_state=STATE_TIMER;
			}
			break;
			
			case STATE_TIMER:
			// Wait until timer finishes, then...
			_delay_ms(DEBOUNCE_TIME);
			if (readButton == BUTTON_NOT_PRESSED) {
				Next_state = STATE_DEBOUNCED;
			} else {
				Next_state = STATE_RELEASE;
			}
			break;
			
			case STATE_RELEASE:
			// Wait until the push is released (HIGH), then...
			if (readButton == BUTTON_NOT_PRESSED){
				Next_state = STATE_TIMER;
			} else {
				Next_state = STATE_RELEASE;
			}
			break;

			case STATE_DEBOUNCED:
			// Without conditions
			Next_state=STATE_START;
			break;
			
			default:
			Next_state=STATE_START;
			break;
		} // Close Switch-Transitions
		//------------------------------------------------------------------------

		/// 3. Set the OUTPUTS in every state. Nothing to do in any state but the
		/// "STATE_DEBOUNCED" one.
		switch (state) {
			case STATE_START:
			break;
			
			case STATE_TIMER:
			break;
			
			case STATE_RELEASE:
			break;

			case STATE_DEBOUNCED:
			LED_TOGGLE(GPIO_D_OUT,LED_PIN);
			break;
			
			default:
			break;
		}	// Close Switch-Outputs
		//--------------------------------------------------------------------------
		
		// 4. UPDATE state
		state=Next_state;
		//--------------------------------------------------------------------------
	}		// Close While
} 		// Close Main
