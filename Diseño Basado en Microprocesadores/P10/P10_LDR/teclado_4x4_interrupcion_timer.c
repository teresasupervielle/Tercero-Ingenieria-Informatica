/***************************************************************************//**
 * \file    teclado_4x4_interrupcion_timer.c
 *
 * \brief   Funciones para manejar un teclado matricial 4x4.
 *
 *          La disposición de la teclas es siguientes teclas:
 *
 *                  Columna 0   Columna 1   Columna 2   Columna 3 
 *                  
 *          Fila 0      1           2           3           A
 *          Fila 1      4           5           6           B
 *          Fila 2      7           8           9           C
 *          Fila 3      *           0           #           D
 *
 *          Esta versión usa un timer y su interrupción para sondear el teclado
 *          periódicamente.
 *
 *          También incluye un buffer para guardar pulsaciones hasta que la
 *          aplicación las solicite. El tamaño del buffer está dado por el
 *          símbolo TEC4X4_TAMANO_BUFFER definido en teclado_4x4.h.
 *          
 *          Los pines del microcontrolador usados para conectar a las líneas de
 *          fila y columna está definidos en el fichero teclado_4x4.h.
 *
 *          Se asume que todas las filas están conectadas a los pines de un
 *          mismo puerto GPIO y que también todas las columnas están conectadas
 *          a los pines de un mismo puerto, no necesariamente el mismo que el
 *          utilizado para las filas.
 *
 *          Los pines del microcontrolador que se usen para conectar a las
 *          líneas de columna deben tener la posibilidad de activar resistencias
 *          de pull-up internas. Si uno o más de estos pines no disponen de
 *          resistencias de pull-up internas, deben conectarse resistencias de
 *          pull-up en el exterior.
 *
 *          El timer usado para el barrido periódico está definido por el
 *          símbolo TEC4X4_TIMER en el fichero teclado_4x4.h.
 *
 *          La aplicación debe llamar primero a la función tec4x4_inicializar.
 */
 
#include <LPC407x_8x_177x_8x.h>
#include "teclado_4x4.h"
#include "iocon_lpc40xx.h"
#include "gpio_lpc40xx.h"
#include "timer_lpc40xx.h"
#include "error.h"
#include "glcd.h"

/* Array para obtener una máscara de fila a partir de un número de fila.
 */
static const uint32_t mascaras_filas[4] = {TEC4X4_MASCARA_FILA_0, 
                                           TEC4X4_MASCARA_FILA_1,
                                           TEC4X4_MASCARA_FILA_2,
                                           TEC4X4_MASCARA_FILA_3};

/* Array para obtener una máscara de columna a partir de un número de columna.
 */
static const uint32_t mascaras_columnas[4] = {TEC4X4_MASCARA_COLUMNA_0, 
                                              TEC4X4_MASCARA_COLUMNA_1,
                                              TEC4X4_MASCARA_COLUMNA_2,
                                              TEC4X4_MASCARA_COLUMNA_3};                                   

/* Matriz para obtener el ASCII de la tecla posición del teclado.
 */
static const char matriz_teclas[4][4] = {{'1', '2', '3', 'A'},
                                         {'4', '5', '6', 'B'},
                                         {'7', '8', '9', 'C'},
                                         {'*', '0', '#', 'D'}};

/* Buffer para almacenar temporalmente los caracteres que se pulsan hasta que la
 * aplicación los lea.
 */
static char buffer_teclado[TEC4X4_TAMANO_BUFFER];

/* Índice dentro de buffer_teclado donde se almacenará el siguiente carácter.
 */
static uint32_t indice_escritura = 0;

/* Índice dentro de buffer_teclado de donde se leerá el siguiente carácter.
 */
static uint32_t indice_lectura = 0;

/* Número de caracteres almacenados actualmente en el buffer del teclado.
 */
static uint32_t numero_caracteres_en_buffer = 0;

