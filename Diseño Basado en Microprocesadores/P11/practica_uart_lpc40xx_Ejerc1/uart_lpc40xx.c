/***************************************************************************//**
 * \file    uart_lpc40xx.h
 *
 * \brief   Funciones de manejo de las UARTs del LPC40xx.
 */
 
#include <LPC407x_8x_177x_8x.h>
#include "uart_lpc40xx.h"
#include "iocon_lpc40xx.h"
#include "error.h"
#include "math.h"

/***************************************************************************//**
 * \brief       Inicializar una UART del LPC40xx.
 *
 * \param[in]   uart_regs               ptr. al bloque de registros de la UART.
 * \param[in]   baudrate                velocidad en baudios requerida.
 * \param[in]   numero_bits_datos       bits de datos a usar. De 5 a 8.
 * \param[in]   tipo_paridad            paridad a usar (NINGUNA, IMPAR o PAR).
 * \param[in]   numero_bits_stop        bits de stop a usar (1 � 2).
 * \param[in]   puerto_txd              puerto que se desea para la se�al TXD.
 * \param[in]   pin_txd                 pin que se desea para la se�al TXD.
 * \param[in]   puerto_rxd              puerto que se desea para la se�al RXD.
 * \param[in]   pin_rxd                 pin que se desea para la se�al RXD.
 * \param[in]   prioridad_interrupcion  prioridad a asignar a int. de la UART.
 * \param[out]  baudrate_real_obtenido  puntero a float32_t donde almacenar el
 *                                      mejor baudrate que se pudo ajustar.
 *                                      Si es NULL no se usa.
 *
 * \note        La raz�n de especificar los puertos y los pines mediante punteros
 *              a los registros GPIO y m�scaras de pin en lugar de n�meros
 *              de puerto y n�meros de pin es conseguir que la forma de
 *              especificar un pin sea igual que la usada en los m�dulos
 *              gpio_lpc40xx e iocon_lpc40xx. Esto permite usar los mismos
 *              s�mbolos PUERTOx y PINx definidos en gpio_lpc40xx.h.
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
                      float32_t *baudrate_real_obtenido)
{
    uint32_t lcr_word_length_select;
    uint32_t lcr_stop_bit_select;
    uint32_t lcr_parity_enable;
    uint32_t lcr_parity_select;
    uint32_t dlmdll;
    uint32_t divaddval;
    uint32_t mulval;
    uint32_t temp;
    uint32_t i;
    uint32_t num;
    uint32_t den;
    float32_t error_relativo;
    float32_t mejor_error_relativo;

    /* Comprobar que los par�metros son correctos.
     */
    ASSERT(uart_regs == UART0 || uart_regs == UART1 || uart_regs == UART2 ||
           uart_regs == UART3 || uart_regs == UART4,  
           "Puntero a registros de UART incorrecto.");
    
    ASSERT(numero_bits_datos >= 5 && numero_bits_datos <= 8,
           "N�mero de bits de datos seleccionado incorrecto.");
    
    ASSERT(tipo_paridad == UART_PARIDAD_NINGUNA ||
           tipo_paridad == UART_PARIDAD_PAR ||
           tipo_paridad == UART_PARIDAD_IMPAR,
           "Paridad seleccionada incorrecta.");
           
    ASSERT(numero_bits_stop == 1 || numero_bits_stop == 2,
           "N�mero de bits de stop seleccionado incorrecto.");
        
    /* Los n�meros de puerto y pin se comprueban en las funciones de
     * configuraci�n de pines.
     */

    /* Activar la alimentaci�n de la UART.
     */   
    if (uart_regs == UART0)
    {
        LPC_SC->PCONP |= 1 << 3;
    }
    else if (uart_regs == UART1)
    {
        LPC_SC->PCONP |= 1 << 4;
    }
    else if (uart_regs == UART2)
    {
        LPC_SC->PCONP |= 1 << 24;
    }
    else if (uart_regs == UART3)
    {
        LPC_SC->PCONP |= 1 << 25;
    }
    else if (uart_regs == UART4)
    {
        LPC_SC->PCONP |= 1 << 8;
    }
    else
    {
        ERROR("uart_regs incorrecto.");
    }
  
    /* Ajustar la velocidad de comunicaci�n en baudios solicitada.
     *    
     * Primero, calcular la parte entera del divisor de baudrate.
     */
    dlmdll = PeripheralClock/(16*baudrate);  /* dlmdll = 256*DLM + DLL */
    if (dlmdll == 0)
    {
        dlmdll = 1;
    }

    /* Si es neceario, calcular la parte fraccionario del divisor.
     */
    num = 0;
    den = 1;
    divaddval = num;
    mulval = den;    

    if (16*(int32_t)baudrate*(int32_t)dlmdll != PeripheralClock)
    {
        /* La mejor configuraci�n de DIVADDVAL y MULVAL se encontrar� probando
         * todos los valores posibles y seleccionando aquellos que hacen m�nima
         * el valor absoluto de
         *
         *      DIVADDVAL*a - MULVAL*(PeripheralClock - a)
         *
         *  donde
         *
         *      a = 16*baudrate*(256*DLM + DLL)
         */
        temp = dlmdll;
        mejor_error_relativo =
            fabs(((float)baudrate -
                ((float)PeripheralClock/(16*dlmdll)))/(float)baudrate);
        for (i = temp - 1; i <= temp + 1; i++)
        {
            for (den = 1; den < 16; den++)
            {
                for (num = 1; num < den; num++)
                {
                    error_relativo =
                        fabs(((float)baudrate -
                          ((float)PeripheralClock/((16*i)*(1+(float)num/den))))/
                            (float)baudrate);
                    
                    if (error_relativo < mejor_error_relativo)
                    {
                        dlmdll = i;
                        divaddval = num;
                        mulval = den;
                        mejor_error_relativo = error_relativo;
                    }
                }
            }
        }
    }
      
    /* Escribir los valores calculados en DLM, DLL y FDR.
     */
    uart_regs->LCR |= 0x80;
    uart_regs->DLM = dlmdll >> 8;
    uart_regs->DLL = dlmdll & 0xFF;
    uart_regs->FDR = (mulval << 4) | divaddval;

    if (baudrate_real_obtenido != NULL)
    {
        *baudrate_real_obtenido = (float32_t)(PeripheralClock*mulval)/
                                  (16*dlmdll*(mulval + divaddval));
    }

    /* Configurar el resto de par�metros en el registro LCR.
     */
    lcr_word_length_select = numero_bits_datos - 5;
    lcr_stop_bit_select = numero_bits_stop - 1;
    lcr_parity_enable = tipo_paridad == UART_PARIDAD_NINGUNA ? 0 : 1;
    lcr_parity_select = tipo_paridad == UART_PARIDAD_PAR ? 1 : 0;
    uart_regs->LCR = (lcr_parity_select << 4) |
                        (lcr_parity_enable << 3) |
                        (lcr_stop_bit_select << 2) |
                        lcr_word_length_select;

    /* Activar y limpiar las FIFOs.
     */
    uart_regs->FCR = 0x07;
    
    /* Configurar los pines indicados.
     */
    if (uart_regs == UART0)
    {
        iocon_configurar_pin(puerto_txd, mascara_pin_txd, U0_TXD,
            IOCON_NO_PULL_UP_NO_PULL_DOWN);
        iocon_configurar_pin(puerto_rxd, mascara_pin_rxd, U0_RXD, IOCON_PULL_UP);
    }
    else if (uart_regs == UART1)
    {
        iocon_configurar_pin(puerto_txd, mascara_pin_txd, U1_TXD,
            IOCON_NO_PULL_UP_NO_PULL_DOWN);
        iocon_configurar_pin(puerto_rxd, mascara_pin_rxd, U1_RXD, IOCON_PULL_UP);
    }
    else if (uart_regs == UART2)
    {
        iocon_configurar_pin(puerto_txd, mascara_pin_txd, U2_TXD,
            IOCON_NO_PULL_UP_NO_PULL_DOWN);
        iocon_configurar_pin(puerto_rxd, mascara_pin_rxd, U2_RXD, IOCON_PULL_UP);
    }
    else if (uart_regs == UART3)
    {
        iocon_configurar_pin(puerto_txd, mascara_pin_txd, U3_TXD,
            IOCON_NO_PULL_UP_NO_PULL_DOWN);
        iocon_configurar_pin(puerto_rxd, mascara_pin_rxd, U3_RXD, IOCON_PULL_UP);
    }
    else
    {
        iocon_configurar_pin(puerto_txd, mascara_pin_txd, U4_TXD,
            IOCON_NO_PULL_UP_NO_PULL_DOWN);
        iocon_configurar_pin(puerto_rxd, mascara_pin_rxd, U4_RXD, IOCON_PULL_UP);
    }    
}

