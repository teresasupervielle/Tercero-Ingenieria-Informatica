/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/

#ifndef ADC_H_
#define ADC_H_
#include <avr/io.h>
// PArameters related to ADC -----------------------------------



//--------------- PROTOTYPES ---------------------------------------

uint16_t ADC_Read_Single_Poll(uint8_t channel);

//---------------- FUNCTIONS -----------------------------------------

static inline void ADC_Init_Single()	{
	//  0.- Delete a previous configuration
		 ADMUX = 0;
		 ADCSRA = 0;
	//  1.- Select Vref: AVcc --> (REFS1-0 = "01")	Aref --> (REFS1-0 = "00")
		ADMUX |= (1 << REFS0);
	//	2.- Select the aligment format for ADC register (10-bits):
	//			--> ALIGN_LEFT --> (ADLAR=1)  --> ALIGN_RIGHT --> (ADLAR=0)
		ADCSRA &= ~(1 << ADLAR);
	//  3.- Set pre-scaler  -->  Prescaler 16MHZ/128 = 125 KHz
		ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
	//  4.- Enable ADC (ADEN = '1')
	// 	(It could be an separated function if disable the aDC is desirable)
		ADCSRA |= (1 << ADEN);
	//  5.- Single Mode
	// 	(It could be an separated function if changing the ADC mode is desirable)
		ADCSRA |= (0 << ADATE);	
}

#endif /* PORTS_H_ */