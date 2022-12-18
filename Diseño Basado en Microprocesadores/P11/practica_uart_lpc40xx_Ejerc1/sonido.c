/***************************************************************************//**
 * \file    sonido.c
 *
 * \brief   Funciones básicas de sonido.
 */

#include <LPC407x_8x_177x_8x.h>
#include "sonido.h"
#include "error.h"
#include "gpio_lpc40xx.h"
#include "timer_lpc40xx.h"

/* Array de conversión de nota a semiperiodo en microsegundos.
 * El índice 0 no se usa porque la nota 0 indicará silencio.
 */
const uint16_t nota_a_semiperiodo_us[] = {
        0,
    16198,  /* B0  */  
    15289,  /* C1  */
    14431,  /* CS1 */ 
    13621,  /* D1  */ 
    12856,  /* DS1 */
    12135,  /* E1  */
    11454,  /* F1  */
    10811,  /* FS1 */
    10204,  /* G1  */
     9631,  /* GS1 */
     9091,  /* A1  */
     8581,  /* AS1 */
     8099,  /* B1  */
     7645,  /* C2  */
     7215,  /* CS2 */
     6810,  /* D2  */
     6428,  /* DS2 */
     6067,  /* E2  */  
     5727,  /* F2  */  
     5405,  /* FS2 */ 
     5102,  /* G2  */  
     4816,  /* GS2 */ 
     4545,  /* A2  */  
     4290,  /* AS2 */ 
     4050,  /* B2  */  
     3822,  /* C3  */  
     3608,  /* CS3 */ 
     3405,  /* D3  */  
     3214,  /* DS3 */ 
     3034,  /* E3  */  
     2863,  /* F3  */  
     2703,  /* FS3 */ 
     2551,  /* G3  */  
     2408,  /* GS3 */ 
     2273,  /* A3  */  
     2145,  /* AS3 */ 
     2025,  /* B3  */  
     1911,  /* C4  */  
     1804,  /* CS4 */ 
     1703,  /* D4  */  
     1607,  /* DS4 */ 
     1517,  /* E4  */  
     1432,  /* F4  */  
     1351,  /* FS4 */ 
     1276,  /* G4  */  
     1204,  /* GS4 */ 
     1136,  /* A4  */  
     1073,  /* AS4 */ 
     1012,  /* B4  */  
      956,  /* C5  */  
      902,  /* CS5 */ 
      851,  /* D5  */  
      804,  /* DS5 */ 
      758,  /* E5  */  
      716,  /* F5  */  
      676,  /* FS5 */ 
      638,  /* G5  */  
      602,  /* GS5 */ 
      568,  /* A5  */  
      536,  /* AS5 */ 
      506,  /* B5  */  
      478,  /* C6  */  
      451,  /* CS6 */ 
      426,  /* D6  */  
      402,  /* DS6 */ 
      379,  /* E6  */  
      358,  /* F6  */  
      338,  /* FS6 */ 
      319,  /* G6  */  
      301,  /* GS6 */ 
      284,  /* A6  */  
      268,  /* AS6 */ 
      253,  /* B6  */  
      239,  /* C7  */  
      225,  /* CS7 */ 
      213,  /* D7  */  
      201,  /* DS7 */ 
      190,  /* E7  */  
      179,  /* F7  */  
      169,  /* FS7 */ 
      159,  /* G7  */  
      150,  /* GS7 */ 
      142,  /* A7  */  
      134,  /* AS7 */ 
      127,  /* B7  */  
      119   /* C8  */ 
};

/***************************************************************************//**
 * \brief       Generar un pitido a través del altavoz.
 *
 * \param[in]   frecuencia      frecuencia del pitido.
 * \param[in]   duracion_ms     duración del pitido en milisegundos.
 */
void sonido_emitir_pitido(uint32_t frecuencia, uint32_t duracion_ms)
{
    uint32_t T_2_us;
    uint32_t N_periodos;
    uint32_t i;
    
    T_2_us = 500000/frecuencia;
    N_periodos = duracion_ms*frecuencia/1000;
    
    LPC_GPIO0->DIR |= 1u << 26;
    
    timer_inicializar(TIMER0);
    timer_iniciar_ciclos_us(TIMER0, T_2_us);
    
    for (i = 0; i < N_periodos; i++)
    {
        LPC_GPIO0->SET = 1u << 26;
        timer_esperar_match0(TIMER0);
        LPC_GPIO0->CLR = 1u << 26;
        timer_esperar_match0(TIMER0);
    }
}

/***************************************************************************//**
 * \brief       Hacer sonar una nota a través del altavoz.
 *
 * \param[in]   nota            nota musical según las definiciones en sonido.h.
 * \param[in]   duracion_ms     duración de la nota en milisegundos.
 */
