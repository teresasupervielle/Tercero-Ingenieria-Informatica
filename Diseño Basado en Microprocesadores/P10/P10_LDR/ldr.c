/***************************************************************************//**
 * \file    ldr.c
 *
 * \brief   Conversión de la tensión en un divisor de tensión con LDR a la
 *          iluminancia en luxes correspondiente.
 */

#include "ldr.h"
#include "math.h"

/***************************************************************************//**
 * \brief     Calcular la iluminancia en lux correspondiente a la tensión de
 *            salida del módulo LDR KY-018 de Keyes.
 *
 * \param[in] V_s   tensión en el divisor de tensión formado por la LDR y una
 *                  resistencia fija de 10k según se indica abajo.
 *
 * \return    Iluminancia en luxes.
 *
 *   V_cc = 3.3 V
 *    ^
 *    |
 *    -
 *   | | R_1 = 10 kohm
 *   | |
 *    -
 *    |
 *    |---------> V_s
 *    |
 *    -
 *   | | R_ldr 
 *   | |
 *    -
 *    |
 *   ---
 *   GND     
 *
 * V_s es la tensión la tensión de salida del módulo sensor, igual a la
 * tensión en el centro del divisor de tensión formado por la resistencia
 * fija de 10 kohm (parte superior) y la LDR (parte inferior).
 *
 *               R_ldr              3.3*R_ldr
 *      V_s = ------------*V_cc = -------------- (Voltios)
 *             R1 + R_ldr          10000 + R_ldr
 *
 * Resolviendo para R_ldr:
 *
 *                          V_s
 *      R_ldr  = 10000*------------ (Ohmios)
 *                       3.3 - V_s
 *
 * La relación entre la ilumancia y la resistencia de la LDR se toma:
 *
 *            
 *      E_v = 1.25*10^7 (R_ldr)^(-1.41) (lx)
 *
 * No hay información fiable sobre la LDR usada en el módulo KY-018 de Keyes.
 */
float32_t ldr_traducir_a_iluminancia(float32_t V_s)
{
    float32_t R_ldr;
		float32_t iluminancia;
		
		R_ldr = 10000 * (V_s/(3.3 - V_s));
		iluminancia = 1.25 * pow(10, 7) * pow(R_ldr, -1.41);
	
	return iluminancia;
}
