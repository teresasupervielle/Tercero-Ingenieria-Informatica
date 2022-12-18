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

void mainMenu();

int main(void) {
	USART0_Init (UBRR_VALUE);
	
	while(1){
		if (hayChar() == EstaEscrito)
			mainMenu();
	}
}

void mainMenu(){
	char c;
	USART0_putString("Escriba una letra: \n \r");
	c = USART0_getchar();
	switch(c){
		case 'a':
		USART0_putString("Esta presionando la letra a \n \r");
		break;
		case'b':
		USART0_putString("Esta presionando la letra b \n \r");
		break;
		case 'H':
		case 'h':
		USART0_putString("\f");
		mainMenu();
		break;
		default:
		USART0_putString("No se que letra esta presionando \n \r");
		break;
	}
}
