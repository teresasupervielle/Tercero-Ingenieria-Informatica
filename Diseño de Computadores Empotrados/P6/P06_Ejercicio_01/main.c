/**
	@file		main.c
	@author		Mirian Cifredo
	@date		22/04/2022
    @brief		500ms - Hardware timer 
    @par		Description 
				Use the 16-bit Timer1 for blinking the Arduino built-in LED. (1Hz)
*/

#include <avr/io.h>	 
#include <avr/interrupt.h>	 	
#include "PORTS.h"
#include "LED_BUTTON.h"			
#include "TMR1.h"
#include "ADC.h"

static volatile uint16_t portValue;

// ===================		ISR          ===============================================
ISR (TIMER1_COMPA_vect){
	portValue = ADC_Read_Single_Poll(ADC_PORT);
	if (portValue > 512) LED_ON (GPIO_D_OUT, LED_PIN_0);
	else LED_OFF (GPIO_D_OUT, LED_PIN_0);
}

/// ===================	MAIN FUNCTION    =================================================
int main(){
	
///-------------		Setup			-------------------------------------------------------
	/// 1.- Config ports
	ADC_Init_Single();
	configPorts();
	/// 2.- Configure TMR1 as CTC with interrupts
	TMR1_CTC_Interrupt_Init();
	/// 3.- Set the matching value for reaching 500ms (@Pre-scaler 1024)
	TMR1_CTC_Set(7812);
	/// 4.- Set the pre-scaler and start the timer
	TMR1_CTC_Start(DIV_CLK_1024);
	
	sei();
			
/// -------------		Super-Loop      -----------------------------------
	while(1){	
	
	}
}


