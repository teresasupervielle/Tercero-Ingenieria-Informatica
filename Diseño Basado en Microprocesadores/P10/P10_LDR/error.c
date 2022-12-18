/***************************************************************************//**
 * \file    error.c
 *
 * \brief   Tratamiento de errores.
 */

#include <LPC407x_8x_177x_8x.h>
#include "error.h"
#include "glcd.h"
#include <stdio.h>

/***************************************************************************//**
 * \brief   Función que es llamada por la macro ERROR y por la macro ASSERT es
 *          caso de que no se cumpla su expresión.
 *
 *          Imprime la función, fichero fuente y línea donde se produjo el
 *          error seguido del mensaje descriptivo del error que se indicó en
 *          ERROR o ASSERT. A continuación el programa queda en un bucle sin
 *          fin. Este comportamiento puede cambiarse modificando la función.
 *
 * \param[in]   fichero     nombre del fichero fuente donde se produjo el error.
 * \param[in]   funcion     nombre de la función donde se produjo el error.
 * \param[in]   linea       número de línea del fichero fuente donde produjo el
 *                          error.
 * \param[in]   mensaje     mensaje descriptivo del error.
 */
void parar_con_error(const char *fichero,
                     const char *funcion,
                     const uint32_t linea,
                     const char *mensaje)
{
    char buffer[61];
    
    /* Dashabilitar las interrupciones.
     */
    __disable_irq();
    
    /* Imprimir la información del error en la pantalla LCD.
     */    
    snprintf(buffer, 61, "Error: %s", mensaje);
    glcd_texto(0, 0, WHITE, BLACK, FONT8X16, buffer);
    snprintf(buffer, 61, "En funcion: %s", funcion);
    glcd_texto(0, 16, WHITE, BLACK, FONT8X16, buffer);    
    snprintf(buffer, 61, "Fichero: %s", fichero);
    glcd_texto(0, 32, WHITE, BLACK, FONT8X16, buffer);
    snprintf(buffer, 61, "Linea: %u", linea);
    glcd_texto(0, 48, WHITE, BLACK, FONT8X16, buffer);
    
    /* Dejar al programa encerrado aquí.
     */
    for (;;) {}
}
