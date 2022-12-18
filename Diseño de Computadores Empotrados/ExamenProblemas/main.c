#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "PORTS.h"
#include "ADC.h"
#include "USART.h"
#include "LED_BUTTON.h"
#include "functionsGPIO.h"
#include "PARAMETERS.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//Estados para la FSM
typedef enum {
	STATE_MODE,
	STATE_LDR,
	STATE_POT
} State_t;

//Prototipo de la funcion parpadeo
void parpadeo (void);

int main(void) {
	//Inicializaciones
	static State_t state		= STATE_MODE;
	static State_t Next_state	= STATE_MODE;
	
	bool readButton_MODE		= BUTTON_NOT_PRESSED; //Boton para el modo
	bool readButton_INTRO		= BUTTON_NOT_PRESSED; //Boton para el intro
	
	bool ESTADO = PRODUCTION; //Estado inicial con el que empieza el programa (varia entre PRODUCTION o CONFIGURATION)
	
	uint16_t ldr, pot; //Variables para almacenar los datos de la ldr y del pot
	char cad[4]; //Cadena auxiliar para usarla en la funcion putString
	
	//Configuraciones
	configPorts();
	ADC_Init_Single();
	USART0_Init (UBRR_VALUE);
	
	//Inicia el programa 3 parpadeos
	parpadeo();
	
	while(1) {
		//Leemos ambos botones
		readButton_MODE 	= READ_BUTTON (GPIO_D_IN, BUTTON_MODE_PIN);
		readButton_INTRO 	= READ_BUTTON (GPIO_D_IN, BUTTON_INTRO_PIN);
		switch (state) {
			
			//Primer estado
			case STATE_MODE:
				_delay_ms(SAMPLE_TIME); //Delay para que no este continuamente mostrando datos y se pueda leer
				utoa(SET_POINT, cad, 10); //Funcion que transforma los unsigned en char
				//Mostramos por la terminal usando Putty
				USART0_putString ("SET POINT value: ");
				USART0_putString (cad);
				USART0_putString ("\n \r");
				if (ESTADO == PRODUCTION) { //Esta en produccion
					LED_ON(GPIO_D_OUT,LED_MODE); //La led Mode debe estar continuamente encendida
					//Comprobar encendido bombilla
					if (ldr > SET_POINT)	//Si se encuentra superior al set point se iluminara (cuando este a oscuras)
						LED_ON(GPIO_D_OUT, BOMBILLA);
					else 					//Si no, permanecera apagada la bombilla
						LED_OFF(GPIO_D_OUT, BOMBILLA);
						
					//Cambios de estado
					if (readButton_MODE == BUTTON_PRESSED) {	//Si se presiona el boton Mode, pasara a configuracion
						ESTADO == CONFIGURATION;
						Next_state = STATE_POT;
					} else Next_state = STATE_LDR; //Si no, seguira en produccion, y se pasara al estado LDR
					
				} else { //Esta en configuracion
					LED_OFF(GPIO_D_OUT,LED_MODE); //La led Mode debe estar continuamente apagada
					SET_POINT = pot;	//Se ha cambiado el dato del Set Point por el recogido por el pot
					if (readButton_INTRO == BUTTON_PRESSED) {	//Si se presiona el boton Intro, pasara a produccion
						ESTADO == PRODUCTION;
						Next_state = STATE_LDR;
					} else Next_state = STATE_POT;	//Si no, seguira en configuracion, y se pasara al estado POT
				}
			break;
			
			//Segundo estado
			case STATE_LDR:
				_delay_ms(SAMPLE_TIME); //Delay para que no este continuamente mostrando datos y se pueda leer
				ldr = ADC_Read_Single_Poll(2); //Se lee el dato del puerto A2 (LDR)
				utoa(ldr, cad, 10); //Funcion que transforma los unsigned en char
				//Mostramos por la terminal usando Putty
				USART0_putString ("LDR value: ");
				USART0_putString (cad);
				USART0_putString ("\n \r");
				ESTADO = PRODUCTION; //Pasamos al estado produccion
				Next_state = STATE_MODE; //Volvemos al estado de modo
			break;
			
			//Tercer estado
			case STATE_POT:
				_delay_ms(SAMPLE_TIME); //Delay para que no este continuamente mostrando datos y se pueda leer
				pot = ADC_Read_Single_Poll(1); //Se lee el dato del puerto A1 (POT)
				utoa(pot, cad, 10); //Funcion que transforma los unsigned en char
				USART0_putString ("POT value: ");
				USART0_putString (cad);
				USART0_putString ("\n \r");
				//Mostramos por la terminal usando Putty
				ESTADO = CONFIGURATION; //Pasamos al estado configuracion
				Next_state = STATE_MODE; //Volvemos al estado de modo
			break;
			
			//Estado default
			default:
				Next_state = STATE_MODE;
			break;
		}
		state = Next_state;
	}
}

//Funcion 3 parpadeos
void parpadeo (void) {
	GPIO_D_OUT &= ~ ( 1 << LED_MODE);
	_delay_ms(BLINK_TIME);
	GPIO_D_OUT |=(1 << LED_MODE);
	_delay_ms(BLINK_TIME);
	GPIO_D_OUT &= ~ ( 1 << LED_MODE);
	_delay_ms(BLINK_TIME);
	GPIO_D_OUT |=(1 << LED_MODE);
	_delay_ms(BLINK_TIME);
	GPIO_D_OUT &= ~ ( 1 << LED_MODE);
	_delay_ms(BLINK_TIME);
	GPIO_D_OUT |=(1 << LED_MODE);
}
