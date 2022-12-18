/***************************************************************************//**
 * \file    error.h
 *
 * \brief   Tratamiento de errores.
 */

#ifndef ERROR_H
#define ERROR_H

#include "tipos.h"

/*===== Constantes =============================================================
 */

/**
 * Este define permite habilitar o deshabilitar los ASSERT.
 */
#define HABILITAR_ASSERT 1

/*===== Macros =================================================================
 */

#define ERROR(mensaje) parar_con_error(__FILE__, __FUNCTION__, __LINE__, mensaje)

#if HABILITAR_ASSERT != 0
#define ASSERT(expr, mensaje)\
if (expr) {} else { parar_con_error(__FILE__, __FUNCTION__, __LINE__, mensaje); }
#else
#define ASSERT(expr, mensaje)
#endif /* HABILITAR_ASSERT */

/*===== Prototipos de funciones ================================================
 */

void parar_con_error(const char *fichero,
                     const char *funcion,
                     const uint32_t linea,
                     const char *mensaje);

#endif /* ERROR_H */