/***************************************************************************//**
 * \brief   Inicializar la lectura del teclado.
 *
 *          Los ocho pines del microcontrolador conectados a las filas y
 *          columnas se configuran como GPIO (ver nota).
 *                                         
 *          Se desactivan las resistencias de pull-up y pull-down internas de
 *          los cuatro pines del microcontrolador conectados a las filas, ya que
 *          estos pines no llegarán a ser leídos, aunque en un momento dado
 *          estén configurados como entradas, y por tanto no son necesarias.
 *
 *          Se activan las resistencias de pull-up internas de los cuatro pines
 *          del microcontrolador conectados a las columnas (ver nota).
 *
 *          Los ocho pines del microcontrolador que conectan con las filas y
 *          columnas del teclado se configuran inicialmente como entradas
 *          (ver nota), excepto el pin conectado a la fila 0, que se configura
 *          como salida y se pone a 0 para que cuando se ejecute por primera
 *          vez el manejador de interrupción del timer esté preparada la
 *          lectura de la primera fila.
 *          
 *          Se inicializa el timer usado por las funciones del teclado y se
 *          programa para que realice ciclos de duración TEC4X4_TIEMPO_FILA_US
 *          definido en teclado_4x4.h
 *
 *          Se configura y habilita la interrupción del timer con prioridad dada
 *          el símbolo TEC4X4_PRIORIDAD_INTERRUPCION definido en teclado_4x4.h.
 *
 * \note    Aunque tras el reset esta debería ser la configuración por defecto
 *          la función se asegura de ello por si previamente se había cambiado.
 */
void tec4x4_inicializar(void)
{
    uint32_t i;
    
    /* Configurar como GPIO los cuatro pines conectados a las filas y desactivar
     * sus pull-ups y pull-downs.
     *
     * Configurar como GPIO los cuatro pines conectados a las columnas y activas sus
     * pull-ups.
     *
     * Se podría usar también la función iocon_configurar_grupo_pines.
     */
    for (i = 0; i < 4; i++)
    {
        iocon_configurar_pin(TEC4X4_PUERTO_FILAS,
                             mascaras_filas[i],
                             GPIO,
                             IOCON_NO_PULL_UP_NO_PULL_DOWN);
        iocon_configurar_pin(TEC4X4_PUERTO_COLUMNAS,
                             mascaras_columnas[i],
                             GPIO,
                             IOCON_PULL_UP);
    }
    
    /* El pin que maneja la fila 0 se configura como salida y se pone a 0.
     */
    gpio_ajustar_dir(TEC4X4_PUERTO_FILAS, TEC4X4_MASCARA_FILA_0, DIR_SALIDA);
    gpio_pin_a_0(TEC4X4_PUERTO_FILAS, TEC4X4_MASCARA_FILA_0);
    
    /* Los demás pines de fila se configuran inicialmente como entradas.
     */    
    gpio_ajustar_dir(TEC4X4_PUERTO_FILAS,
                     TEC4X4_MASCARA_FILA_1 |
                     TEC4X4_MASCARA_FILA_2 |
                     TEC4X4_MASCARA_FILA_3,
                     DIR_ENTRADA);

    /* Todos los pines de columna se configuran como entradas.
     */
    gpio_ajustar_dir(TEC4X4_PUERTO_COLUMNAS,
                     TEC4X4_MASCARA_TODAS_LAS_COLUMNAS,
                     DIR_ENTRADA);
                     
    /* Inicializar el timer usado por el teclado y programarlo para que realice
     * ciclos de duración TEC4X4_TIEMPO_FILA_US microsegundos.
     */
    timer_inicializar(TEC4X4_TIMER);    
    timer_iniciar_ciclos_us(TEC4X4_TIMER, TEC4X4_TIEMPO_FILA_US);
    
    /* Configurar y habilitar la interrupción del timer.
     */
    NVIC_ClearPendingIRQ(TEC4X4_TIMER_IRQn);
    NVIC_SetPriority(TEC4X4_TIMER_IRQn, TEC4X4_PRIORIDAD_INTERRUPCION);
    NVIC_EnableIRQ(TEC4X4_TIMER_IRQn);
    __enable_irq();
}

/***************************************************************************//**
 * \brief       Introducir un carácter en el buffer del teclado.
 *
 * \param[in]   c   carácter a introducir.
 *
 * \return      TRUE => la operación se completó con éxito.
 *              FALSE => el buffer de teclado está completamente lleno. No se
 *              introdujo el carácter.
 */
