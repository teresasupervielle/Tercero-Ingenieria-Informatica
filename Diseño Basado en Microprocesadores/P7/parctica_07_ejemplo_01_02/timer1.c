/***************************************************************************//**
 */

#include <LPC407x_8x_177x_8x.h>
#include "timer1.h"
#include "joystick.h"

static bool_t hay_nueva_pulsacion = FALSE;
static bool_t nueva_pulsacion = FALSE;

/***************************************************************************//**
 */
void timer1_inicializar(void)
{
	LPC_TIM1->TCR = 0;
	LPC_TIM1->PC = 0;
	LPC_TIM1->TC = 0;
    LPC_TIM1->PR = 60 - 1;
    LPC_TIM1->MR0 = 20000 - 1;
    LPC_TIM1->MCR = 3;

    NVIC_EnableIRQ(TIMER1_IRQn);
	
	__enable_irq();	

    LPC_TIM1->TCR = 1;
}

/***************************************************************************//**
 */
void TIMER1_IRQHandler(void)
{
    static int32_t pulsacion_anterior = 0;
    int32_t pulsacion_actual;

    LPC_TIM1->IR = 1;

    pulsacion_actual = leer_joystick();

    if (pulsacion_anterior == 0 &&
        pulsacion_actual != 0 &&
        !hay_nueva_pulsacion)
    {
        nueva_pulsacion = pulsacion_actual;
        hay_nueva_pulsacion = TRUE;
    }
    else if (pulsacion_anterior != 0 &&
             pulsacion_actual == 0 &&
             !hay_nueva_pulsacion)
    {
        nueva_pulsacion = pulsacion_anterior + 0x10;
        hay_nueva_pulsacion = TRUE;
    }

    pulsacion_anterior = pulsacion_actual;
}

/***************************************************************************//**
 */
int32_t leer_pulsacion(void)
{
    if (hay_nueva_pulsacion)
    {
        hay_nueva_pulsacion = FALSE;
        return nueva_pulsacion;
    }

    return 0;
}
