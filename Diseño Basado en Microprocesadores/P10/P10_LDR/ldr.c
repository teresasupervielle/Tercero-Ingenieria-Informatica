/***************************************************************************//**
 * \file    ldr.c
 *
 * \brief   Conversi�n de la tensi�n en un divisor de tensi�n con LDR a la
 *          iluminancia en luxes correspondiente.
 */

#include "ldr.h"
#include "math.h"

/***************************************************************************//**
 * \brief     Calcular la iluminancia en lux correspondiente a la tensi�n de
 *            salida del m�dulo LDR KY-018 de Keyes.
 *
 * \param[in] V_s   tensi�n en el divisor de tensi�n formado por la LDR y una
 *                  resistencia fija de 10k seg�n se indica abajo.
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
 * V_s es la tensi�n la tensi�n de salida del m�dulo sensor, igual a la
 * tensi�n en el centro del divisor de tensi�n formado por la resistencia
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
 * La relaci�n entre la ilumancia y la resistencia de la LDR se toma:
 *
 *            
 *      E_v = 1.25*10^7 (R_ldr)^(-1.41) (lx)
 *
 * No hay informaci�n fiable sobre la LDR usada en el m�dulo KY-018 de Keyes.
 */
float32_t ldr_traducir_a_iluminancia(float32_t V_s)
{
    float32_t R_ldr;
		float32_t iluminancia;
		
		R_ldr = 10000 * (V_s/(3.3 - V_s));
		iluminancia = 1.25 * pow(10, 7) * pow(R_ldr, -1.41);
	
	return iluminancia;
}
