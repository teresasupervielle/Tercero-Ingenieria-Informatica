/*
 * P02_Ejercicio03.c
 *
 * Created: 22/02/2022 12:17:03
 * Author : DCE
 */ 

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "PORTS.h"

#define BAUD 9600
#define UBRR_VALUE ((F_CPU / (16UL * BAUD)) - 1)

void USART0_putchar (unsigned char data)
{
	// 1.(Polling)Wait for empty transmit register
	while (!(UCSR0A & ( 1 << UDRE0)));
	// 2. Write “data” in register for sending a character
	UDR0 = data;
}

void USART0_putString (char *strPointer) {
	
	while (*strPointer){
		USART0_putchar(*strPointer);
		strPointer++;
	}
	
}

int main(void) {
	//Set BAUD rate
	UBRR0H = (unsigned char) (UBRR_VALUE >> 8);
	UBRR0L = (unsigned char) UBRR_VALUE;
	
	//Enable receiver and transmitter
	UCSR0B |= (1 << RXEN0) | (1 << TXEN0);
	
	//Set the speed: normal asynchronous
	
	//Set frame format: 8 data, 1 stop bit
	UCSR0C |= (1 << UCSZ01) | (1 << UCSZ00);
	
	while(1){
		USART0_putString("Hello world \n\r");
	}
}