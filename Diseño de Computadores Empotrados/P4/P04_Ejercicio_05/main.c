/*
 * P02_Ejercicio03.c
 *
 * Created: 22/02/2022 12:17:03
 * Author : DCE
 */ 

#define  F_CPU	16000000UL
#include <avr/io.h>	 	
#include <avr/interrupt.h>
#include "PORTS.h"	
#include "EXT_INT.h"	
#include "USART.h" 
#include "LED_BUTTON.h" 
#include <stdbool.h>

/// -------------  ISR functions -----------------------------------
// For fulfill the a) requirement
ISR (INT0_vect){
	static char *datum = "Hola mundo\r\n";
	//-------------------------------------------------------------
	// 1.- Check if the USART is available for sending 
	//-------------------------------------------------------------
		// SOL_1: Not blocking
/*		//-------------------------------------------------------------
		if (UCSR0A & (1 << UDRE0)){		// (Polling for TX) Only sends if the buffer is empty ('1')
			UDR0 = datum;				// Send the data
		//-------------------------------------------------------------	
*/	
		// SOL_2 - Blocking
		USART0_putString(datum);			// BLOCKING!!! due to the "while" in the function.
}
//-------------------------------------------------------------------
// For fulfill the b) requirement
ISR (USART_RX_vect){
	//-----------------------------------------------------------------------------
	// 1.- Clear the 4MSB in PORTD. The remaining bits keep the value (Rpull-up)
	// Then, OR with the 4LSB of the ASCII and shifts the value for showing
	// onto the LED.
	PORTD = (PORTD & 0b00001111) | ((UDR0 & 0x0F)<<4);
}

//-------------------------------------------------------------------

int main(){
	bool readButton	= BUTTON_NOT_PRESSED;
	/// -------------  SETUP -----------------------------------
	/// 1. Config ports (4 LED and pushbutton - "PORTS.h")
	configPorts();
	//---------------------------------------------------------
	/// 2. External interrupt setup (INT0 - Pushbutton)
	INT0_config(FALLING);
	INT0_enable();
	//----------------------------------------------------------
	/// 3. USART setup (9600 8N1 - Keyboard)
	USART0_Init(UBRR_VALUE);
	USART0_enaInterrupt_RX();
	
	/// -------------  SUPER-LOOP -----------------------------------
	while(1){	
		readButton 	= READ_BUTTON(GPIO_D_IN,BUTTON_PIN);
		if (readButton == BUTTON_PRESSED)		
			sei();
	}
}

