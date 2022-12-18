#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "PORTS.h"
#include "PARAMETERS.h"
#include "TMR4.h"
#include "wheels.h"

int main(void){	
	//DDRD |= (1 << DDD6);
	//DDRE |= (1 << DDE6);
	
	//TMR4_PWM_Phase_Init ();
	setupWheels();
	TMR4_PWM_Phase_Start(DIV_CLK_64);
	
	while(1){
		
		//PORTD &= ~(1 << PORTD6);
		//PORTE &= ~(1 << PORTE6);
		
		//TMR4_PWM_Phase_Duty(200,50);
		
		//_delay_ms(1000);
		
		//PORTD |= (1 << PORTD6);
		//PORTE |= (1 << PORTE6);
		
		//TMR4_PWM_Phase_Duty(200,50);
		//_delay_ms(1000);
		
		//PORTD |= (1 << PORTD6);
		//PORTE |= (1 << PORTE6);
		
		//TMR4_PWM_Phase_Duty(255,35);
		
		//_delay_ms(1000);
		Robot_FWD (200, 50);
		_delay_ms(1000);
		
		Robot_BWD (200, 50);
		_delay_ms(1000);
		
		Robot_STOP ();
		_delay_ms(1000);
		
		Robot_RIGHT(200, 50);	
		_delay_ms(1000);	
		
		Robot_LEFT(50, 200);
		_delay_ms(1000);
	}
}