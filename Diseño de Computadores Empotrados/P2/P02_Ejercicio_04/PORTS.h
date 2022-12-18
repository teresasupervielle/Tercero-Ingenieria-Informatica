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
#define GPIO_PORT_MODE	DDRD
///Pin of port where the LED is connected. Configured as output.	
#define LED_PIN_MODE_3			DDD3
#define LED_PIN_MODE_2			DDD2
#define LED_PIN_MODE_1			DDD1
#define LED_PIN_MODE_0			DDD0

#define BUTTON_RPULLUP			PORTD7
///MCU port where the LED is connected. 
#define GPIO_OUT		PORTD	
#define GPIO_IN			PIND	
///Pin where the LED is connected.
#define LED_PIN_3		PORTD3
#define LED_PIN_2		PORTD2
#define LED_PIN_1		PORTD1
#define LED_PIN_0		PORTD0


#define BUTTON_PIN		PIND7


#endif /* PORTS_H_ */