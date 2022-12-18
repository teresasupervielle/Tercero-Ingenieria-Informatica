/***************************************************************************//**
 */

#ifndef MARCADOR_H
#define MARCADOR_H

#include "bloque.h"
#include "pieza.h"

#define MARCADOR_POSICION_X (18*BLOQUE_TAMANO)
#define MARCADOR_POSICION_Y 0

void marcador_pintar(void);
void marcador_puntos(int32_t puntos);
void marcador_lineas(int32_t lineas);
void marcador_nivel(int32_t nivel);
void marcador_siguiente(pieza_t *pptr);

#endif  /* MARCADOR_H */
