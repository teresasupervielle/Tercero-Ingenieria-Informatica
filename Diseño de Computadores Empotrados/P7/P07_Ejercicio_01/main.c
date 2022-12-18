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
#include "TMR0.h"
#include "ADC.h"

/// ===================	MAIN FUNCTION    =================================================
int main(){
	
	//set OC0A/PD6 as output
	
	TMR0_PWM_Phase_Init();
	TMR0_PWM_Phase_Duty(179, 90);
	TMR0_PWM_Phase_Start (3);
	while(1) {} //doing nothing
}


