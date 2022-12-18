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
#define GPIO_D_MODE		DDRD
///Pin where every LED is connected.
#define LED_PIN_0			PORTD4
#define LED_PIN_1			PORTD5
#define LED_PIN_2			PORTD6
#define LED_PIN_3			PORTD7
///MCU port where the LED is connected.
#define GPIO_D_OUT		PORTD
///MCU port where the PUSHBUTTON is connected.
#define GPIO_D_IN		PIND
///Pin where the BUTTON is connected.
#define BUTTON_PIN		PIND2
///Pull-up for PUSHBUTTON
#define BUTTON_RPULLUP	PORTD2
//ADC
#define ADC_OUT PINC
#define ADC_PORT PORTC1

/**---------  FUNCTIONS -------------------------*/
/// Pin and ports configuration function.
static inline void configPorts(void){
	/// 1) LED as output
	GPIO_D_MODE |= (1<<LED_PIN_0);
	GPIO_D_MODE |= (1<<LED_PIN_1);
	GPIO_D_MODE |= (1<<LED_PIN_2);
	GPIO_D_MODE |= (1<<LED_PIN_3);
	/// 2) Enable Pull-up for Pushbutton
	//GPIO_D_OUT	|= (1<<BUTTON_RPULLUP);
	DDRC &= ~(1 << ADC_PORT);
}

#endif /* PORTS_H_ */