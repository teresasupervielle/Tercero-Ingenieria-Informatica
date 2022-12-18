/***************************************************************************//**
 * \file    leds.c
 *
 * \brief   Funciones para manejar cuatro de los LEDs de la tarjeta Embedded
 *          Artist LPC4088.
 *
 * Las conexiones entre dos de los LEDs de la tarjeta y el microcontrolador son
 * las siguientes:
 *
 *      P1[5]   --> LED1 (ROJO)
 *      P0[14] 	--> LED2 (VERDE)
 *      P0[13]  --> LED3 (VERDE)
 *		P1[18]  -->	LED4 (VERDE)
 *
 * Los LEDs son activos a nivel bajo: cuando uno de estos pines del
 * microcontrolador se pone a 1 el correspondiente LED se apaga y cuando se
 * pone a 0 el LED se enciende.
 */

#include <LPC407x_8x_177x_8x.h>
#include "leds.h"
#include "gpio_lpc40xx.h"
#include "error.h"

/***************************************************************************//**
 * \brief   Configurar como salidas los pines del microcontrolador que están
 *          conectados a los LEDs y apagar todos los LEDs.
 */
void leds_inicializar(void)
{
    /* C O M P L E T A R
     */
	  int32_t i;
	
		LPC_GPIO1->DIR |= (1 << 5); //configura el P1[5] como salida (DIR a 1)
	  LPC_GPIO1->DIR |= (1 << 18); //configura el P1[18] como salida (DIR a 1)
		LPC_GPIO0->DIR |= (1 << 14); //configura el P0[14] como salida (DIR a 1)
	  LPC_GPIO0->DIR |= (1 << 13); //configura el P0[13] como salida (DIR a 1)

		
		for(i=1;i<=4;i++) led_ajustar(i, FALSE);
	
}

/***************************************************************************//**
 * \brief       Encender un LED.
 *
 * \param[in]   numero_led  número del LED a encender. Debe estar entre 1 y 4.
 */
void led_encender(int32_t numero_led)
{
    /* C O M P L E T A R
     */
	  led_ajustar(numero_led, TRUE);
}

/***************************************************************************//**
 * \brief       Apagar un LED.
 *
 * \param[in]   numero_led  número del LED a apagar. Debe estar entre 1 y 4.
 */
void led_apagar(int32_t numero_led)
{
    /* C O M P L E T A R
     */
	  led_ajustar(numero_led, FALSE);
}

/***************************************************************************//**
 * \brief       Invertir el estado de un LED.
 *
 * \param[in]   numero_led  número del LED a invertir. Debe estar entre 1 y 4.
 */
void led_invertir(int32_t numero_led)
{
    /* C O M P L E T A R
     */
	  switch(numero_led) {
			case LED1:
				if(LPC_GPIO1->PIN & (1 << 5))  //si el pin está a 1 (apagado)
					led_ajustar(numero_led, TRUE); //lo enciendo
				else
					led_ajustar(numero_led, FALSE); //lo apago
				break;
			case LED2:
				if(LPC_GPIO1->PIN & (1 << 18))  //si el pin está a 1 (apagado)
					led_ajustar(numero_led, TRUE); //lo enciendo
				else
					led_ajustar(numero_led, FALSE); //lo apago
				break;
			case LED3:				
				if(LPC_GPIO0->PIN & (1 << 14))  //si el pin está a 1 (apagado)
					led_ajustar(numero_led, TRUE); //lo enciendo
				else
					led_ajustar(numero_led, FALSE); //lo apago
				break;
			case LED4:
				if(LPC_GPIO0->PIN & (1 << 13))  //si el pin está a 1 (apagado)
					led_ajustar(numero_led, TRUE); //lo enciendo
				else
					led_ajustar(numero_led, FALSE); //lo apago
				break;
		}
}

/***************************************************************************//**
 * \brief       Ajustar el estado de una LED
 *
 * \param[in]   numero_led  número del LED a ajustar. Debe estar entre 1 y 4.
 * \param[in]   estado      estado que debe adoptar el LED. TRUE => encendido
 *                          FALSE => apagado.
 */
void led_ajustar(int32_t numero_led, bool_t estado)
{
    /* C O M P L E T A R
     */
				  	
		switch(numero_led) {
			case LED1:
				if(estado) LPC_GPIO1->PIN &= ~(1 << 5); //si encender, pongo el PIN a 0
				else LPC_GPIO1->PIN |= (1 << 5); //si apagar, pongo el PIN a 1
				break;
			case LED2:
				if(estado) LPC_GPIO1->PIN &= ~(1 << 18); 
				else LPC_GPIO1->PIN |= (1 << 18);
				break;
			case LED3:
				if(estado) LPC_GPIO0->PIN &= ~(1 << 14); 
				else LPC_GPIO0->PIN |= (1 << 14);
				break;
			case LED4:
				if(estado) LPC_GPIO0->PIN &= ~(1 << 13); 
				else LPC_GPIO0->PIN |= (1 << 13);
				break;
		}
}
