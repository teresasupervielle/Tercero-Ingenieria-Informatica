/**
	@file		main_noBlocking.c
	@author		Mirian Cifredo
	@date		10/02/2022
    @brief		Toggle a LED by means a pushbutton
    @par		Description 
				Allow toggle a LED every time a pushbutton is pressed.
				In order to avoid a bouncing in the pushbutton, the system waits for a time
				until the state of the pushbutton is stable.
*/
/// Define CPU frequency as 16 MHz 
#include "USART.h" 


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

char USART0_getchar (void)
{
	// 1.(Polling)Wait for empty transmit register
	while (!(UCSR0A & ( 1 << RXC0)));
	// 2. Write “data” in register for sending a character
	return UDR0;
}

