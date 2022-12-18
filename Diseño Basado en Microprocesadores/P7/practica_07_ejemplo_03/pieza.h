/***************************************************************************//**
 */

#ifndef PIEZA_H
#define PIEZA_H

#include "glcd.h"

#define DERECHA     0
#define IZQUIERDA   1

#define PIEZA_NUM_PIEZAS 7

#define PIEZA_MAX_TAM_MATRIZ  4
#define PIEZA_TAM_BLOQUE 15

typedef enum
{
    PIEZA_PALO,
    PIEZA_CUADRADO,
    PIEZA_ESE,
    PIEZA_ZETA,
    PIEZA_ELE,
    PIEZA_ELEREVES,
    PIEZA_TE
} pieza_tipo_t;

typedef struct
{
    pieza_tipo_t tipo;
    int32_t tamano;
    int8_t matriz[PIEZA_MAX_TAM_MATRIZ][PIEZA_MAX_TAM_MATRIZ];
    int16_t color;
} pieza_t;

void pieza_rotar(pieza_t *pptr, int32_t sentido);
void pieza_pintar(pieza_t *pptr, int32_t x, int32_t y);
void pieza_borrar(pieza_t *pptr, int32_t x, int32_t y);
void pieza_inicializar(pieza_t *pptr, pieza_tipo_t tipo);

#endif  /* PIEZA_H */
