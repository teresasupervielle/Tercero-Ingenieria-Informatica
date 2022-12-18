/***************************************************************************//**
 * \file    main.c
 *
 * \brief   Función main para la práctica 10.
 */

#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "adc_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "termistor_ntc.h"

//EJERCICIO 1

/*
int main(void)
{
	//Variables
	
	uint32_t conversion;
	float32_t tension;
	
	//Inicializador de periféricos
	
	adc_inicializar(1000000, SEL_CANAL_2); //El conversor
	glcd_inicializar(); //La pantalla LCD
	timer_inicializar(TIMER0); //El timer
	
	timer_iniciar_ciclos_ms (TIMER0, 1000); //Iniciamos el timer
	
	while (TRUE){
		conversion = adc_convertir(2);
		tension = adc_traducir_a_tension(conversion);
		
		glcd_xy_texto (0 , 0);
		glcd_printf("Resultado ADC:\t%d\n", conversion);
		glcd_printf("Tension potenciometro:\t%0.4f\n", tension);
		timer_esperar_fin_ciclo(TIMER0);
	}
}
*/

//EJERCICIO 2

/*
int main(void)
{
	//Variables
	
	uint32_t conversion;
	float32_t tension;
	float32_t temperatura;
	
	//Inicializador de periféricos
	
	adc_inicializar(1000000, SEL_CANAL_0); //El conversor
	glcd_inicializar(); //La pantalla LCD
	timer_inicializar(TIMER0); //El timer
	
	timer_iniciar_ciclos_ms (TIMER0, 1000); //Iniciamos el timer
	
	while(TRUE){
		conversion = adc_convertir(0);
		tension = adc_traducir_a_tension(conversion);
		temperatura = ntc_traducir_tension_a_temperatura(tension);
		
		glcd_xy_texto (0 , 0);
		glcd_printf("Resultado ADC:\t%d\n", conversion);
		glcd_printf("Tension potenciometro:\t%0.4f\n", tension);
		glcd_printf("Temperatura:\t%4.1f\n", temperatura);
		timer_esperar_fin_ciclo(TIMER0);
	}	
}
*/

//EJERCICO 3

int main(void)
{
	//Variables
	
	uint32_t conversion;
	uint32_t i;
	float32_t tension;
	float32_t temperatura;
	float32_t acumulador = 0;
	
	//Inicializador de periféricos
	
	adc_inicializar(1000000, SEL_CANAL_0); //El conversor
	glcd_inicializar(); //La pantalla LCD
	timer_inicializar(TIMER0); //El timer
	
	timer_iniciar_ciclos_ms (TIMER0, 10); //Iniciamos el timer
	
	while(TRUE){
		acumulador = 0;
		for (i = 0; i < 100; i++){			
			conversion = adc_convertir(0);
			tension = adc_traducir_a_tension(conversion);
			temperatura = ntc_traducir_tension_a_temperatura(tension);
			
			glcd_xy_texto (0 , 0);
			glcd_printf("Resultado ADC:\t%d\n", conversion);
			glcd_printf("Tension potenciometro:\t%9.4f\n", tension);
			glcd_printf("Temperatura:\t%9.4f\n", temperatura);
			
			acumulador += temperatura;
			timer_esperar_fin_ciclo(TIMER0);
		}
		acumulador /= 100;
		glcd_printf("Temperatura media:\t%9.4f\n", acumulador);
	}	
}