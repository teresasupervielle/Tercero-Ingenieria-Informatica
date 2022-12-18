/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/


#ifndef PORTS_H_
#define PORTS_H_
///MCU Port where the LED is connected. Mode Configuration register.
#define LED_PORT_MODE	DDRD
///Pin of port where the LED is connected. Configured as output.	
#define LED_PIN_MODE		DDD3
///MCU port where the LED is connected. 
#define LED_PORT		PORTD	
///Pin where the LED is connected.
#define LED_PIN		PORTD3


#endif /* PORTS_H_ */