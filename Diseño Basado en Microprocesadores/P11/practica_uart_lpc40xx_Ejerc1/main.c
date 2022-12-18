/***************************************************************************//**
 * \file    main.c
 * \brief   Función main para la práctica sobre UART.
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "joystick.h"
#include "leds.h"
#include "error.h"
#include "uart_lpc40xx.h"
#include "stdlib.h"
#include "stdio.h"

// main para el ejercicio 1.

int main(void)
{
	// Declaración de las variables necesarias.
    
 uint32_t joystick;
 char dato_uart;
    
 // Inicializar la pantalla LCD.
    
 glcd_inicializar();
    
 // Inicializar la UART0:
 // 9600 baudios, datos de 8 bits, sin paridad y un bit de stop
 // Usar el pin P0[2] para TxD y el pin P0[3] para RxD.
	
	uart_inicializar(UART0, UART_BAUDRATE_9600, UART_BITS_DATOS_8, UART_PARIDAD_NINGUNA, UART_BITS_STOP_1, PUERTO0, PIN2, PUERTO0, PIN3, NULL);
    
 // Inicializar los LEDs.
    
 leds_inicializar();
    
 // Dentro de un bucle "infinito" ...
    
	while (TRUE){
		joystick = leer_joystick(); // Leer el joystick.
	  switch(joystick){ 
			case JOYSTICK_ARRIBA:
					uart_transmitir_dato(UART0, 'A');
				break;	// Si está pulsado hacia arriba, enviar el carácter 'A' a través de la UART0.
    case JOYSTICK_ABAJO:
					uart_transmitir_dato(UART0, 'B');
				break;	// Si está pulsado hacia abajo, enviar el carácter 'B' a través de la UART0.
    case JOYSTICK_IZQUIERDA:
					uart_transmitir_dato(UART0, 'C');
				break;	// Si está pulsado hacia la izquierda, enviar el carácter 'I' a través de la UART0.
    case JOYSTICK_DERECHA:
					uart_transmitir_dato(UART0, 'D');
				break;	// Si está pulsado hacia la derecha, enviar el carácter 'D' a través de la UART0.
    }   
	
         
    // Si en este momento hay al menos un dato en el buffer de entrada de la UART0 (función uart_hay_dato_disponible).
          
    // Leer un dato de la UART0 (sacar un dato del buffer de entrada de la UART0).
    
		if (uart_hay_dato_disponible(UART0)){
			dato_uart = uart_leer_dato(UART0);
			glcd_printf ("Dato: %c", dato_uart);
			switch(dato_uart){
				case '1':
						led_invertir(LED1);
					break;	// Si el dato es el carácter '1' invertir el estado del LED1. */
				case '2':
						led_invertir(LED2);
					break;	// Si el dato es el carácter '2' invertir el estado del LED2. */
				case '3':
						led_invertir(LED3);
					break;	// Si el dato es el carácter '3' invertir el estado del LED3. */
				case '4':
						led_invertir(LED4);
					break;	// Si el dato es el carácter '4' invertir el estado del LED4. */
			}
		}
	}

}
