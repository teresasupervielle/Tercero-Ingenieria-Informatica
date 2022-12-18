/*
 * P02_Ejercicio03.c
 *
 * Created: 22/02/2022 12:17:03
 * Author : DCE
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "USART.h"

#define UBRR_VALUE ((F_CPU/(16UL*BAUD))-1)

int main(void) {
	char c;
	USART0_Init (UBRR_VALUE);
	
	while(1){
		c = USART0_getchar();
		USART0_putchar(c);
		USART0_putString("\n \r");
	}
}