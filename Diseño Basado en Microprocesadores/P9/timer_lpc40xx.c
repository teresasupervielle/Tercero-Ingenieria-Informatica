/***************************************************************************//**
 * \file    timer_lpc40xx.c
 *
 * \brief   Funciones de uso de los timers del LPC40xx.
 */

#include <LPC407x_8x_177x_8x.h>
#include "timer_lpc40xx.h"
#include "error.h"

/***************************************************************************//**
 * \brief       Inicializar un timer habilitándolo en el registro de control de
 *              consumo de periféricos PCONP.
 *
 * \param[in]   timer_regs    puntero al bloque de registros del timer a
 *                            inicializar.
 */
void timer_inicializar(LPC_TIM_TypeDef *timer_regs)
{
    if (timer_regs == TIMER0)
    {
        LPC_SC->PCONP |= 1 << 1;
    }
    else if (timer_regs == TIMER1)
    {
        LPC_SC->PCONP |= 1 << 2;
    }
    else if (timer_regs == TIMER2)
    {
        LPC_SC->PCONP |= 1 << 22;
    }
    else if (timer_regs == TIMER3)
    {
        LPC_SC->PCONP |= 1 << 23;
    }
    else ERROR("timer_regs incorrecto");
}

/***************************************************************************//**
 * \brief       Usar un timer para generar un retardo del número de milisegundos
 *              indicado. La función no retorna hasta que transcurre este
 *              tiempo.
 *
 * \param[in]   timer_regs      puntero al bloque de registros del timer.
 * \param[in]   retado_en_ms    número de milisegundos de duración del retardo.
 */
void timer_retardo_ms(LPC_TIM_TypeDef *timer_regs,
                      uint32_t retardo_en_ms)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
    
    if (retardo_en_ms == 0) return;

    timer_regs->TCR = 0;
    timer_regs->TC = 0;
    timer_regs->PC = 0;
    timer_regs->PR = PeripheralClock/1000000 - 1;
    timer_regs->MR0 = 1000*retardo_en_ms - 1;
    timer_regs->MCR |= 7;
    timer_regs->IR = 1;
    timer_regs->TCR = 1;    
    while ((timer_regs->IR & 1) == 0) {}
}

/***************************************************************************//**
 * \brief       Usar un timer para generar un retardo del número de
 *              microsegundos indicado. La función no retorna hasta que
 *              transcurre este tiempo.
 *
 * \param[in]   timer_regs      puntero al bloque de registros del timer.
 * \param[in]   retado_en_us    número de microsegundos de duración del retardo.
 */
void timer_retardo_us(LPC_TIM_TypeDef *timer_regs,
                      uint32_t retardo_en_us)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
           
    if (retardo_en_us == 0) return;

    timer_regs->TCR = 0;
    timer_regs->TC = 0;
    timer_regs->PC = 0;
    timer_regs->PR = PeripheralClock/10000000 - 1;
    timer_regs->MR0 = 10*retardo_en_us - 1;
    timer_regs->MCR |= 7;
    timer_regs->IR = 1;
    timer_regs->TCR = 1;    
    while ((timer_regs->IR & 1) == 0) {}
}

/***************************************************************************//**
 * \brief       Programar un timer para que realice ciclos con una duración del
 *              número de milisegundos indicado.
 *
 * \param[in]   timer_regs    puntero al bloque de registros del timer.
 * \param[in]   periodo_en_ms   duración de cada ciclo en milisegundos.
 */
void timer_iniciar_ciclos_ms(LPC_TIM_TypeDef *timer_regs,
                             uint32_t periodo_en_ms)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
           
    ASSERT(periodo_en_ms != 0, "periodo_en_ms es 0");
    
    timer_regs->TCR = 0;
    timer_regs->PC = 0;
    timer_regs->TC = 0;
    timer_regs->PR = PeripheralClock/10000 - 1;
    timer_regs->MR0 = 10*periodo_en_ms - 1;
    timer_regs->MCR = 3;
    timer_regs->IR = 1;
    timer_regs->TCR = 1;
}

/***************************************************************************//**
 * \brief       Programar un timer para que realice ciclos con una duración del
 *              número de microgundos indicado.
 *
 * \param[in]   timer_regs      puntero al bloque de registros del timer.
 * \param[in]   periodo_en_us   duración de cada ciclo en microsegundos.
 */
void timer_iniciar_ciclos_us(LPC_TIM_TypeDef *timer_regs,
                             uint32_t periodo_en_us)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");        
    
    ASSERT(periodo_en_us != 0, "periodo_en_us es 0");
    
    timer_regs->TCR = 0;
    timer_regs->PC = 0;
    timer_regs->TC = 0;
    timer_regs->PR = PeripheralClock/10000000 - 1;
    timer_regs->MR0 = 10*periodo_en_us - 1;
    timer_regs->MCR = 3;
    timer_regs->IR = 1;
    timer_regs->TCR = 1;
}

/***************************************************************************//**
 * \brief       Esperar a que el bit de petición de interrupción de match 0 de
 *              un timer se ponga a 1. Cuando esto ocurra, ponerlo a 0 y
 *              retornar.
 *
 * \param[in]   timer_regs    puntero al bloque de registros del timer.
 */
void timer_esperar_fin_ciclo(LPC_TIM_TypeDef *timer_regs)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
           
    while ((timer_regs->IR & 1) == 0) {}
    timer_regs->IR = 1;
}

/***************************************************************************//**
 * \brief       Programar un timer para que se incremente indefinidamente una
 *              vez por milisegundo.
 *
 * \param[in]   timer_regs    puntero al bloque de registros del timer.
 */
void timer_iniciar_conteo_ms(LPC_TIM_TypeDef *timer_regs)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
           
    timer_regs->TCR = 0;
    timer_regs->PC = 0;
    timer_regs->TC = 0;
    timer_regs->PR = PeripheralClock/1000 - 1;
    timer_regs->MCR = 0;
    timer_regs->IR = 1;
    timer_regs->TCR = 1;
}

/***************************************************************************//**
 * \brief       Programar un timer para que se incremente indefinidamente una
 *              vez por microsegundo.
 *
 * \param[in]   timer_regs      puntero al bloque de registros del timer.
 */
void timer_iniciar_conteo_us(LPC_TIM_TypeDef *timer_regs)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
           
    timer_regs->TCR = 0;
    timer_regs->PC = 0;
    timer_regs->TC = 0;
    timer_regs->PR = PeripheralClock/1000000 - 1;
    timer_regs->MCR = 0;
    timer_regs->IR = 1;
    timer_regs->TCR = 1;
}

/***************************************************************************//**
 * \brief       Leer el valor del registro TC de un timer.
 *
 * \param[in]   timer_regs      puntero al bloque de registros del timer.
 *
 * \return      Valor actual del registro TC de un timer.
 */
uint32_t timer_leer(LPC_TIM_TypeDef *timer_regs)
{
    ASSERT(timer_regs == TIMER0 ||
           timer_regs == TIMER1 ||
           timer_regs == TIMER2 ||
           timer_regs == TIMER3,
           "timer_regs incorrecto");    
           
    return timer_regs->TC;
}