static bool_t tec4x4_insertar_en_buffer(char c)
{    
    if (numero_caracteres_en_buffer == TEC4X4_TAMANO_BUFFER)
    {
        return FALSE;
    }
    
    NVIC_DisableIRQ(TEC4X4_TIMER_IRQn);
    
    buffer_teclado[indice_escritura] = c;
    
    numero_caracteres_en_buffer++;
    
    if (indice_escritura < TEC4X4_TAMANO_BUFFER - 1)
    {
        indice_escritura++;
    }
    else
    {
        indice_escritura = 0;
    }
    
    NVIC_EnableIRQ(TEC4X4_TIMER_IRQn);
    
    return TRUE;
}

/***************************************************************************//**
 * \brief       Extraer un carácter del buffer del teclado.
 *
 * \param[out]  ptr puntero con la dirección donde almacenar el carácter extraído.
 *
 * \return      TRUE => había al menos un carácter en el buffer.
 *              FALSE => el buffer estaba vacío. No pudo extraerse ningún carácter.
 */
static bool_t tec4x4_extraer_de_buffer(char *ptr)
{
    ASSERT(ptr != NULL, "Puntero ptr nulo.");
    
    if (numero_caracteres_en_buffer == 0)
    {
        return FALSE;
    }
    
    NVIC_DisableIRQ(TEC4X4_TIMER_IRQn);
    
    *ptr = buffer_teclado[indice_lectura];
    
    numero_caracteres_en_buffer--;
    
    if (indice_lectura < TEC4X4_TAMANO_BUFFER - 1)
    {
        indice_lectura++;
    }
    else
    {
        indice_lectura = 0;
    }
    
    NVIC_EnableIRQ(TEC4X4_TIMER_IRQn);
    
    return TRUE;
}

/***************************************************************************//**
 * \brief   Vaciar el buffer del teclado.
 */
void tec4x4_vaciar_buffer(void)
{
    NVIC_DisableIRQ(TEC4X4_TIMER_IRQn);
    indice_escritura = 0;
    indice_lectura = 0;
    numero_caracteres_en_buffer = 0;
    NVIC_EnableIRQ(TEC4X4_TIMER_IRQn);
}

/***************************************************************************//**
 * \brief   Retorna el número de caracteres almacenados actualmente en el
 *          buffer del teclado.
 *
 * \return  Número de caracteres en el buffer del teclado.
 */
uint32_t tec4x4_caracteres_en_buffer(void)
{
    return numero_caracteres_en_buffer;
}

/***************************************************************************//**
 * \brief   Obtiene el siguiente carácter del buffer del teclado.
 *
 * \return  Código ASCII del carácter o 0 si el buffer de teclado está vacío.
 */
char tec4x4_leer(void)
{
    char tecla;
    bool_t hay_tecla;
    
    hay_tecla = tec4x4_extraer_de_buffer(&tecla);
    
    if (hay_tecla) return tecla;
    else return 0;
}

/***************************************************************************//**
 * \brief   Espera hasta que haya al menos un carácter en el buffer de teclado
 *          y lo retorna.
 *
 * \return  Código ASCII de la tecla pulsada.
 */
char tec4x4_esperar_pulsacion(void)
{
    char tecla;
    bool_t hay_tecla;
    
    do
    {
        hay_tecla = tec4x4_extraer_de_buffer(&tecla);
    }
    while (!hay_tecla);

    return tecla;
}

/***************************************************************************//**
 * \brief       Leer una cadena de caracteres del teclado.
 *
 *              Las pulsaciones en el teclado se reflejarán en el LCD.
 *
 *              La lectura de la cadena terminará cuando se pulse el carácter
 *              '#' que actúa a modo de ENTER.
 *
 *              La función sólo almacena en el buffer los (tamano_buffer - 1)
 *              primeros caracteres que se pulsen y descartará el resto.
 *
 *              No se usa ningún carácter para borrado, así que los caracteres
 *              que se tecleen y almacenen en la cadena no pueden borrarse
 *              después.
 *
 * \param[out]  ptr_buffer      puntero al buffer donde se almacenará la cadena.
 *                              La cadena quedará terminada con un carácter nulo.
 *
 * \parar[in]   tamano_buffer   longitud del buffer en bytes. La función sólo
 *                              almacenará en el buffer los (tamano_buffer - 1)
 *                              primeros caracteres que se pulsen. El tamaño
 *                              del buffer debe ser como mínimo 1 para tener
 *                              espacio al menos para el terminador.
 */
