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

