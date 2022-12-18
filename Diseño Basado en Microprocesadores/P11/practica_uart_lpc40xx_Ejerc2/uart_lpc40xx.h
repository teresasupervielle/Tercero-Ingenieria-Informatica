/***************************************************************************//**
 * \file    uart_lpc40xx.h
 *
 * \brief   Funciones de manejo de las UARTs del LPC40xx.
 */

#ifndef UART_LPC40XX_H
#define UART_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "gpio_lpc40xx.h"
#include "tipos.h"

/*==============================================================================
 * El LPC40xx tiene 5 UARTs. Las UARTs 0, 2 y 3 son exactamente iguales entre
 * sí. La UART 1 añade señales de control de modem y tiene registros adicionales
 * a los de las UARTs 0, 2 y 3. La UART 4 puede funcionar en un modo síncrono y
 * puede comunicar con smart cards, así que también tiene registros adicionales.
 *
 * Las funciones de este módulo no usan ninguna de las características
 * especiales de las UARTs 1 y 4. Las posiciones de los registros comunes a
 * todas las UARTs coinciden, así que todas se manejarán mediante punteros a
 * estructura de tipo LPC_UART_TypeDef.
 */
#define LPC_UART1_  ((LPC_UART_TypeDef*)LPC_UART1_BASE)
#define LPC_UART4_  ((LPC_UART_TypeDef*)LPC_UART4_BASE)

/*===== Constantes =============================================================
 */
 
/* Símbolos para referirse a los bloques de registros de las UARTs.
 */

#define UART0   LPC_UART0
#define UART1   LPC_UART1_
#define UART2   LPC_UART2
#define UART3   LPC_UART3
#define UART4   LPC_UART4_

/* Símbolos para especificar baudrates estándar.
 */
 
#define UART_BAUDRATE_110       110u
#define UART_BAUDRATE_300       300u
#define UART_BAUDRATE_600       600u
#define UART_BAUDRATE_1200      1200u
#define UART_BAUDRATE_2400      2400u
#define UART_BAUDRATE_4800      4800u
#define UART_BAUDRATE_9600      9600u
#define UART_BAUDRATE_14400     14400u
#define UART_BAUDRATE_19200     19200u
#define UART_BAUDRATE_28800     28800u
#define UART_BAUDRATE_38400     38400u
#define UART_BAUDRATE_57600     57600u
#define UART_BAUDRATE_115200    115200u

/* Símbolos para especificar el número de bits de datos.
 */

#define UART_BITS_DATOS_5       5u
#define UART_BITS_DATOS_6       6u
#define UART_BITS_DATOS_7       7u
#define UART_BITS_DATOS_8       8u

/* Símbolos para especificar el número de bits de stop.
 */

#define UART_BITS_STOP_1        1u
#define UART_BITS_STOP_2        2u

/*===== Tipos de datos =========================================================
 */

/* Tipos de paridad.
 */
typedef enum
{
    UART_PARIDAD_NINGUNA,
    UART_PARIDAD_IMPAR,
    UART_PARIDAD_PAR
} uart_tipo_paridad_t;

/*===== Prototipos de funciones ================================================
 */

void uart_inicializar(LPC_UART_TypeDef *uart_regs,
                      uint32_t baudrate,
                      uint32_t numero_bits_datos,
                      uart_tipo_paridad_t tipo_paridad,
                      uint32_t numero_bits_stop,
                      LPC_GPIO_TypeDef *puerto_txd,
                      uint32_t mascara_pin_txd,
                      LPC_GPIO_TypeDef *puerto_rxd,
                      uint32_t mascara_pin_rxd,
                      float32_t *baudrate_real_obtenido);
                         
void uart_transmitir_dato(LPC_UART_TypeDef *uart_regs,
                          uint8_t dato);

bool_t uart_hay_dato_disponible(LPC_UART_TypeDef *uart_regs);

uint8_t uart_leer_dato(LPC_UART_TypeDef *uart_regs);

uint8_t uart_esperar_recibir_dato(LPC_UART_TypeDef *uart_regs);

void uart_transmitir_cadena(LPC_UART_TypeDef *uart_regs,
                            const char *cadena);

void uart_recibir_cadena(LPC_UART_TypeDef *uart_regs,
                         char *ptr_buffer,
                         uint32_t tamano_buffer);

#endif  /* UART_LPC40XX_H */
