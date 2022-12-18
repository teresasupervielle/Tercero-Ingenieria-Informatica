/*
 * P02_Ejercicio03.c
 *
 * Created: 22/02/2022 12:17:03
 * Author : DCE
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>
#include "PORTS.h"
#include "ADC.h"

int main(void) {
	configPorts();
	ADC_Init_Single();
	
	uint16_t adc = ADC_Read_Single_Poll(PORTC1);
	
	if (adc > 0 && adc < 255) GPIO_D_OUT |= (1 << LED_PIN_0);
	else { if (adc > 256 && adc < 512) GPIO_D_OUT |= (1 << LED_PIN_1);
		else { if (adc > 513 && adc < 768) GPIO_D_OUT |= (1 << LED_PIN_2);
				else  GPIO_D_OUT |= (1 << LED_PIN_3);
		}
	}
}