void tec4x4_leer_cadena(char *ptr_buffer, uint32_t tamano_buffer)
{
    char c;
    
    ASSERT(ptr_buffer != NULL, "El puntero al buffer es nulo.");
    ASSERT(tamano_buffer >= 1, "El tamaño mínimo del buffer es 1");

    do
    {       
        /* Esperar la pulsación de una tecla y leerla.
         */
        c = tec4x4_esperar_pulsacion();
            
        /* Almacenar en la cadena sólo si no es '#' (ENTER) y en
         * el buffer aún hay espacio para este carácter y el terminador
         * nulo que se añadirá al final del proceso de recepción.
         */
        if (c != '#' && tamano_buffer > 1)
        {
            *ptr_buffer = c;
            glcd_printf("%c", c);
            ptr_buffer++;
            tamano_buffer--;
        }
    }
    while (c != '#');  /* Terminar la lectura si se pulsó '#'.
                         */
    
    /* Almacena el terminador nulo al final de la cadena recibida.
     */
    *ptr_buffer = 0;
}

/***************************************************************************//**
 * \brief       Leer una cadena de caracteres numéricos del teclado.
 *
 *              Las pulsaciones en el teclado se reflejarán en el LCD.
 *
 *              La lectura de la cadena terminará cuando se pulse el carácter
 *              '#' que actúa a modo de ENTER.
 *
 *              La función sólo almacena en el buffer los (tamano_buffer - 1)
 *              primeros caracteres que se pulsen y descartará el resto.
 *
 *              No se usa ningún carácter para borrado así que los caracteres
 *              que se tecleen y almacenen en la cadena no pueden borrarse
 *              después.
 *
 * \param[out]  ptr_buffer      puntero al buffer donde se almacenará la cadena.
 *                              La cadena quedará terminada con un carácter nulo.
 *
 * \parar[in]   tamano_buffer   longitud del buffer en bytes. La función sólo
 *                              almacenará en el buffer los (tamano_buffer - 1)
 *                              primeros caracteres que se pulsen. El tamaño
 *                              del buffer debe ser como mínimo 1 para tener
 *                              espacio al menos para el terminador.
 */
void tec4x4_leer_cadena_numeros(char *ptr_buffer, uint32_t tamano_buffer)
{
    char c;
    
    ASSERT(ptr_buffer != NULL, "El puntero al buffer es nulo.");
    ASSERT(tamano_buffer >= 1, "El tamaño mínimo del buffer es 1");

    do
    {       
        /* Esperar la pulsación de una tecla y leerla.
         */
        c = tec4x4_esperar_pulsacion();
            
        /* Almacenar en la cadena sólo si no es '#' (ENTER) y en
         * el buffer aún hay espacio para este carácter y el terminador
         * nulo que se añadirá al final del proceso de recepción.
         */
        if ('0' <= c && c <= '9' && tamano_buffer > 1)
        {
            *ptr_buffer = c;
            glcd_printf("%c", c);
            ptr_buffer++;
            tamano_buffer--;
        }
    }
    while (c != '#');  /* Terminar la lectura si se pulsó '#'.
                         */
    
    /* Almacena el terminador nulo al final de la cadena recibida.
     */
    *ptr_buffer = 0;
}

/***************************************************************************//**
 * \brief   Función de interrupción del timer usado por el teclado.
 */
