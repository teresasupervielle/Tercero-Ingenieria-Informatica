/***************************************************************************//**
 * \file   gpio_lpc40xx.c
 *
 * \brief  Funciones para manejar los puertos E/S digital del LPC40xx.
 *
 *         Las funciones de lectura y escritura en los pines se han declarado
 *         inline y est�n definidas en el fichero gpio_lpc40xx.h.
 */

#include "gpio_lpc40xx.h"
#include "error.h"
#include <LPC407x_8x_177x_8x.h>

/***************************************************************************//**
 * \brief      Configurar la direcci�n de uno o m�s pines.
 *
 * \param[in]  puerto       Puerto del pin o pines cuya direcci�n se quiere
 *                          ajustar.
 * \param[in]  mascara_pin  M�scara de selecci�n del pin o pines.
 * \param[in]  direccion    Direcci�n: DIR_ENTRADA o DIR_SALIDA.
 */
void gpio_ajustar_dir(LPC_GPIO_TypeDef *gpio_regs,
                      uint32_t mascara_pin,
                      uint32_t direccion)
{   
    ASSERT(gpio_regs == PUERTO0 ||
           gpio_regs == PUERTO1 ||
           gpio_regs == PUERTO2 ||
           gpio_regs == PUERTO3 ||
           gpio_regs == PUERTO4 ||
           gpio_regs == PUERTO5, "Puerto no valido.");
           
    ASSERT(gpio_regs != PUERTO5 ||
           (gpio_regs == PORT5 && mascara_pin < (1u << 6)),
           "Pin no v�lido.");
        
    ASSERT(direccion == DIR_ENTRADA || direccion == DIR_SALIDA,
           "Direccion no valida.");
        
    if (direccion == DIR_ENTRADA)
    {
        gpio_regs->DIR &= ~mascara_pin;
    }
    else
    {
        gpio_regs->DIR |= mascara_pin;
    }
}

/***************************************************************************//**
 * \brief       Consultar la direcci�n de un pin establecida actualmente.
 *
 * \param[in]   puerto      Puerto del pin cuya direcci�n se quiere obtener.
 * \param[in]   mascara_pin M�scara de selecci�n del pin.
 *
 * \return      Direcci�n del puerto (DIR_IN o DIR_OUT).
 */
uint32_t gpio_obtener_dir(LPC_GPIO_TypeDef *gpio_regs,
                          uint32_t mascara_pin)
{
    ASSERT(gpio_regs == PUERTO0 ||
           gpio_regs == PUERTO1 ||
           gpio_regs == PUERTO2 ||
           gpio_regs == PUERTO3 ||
           gpio_regs == PUERTO4 ||
           gpio_regs == PUERTO5, "Puerto no valido.");
           
    ASSERT(gpio_regs != PUERTO5 ||
           (gpio_regs == PORT5 && mascara_pin < (1u << 6)),
           "Pin no v�lido.");
    
    if ((gpio_regs->DIR & mascara_pin) != 0)
    {
        return DIR_SALIDA;
    }
    else
    {
        return DIR_ENTRADA;
    }
}
