/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Ejemplo de uso de interrupciones que usa la interrupción del timer 0
 *          para mostrar un cronómetro con horas, minutos y segundos.
 */

#include <LPC407x_8x_177x_8x.h>
#include <stdio.h>
#include "tipos.h"
#include "glcd.h"
#include "timer_lpc40xx.h"
#include "joystick.h"
#include "leds.h"

/* Los nombres de los registros de las interrupciones de los pines de los
 * puertos P0 y P2 del fichero LPC407x_8x_177x_8x.h no están actualizados
 * a la última versión del manual del microcontrolador.
 *
 * Aquí se redefinen de forma que coincidan con el manual.
 */

typedef struct
{
    __I  uint32_t STATUS;
    __I  uint32_t STATR0;
    __I  uint32_t STATF0;
    __O  uint32_t CLR0;
    __IO uint32_t ENR0;
    __IO uint32_t ENF0;
       uint32_t RESERVED0[3];
    __I  uint32_t STATR2;
    __I  uint32_t STATF2;
    __O  uint32_t CLR2;
    __IO uint32_t ENR2;
    __IO uint32_t ENF2;
} LPC_GPIOINT_TypeDef_corregido;

#undef  LPC_GPIOINT
#define LPC_GPIOINT ((LPC_GPIOINT_TypeDef_corregido   *) LPC_GPIOINT_BASE  )

// Variables globales para mantener el tiempo.

int main(void)
{
    // Inicializar el LCD.
     
    glcd_inicializar();   
    	
	  // Borrar peticiones de interrupción del timer 0 pendientes.		

		NVIC_ClearPendingIRQ(TIMER0_IRQn);		
	
    // Asignar prioridad 1 a la interrupción del timer 0.
     
    NVIC_SetPriority(TIMER0_IRQn, 1);  

    // Habilitar la interrupción del timer 0.
     
    NVIC_EnableIRQ(TIMER0_IRQn);

    // Habilitar globalmente las interrupciones.
     
		 NVIC_ClearPendingIRQ(GPIO_IRQn);
		 NVIC_SetPriority(GPIO_IRQn, 0); 
		 NVIC_EnableIRQ(GPIO_IRQn);
		 
		 LPC_GPIOINT->CLR2 = (1 << 27)|(1 << 25);
		 LPC_GPIOINT->ENF2 = (1 << 27)|(1 << 25);
    __enable_irq();
                 
    // Inicializar el timer 0.
     
    timer_inicializar(TIMER0);
    
    // Iniciar la generación de ciclos de 1 segundo con el timer 0. (función timer_iniciar_ciclos_ms de la práctica anterior).
		
    timer_iniciar_ciclos_ms(TIMER0, 1000);
    
    // Imprimir el reloj por primera vez.
     
    glcd_xprintf(0, 0, WHITE, BLACK, FONT16X32, "%00:%00:%00");

    // Inicializar los LEDs.
	
    leds_inicializar();
   
    while (TRUE)
    {
        // Si el joystick se pulsa hacia el centro, encender el LED 1, si no, apagarlo.
         
			if(leer_joystick() == JOYSTICK_CENTRO){
				led_encender(1);
			} else {
				led_apagar(1);
			}
		}
	}
/***************************************************************************//**
 * \brief   Rutina de servicio de interrupción del timer 0.
 */
void TIMER0_IRQHandler(void)
{
		static uint32_t horas = 0;
		static uint32_t minutos = 0;
		static uint32_t segundos = 0;
		LPC_TIM0->IR = 1;
    NVIC_ClearPendingIRQ(TIMER0_IRQn);
		segundos++;
		  if (segundos == 60){
				segundos = 0;
				minutos++;
				if(minutos == 60){
					minutos = 0;
					horas++;
					if(horas == 24) horas = 0;
				}
			}
			glcd_xprintf(0, 0, NEGRO, BLANCO, FONT12X24, "%02d:%02d:%02d", horas, minutos, segundos);
}

/***************************************************************************//**
 * \brief   Manejador de interrupción de las interrupciones de los pines
 *          de los puertos P0 y P2.
 */
/*******************************************************************************
 * PARA EL EJERCICIO 2. NO ES NECESARIO COMPLETAR PARA EL EJERCICIO 1.
 */

void GPIO_IRQHandler(void)
{
	NVIC_ClearPendingIRQ(GPIO_IRQn);
	if (LPC_GPIOINT->STATF2 & (1 << 25)){ //ARRIBA
		LPC_GPIOINT->CLR2 = 1 << 25;
		TIMER0->TCR = 1;
	}if (LPC_GPIOINT->STATF2 & (1 << 27)){ //ABAJO
		 LPC_GPIOINT->CLR2 = 1 << 27;
		 TIMER0->TCR = 0;
	}
}
