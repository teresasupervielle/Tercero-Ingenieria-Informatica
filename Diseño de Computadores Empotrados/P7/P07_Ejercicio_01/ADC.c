/**
	@file		main_noBlocking.c
	@author		Mirian Cifredo
	@date		10/02/2022
    @brief		Toggle a LED by means a pushbutton
    @par		Description 
				Allow toggle a LED every time a pushbutton is pressed.
				In order to avoid a bouncing in the pushbutton, the system waits for a time
				until the state of the pushbutton is stable.
*/

#include "ADC.h"
//----------------------------------------------------------------------
uint16_t ADC_Read_Single_Poll(uint8_t channel){
	// 1. Clear the flag asserted in a previous readout
		ADCSRA |= (1 << ADIF);
	// 2. Clear the channel to set a new one
		ADMUX &= ~((1 << MUX3) | (1 << MUX2) | (1 << MUX1) | (1 << MUX0));
	// 3. Set the channel
		ADMUX |= channel;
	// 4. Start a conversion for the selected channel
		ADCSRA |= (1 << ADSC);
	// 5. Wait the sample is read. (Polling the flag)
		while (ADCSRA & (1 << ADIF));
	// 6. Return the 10-bit sample read in the ADC.
		return ADC;
}
