/***************************************************************************//**
 * \file    adc_lpc40xx.h
 *
 * \brief   Funciones de manejo del ADC del LPC40xx.
 */

#ifndef ADC_LPC40XX_H
#define ADC_LPC40XX_H

#include "tipos.h"

/*===== Constantes =============================================================
 */
 
#define SEL_CANAL_0 (1u << 0)
#define SEL_CANAL_1 (1u << 1)
#define SEL_CANAL_2 (1u << 2)
#define SEL_CANAL_3 (1u << 3)
#define SEL_CANAL_4 (1u << 4)
#define SEL_CANAL_5 (1u << 5)
#define SEL_CANAL_6 (1u << 6)
#define SEL_CANAL_7 (1u << 7)

/*===== Prototipos de funciones ================================================
 */

void adc_inicializar(uint32_t frecuencia_adc, uint32_t canales);
uint32_t adc_convertir(uint32_t canal);
float adc_traducir_a_tension(uint32_t resultado_adc);

#endif  /* ADC_LPC40XX_H */
