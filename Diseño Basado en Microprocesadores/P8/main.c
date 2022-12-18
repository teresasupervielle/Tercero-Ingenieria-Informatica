/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Función main para la práctica sobre los timers.
 */

#include <LPC407x_8x_177x_8x.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpio_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "glcd.h"
#include "joystick.h"
#include "leds.h"

/*******************************************************************************
 * Función main para el ejericio 1.
 */
/*int main(void)
{
    uint32_t horas = 0, minutos = 0, segundos = 0;
    
    // Inicializar la pantalla LCD.
    
    glcd_inicializar();

    // Inicializar el timer 0.

    timer_inicializar(TIMER0);
    
    while (TRUE)
    {
        // Imprimir el cronometro en la coordenada (0, 0) de la pantalla.
        
			glcd_xprintf(0, 0, NEGRO, BLANCO, FONT12X24, "%02d:%02d:%02d", horas, minutos, segundos);
        
        // Realizar un retardo de 1 segundo.

			timer_retardo_ms(TIMER0, 1000);

        // Actualizar las variables segundos, minutos y horas.

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
	}
} */

/*******************************************************************************
 * Función main para el ejericio 2.
 */

/*int main(void)
{
    uint32_t horas = 0, minutos = 0, segundos = 0;
    
    // Inicializar la pantalla LCD.
     
    glcd_inicializar();

    // Inicializar el timer 0.
    
    timer_inicializar(TIMER0);
 
    // Configurar el timer 0 para que realice automáticamente ciclos de un segundo de duración (función timer_iniciar_ciclos_ms).
  
    timer_iniciar_ciclos_ms(TIMER0, 1000);
  
    while (TRUE)
    {
        // Imprimir el cronometro en la coordenada (0, 0) de la pantalla.
        
        glcd_xprintf(0, 0, NEGRO, BLANCO, FONT12X24, "%02d:%02d:%02d", horas, minutos, segundos);

        // Esperar a que finalice el ciclo de un segundo actual (función timer_esperar_fin_ciclo).

			  timer_esperar_fin_ciclo(TIMER0);

        // Actualizar las variables segundos, minutos y horas.
         
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
    }
}*/

/*******************************************************************************/
 // Función main para el ejericio 3.
 
int main(void)
{
    uint32_t tiempo_aleatorio;
    uint32_t tiempo_reaccion;

    // Inicializar la pantalla LCD.    
	
    glcd_inicializar();

    // Inicializar el timer 0.
    
    timer_inicializar(TIMER0);
    
    while (TRUE)
    {
        // Borrar la pantalla rellenándola de color negro.
         
        glcd_borrar(NEGRO);
   
        // Imprimir "Pulsa abajo para comenzar" en el LCD.
        
        glcd_xprintf(0, 0, BLANCO, NEGRO, FONT12X24, "Pulsa abajo para comenzar");
			
        // Esperar hasta que el usuario pulse el joystick hacia abajo.
        
        while(leer_joystick() != JOYSTICK_ABAJO);

        // Borrar la pantalla rellenándola de color negro.
         
        glcd_borrar(NEGRO);

        // Imprimir "¡Preparado!" en el LCD.
         
        glcd_xprintf(0, 0, BLANCO, NEGRO, FONT12X24, "¡Preparado!"); 

        // Generar un número aleatorio entre 1000 y 5000.
         
        tiempo_aleatorio = 1000 + rand() % 4000;
				
        // Realizar un retardo de un número de milisegundos igual al número aleatorio generado.
           
				timer_retardo_ms(TIMER0, tiempo_aleatorio);
        
        // Borrar la pantalla rellenándola de color rojo.
                  
        glcd_borrar(ROJO);
     
        // Hacer que el timer 0 empiece a contar el transcurso del tiempo en unidades de milisegundos.
                  
				timer_iniciar_conteo_ms(TIMER0);
				
        // Esperar a que usuario pulse el joystick hacia el centro.
         
        while(leer_joystick() != JOYSTICK_CENTRO);

        // Leer el valor del registro contador del timer 0. El valor obtenido es el tiempo en milisegundos entre el momento en que la pantalla cambia a color rojo y el instante en el que el usuario pulsa el joystick hacia el centro = tiempo de reacción.
         
				tiempo_reaccion = timer_leer(TIMER0);
				
				// Imprimir en pantalla el tiempo de reacción
				
        glcd_xprintf(0, 0, NEGRO, BLANCO, FONT12X24, "Tiempo de reaccion: %d", tiempo_reaccion);
         
        // Hacer un retardo de 5 segundos para que el usuario tenga tiempo de leer su tiempo de reacción antes de empezar otro test.
        
				timer_retardo_ms(TIMER0, 5000);				
    }    
}
