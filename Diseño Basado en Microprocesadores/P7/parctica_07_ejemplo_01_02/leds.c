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
    LPC_GPIO0->DIR |= (1<<14) | (1<<13);  //Escribimos en dir para encender (ponemos un niver bajo) el led
		LPC_GPIO1->DIR |= (1<<5) | (1<<18); 
		LPC_GPIO0->SET = (1<<14) | (1<<13); //Escribimos set para asegurarnos de que esta apagado (ponemso nivel alto)
		LPC_GPIO1->SET = (1<<5) | (1<<18); 
}

/***************************************************************************//**
 * \brief       Encender un LED.
 *
 * \param[in]   numero_led  número del LED a encender. Debe estar entre 1 y 4.
 */
void led_encender(int32_t numero_led)
{
    switch(numero_led)
		{
			case LED1: 
				LPC_GPIO1->CLR = (1<<5);	//Para encender escribimos un 1 en clr para poner el pin a nivel bajo
				break;
			case LED2:
				LPC_GPIO0->CLR = (1<<14);
				break;
			case LED3:
				LPC_GPIO0->CLR = (1<<13);
				break;
			case LED4:
				LPC_GPIO1->CLR = (1<<18);
				break;
		}
}

/***************************************************************************//**
 * \brief       Apagar un LED.
 *
 * \param[in]   numero_led  número del LED a apagar. Debe estar entre 1 y 4.
 */
void led_apagar(int32_t numero_led)
{
    switch(numero_led)
		{
			case LED1: 
				LPC_GPIO1->SET = (1<<5);	//Para apagar escribimos un 1 en set para poner el pin a nivel alto
				break;
			case LED2:
				LPC_GPIO0->SET = (1<<14);
				break;
			case LED3:
				LPC_GPIO0->SET = (1<<13);
				break;
			case LED4:
				LPC_GPIO1->SET = (1<<18);
				break;
		}
}

/***************************************************************************//**
 * \brief       Invertir el estado de un LED.
 *
 * \param[in]   numero_led  número del LED a invertir. Debe estar entre 1 y 4.
 */
void led_invertir(int32_t numero_led)
{
    switch(numero_led)
		{
			case LED1: 
				if(LPC_GPIO1->PIN & (1<<5))	//Si !=0 ==true -> entra en el if pin apagado -> lo enciende
					LPC_GPIO1->CLR = (1<<5);
				else
					LPC_GPIO1->SET = (1<<5);	//Si ==0 ==false -> entra en el else pin encendido -> lo apaga
				break;
			case LED2:
			  if(LPC_GPIO0->PIN & (1<<14))	//Si !=0 ==true -> entra en el if pin apagado -> lo enciende
					LPC_GPIO0->CLR = (1<<14);
				else
					LPC_GPIO0->SET = (1<<14);	//Si ==0 ==false -> entra en el else pin encendido -> lo apaga
				break;
			case LED3:
				if(LPC_GPIO0->PIN & (1<<13))	//Si !=0 ==true -> entra en el if pin apagado -> lo enciende
					LPC_GPIO0->CLR = (1<<13);
				else
					LPC_GPIO0->SET = (1<<13);	//Si ==0 ==false -> entra en el else pin encendido -> lo apaga
				break;
			case LED4:
				if(LPC_GPIO1->PIN & (1<<18))	//Si !=0 ==true -> entra en el if pin apagado -> lo enciende
					LPC_GPIO1->CLR = (1<<18);
				else
					LPC_GPIO1->SET = (1<<18);	//Si ==0 ==false -> entra en el else pin encendido -> lo apaga
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
    switch(numero_led)
		{
			case LED1: 
				if(estado)							//Si estado == 1 lo enciende sino lo apaga
					LPC_GPIO1->CLR = (1<<5);
				else
					LPC_GPIO1->SET = (1<<5);	
				break;
			case LED2:
			  if(estado)							//Si estado == 1 lo enciende sino lo apaga
					LPC_GPIO0->CLR = (1<<14);
				else
					LPC_GPIO0->SET = (1<<14);	
				break;
			case LED3:
				if(estado)							//Si estado == 1 lo enciende sino lo apaga
					LPC_GPIO0->CLR = (1<<13);
				else
					LPC_GPIO0->SET = (1<<13);	
				break;
			case LED4:
				if(estado)							//Si estado == 1 lo enciende sino lo apaga
					LPC_GPIO1->CLR = (1<<18);
				else
					LPC_GPIO1->SET = (1<<18);	
				break;
		}
}