void TEC4X4_TIMER_IRQHandler(void)
{                 
    /* pulsacion_actual comienza en TEC4X4_NINGUNA_PULSADA al principio de cada
     * barrido y cambia a la tecla pulsada cuando se detecta una pulsación
     * a lo largo de un barrido.
     */
    static char pulsacion_actual = TEC4X4_NINGUNA_PULSADA;
    
    /* estado_estable_anterior indica el último estado estable registrado.
     */    
    static char estado_estable_anterior = TEC4X4_NINGUNA_PULSADA;
    
    /* Cuando se produce un cambio en el estado de pulsación del teclado (de no
     * pulsado a pulsado, de no pulsado a pulsado o de un estado de pulsación a
     * otro) esta variable indica el estado del teclado después de ese último
     * cambio.
     */
    static char estado_ultimo_cambio = TEC4X4_NINGUNA_PULSADA;
    
    /* tiempo_estable_us mide el tiempo que, a lo largo de barridos completos
     * sucesivos del teclado, éste se mantiene en el mismo estado. Si el estado
     * cambia, tiempo_estable_us vuelve a 0.
     */
    static uint32_t tiempo_estable_us = 0;  

    /* Fila del teclado activa actualmente. Va tomando los valores
     * 0, 1, 2, 3, 0, 1, ... a lo largo de sucesivas ejecuciones del manejador
     * de interrupción para activar cada vez una fila del teclado.
     */
    static uint32_t fila = 0;

    /* estado_ultimo_barrido indica la tecla detectada en el último barrido
     * del teclado (o 0 si no se detectó ninguna pulsación).
     */    
    char estado_ultimo_barrido = TEC4X4_NINGUNA_PULSADA;
    
    uint32_t columna;                                      
    uint32_t estado_puerto_columnas;
    
    /* Borrar el flag de petición de interrupción del timer.
     */
    TEC4X4_TIMER->IR = 1;
    
    /* Comprobar la fila actual.
     */ 
    estado_puerto_columnas = gpio_leer_puerto(TEC4X4_PUERTO_COLUMNAS);
    for (columna = 0; columna < 4; columna++)
    {
        if ((estado_puerto_columnas & mascaras_columnas[columna]) == 0)
        {
            /* Si se encuentra pulsación en esta fila y columa, pulsacion_actual
             * toma el ASCII de la tecla pulsada.
             */
            pulsacion_actual = matriz_teclas[fila][columna];
            break;
        }
    }

    /* Volver a configurar la fila actual como entrada.
     */
    gpio_ajustar_dir(TEC4X4_PUERTO_FILAS, mascaras_filas[fila], DIR_ENTRADA);
    
    /* Pasar a la siguiente fila ...
     */
    if (fila < 3) 
    {
        fila++;
    }
    else
    {        
        /* ... pero si ya es 3, volver a la fila 0.
         */
        fila = 0;
        
        /* Además, esto significa que se ha completado un barrido de todo el
         * teclado.
         */
        
        estado_ultimo_barrido = pulsacion_actual;
        
        /* Si el teclado se mantiene igual desde el último cambio ...
         */
        if (estado_ultimo_barrido == estado_ultimo_cambio)
        {
            /* Aumentar el contador de tiempo estable.
             */
            tiempo_estable_us += TEC4X4_PERIODO_BARRIDO_US;
            
            /* Si tiempo_estable_us llega a TEC4X4_TIEMPO_FILTRO_REBOTES_US
             * significa que el nuevo estado se ha repetido
             * TEC4X4_TIEMPO_FILTRO_REBOTES_US / TEC4X4_PERIODO_BARRIDO_US
             * veces en sucesivos barridos completos del teclado y por tanto
             * se considera estable.
             */                
            if (tiempo_estable_us >= TEC4X4_TIEMPO_FILTRO_REBOTES_US)
            {                
                /* Si el nuevo estado estable es una pulsación y el anterior era
                 * una "no pulsación", introducir el carácter en el buffer del
                 * teclado.
                 */
                if (estado_ultimo_barrido != TEC4X4_NINGUNA_PULSADA &&
                    estado_estable_anterior == TEC4X4_NINGUNA_PULSADA)
                {
                    tec4x4_insertar_en_buffer(estado_ultimo_barrido);
                }
                
                /* El nuevo estado estable es el presente.
                 */
                estado_estable_anterior = estado_ultimo_barrido;
                
                /* Poner a cero la cuenta de tiempo estable.
                 */                            
                tiempo_estable_us = 0;
            }      
        }
        else
        {
            /* Si hay cambio en el estado del teclado, poner la cuenta de tiempo
             * estable a 0 y memorizar el nuevo estado en estado_ultimo_cambio.
             */
            tiempo_estable_us = 0;
            estado_ultimo_cambio = pulsacion_actual;
        }
        
        /* Borrar la pulsación actual de cara al siguiente barrido.
         */
        pulsacion_actual = TEC4X4_NINGUNA_PULSADA;
    }
    
    /* Configurar la siguiente fila como salida y ponerla a 0.
     */
    gpio_ajustar_dir(TEC4X4_PUERTO_FILAS, mascaras_filas[fila], DIR_SALIDA);
    gpio_pin_a_0(TEC4X4_PUERTO_FILAS, mascaras_filas[fila]);    
}
