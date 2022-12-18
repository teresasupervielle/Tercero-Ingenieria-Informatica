/**
	@file		PORTS.h
	@author		Mirian Cifredo
	@date		23/12/2021
    @brief		Header file describing the name of the ports for this project.
    @par		Description 
				Allow modify the pin with the LED connected easily.
				For other MCU only this header file will need be modified.
*/

#ifndef USART_H_
#define USART_H_

#include <avr/io.h>

/*Parametros*/
#define F_CPU 16000000UL
#define BAUD 9600
#define UBRR_VALUE ((F_CPU/(16UL*BAUD))-1)

/*Funciones*/
void USART0_putchar (unsigned char data);
void USART0_putString (char *strPointer);
char USART0_getchar (void);

static inline void USART0_Init (uint16_t value){
	//Set BAUD rate
	UBRR0H = (unsigned char) (value >> 8);
	UBRR0L = (unsigned char) value;
	
	//Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	//Set the speed: normal asynchronous
	
	//Set frame format: 8 data, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
}

#endif /* LED_BUTTON_H_ */