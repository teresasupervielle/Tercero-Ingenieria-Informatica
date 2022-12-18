/***************************************************************************//**
 * \file    adc_lpc40xx.c
 *
 * \brief   Funciones de manejo del ADC del LPC40xx.  
 */

#include <LPC407x_8x_177x_8x.h>
#include "adc_lpc40xx.h"
#include "error.h"

/***************************************************************************//**
 * \brief       Inicializar el ADC del LPC40xx.
 *
 * \param[in]   frecuencia_adc  frecuencia de reloj a la que funcionará el ADC.
 *
 * \param[in]   canales         indica qué canales de entrada analógicos
 *                              queremos usar. Los pines correspondientes a los
 *                              canales indicados se configurarán con función
 *                              analógica. Cada bit de 0 a 7 de canales indica
 *                              si se usará el correspondiente canal analógico.
 */
void adc_inicializar(uint32_t frecuencia_adc, uint32_t canales)
{
    /* Los pines que pueden usarse como canales de entrada para el convertidor
     * A/D son los siguientes:
     *
     *  Pin         Canal analógico     Valor del campo FUNC
     *  ----------------------------------------------------
     *  P0[23]      0                   1
     *  P0[24]      1                   1
     *  P0[25]      2                   1
     *  P0[26]      3                   1
     *  P1[30]      4                   3
     *  P1[31]      5                   3
     *  P0[12]      6                   3
     *  P0[13]      7                   3
     *
     * La columna "Valor del campo FUNC" se refiere al valor que hay que
     * poner en los bits FUNC del registro IOCON correspondiente al pin
     * de la primera columna para conseguir seleccionar la función de
     * entrada analógica en ese pin.
     */
    
    /* El array puertos contiene el puerto en el que está cada pin de entrada
     * analógico.
     */
    const uint32_t puertos[8] = {0,  0,  0,  0,  1,  1,  0,  0};
    
    /* El array pines contiene el número de pin dentro del puerto indicado por
     * el array puertos donde está cada pin de entrada analógico.
     */
    const uint32_t pines[8] = {23, 24, 25, 26, 30, 31, 12, 13};
    
    /* El array funciones contiene el valor del campo FUNC para seleccionar
     * la función de entrada analógica en el registro IOCON del puerto y pin
     * de los pines con función de entrada analógica.
     */
    const uint32_t funciones[8] = {1,  1,  1,  1,  3,  3,  3,  3};
    
    uint32_t i;
    volatile uint32_t *iocon_reg;
    
    ASSERT(frecuencia_adc >= PeripheralClock/256,
        "La frecuencia de reloj del ADC indicada es demasiado baja.");
    
    ASSERT(frecuencia_adc < 12400000,
        "La frecuencia de reloj del ADC debe ser < 12.4 MHz.");
    
    ASSERT(canales < 256, "Canales incorrectos.");
        
    /* Activar el bit PCADC en el registro PCONP.
     */
    LPC_SC->PCONP |= 1u << 12;

    /* Registro de CR del ADC: activar PDN, ajustar CLKDIV según frecuencia_adc, resto de bits a 0.
     */
    LPC_ADC->CR = (1u << 21) | ((PeripheralClock/frecuencia_adc - 1) << 8);
    
    /* Configurar como entradas analógicas los pines indicados por canales.
     */
    for (i = 0; i < 8; i++)
    {
        if ((canales & (1u << i)) != 0)
        {
            /* Si el bit i de canales está a 1, seleccionar la función
             * de canal analógico i en el pin adecuado.
             *
             * Obtenemos un puntero al registro IOCON que configura la
             * función del pin en el que está el canal analógico i.
             * Los registros IOCON están colocados uno tras otro a partir
             * de la posición indicada por LPC_IOCON. Como cada puerto
             * tiene asociado 32 registros IOCON (uno por cada pin),
             * multiplicamos el número de puerto por 32. A esto sumamos el
             * número de pin. El resultado se suma al puntero LPC_IOCON
             * (Esta suma se hace con aritmética de punteros. El compilador
             * tiene en cuenta que cada registro IOCON ocupa 4 posicones
             * de memoria porque moldeamos el tipo del puntero LPC_IOCON
             * a puntero a uint32_t.
             */
            iocon_reg = ((uint32_t*)LPC_IOCON) + puertos[i]*32 + pines[i];
            
            /* Se configura el registro IOCON del pin con el número de función
             * adecuado para que funcione como entrada analógica.
             */
            *iocon_reg = funciones[i];
        }
    }
}

/***************************************************************************//**
 * \brief       Realizar un conversión AD de uno de los canales.
 *
 * \param[in]   canal   Canal de entrada (entre 0 y 7)
 *
 * \return      Resultado de la conversión de 12 bits.
 */
uint32_t adc_convertir(uint32_t canal)
{
    ASSERT (canal <= 7, "Canal ADC incorrecto.");

    LPC_ADC->CR = (LPC_ADC->CR & ~0xFF) | (1<<24) | (1 << canal);
    while ((LPC_ADC->GDR & (1u << 31)) == 0);
    return (LPC_ADC->GDR >> 4) & 0xFFF;
}

/***************************************************************************//**
 * \brief       Convierte un valor entre 0 y 4095 obtenido como resultado del
 *              convertidor A/D del LPC40xx en la tensión de entrada
 *              correspondiente.
 *
 * \param[in]   resultado_adc   valor obtenido como resultado del ADC.
 *
 * \return      Tensión correspondiente a resultado_adc.
 */
float32_t adc_traducir_a_tension(uint32_t resultado_adc)
{
    ASSERT(resultado_adc < 4096, "Valor ADC de entrada incorrecto.");
    
	return (3.30f*(float)resultado_adc)/4096;
}