/***************************************************************************//**
 * \brief       Transmitir un dato mediante una UART.
 * 
 * \parar[in]   uart_regs   puntero al bloque de registros de la UART. 
 * \param[in]   dato        dato a transmitir.
 */
void uart_transmitir_dato(LPC_UART_TypeDef *uart_regs, uint8_t dato)
{
    ASSERT(uart_regs == UART0 || uart_regs == UART1 || uart_regs == UART2 ||
           uart_regs == UART3 || uart_regs == UART4, "uart_regs incorrecto.");
           
    while (!(uart_regs->LSR & (1u << 5))) {}  /* Esperar a que U0THR est� libre. */
    uart_regs->THR = dato;
}

/***************************************************************************//**
 * \brief       Indicar si hay al menos un dato en el FIFO de recepci�n de la
 *              UART.
 *
 * \parar[in]   uart_regs   puntero al bloque de registros de la UART. 
 *
 * \return      FALSE => Ning�n dato disponible.
 *              TRUE  => Al menos un dato disponible.
 */
bool_t uart_hay_dato_disponible(LPC_UART_TypeDef *uart_regs)
{
    ASSERT(uart_regs == UART0 || uart_regs == UART1 || uart_regs == UART2 ||
           uart_regs == UART3 || uart_regs == UART4, "uart_regs incorrecto.");    
    
    if (uart_regs->LSR & 0x01) return TRUE;
    return FALSE;
}

