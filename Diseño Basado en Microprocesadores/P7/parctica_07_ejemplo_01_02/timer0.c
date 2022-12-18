/***************************************************************************//**
 */

#include <LPC407x_8x_177x_8x.h>
#include "timer0.h"

int32_t contador_ms = 0;

/***************************************************************************//**
 */
void timer0_inicializar(void)
{
	LPC_TIM0->TCR = 0;
	LPC_TIM0->PC = 0;
	LPC_TIM0->TC = 0;	
    LPC_TIM0->PR = 60 - 1;
    LPC_TIM0->MR0 = 1000 - 1;
    LPC_TIM0->MCR = 3;

    NVIC_EnableIRQ(TIMER0_IRQn);
	
	__enable_irq();

    LPC_TIM0->TCR = 1;
}

/***************************************************************************//**
 */
void TIMER0_IRQHandler(void)
{
    contador_ms++;

    LPC_TIM0->IR = 1;
}
