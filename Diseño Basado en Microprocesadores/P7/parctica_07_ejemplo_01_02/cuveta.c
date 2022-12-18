/***************************************************************************//**
 */

#include "cuveta.h"
#include "bloque.h"
#include "pieza.h"
#include "error.h"
#include "glcd.h"
#include <stdlib.h>

/***************************************************************************//**
 */
void cuveta_inicializar(cuveta_t *cptr)
{
    int32_t i, j;
  
    ASSERT(cptr != NULL, "El puntero cptr es nulo");

    for (i = 0; i < CUVETA_ALTO; i++)
    {
        for (j = 0; j < CUVETA_ANCHO; j++)
        {
            cptr->matriz[i][j] = 0;
        }
    }

    cptr->x_pantalla = 7*BLOQUE_TAMANO;
    cptr->y_pantalla = 0;
}

/***************************************************************************//**
 */
void cuveta_revisar_filas(cuveta_t *cptr, int32_t *filas_eliminadas)
{
    int32_t i, j, e = 0;
  
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(filas_eliminadas != NULL, "El puntero filas_eliminadas es nulo");

    for (i = 0; i < CUVETA_ALTO; i++)
    {
        for (j = 0; j < CUVETA_ANCHO; j++)
        {
            if (cptr->matriz[i][j] == 0) break;
        }

        if (j == CUVETA_ANCHO)
        {
            cuveta_eliminar_fila(cptr, i);
            e++;
        }
    }

    *filas_eliminadas = e;
}

/***************************************************************************//**
 */
void cuveta_eliminar_fila(cuveta_t* cptr, int32_t fila)
{
    int32_t i, j;
  
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(fila >= 0 && fila < CUVETA_ALTO, "Argumento fila fuera de rango");

    for (i = fila; i > 0; i--)
    {
        for (j = 0; j < CUVETA_ANCHO; j++)
        {
            cptr->matriz[i][j] = cptr->matriz[i-1][j];
        }
    }

    for (j = 0; j < CUVETA_ANCHO; j++)
    {
        cptr->matriz[0][j] = 0;
    }
}

/***************************************************************************//**
 */
void cuveta_hay_desbordamiento(cuveta_t *cptr, pieza_t *pptr,
                               int32_t x, int32_t y,
                               bool_t *desborda)
{
    int32_t i, j;
  
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(pptr != NULL, "El puntero pptr es nulo");
    ASSERT(desborda != NULL, "El puntero desborda es nulo");
               
    for (i = 0; i < pptr->tamano; i++)
    {
        for (j = 0; j < pptr->tamano; j++)
        {
            if (pptr->matriz[i][j] != 0 && y + i < 0)
            {
                *desborda = TRUE;
                return;
            }
        }
    }
    
    *desborda = FALSE; 
}

/***************************************************************************//**
 */
void cuveta_pintar_pieza(cuveta_t *cptr, pieza_t *pptr, int32_t x, int32_t y)
{
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    pieza_pintar(pptr, cptr->x_pantalla + x*BLOQUE_TAMANO,
                       cptr->y_pantalla + y*BLOQUE_TAMANO);
}

/***************************************************************************//**
 */
void cuveta_borrar_pieza(cuveta_t *cptr, pieza_t *pptr, int32_t x, int32_t y)
{
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    pieza_borrar(pptr, cptr->x_pantalla + x*BLOQUE_TAMANO,
                       cptr->y_pantalla + y*BLOQUE_TAMANO);
}

/***************************************************************************//**
 */
void cuveta_fijar_pieza(cuveta_t *cptr, pieza_t *pptr, int32_t x, int32_t y)
{
    int32_t i, j;
  
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(pptr != NULL, "El puntero pptr es nulo");

    for (i = 0; i < pptr->tamano; i++)
    {
        for (j = 0; j < pptr->tamano; j++)
        {
            if (y + i >= 0 &&
                x + j >= 0 &&
                y + i < CUVETA_ALTO &&
                x + j < CUVETA_ANCHO &&
                pptr->matriz[i][j] != 0)
            {            
                cptr->matriz[y + i][x + j] = pptr->color;
            }
        }
    }
}

/***************************************************************************//**
 */
void cuveta_hay_interseccion(cuveta_t *cptr, pieza_t *pptr,
                             int32_t x, int32_t y,
                             bool_t *hay_interseccion)
{
    int i, j;
  
    ASSERT(cptr != NULL, "El puntero cptr es nulo");
    ASSERT(pptr != NULL, "El puntero pptr es nulo");
    ASSERT(hay_interseccion != NULL, "El puntero hay_interseccion es nulo");

    for (i = 0; i < pptr->tamano; i++)
    {
        for (j = 0; j < pptr->tamano; j++)
        {                        
            if (pptr->matriz[i][j] != 0)
            {
                if (y + i >= CUVETA_ALTO ||
                    x + j >= CUVETA_ANCHO ||
                    x + j < 0)
                {
                    *hay_interseccion = TRUE;
                    return;
                }               
                if (y + i >= 0 &&
                    x + j >= 0 &&
                    y + i < CUVETA_ALTO &&
                    x + j < CUVETA_ANCHO)
                {                            
                    if (cptr->matriz[y + i][x + j] != 0)
                    {
                        *hay_interseccion = TRUE;
                        return;
                    }
                }
            }
        }
    }

    *hay_interseccion = FALSE;
}

/***************************************************************************//**
 */
void cuveta_pintar(cuveta_t *cptr)
{
    int32_t i, j;
    
    ASSERT(cptr != NULL, "El puntero cptr es nulo");

    for (i = 0; i < CUVETA_ALTO + 1; i++)
    {
        bloque_pintar(cptr->x_pantalla - BLOQUE_TAMANO,
                      cptr->y_pantalla + i*BLOQUE_TAMANO,
                      WHITE);

        bloque_pintar(cptr->x_pantalla + BLOQUE_TAMANO*CUVETA_ANCHO,
                      cptr->y_pantalla + i*BLOQUE_TAMANO,
                      WHITE);
    }

    for (j = 0; j < CUVETA_ANCHO + 1; j++)
    {
        bloque_pintar(cptr->x_pantalla + (j - 1)*BLOQUE_TAMANO,
                      cptr->y_pantalla + (CUVETA_ALTO)*BLOQUE_TAMANO,
                      WHITE);
    }

    for (i = 0; i < CUVETA_ALTO; i++)
    {
        for (j = 0; j < CUVETA_ANCHO; j++)
        {
            bloque_pintar(cptr->x_pantalla + j*BLOQUE_TAMANO,
                          cptr->y_pantalla + i*BLOQUE_TAMANO,
                          cptr->matriz[i][j]);
        }
    }
}