/***************************************************************************//**
 * \brief       Leer un dato del FIFO de recepci�n de una UART. Debe ser
 *              llamada si se sabe que hay al menos un dato en la FIFO.
 *
 * \parar[in]   uart_regs   puntero al bloque de registros de la UART. 
 *
 * \return      Dato obtenido del FIFO de la UART.
 */
uint8_t uart_leer_dato(LPC_UART_TypeDef *uart_regs)
{
    ASSERT(uart_regs == UART0 || uart_regs == UART1 || uart_regs == UART2 ||
           uart_regs == UART3 || uart_regs == UART4, "uart_regs incorrecto.");    
    
    return uart_regs->RBR;
}

/***************************************************************************//**
 * \brief       Esperar a recibir un dato a trav�s de una UART.
 *
 * \parar[in]   uart_regs   puntero al bloque de registros de la UART. 
 *
 * \return      Dato recibido.
 */
uint8_t uart_esperar_recibir_dato(LPC_UART_TypeDef *uart_regs)
{
    ASSERT(uart_regs == UART0 || uart_regs == UART1 || uart_regs == UART2 ||
           uart_regs == UART3 || uart_regs == UART4, "uart_regs incorrecto.");    
    
    while (!(uart_regs->LSR & 0x01)) {} /* Esperar a que haya un dato
                                         * disponible. */
    return uart_regs->RBR;
}

/***************************************************************************//**
 * \brief       Transmitir una cadena de caracteres mediante una UART.
 * 
 * \parar[in]   uart_regs   puntero al bloque de registros de la UART. 
 * \param[in]   cadena      puntero a la cadena a transmitir.
 */
void uart_transmitir_cadena(LPC_UART_TypeDef *uart_regs, const char *cadena)
{
    /* C O M P L E T A R
     */
}

/***************************************************************************//**
 * \brief       Recibir una cadena de caracteres mediante una UART.
 *
 *              La recepci�n de la cadena terminar� cuando se reciba el car�cter
 *              nueva l�nea (0x0A).
 *
 *              La funci�n descarta todos los caracteres no imprimibles y s�lo
 *              almacena en el buffer los (tamano_buffer - 1) primeros
 *              caracteres que se reciban y descartar� el resto.
 *
 *              No se trata el car�cter de borrado (backspace, ASCII = 0x08),
 *              as� que los caracteres que se reciban y almacen en la cadena
 *              no pueden borrarse despu�s.
 *
 * \parar[in]   uart_regs       puntero al bloque de registros de la UART. 
 * \param[out]  ptr_buffer      puntero al buffer donde se almacenar� la cadena
 *                              recibida. La cadena quedar� terminada con un
 *                              car�cter nulo.
 * \parar[in]   tamano_buffer   longitud del buffer en bytes. La funci�n s�lo
 *                              almacenar� en el buffer los (tamano_buffer - 1)
 *                              primeros caracteres que se reciban. El tama�o
 *                              del buffer debe ser al menos 1 para tener
 *                              espacio para el terminador (pero si es uno
 *                              solo aceptar� la pulsac�n de ENTER para
 *                              finalizar la entrada).
 */
void uart_recibir_cadena(LPC_UART_TypeDef *uart_regs,
                         char *ptr_buffer,
                         uint32_t tamano_buffer)
{
    /* C O M P L E T A R
     */
}


