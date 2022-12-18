/***************************************************************************//**
 * \file    termistor_ntc.c
 *
 * \brief   Conversi�n de la tensi�n en un divisor de tensi�n con NTC a la
 *          temperatura correspondiente.
 */

#include "termistor_ntc.h"
#include "math.h"

/***************************************************************************//**
 * \brief     Calcular la temperatura en grados cent�grados correspondiente
 *            al resultado de 12 bits de la conversi�n A/D de la tensi�n de
 *            salida del m�dulo KY-013 de Keyes basado en un termistor NTC.
 *
 * \param[in] V_s   tensi�n en el divisor de tensi�n formado por el NTC y una
 *                  resistencia fija de 10k seg�n se indica abajo.
 *
 * \return    Temperatura correspondiente en grados cent�grados.
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
 *   | | R_ntc 
 *   | |
 *    -
 *    |
 *   ---
 *   GND     
 *
 * V_s es la tensi�n la tensi�n de salida del m�dulo sensor, igual a la
 * tensi�n en el centro del divisor de tensi�n formado por la resistencia
 * fija de 10 kohm (parte superior) y la NTC (parte inferior).
 *
 *                R_ntc              3.3*R_ntc
 *      V_s = ------------*V_cc = -------------- (Voltios)
 *           R1 + R_ntc          10000 + R_ntc
 *
 * Resolviendo para R_ntc:
 *
 *                            V_s
 *      R_ntc  = 10000*------------ (Ohmios)
 *                       3.3 - V_s
 *
 * La relaci�n entre la temperatura y la resistencia de la NTC se aproxima
 * por la ecuaci�n de Steinhart-Hart:
 *
 *                          1
 *      T = ------------------------------------ - 273.16 (�C)
 *             a + b*ln(R_ntc) + c*(ln(R_ntc))^3
 *
 * Para el termistor utilizado:
 *
 *      a = 0.001129,    b = 0.0002341, c = 0.00000008767
 *
 * No hay informaci�n fible sobre la NTC usada en el m�dulo KY-013 de Keyes.
 * Estos coeficientes est�n tomados de la informaci�n que circula por
 * internet sobre el m�dulo.
 */
float32_t ntc_traducir_tension_a_temperatura(float32_t V_s)
{
    float R_ntc;
    float ln_R_ntc;
    float T;        
    const float a = 1.129E-3f;     /* Coeficientes Steinhart-Hart usados */
    const float b = 2.341E-4f;
    const float c = 8.767E-8f;
    
    R_ntc = 10000*(V_s/(3.3 - V_s));
	
		ln_R_ntc = log(R_ntc);
	
		T = (1/((a + b*ln_R_ntc) + (c*pow(ln_R_ntc, 3)))) - 273.16;
	
	  return T;
}
