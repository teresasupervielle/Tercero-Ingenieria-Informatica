/***************************************************************************//**
 * \file    joystick.c
 *
 * \brief   Función básica de lectura del joystick de la tarjeta Embedded
 *          Artist LPC4088.
 *
 * Las conexiones entre el joystick el microcontrolador son las siguientes:
 *
 *     	ARRIBA  	--> P2[25]
 *      ABAJO   	--> P2[27]
 *      IZQUIERDA	--> P2[23]
 *      DERECHA		--> P2[26]
 *      CENTRAL		--> P2[22]
 *
 *
 * Los pulsadores del joystick son activos a nivel bajo: cuando se pulsan ponen
 * el correspondiente pin del microcontrolador a 0 y cuando están sin pulsar
 * ponen el correspondiente pin a 1.
 */

#include <LPC407x_8x_177x_8x.h>
#include "joystick.h"
#include "gpio_lpc40xx.h"
#include "leds.h"
#include "tipos.h"

/***************************************************************************//**
 *
 * \brief   Leer el joystick y retornar un número diferente según la dirección
 *          que se esté pulsando.
 *
 * \return  0 si no se está pulsando ningúna dirección.
 *          1 si el joystick está pulsado hacia ARRIBA.
 *          2 si el joystick está pulsado hacia ABAJO.
 *          3 si el joystick está pulsado hacia la IZQUIERDA.
 *          4 si el joystick está pulsado hacia la DERECHA.
 *          5 si el joystick está pulsado hacia el CENTRO.
 */
int32_t leer_joystick(void)
{
    if(!(LPC_GPIO2->PIN & (1<<25)))	//Leemos pin -> si 1 en el puerto 25-> jostick llevado hacia arriba 
			return JOYSTICK_ARRIBA;
		
		if(!(LPC_GPIO2->PIN & (1<<27)))  //Leemos pin -> si 1 en el puerto 27-> jostick llevado hacia abajo 
			return JOYSTICK_ABAJO;
		
		if(!(LPC_GPIO2->PIN & (1<<23))) 	//Leemos pin -> si 1 en el puerto 23-> jostick llevado hacia izq 
			return JOYSTICK_IZQUIERDA;
		
		if(!(LPC_GPIO2->PIN & (1<<26)))		//Leemos pin -> si 1 en el puerto 26-> jostick llevado hacia der 
			return JOYSTICK_DERECHA;
		
		if(!(LPC_GPIO2->PIN & (1<<22)))	 //Leemos pin -> si 1 en el puerto 22-> jostick pulsado && encendemos leds
		{	
			led_encender(LED1);
			led_encender(LED2);
			led_encender(LED3);
			led_encender(LED4);
			return JOYSTICK_CENTRO;
		}
		//Si el led no esta pulsado apagamos los led (aseguramos que esten apagados)
		led_apagar(LED1);	
		led_apagar(LED2);	
		led_apagar(LED3);	
		led_apagar(LED4);	
		
		return JOYSTICK_NADA;	//Por si no se mueve el jostick
}
