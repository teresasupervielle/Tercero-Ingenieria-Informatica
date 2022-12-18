/***************************************************************************//**
 * \file    timer_lpc40xx.h
 *
 * \brief   Funciones de uso de los timers del LPC40xx.
 */

#ifndef TIMER_LPC40XX_H
#define TIMER_LPC40XX_H

#include "tipos.h"
#include <LPC407x_8x_177x_8x.h>

/*===== Constantes =============================================================
 */

/* Símbolos para referirse a los timers.
 */
#define TIMER0   LPC_TIM0
#define TIMER1   LPC_TIM1
#define TIMER2   LPC_TIM2
#define TIMER3   LPC_TIM3

/*===== Prototipos de funciones ================================================
 */

void timer_inicializar(LPC_TIM_TypeDef *timer_regs);

void timer_retardo_ms(LPC_TIM_TypeDef *timer_regs,
                      uint32_t retardo_en_ms);
                      
void timer_retardo_us(LPC_TIM_TypeDef *timer_regs,
                      uint32_t retardo_en_us);
                      
void timer_iniciar_ciclos_ms(LPC_TIM_TypeDef *timer_regs,
                             uint32_t periodo_en_ms);
                               
void timer_iniciar_ciclos_us(LPC_TIM_TypeDef *timer_regs,
                             uint32_t periodo_en_us);
                               
void timer_esperar_fin_ciclo(LPC_TIM_TypeDef *timer_regs);

void timer_iniciar_conteo_ms(LPC_TIM_TypeDef *timer_regs);

void timer_iniciar_conteo_us(LPC_TIM_TypeDef *timer_regs);

uint32_t timer_leer(LPC_TIM_TypeDef *timer_regs);

#endif  /* TIMER_LPC40XX_H */
