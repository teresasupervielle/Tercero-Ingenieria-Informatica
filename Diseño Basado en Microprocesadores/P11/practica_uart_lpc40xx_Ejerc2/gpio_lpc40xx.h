/***************************************************************************//**
 * \file    gpio_lpc40xx.h
 *
 * \brief   Constantes y funciones para manejar los puertos E/S digital del
 *          LPC40xx.
 */

#ifndef GPIO_LPC40XX_H
#define GPIO_LPC40XX_H

#include <LPC407x_8x_177x_8x.h>
#include "tipos.h"

/*===== Constantes =============================================================
 */
 
#define GPIO_NUMERO_PUERTOS             6u
#define GPIO_MAXIMO_PINES_POR_PUERTO    32u

/* Símbolos para referirse a los puertos.
 */
#define PORT0   LPC_GPIO0
#define PORT1   LPC_GPIO1
#define PORT2   LPC_GPIO2
#define PORT3   LPC_GPIO3
#define PORT4   LPC_GPIO4
#define PORT5   LPC_GPIO5

#define PUERTO0 PORT0
#define PUERTO1 PORT1
#define PUERTO2 PORT2
#define PUERTO3 PORT3
#define PUERTO4 PORT4
#define PUERTO5 PORT5

/* Máscaras para los pines.
 */
#define PIN0    (1u << 0)
#define PIN1    (1u << 1)
#define PIN2    (1u << 2)
#define PIN3    (1u << 3)
#define PIN4    (1u << 4)
#define PIN5    (1u << 5)
#define PIN6    (1u << 6)
#define PIN7    (1u << 7)
#define PIN8    (1u << 8)
#define PIN9    (1u << 9)
#define PIN10   (1u << 10)
#define PIN11   (1u << 11)
#define PIN12   (1u << 12)
#define PIN13   (1u << 13)
#define PIN14   (1u << 14)
#define PIN15   (1u << 15)
#define PIN16   (1u << 16)
#define PIN17   (1u << 17)
#define PIN18   (1u << 18)
#define PIN19   (1u << 19)
#define PIN20   (1u << 20)
#define PIN21   (1u << 21)
#define PIN22   (1u << 22)
#define PIN23   (1u << 23)
#define PIN24   (1u << 24)
#define PIN25   (1u << 25)
#define PIN26   (1u << 26)
#define PIN27   (1u << 27)
#define PIN28   (1u << 28)
#define PIN29   (1u << 29)
#define PIN30   (1u << 30)
#define PIN31   (1u << 31)

/* Símbolos para especificar la dirección de un pin.
 */
#define DIR_IN      0u
#define DIR_OUT     1u

#define DIR_ENTRADA DIR_IN
#define DIR_SALIDA  DIR_OUT

/* Definición del cualificador inline no disponible en modo C90.
 */
#ifndef inline
#define inline __inline
#endif

/*===== Funciones inline =======================================================
 *
 * No se comprueba la validez de los argumentos para que el tiempo de ejecución
 * sea corto y reducir el tamaño de la expansión en línea.
 */
 
/***************************************************************************//**
 * \brief       Leer el estado de un pin.
 *
 * \param[in]   gpio_regs       puntero al bloque de registros del puerto.
 * \param[in]   mascara_pin     mascara para seleccionar el pin. 
 *
 * \return      FALSE => el pin está a 0, TRUE => el pin está a 1.
 */
static inline bool_t gpio_leer_pin(LPC_GPIO_TypeDef *gpio_regs,
                                   uint32_t mascara_pin)
{
    return (gpio_regs->PIN & mascara_pin) != 0;
}

/***************************************************************************//**
 * \brief       Leer el estado de un puerto completo.
 *
 * \param[in]   gpio_regs   puntero al bloque de registros del puerto.
 *
 * \return      Valor leído del puerto.
 */
static inline uint32_t gpio_leer_puerto(LPC_GPIO_TypeDef *gpio_regs)
{
    return gpio_regs->PIN;
}

/***************************************************************************//**
 * \brief       Establecer el estado de uno o más pines de salida al mismo
 *              estado.
 *
 * \param[in]   gpio_regs       puntero al bloque de registros del puerto.
 * \param[in]   mascara_pin     mascara de selección del pin o pines.
 * \param[in]   valor           FALSE => poner a 0, TRUE => poner a 1.
 */
static inline void gpio_escribir_pin(LPC_GPIO_TypeDef *gpio_regs,
                                     uint32_t mascara_pin,
                                     bool_t valor)
{
    if (valor)
    {
        gpio_regs->SET = mascara_pin;
    }
    else
    {
        gpio_regs->CLR = mascara_pin;
    }
}

/***************************************************************************//**
 * \brief       Establecer el estado de los pines de salida de un puerto.
 *
 * \param[in]   gpio_regs   puntero al bloque de registros del puerto.
 * \param[in]   valor       valor a escribir en el puerto.
 */
static inline void gpio_escribir_puerto(LPC_GPIO_TypeDef *gpio_regs,
                                        uint32_t valor)
{
    gpio_regs->PIN = valor;
}

/***************************************************************************//**
 * \brief       Poner a 1 uno o más pines de salida.
 *
 * \param[in]   gpio_regs       puntero al bloque de registros del puerto.
 * \param[in]   mascara_pin     mascara de selección del pin o pines.
 */
static inline void gpio_pin_a_1(LPC_GPIO_TypeDef *gpio_regs,
                                uint32_t mascara_pin)
{
    gpio_regs->SET = mascara_pin;
}

/***************************************************************************//**
 * \brief       Poner a 0 uno o más pines de salida.
 *
 * \param[in]   gpio_regs       puntero al bloque de registros del puerto.
 * \param[in]   mascara_pin     mascara de selección del pin o pines.
 */
static inline void gpio_pin_a_0(LPC_GPIO_TypeDef *gpio_regs,
                                uint32_t mascara_pin)
{
    gpio_regs->CLR = mascara_pin;
}

/***************************************************************************//**
 * \brief       Invertir el estado de uno o más pines de salida.
 *
 * \param[in]   gpio_regs       puntero al bloque de registros del puerto.
 * \param[in]   mascara_pin     mascara de selección del pin o pines.
 */
static inline void gpio_invertir_pin(LPC_GPIO_TypeDef *gpio_regs,
                                     uint32_t mascara_pin)
{
    gpio_regs->PIN ^= mascara_pin;
}

/*===== Prototipos de funciones definidas en gpio_lpc40xx.c ====================
 */

void gpio_ajustar_dir(LPC_GPIO_TypeDef *gpio_regs,
                      uint32_t mascara_pin,
                      uint32_t direccion);

uint32_t gpio_obtener_dir(LPC_GPIO_TypeDef *gpio_regs,
                          uint32_t mascara_pin);

#endif  /* GPIO_LPC40XX_H */
