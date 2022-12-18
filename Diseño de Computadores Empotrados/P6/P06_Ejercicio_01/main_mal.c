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
#include "TMR1.h"
#include "LED_BUTTON.h" 
#include <stdbool.h>

/// -------------  ISR functions -----------------------------------
// For fulfill the a) requirement
ISR(TIMER1_COMPA_vect){
	LED_TOGGLE(GPIO_D_OUT,  LED_PIN_0);
}


int main(){
	configPorts();
	
	TMR_CTC_Init();
	TMR_CTC_Set(7812);
	TMR_CTC_Start(c_1024);
	
	sei();
	
	while (1) {
		// do nothing
	}
}

