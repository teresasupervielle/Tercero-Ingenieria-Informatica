/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/

#ifndef FUNCTIONSGPIO_H_
#define FUNCTIONSGPIO_H_

#include "LED_BUTTON.h"

static bool read_input(uint8_t portGPIO, uint8_t pinNumber);

#endif /* LED_BUTTON_H_ */