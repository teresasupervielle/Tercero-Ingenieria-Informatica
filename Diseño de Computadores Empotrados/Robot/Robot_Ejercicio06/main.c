#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#include "PORTS.h"
#include "PARAMETERS.h"
#include "TMR0.h"
#include "TMR1.h"
#include "TMR4.h"
#include "ADC.h"
#include "FUNCTIONS.h"
#include "wheels.h"

ISR (TIMER1_COMPA_vect){
	BUZZER_PORT &= ~(1<<BUZZER_PIN);

	TMR0_CTC_disInterrupt();
	TMR0_CTC_Stop();

	TMR1_CTC_disInterrupt();
	TMR1_CTC_Stop();
}

ISR (TIMER0_COMPA_vect){
	BUZZER_PORT ^=(1<<BUZZER_PIN);
}

typedef enum {
	startSTATE,
	fwdSTATE,
	leftSTATE,
	rightSTATE,
	megaLeftSTATE,
	megaRightSTATE
} State_t;

State_t actuar (State_t state,  uint16_t *value);

int main(void){	
	static State_t state = startSTATE;
	uint16_t value[5];
		
	setupWheels();
	ADC_Init_Single();
	Robot_STOP();
	TMR4_PWM_Phase_Start(DIV_CLK_64);
	sei();
	
	while(1){
		
		value[0] = ADC_Read_Single_Poll(ADC7D); //MEGAIZQ
		value[1] = ADC_Read_Single_Poll(ADC6D); //IZQ
		value[2] = ADC_Read_Single_Poll(ADC5D); //CENTRO
		value[3] = ADC_Read_Single_Poll(ADC4D); //DER
		value[4] = ADC_Read_Single_Poll(ADC1D); //MEGADER
		
		switch(state){
			case startSTATE:
				playSoundTIMERS (DURACION_SHORT, STARTING_SOUND);
			break;
			
			case fwdSTATE:
				Robot_FWD(~ROBOTSPEED, ROBOTSPEED);
			break;
			
			case rightSTATE:
				Robot_RIGHT(~ROBOTSPEED, ROBOTSPEED * 0.6);
			break;
			
			case leftSTATE:
				Robot_LEFT((~ROBOTSPEED) * 0.6, ROBOTSPEED);
			break;
			
			case megaRightSTATE:
				Robot_RIGHT(~ROBOTSPEED, 10);
			break;
			
			case megaLeftSTATE:
				Robot_LEFT(~10, ROBOTSPEED);
			break;
		}
		state = actuar(state, value);
	}
}

State_t actuar (State_t state, uint16_t *value) {
	if (value[0] <= BLACK) return megaLeftSTATE; //gira megaizq
	if (value[1] <= BLACK) return leftSTATE; //gira izq
	if (value[2] <= BLACK) return fwdSTATE;
	if (value[3] <= BLACK) return rightSTATE; //gira derch
	if (value[4] <= BLACK) return megaRightSTATE; //gira megader
	
	return state;
}
		
		
		