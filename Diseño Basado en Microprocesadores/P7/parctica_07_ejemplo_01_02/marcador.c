/***************************************************************************//**
 */

#include "marcador.h"
#include "glcd.h"
#include "pieza.h"
#include "bloque.h"
#include <stdio.h>

/***************************************************************************//**
 */
void marcador_pintar(void)
{
    int32_t i;

    for (i = 0; i < 5; i++)
    {
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 0, WHITE);
    }

    for (i = 0; i < 5; i++)
    {
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 6*BLOQUE_TAMANO,
                      WHITE);
    }

    for (i = 0; i < 5; i++)
    {
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 9*BLOQUE_TAMANO,
                      WHITE);
    }

    for (i = 0; i < 5; i++)
    {
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 12*BLOQUE_TAMANO,
                      WHITE);
    }

    for (i = 0; i < 5; i++)
    {
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 15*BLOQUE_TAMANO,
                      WHITE);
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 16*BLOQUE_TAMANO,
                      WHITE);
        bloque_pintar(MARCADOR_POSICION_X + i*BLOQUE_TAMANO, 17*BLOQUE_TAMANO,
                      WHITE);
    }

    for (i = 0; i < 18; i++)
    {
        bloque_pintar(MARCADOR_POSICION_X + BLOQUE_TAMANO*5, i*BLOQUE_TAMANO, WHITE);
    }

    glcd_texto(MARCADOR_POSICION_X + 1, BLOQUE_TAMANO,
               CYAN, BLACK, FONT8X16,
               "SIGUIENTE");
    glcd_texto(MARCADOR_POSICION_X + BLOQUE_TAMANO, BLOQUE_TAMANO*7,
               CYAN, BLACK, FONT8X16,
               "LINEAS");
    glcd_texto(MARCADOR_POSICION_X + BLOQUE_TAMANO, BLOQUE_TAMANO*10,
               CYAN, BLACK, FONT8X16,
               "PUNTOS");
    glcd_texto(MARCADOR_POSICION_X + BLOQUE_TAMANO + BLOQUE_TAMANO/2,
               BLOQUE_TAMANO*13, CYAN, BLACK, FONT8X16,
               "NIVEL");
}

/***************************************************************************//**
 */
void marcador_lineas(int32_t lineas)
{
    glcd_xprintf(MARCADOR_POSICION_X, BLOQUE_TAMANO*8 - 1,
                 WHITE, BLACK, FONT8X16, "%8d", lineas);
}

/***************************************************************************//**
 */
void marcador_puntos(int32_t puntos)
{   
    glcd_xprintf(MARCADOR_POSICION_X, BLOQUE_TAMANO*11 - 1,
                 WHITE, BLACK, FONT8X16, "%8d", puntos);
}

/***************************************************************************//**
 */
void marcador_nivel(int nivel)
{   
    glcd_xprintf(MARCADOR_POSICION_X, BLOQUE_TAMANO*14 - 1,
                 WHITE, BLACK, FONT8X16, "%8d", nivel);
}

/***************************************************************************//**
 */
void marcador_siguiente(pieza_t *pptr)
{
    glcd_rectangulo_relleno(MARCADOR_POSICION_X,
                            BLOQUE_TAMANO*2,
                            MARCADOR_POSICION_X + BLOQUE_TAMANO*5 - 1,
                            6*BLOQUE_TAMANO - 1,
                            BLACK);
    pieza_pintar(pptr,
                 MARCADOR_POSICION_X + (4 - pptr->tamano)*BLOQUE_TAMANO/2,
                 BLOQUE_TAMANO*2 + (4 - pptr->tamano)*BLOQUE_TAMANO/2);
}
