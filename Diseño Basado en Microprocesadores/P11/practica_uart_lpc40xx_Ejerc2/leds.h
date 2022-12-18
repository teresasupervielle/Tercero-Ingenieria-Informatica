/***************************************************************************//**
 * \file    leds.h
 *
 * \brief   Funciones para manejar cuatro de los LEDs de la tarjeta Embedded
 *          Artist LPC4088.
 *
 * Las conexiones entre dos de los LEDs de la tarjeta y el microcontrolador son
 * las siguientes:
 *
 *      P1[5]   --> LED4 (ROJO) 
 *      P0[14] 	--> LED3 (VERDE) 
 *      P0[13]  --> LED2 (VERDE)  
 *		P1[18]  -->	LED1 (VERDE) 
 *
 * Los LEDs son activos a nivel bajo: cuando uno de estos pines del
 * microcontrolador se pone a 1 el correspondiente LED se apaga y cuando se
 * pone a 0 el LED se enciende.
 */

#ifndef LEDS_H
#define LEDS_H

#include "tipos.h"

/*******************************************************************************
 * Constantes.
 */
#define LED1            1
#define LED2            2
#define LED3            3
#define LED4            4

#define LED_ON          TRUE
#define LED_ENCENDIDO   TRUE
#define LED_OFF         FALSE
#define LED_APAGADO     FALSE

/*******************************************************************************
 * Prototipos de funciones.
 */

void leds_inicializar(void);
void led_encender(int32_t numero_led);
void led_apagar(int32_t numero_led);
void led_invertir(int32_t numero_led);
void led_ajustar(int32_t numero_led, bool_t estado);

#endif  /* LEDS */
