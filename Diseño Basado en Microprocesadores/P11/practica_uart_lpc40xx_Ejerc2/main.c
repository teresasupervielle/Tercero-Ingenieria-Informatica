/***************************************************************************//**
 * \file    main.c
 * \brief   Funci�n main para la pr�ctica sobre UART.
 */
#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "joystick.h"
#include "leds.h"
#include "error.h"
#include "uart_lpc40xx.h"
#include "stdlib.h"
#include "stdio.h"

// main para el ejercicio 2.

int main(void)
{ 
	// Declaraci�n de las variables necesarias.
    
  uint32_t sumando1, sumando2, suma;
	char buffer[15];
	
  // Inicializar la pantalla LCD.
    
  glcd_inicializar();
    
  // Inicializar la UART0:
  // 9600 baudios, datos de 8 bits, sin paridad y un bit de stop.
  // Usar el pin P0[2] para TxD y el pin P0[3] para RxD.
    
  uart_inicializar(UART0, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);
    
  // Dentro de un bucle "infinito" ...
    
		while(TRUE){
   
     // Enviar a trav�s de la UART0 un mensaje que indique al usuario que
     // debe introducir el primer n�mero entero a sumar
     // (funci�n uart_transmitir_cadena)
        
     uart_transmitir_cadena (UART0, "\nIntroduzca el primer sumando:");
    
     // Recibir una cadena de caracteres a trav�s de la UART0
     // (funci�n uart_recibir_cadena).
        
     uart_recibir_cadena (UART0, buffer, 15);
        
     // Convertir la cadena de caracteres recibida a un valor entero
     // mediante la funci�n atoi y guardar el resultado en una variable.
			
			sumando1 = atoi(buffer);
        
     // Enviar a trav�s de la UART0 un mensaje que indique al usuario que
     // debe introducir el segundo n�mero entero a sumar.
        
      uart_transmitir_cadena (UART0, "\nIntroduzca el segundo sumando:");
    
     // Recibir una cadena de caracteres a trav�s de la UART0.
        
     uart_recibir_cadena (UART0, buffer, 15);
        
     // Convertir la cadena de caracteres recibida a un valor entero
     // y guardar el resultado en otra variable.
        
     sumando2 = atoi(buffer);
        
     // Sumar las variables que contienen los n�meros.
        
     suma = sumando1 + sumando2;
		 glcd_printf ("%d + %d = %d\n", sumando1, sumando2, suma);
		 
		 
     // Transformar el valor de la suma en una cadena de caracteres que la
     // represente en decimal mediante la funci�n snprintf.
      
			snprintf(buffer, 15, "\n Suma: %d", suma);
        
     // Transmitir a trav�s de la UART0 la cadena con el resultado.
        
    uart_transmitir_cadena (UART0, buffer);     
	}
}
  
    

