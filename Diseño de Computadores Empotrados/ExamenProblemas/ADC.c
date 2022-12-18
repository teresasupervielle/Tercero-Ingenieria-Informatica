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
