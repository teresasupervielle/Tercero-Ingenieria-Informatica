/***************************************************************************//**
 * \file    termistor_ntc.h
 *
 * \brief   Conversión de la tensión en un divisor de tensión con NTC a la
 *          temperatura correspondiente.
 */

#ifndef TERMISTOR_NTC_H
#define TERMISTOR_NTC_H

#include "tipos.h"

/*===== Prototipos de funciones ================================================
 */

float32_t ntc_traducir_tension_a_temperatura(float32_t V_s);

#endif  /* TERMISTOR_NTC_H */
