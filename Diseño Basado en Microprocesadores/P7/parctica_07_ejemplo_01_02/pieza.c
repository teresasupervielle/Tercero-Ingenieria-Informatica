/***************************************************************************//**
 */

#include "pieza.h"
#include "error.h"
#include "glcd.h"
#include "bloque.h"
#include <stdint.h>
#include <stdlib.h>

pieza_t pieza_palo =
{
    PIEZA_PALO,
    4,
    {{0, 1, 0 ,0},
     {0, 1, 0, 0},
     {0, 1, 0, 0},
     {0, 1, 0, 0}},
    RED
};

pieza_t pieza_cuadrado =
{
    PIEZA_CUADRADO,
    2,
    {{1, 1, 0 ,0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    BLUE
};

pieza_t pieza_ese =
{
    PIEZA_ESE,
    3,
    {{0, 1, 1 ,0},
     {1, 1, 0, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    CYAN
};

pieza_t pieza_zeta =
{
    PIEZA_ZETA,
    3,
    {{1, 1, 0 ,0},
     {0, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    MAGENTA
};

pieza_t pieza_ele =
{
    PIEZA_ELE,
    3,
    {{0, 1, 0 ,0},
     {0, 1, 0, 0},
     {0, 1, 1, 0},
     {0, 0, 0, 0}},
    YELLOW
};

pieza_t pieza_elereves =
{
    PIEZA_ELEREVES,
    3,
    {{0, 1, 0 ,0},
     {0, 1, 0, 0},
     {1, 1, 0, 0},
     {0, 0, 0, 0}},
    ORANGE
};

pieza_t pieza_te =
{
    PIEZA_TE,
    3,
    {{0, 1, 0 ,0},
     {1, 1, 1, 0},
     {0, 0, 0, 0},
     {0, 0, 0, 0}},
    GREEN
};


/***************************************************************************//**
 */
void pieza_inicializar(pieza_t *pptr, pieza_tipo_t tipo)
{
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    switch (tipo)
    {
    case PIEZA_PALO:
        *pptr = pieza_palo;
        break;
    case PIEZA_ESE:
        *pptr = pieza_ese;
        break;
    case PIEZA_ZETA:
        *pptr = pieza_zeta;
        break;
    case PIEZA_CUADRADO:
        *pptr = pieza_cuadrado;
        break;
    case PIEZA_ELE:
        *pptr = pieza_ele;
        break;
    case PIEZA_ELEREVES:
        *pptr = pieza_elereves;
        break;
    case PIEZA_TE:
        *pptr = pieza_te;
        break;
    default:
        ERROR("Tipo de pieza incorrecto");
        break;
    }
}

/***************************************************************************//**
 */
void pieza_rotar(pieza_t *pptr, int32_t sentido)
{
    int32_t i, j;
    int8_t temp[PIEZA_MAX_TAM_MATRIZ][PIEZA_MAX_TAM_MATRIZ];
    
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    if (sentido == DERECHA)
    {
        for (i = 0; i < pptr->tamano; i++)
        {
            for (j = 0; j < pptr->tamano; j++)
            {
                temp[j][pptr->tamano - i - 1] = pptr->matriz[i][j];
            }
        }
    }
    else
    {
        for (i = 0; i < pptr->tamano; i++)
        {
            for (j = 0; j < pptr->tamano; j++)
            {
                temp[pptr->tamano - j - 1][i] = pptr->matriz[i][j];
            }
        }
    }

    for (i = 0; i < pptr->tamano; i++)
    {
        for (j = 0; j < pptr->tamano; j++)
        {
            pptr->matriz[i][j] = temp[i][j];
        }
    }
}

/***************************************************************************//**
 */
void pieza_pintar(pieza_t *pptr, int32_t x, int32_t y)
{
    int32_t i, j;  
  
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    for (i = 0; i < pptr->tamano; i++)
    {
        for (j = 0; j < pptr->tamano; j++)
        {
            if (pptr->matriz[i][j] != 0)
            {
                bloque_pintar(x + j*PIEZA_TAM_BLOQUE,
                              y + i*PIEZA_TAM_BLOQUE,
                              pptr->color);
            }
        }
    }
}

/***************************************************************************//**
 */
void pieza_borrar(pieza_t *pptr, int32_t x, int32_t y)
{
    int32_t i, j;
    
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    for (i = 0; i < pptr->tamano; i++)
    {
        for (j = 0; j < pptr->tamano; j++)
        {
            if (pptr->matriz[i][j] != 0)
            {
                bloque_pintar(x + j*PIEZA_TAM_BLOQUE,
                              y + i*PIEZA_TAM_BLOQUE,
                              BLACK);
            }
        }
    }
}
