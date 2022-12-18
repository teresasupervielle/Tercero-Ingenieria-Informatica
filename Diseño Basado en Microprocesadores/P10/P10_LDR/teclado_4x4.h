/***************************************************************************//**
 * \file    teclado_4x4.h
 *
 * \brief   Teclado matricial de 4x4 teclas con filtrado de rebotes por software
 *          y buffer.
 */

#ifndef TECLADO_4X4_H
#define TECLADO_4X4_H

#include <LPC407x_8x_177x_8x.h>

/*===== Constantes =============================================================
 */
 
/* Símbolos para referirse a los números de los puertos a los que está conectado
 * el teclado.
 */
#define TEC4X4_PUERTO_FILAS    LPC_GPIO0
#define TEC4X4_PUERTO_COLUMNAS LPC_GPIO2

/* Símbolos para referirse a las líneas de puerto a las que están conectadas las
 * distintas filas y columnas del teclado.
 */
#define TEC4X4_PIN_FILA_0      5u
#define TEC4X4_PIN_FILA_1      7u
#define TEC4X4_PIN_FILA_2      9u
#define TEC4X4_PIN_FILA_3      21u

#define TEC4X4_PIN_COLUMNA_0   0u
#define TEC4X4_PIN_COLUMNA_1   1u
#define TEC4X4_PIN_COLUMNA_2   14u
#define TEC4X4_PIN_COLUMNA_3   19u

/* Máscaras de selección de pines de filas y columnas.
 */
#define TEC4X4_MASCARA_FILA_0      (1u << (TEC4X4_PIN_FILA_0))
#define TEC4X4_MASCARA_FILA_1      (1u << (TEC4X4_PIN_FILA_1))
#define TEC4X4_MASCARA_FILA_2      (1u << (TEC4X4_PIN_FILA_2))
#define TEC4X4_MASCARA_FILA_3      (1u << (TEC4X4_PIN_FILA_3))

#define TEC4X4_MASCARA_TODAS_LAS_FILAS  (TEC4X4_MASCARA_FILA_0 | \
                                         TEC4X4_MASCARA_FILA_1 | \
                                         TEC4X4_MASCARA_FILA_2 | \
                                         TEC4X4_MASCARA_FILA_3)

#define TEC4X4_MASCARA_COLUMNA_0   (1u << (TEC4X4_PIN_COLUMNA_0))
#define TEC4X4_MASCARA_COLUMNA_1   (1u << (TEC4X4_PIN_COLUMNA_1))
#define TEC4X4_MASCARA_COLUMNA_2   (1u << (TEC4X4_PIN_COLUMNA_2))
#define TEC4X4_MASCARA_COLUMNA_3   (1u << (TEC4X4_PIN_COLUMNA_3))

#define TEC4X4_MASCARA_TODAS_LAS_COLUMNAS  (TEC4X4_MASCARA_COLUMNA_0 | \
                                            TEC4X4_MASCARA_COLUMNA_1 | \
                                            TEC4X4_MASCARA_COLUMNA_2 | \
                                            TEC4X4_MASCARA_COLUMNA_3)

/* Las funciones de teclado retornan 0 para indicar ninguna tecla pulsada.
 */
#define TEC4X4_NINGUNA_PULSADA      0

/* Timer usado por el teclado.
 */
#define TEC4X4_TIMER                LPC_TIM3

/* Tiempo en microsegundos que el teclado debe permanecer en un determinado
 * estado para considerarse estable y no en situación de rebotes.
 */
#define TEC4X4_TIEMPO_FILTRO_REBOTES_US 20000u

/*===== Constantes para la versión básica sin timer ni interrupción ============
 */
 
/* Tiempo en microsegundos entre la activación de una línea y la lectura de
 * otra.
 */
#define TEC4X4_TIEMPO_ESTABILIZACION_US 10u
 
/*===== Constantes para la versión con sondeo periódico con timer ==============
 */

#define TEC4X4_PERIODO_BARRIDO_US       (TEC4X4_TIEMPO_FILTRO_REBOTES_US / 2)
#define TEC4X4_TIEMPO_FILA_US           (TEC4X4_PERIODO_BARRIDO_US / 4)

#define TEC4X4_TIMER_IRQn       TIMER3_IRQn
#define TEC4X4_TIMER_IRQHandler TIMER3_IRQHandler

#define TEC4X4_TAMANO_BUFFER        10u

#define TEC4X4_PRIORIDAD_INTERRUPCION   31u

/*===== Constantes para la versión por interrupciones GPIO =====================
 */
 
#define TEC4X4_ENF      IO2IntEnF
#define TEC4X4_STATF    IO2IntStatF
#define TEC4X4_CLR      IO2IntClr

/*===== Prototipos de funciones ================================================
 */

void tec4x4_inicializar(void);
char tec4x4_leer(void);
char tec4x4_esperar_estable(void);
char tec4x4_esperar_pulsacion_con_rebotes(void);
char tec4x4_esperar_pulsacion(void);
void tec4x4_vaciar_buffer(void);
uint32_t tec4x4_caracteres_en_buffer(void);
void tec4x4_leer_cadena(char *ptr_buffer, uint32_t tamano_buffer);
void tec4x4_leer_cadena_numeros(char *ptr_buffer, uint32_t tamano_buffer);

#endif  /* TECLADO_4X4_H */
