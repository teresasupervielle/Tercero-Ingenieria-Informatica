/***************************************************************************//**
 * \file    leds.c
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
 
#include <LPC407x_8x_177x_8x.h>
#include "leds.h"
#include "gpio_lpc40xx.h"
#include "error.h"

static LPC_GPIO_TypeDef * const puertos_leds[4] = {PUERTO1,
                                                   PUERTO0,
                                                   PUERTO0,
                                                   PUERTO1};

static const uint32_t mascaras_leds[4] = {PIN5, PIN14, PIN13, PIN18};                                                

/***************************************************************************//**
 * \brief   Configurar como salidas los pines del microcontrolador que están
 *          conectados a los LEDs y apagar todos los LEDs.
 */
void leds_inicializar(void)
{
//    LPC_GPIO0->DIR |= (1u << 13) | (1u << 14);
//    LPC_GPIO1->DIR |= (1u << 15) | (1u << 18);
//    LPC_GPIO0->SET = (1u << 13) | (1u << 14);
//    LPC_GPIO1->SET = (1u << 15) | (1u << 18);
    
    gpio_ajustar_dir(PUERTO0, PIN13 | PIN14, DIR_SALIDA);
    gpio_ajustar_dir(PUERTO1, PIN5 | PIN18, DIR_SALIDA);
    gpio_pin_a_1(PUERTO0, PIN13 | PIN14);
    gpio_pin_a_1(PUERTO1, PIN5 | PIN18);
}

/***************************************************************************//**
 * \brief       Encender un LED.
 *
 * \param[in]   numero_led  número del LED a encender. Debe estar entre 1 y 4.
 */
void led_encender(int32_t numero_led)
{ 
    /* Accediendo a los registros de los puertos.
     */
  
//    if (numero_led == LED1)
//    {
//        LPC_GPIO1->CLR = 1u << 5;
//    }
//    else if  (numero_led == LED2)
//    {
//        LPC_GPIO0->CLR = 1u << 14;
//    }
//    else if  (numero_led == LED3)
//    {
//        LPC_GPIO0->CLR = 1u << 13;
//    }
//    else if  (numero_led == LED4)
//    {
//        LPC_GPIO1->CLR = 1u << 18;
//    }
//    else
//    {
//        ERROR("Numero de LED incorrecto.");
//    }
 
    /* Usando las funciones de acceso a los puertos.
     */

//    if (numero_led == LED1)
//    {
//        gpio_pin_a_0(PUERTO1, PIN5);
//    }
//    else if  (numero_led == LED2)
//    {
//        gpio_pin_a_0(PUERTO0, PIN14);
//    }
//    else if  (numero_led == LED3)
//    {
//        gpio_pin_a_0(PUERTO0, PIN13);
//    }
//    else if  (numero_led == LED4)
//    {
//        gpio_pin_a_0(PUERTO1, PIN18);
//    }
//    else
//    {
//        ERROR("Numero de LED incorrecto.");
//    }

    /* Evitando los if-else.
     */

    ASSERT(numero_led >= 1 && numero_led <= 4, "Numero de LED incorrecto.");
    gpio_pin_a_0(puertos_leds[numero_led - LED1],
                 mascaras_leds[numero_led - LED1]);        
}

/***************************************************************************//**
 * \brief       Apagar un LED.
 *
 * \param[in]   numero_led  número del LED a apagar. Debe estar entre 1 y 4.
 */
void led_apagar(int32_t numero_led)
{
    /* Accediendo a los registros de los puertos.
     */
    
//    if (numero_led == LED1)
//    {
//        LPC_GPIO1->SET = 1u << 5;
//    }
//    else if  (numero_led == LED2)
//    {
//        LPC_GPIO0->SET = 1u << 14;
//    }
//    else if  (numero_led == LED3)
//    {
//        LPC_GPIO0->SET = 1u << 13;
//    }
//    else if  (numero_led == LED4)
//    {
//        LPC_GPIO1->SET = 1u << 18;
//    }
//    else
//    {
//        ERROR("Numero de LED incorrecto.");
//    }

    /* Usando las funciones de acceso a los puertos.
     */
     
//    if (numero_led == LED1)
//    {
//        gpio_pin_a_1(PUERTO1, PIN5);
//    }
//    else if  (numero_led == LED2)
//    {
//        gpio_pin_a_1(PUERTO0, PIN14);
//    }
//    else if  (numero_led == LED3)
//    {
//        gpio_pin_a_1(PUERTO0, PIN13);
//    }
//    else if  (numero_led == LED4)
//    {
//        gpio_pin_a_1(PUERTO1, PIN18);
//    }
//    else
//    {
//        ERROR("Numero de LED incorrecto.");
//    }

    /* Evitando los if-else.
     */

    ASSERT(numero_led >= 1 && numero_led <= 4, "Numero de LED incorrecto.");
    gpio_pin_a_1(puertos_leds[numero_led - LED1],
                 mascaras_leds[numero_led - LED1]);    
}

/***************************************************************************//**
 * \brief       Invertir el estado de un LED.
 *
 * \param[in]   numero_led  número del LED a invertir. Debe estar entre 1 y 4.
 */
void led_invertir(int32_t numero_led)
{
    
    /* Accediendo a los registros de los puertos.
     */
    
//    if (numero_led == LED1)
//    {
//        LPC_GPIO1->PIN ^= 1u << 5;
//    }
//    else if  (numero_led == LED2)
//    {
//        LPC_GPIO0->PIN ^= 1u << 14;
//    }
//    else if  (numero_led == LED3)
//    {
//        LPC_GPIO0->PIN ^= 1u << 13;
//    }
//    else if  (numero_led == LED4)
//    {
//        LPC_GPIO1->PIN ^= 1u << 18;
//    }
//    else
//    {
//        ERROR("Numero de LED incorrecto.");
//    }

//    /* Usando las funciones de acceso a los puertos.
//     */
//     
//    if (numero_led == LED1)
//    {
//        gpio_invertir_pin(PUERTO1, PIN5);
//    }
//    else if  (numero_led == LED2)
//    {
//        gpio_invertir_pin(PUERTO0, PIN14);
//    }
//    else if  (numero_led == LED3)
//    {
//        gpio_invertir_pin(PUERTO0, PIN13);
//    }
//    else if  (numero_led == LED4)
//    {
//        gpio_invertir_pin(PUERTO1, PIN18);
//    }
//    else
//    {
//        ERROR("Numero de LED incorrecto.");
//    }

    /* Evitando los if-else.
     */

    ASSERT(numero_led >= 1 && numero_led <= 4, "Numero de LED incorrecto.");
    gpio_invertir_pin(puertos_leds[numero_led - LED1],
                      mascaras_leds[numero_led - LED1]);  
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
//    if (estado)
//    {
//        led_encender(numero_led);
//    }
//    else
//    {
//        led_apagar(numero_led);
//    }
    
    ASSERT(numero_led >= 1 && numero_led <= 4, "Numero de LED incorrecto.");
    gpio_escribir_pin(puertos_leds[numero_led - LED1],
                      mascaras_leds[numero_led - LED1],
                      !estado);  
}
