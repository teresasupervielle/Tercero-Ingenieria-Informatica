/***************************************************************************//**
 */

#ifndef CUVETA_H
#define CUVETA_H

#include "error.h"
#include "pieza.h"

#define CUVETA_ANCHO 10
#define CUVETA_ALTO 17

typedef struct
{
    int matriz[CUVETA_ALTO][CUVETA_ANCHO];
    int x_pantalla;
    int y_pantalla;
} cuveta_t;

void cuveta_inicializar(cuveta_t *cptr);

void cuveta_revisar_filas(cuveta_t *cptr, int32_t *filas_eliminadas);

void cuveta_eliminar_fila(cuveta_t *cptr, int32_t fila);

void cuveta_revisar_pieza(cuveta_t *cptr, pieza_t *pptr,
                          int32_t x, int32_t y,
                          bool_t *encaja, bool_t *desborda);

void cuveta_pintar(cuveta_t* cptr);

void cuveta_pintar_pieza(cuveta_t* cptr, pieza_t* pptr, int32_t x, int32_t y);

void cuveta_borrar_pieza(cuveta_t* cptr, pieza_t* pptr, int32_t x, int32_t y);

void cuveta_fijar_pieza(cuveta_t* cptr, pieza_t* pptr, int32_t x, int32_t y);

void cuveta_hay_interseccion(cuveta_t* cptr, pieza_t* pptr,
                             int32_t x, int32_t y,
                             bool_t *hay_interseccion);

void cuveta_hay_desbordamiento(cuveta_t *cptr, pieza_t *pptr,
                               int32_t x, int32_t y,
                               bool_t *desborda);

#endif  /* CUVETA_H */
