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
#define BUZZER_PORT_MODE	DDRB
///MCU port where the LED is connected. 
#define BUZZER_PORT		PORTB	
///Pin where the LED is connected.
#define BUZZER_PIN		PORTB2


#endif /* PORTS_H_ */