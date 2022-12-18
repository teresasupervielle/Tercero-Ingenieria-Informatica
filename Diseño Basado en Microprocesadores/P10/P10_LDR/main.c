/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Función main para la práctica 8.
 */

#include <LPC407x_8x_177x_8x.h>
#include <stdlib.h>
#include <string.h>
#include "glcd.h"
#include "adc_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "ldr.h"
#include "leds.h"
#include "teclado_4x4.h"
#include "sonido.h"


//EJERCICIO 1

/*
int main(void)
{
  //Variables
	
	uint32_t conversion;
	float32_t tension;
	float32_t iluminancia;
	
	//Inicializacion de los preifericos
	
	adc_inicializar(1000000, SEL_CANAL_0);
	glcd_inicializar();
	timer_inicializar(TIMER0);
	timer_iniciar_ciclos_ms(TIMER0, 1000);
	
	while(TRUE){
		conversion = adc_convertir(0);
		tension = adc_traducir_a_tension(conversion);
		iluminancia = ldr_traducir_a_iluminancia(tension);
		
		glcd_xy_texto( 0, 0);
		glcd_printf("Iluminancia: %9.2f", iluminancia);
		timer_esperar_fin_ciclo(TIMER0);
	}
}
*/

//EJERCICIO 2

int main(void)
{
  //Variables
	
	uint32_t conversion;
	float32_t tension;
	float32_t iluminancia;
	
	//Inicializacion de los preifericos
	
	adc_inicializar(1000000, SEL_CANAL_0);
	glcd_inicializar();
	timer_inicializar(TIMER0);
	timer_iniciar_ciclos_ms(TIMER0, 1000);
	
	while(TRUE){
		conversion = adc_convertir(0);
		tension = adc_traducir_a_tension(conversion);
		iluminancia = ldr_traducir_a_iluminancia(tension);
		
		glcd_xy_texto( 0, 0);
		glcd_printf("Iluminancia: %9.2f", iluminancia);
		if (iluminancia < 100){
			sonido_emitir_pitido (1000, 100);
		}
		timer_esperar_fin_ciclo(TIMER0);
	}
}