void sonido_reproducir_nota(uint8_t nota, uint32_t duracion_ms)
{
    uint32_t T_2_us;
    uint32_t N_periodos;
    uint32_t i;
    
    timer_inicializar(TIMER0);
    
    if (nota == 0)
    {
        timer_retardo_ms(TIMER0, duracion_ms);
        return;
    }
    
    T_2_us = nota_a_semiperiodo_us[nota];
    N_periodos = 1000*duracion_ms/(2*T_2_us);
    
    LPC_GPIO0->DIR |= 1u << 26;

    timer_iniciar_ciclos_us(TIMER0, T_2_us);
    
    for (i = 0; i < N_periodos; i++)
    {
        LPC_GPIO0->SET = 1u << 26;
        timer_esperar_match0(TIMER0);
        LPC_GPIO0->CLR = 1u << 26;
        timer_esperar_match0(TIMER0);
    }
}

/***************************************************************************//**
 * \brief       Reproducir una melodía a través del altavoz.
 *
 * \param[in]   melodia             puntero a la secuencia de notas. La melodía
 *                                  termina con una nota NOTA_FIN.
 * \param[in]   duracion_nota_ms    duración en milisegundos de las notas y
 *                                  silencios de la melodía.
 */
void sonido_reproducir_melodia(const uint8_t *melodia, uint32_t duracion_nota_ms)
{
    ASSERT(melodia != NULL, "Puntero a melodia nulo.");
    
    while (*melodia != 255)
    {
        sonido_reproducir_nota(*melodia, duracion_nota_ms);
        melodia++;
    }
}

/*******************************************************************************
 * Funciones del ejercicio 4.
 */

volatile const static uint8_t *ptr_melodia = NULL;
volatile static bool_t  reproduciendo = FALSE;

/***************************************************************************//**
 * \brief       Inicializar el sistema de reproducción de sonidos.
 */
void sonido_inicializar(void)
{
    timer_inicializar(LPC_TIM2);
    
    LPC_TIM2->TCR = 0;
    LPC_TIM2->TC = 0;
    LPC_TIM2->PC = 0;
    LPC_TIM2->PR = PeripheralClock/1000000 - 1;
    LPC_TIM2->MR2 = 1;
    LPC_TIM2->MCR = 1 << 7;
    LPC_TIM2->IR = 1;
    LPC_TIM2->EMR = (3 << 8) | (1 << 2);
    
    LPC_IOCON->P5_0 = 3;
    
    timer_inicializar(TIMER3);
       
    NVIC_ClearPendingIRQ(TIMER3_IRQn);
    NVIC_SetPriority(TIMER3_IRQn, 0);
    NVIC_EnableIRQ(TIMER3_IRQn);
    
    __enable_irq();
}

/***************************************************************************//**
 * \brief       Reproducir una melodía a través del altavoz.
 *
 * \param[in]   melodia             puntero a la secuencia de notas. La melodía
 *                                  termina con una nota NOTA_FIN.
 * \param[in]   duracion_nota_ms    duración en milisegundos de las notas y
 *                                  silencios de la melodía.
 */
void sonido_reproducir_melodia_2(const uint8_t *melodia, uint32_t duracion_nota_ms)
{
    ASSERT(melodia != NULL, "Puntero a melodia nulo.");
    
    ptr_melodia = melodia;
    
    LPC_TIM2->MR2 = nota_a_semiperiodo_us[*ptr_melodia];
    LPC_TIM2->TC = 0;
    LPC_TIM2->TCR = 1;
    
    timer_iniciar_ciclos_ms(TIMER3, duracion_nota_ms);
    
    reproduciendo = TRUE;
}

/***************************************************************************//**
 * \brief       Informar si se está reproduciendo una melodía en este momento.
 *
 * \return      TRUE => sí se esta reproduciendo, FALSE => no se está
 *              reproduciendo.
 */
bool_t sonido_reproduciendo(void)
{
    return reproduciendo;
}

/***************************************************************************//**
 * \brief       Función manejadora de las interrupciones del timer 3.
 */
void TIMER3_IRQHandler(void)
{
    uint8_t siguiente_nota;
    
    LPC_TIM3->IR = 1;
    
    ptr_melodia++;
    siguiente_nota = *ptr_melodia;
    if (siguiente_nota != NOTA_FIN)
    {
        if (siguiente_nota != NOTA_PAUSA)
        {        
            LPC_TIM2->MR2 = nota_a_semiperiodo_us[siguiente_nota];
            LPC_TIM2->TC = 0;
            LPC_TIM2->TCR = 1;
        }
        else
        {
            LPC_TIM2->TCR = 0;
        }
    }
    else
    {
        LPC_TIM2->TCR = 0;
        LPC_TIM3->TCR = 0;
        reproduciendo = FALSE;
    }
}

