/***************************************************************************//**
 * \file    termistor_ntc.c
 *
 * \brief   Conversión de la tensión en un divisor de tensión con NTC a la
 *          temperatura correspondiente.
 */

#include "termistor_ntc.h"
#include "math.h"

/***************************************************************************//**
 * \brief     Calcular la temperatura en grados centígrados correspondiente
 *            al resultado de 12 bits de la conversión A/D de la tensión de
 *            salida del módulo KY-013 de Keyes basado en un termistor NTC.
 *
 * \param[in] V_s   tensión en el divisor de tensión formado por el NTC y una
 *                  resistencia fija de 10k según se indica abajo.
 *
 * \return    Temperatura correspondiente en grados centígrados.
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
 * V_s es la tensión la tensión de salida del módulo sensor, igual a la
 * tensión en el centro del divisor de tensión formado por la resistencia
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
 * La relación entre la temperatura y la resistencia de la NTC se aproxima
 * por la ecuación de Steinhart-Hart:
 *
 *                          1
 *      T = ------------------------------------ - 273.16 (ºC)
 *             a + b*ln(R_ntc) + c*(ln(R_ntc))^3
 *
 * Para el termistor utilizado:
 *
 *      a = 0.001129,    b = 0.0002341, c = 0.00000008767
 *
 * No hay información fible sobre la NTC usada en el módulo KY-013 de Keyes.
 * Estos coeficientes están tomados de la información que circula por
 * internet sobre el módulo.
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
