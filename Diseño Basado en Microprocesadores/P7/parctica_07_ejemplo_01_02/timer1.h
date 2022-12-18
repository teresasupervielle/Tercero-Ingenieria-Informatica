/***************************************************************************//**
 */

#ifndef TIMER1_H
#define TIMER1_H

#include "tipos.h"

void timer1_inicializar(void);
void TIMER1_IRQHandler(void);
int32_t leer_pulsacion(void);

#endif  /* TIMER1_H */
