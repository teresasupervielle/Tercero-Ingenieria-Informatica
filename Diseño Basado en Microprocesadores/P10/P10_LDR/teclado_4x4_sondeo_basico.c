/***************************************************************************//**
 * \file    teclado_4x4_sondeo_basico.c
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
 *          Esta es la versión más básica sin sondeo periódico con timer ni
 *          interrupciones GPIO.
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
 *          Las funciones de lectura del teclado usan un timer para realizar
 *          retardos y medidas de tiempo. El timer usado está definido por el
 *          símbolo TEC4X4_TIMER en el fichero teclado_4x4.h.
 *
 *          La aplicación debe llamar primero a la función tec4x4_inicializar.
 *          Después, cada vez que quiera realizar un barrido del teclado para
 *          saber si se está presionando una tecla debe llamar a la función
 *          tec4x4_leer o tec4x4_esperar_pulsacion.
 *
 *          La función tec4x4_leer realiza un barrido del teclado y no incluye
 *          filtrado de rebotes.
 *
 *          La función tec4x4_esperar_pulsacion sí incluye filtrado de rebotes.
 *
 *          Se suministra también la función tec4x4_esperar_pulsacion_con_rebotes
 *          para que pueda apreciarse el efecto de los rebotes.
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

/***************************************************************************//**
 * \brief       Función de retardo usada por las funciones del teclado.
 *                                        
 *              Las funciones del teclado necesitan realizar simultáneamente
 *              medidas de tiempo y retardos usando un mismo timer (usar dos
 *              timers para el teclado se ha considerado excesivo). Por tanto,
 *              la función timer_retardo_us no es adecuada por que ésta pone a 0
 *              los contadores del timer cada vez que se la llama.
 *
 *              Es necesario que el timer usado por el teclado haya sido
 *              inicializado y se encuentre contando en microsegundos antes de
 *              llamar a esta función.
 *
 * \param[in]   retardo_us  retardo en microsegundos.
 */
static void tec4x4_retardo_us(uint32_t retardo_us)
{
    uint32_t lectura_timer_inicial;
    
    if (retardo_us == 0) return;
    
    /* Capturar el valor del contador al comienzo del retardo.
     */
    lectura_timer_inicial = timer_leer(TEC4X4_TIMER);
    
    /* Esperar mientras la diferencia entre el valor del contador a medida que
     * se incrementa y el valor inicial capturado sea menor que tiempo de
     * retardo requerido.
     * Se usan implícitamente las propiedades de la aritmética módulo 32 para
     * tratar el caso de que el contador del timer sobrepase 0xFFFFFFFF durante
     * el retardo.
     */
    while (timer_leer(TEC4X4_TIMER) - lectura_timer_inicial < retardo_us) {}    
}

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
 *          (ver nota).
 *          
 *          Se inicializa el timer usado por las funciones del teclado.
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
     * Configurar como GPIO los cuatro pines conectados a las columnas y activar sus
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
    
    /* Todos los pines de fila se configuran inicialmente como entradas.
     */
    gpio_ajustar_dir(TEC4X4_PUERTO_FILAS,
                     TEC4X4_MASCARA_TODAS_LAS_FILAS,
                     DIR_ENTRADA);

    /* Todos los pines de columna se configuran como entradas y permanecerán así
     * todo el tiempo.
     */
    gpio_ajustar_dir(TEC4X4_PUERTO_COLUMNAS,
                     TEC4X4_MASCARA_TODAS_LAS_COLUMNAS,
                     DIR_ENTRADA);
                     
    /* Inicializar el timer usado por el teclado y programarlo para que cuente
     * en microsegundos.
     */
    timer_inicializar(TEC4X4_TIMER);
    timer_iniciar_conteo_us(TEC4X4_TIMER);
}

/***************************************************************************//**
 * \brief   Realiza un barrido del teclado.
 *
 * \return  Código ASCII de la tecla pulsada o 0 si no se está pulsando
 *          ninguna tecla.
 */
char tec4x4_leer(void)
{
    char tecla = 0;
    uint32_t fila, columna;
    uint32_t estado_puerto_columnas;
    
    /* Bucle para barrer las líneas de fila. El proceso se interrumpe en cuanto
     * se detecta una pulsación.
     */
    for (fila = 0; fila < 4 && tecla == 0; fila++)
    {
        /* Configurar un pin de fila como salida y ponerlo a 0.
         *
         * Accediendo a los registros de los GPIO:
         *
         * TEC4X4_PUERTO_FILAS->DIR |= mascaras_filas[fila];
         * TEC4X4_PUERTO_FILAS->CLR = mascaras_filas[fila];
         *
         * O usando las funciones de acceso a los GPIO:
         */
        gpio_ajustar_dir(TEC4X4_PUERTO_FILAS, mascaras_filas[fila], DIR_SALIDA);
        gpio_pin_a_0(TEC4X4_PUERTO_FILAS, mascaras_filas[fila]);
        
        /* Esperar un tiempo para compensar capacidades parásitas y reflexiones
         * en los cables de conexión.
         */
        tec4x4_retardo_us(TEC4X4_TIEMPO_ESTABILIZACION_US);
        
        /* Leer el puerto al que están conectadas las columnas.
         */        
        estado_puerto_columnas = gpio_leer_puerto(TEC4X4_PUERTO_COLUMNAS);
        
        /* Bucle para comprobar líneas de columna.
         */
        for (columna = 0; columna < 4; columna++)
        {
            /* Si se encuentra una línea de columna a 0 significa que hay
             * pulsación en la fila y columna actuales. El carácter correspondiente
             * a la pulsación se obtiene del array matriz_teclas. El break sale
             * del bucle de columnas y al ser tecla != 0 se saldrá también del
             * bucle de filas.
             */ 
            if ((estado_puerto_columnas & mascaras_columnas[columna]) == 0)
            {
                tecla = matriz_teclas[fila][columna];
                break;
            }
        }
        /* Volver a configurar el pin de fila como entrada.
         *
         * Accediendo a los registros de los GPIO:
         *
         * TEC4X4_PUERTO_FILAS->DIR &= ~mascaras_filas[fila];
         *
         * O usando las funciones de acceso a los GPIO:
         */
        gpio_ajustar_dir(TEC4X4_PUERTO_FILAS, mascaras_filas[fila], DIR_ENTRADA);
    }
    
    return tecla;
}

/***************************************************************************//**
 * \brief   Espera a que el teclado se encuentre en una situación estable
 *          durante un tiempo TEC4X4_TIEMPO_FILTRO_REBOTES_US. La ejecución
 *          se mantiene dentro de la función mientras se produzcan cambios de
 *          duración inferior a TEC4X4_TIEMPO_FILTRO_REBOTES_US.
 *
 * \return  Código ASCII de la tecla que se detectado sin cambios durante
 *          TEC4X4_TIEMPO_FILTRO_REBOTES_US. Retorna 0 si el teclado se ha
 *          mantenido sin ninguna pulsación durante este tiempo.
 */
char tec4x4_esperar_estable(void)
{
    /* La variable estado_actual indicará cómo se encuentra el teclado en un
     * instante dado.
     * La variable estado_ultimo_cambio indicará a qué estado cambió el
     * teclado la vez anterior que se detectó un cambio.
     */
    char estado_actual;
    char estado_ultimo_cambio;    
        
    /* Las dos variables se inicializan con el estado actual del teclado.
     */
    estado_actual = estado_ultimo_cambio = tec4x4_leer();      
    
    /* La cuenta en microsegundos del timer usado por el teclado se pone a 0.
     * (El timer ya está contando en microsegundos).
     */
    timer_poner_contador_a_0(TEC4X4_TIMER);
    
    /* Mientras el contador en microsegundos no alcance
     * TEC4X4_TIEMPO_FILTRO_REBOTES_US, es decir, mientras el teclado no
     * permanezca estable TEC4X4_TIEMPO_FILTRO_REBOTES_US ...
     */
    while (timer_leer(TEC4X4_TIMER) < TEC4X4_TIEMPO_FILTRO_REBOTES_US)           
    {
        /* Leer el estado del teclado en este instante.
         */
        estado_actual = tec4x4_leer();
        
        /* Si el estado actual no coincide con el registrado tras el cambio
         * anterior el teclado no está permaneciendo estable. Entonces,
         * se pone a 0 el contador de tiempo estable y estado_ultimo_cambio
         * actualiza al estado actual.
         */
        if (estado_actual != estado_ultimo_cambio)
        {
            timer_poner_contador_a_0(TEC4X4_TIMER);
            estado_ultimo_cambio = estado_actual;
        }
    }
    
    /* Cuando el teclado permanece sin cambios durante
     * TEC4X4_TIEMPO_FILTRO_REBOTES_US termina el bucle anterior y se sale de la
     * función indicando el estado estable alcanzado.
     */
    return estado_actual;
}

/***************************************************************************//**
 * \brief   Esperar la pulsación de una tecla y retornar su código ASCII
 *          filtrando los rebotes del teclado mediante la función
 *          tec4x4_esperar_estable.
 *
 * \return  Código ASCII de la tecla pulsada.
 */
char tec4x4_esperar_pulsacion(void)
{
    char tecla;

    /* Esperar mientras se detecte una pulsación.
     */    
    while (tec4x4_esperar_estable() != TEC4X4_NINGUNA_PULSADA) {}

    /* Luego, esperar mientras no se detecte una pulsación.
     */       
    do
    {
        tecla = tec4x4_esperar_estable();
    }
    while (tecla == TEC4X4_NINGUNA_PULSADA);
    
    /* El bucle do-while anterior también puede cambiarse por este while
     * incluyendo la asignación a tecla dentro de la expresión de la condición.
     *
     *     while ((tecla = tec4x4_esperar_estable()) ==
     *            TEC4X4_NINGUNA_PULSADA) {}
     */

    /* Retornar la pulsación detectada.
     */    
    return tecla;
}

/***************************************************************************//**
 * \brief  Esperar la pulsación de una tecla y retornar su código ASCII SIN
 *         realizar filtrado de rebotes.
 *
 *         La finalidad de esta función es precisamente mostrar el efecto de
 *         los rebotes.
 *
 * \return  Código ASCII de la tecla pulsada.
 */
char tec4x4_esperar_pulsacion_con_rebotes(void)
{
    char tecla;
 
    /* Esperar mientras se detecte una pulsación.
     */
    while (tec4x4_leer() != TEC4X4_NINGUNA_PULSADA) {}
    
    /* Luego, esperar mientras no se detecte una pulsación.
     */
    do
    {
        tecla = tec4x4_leer();
    }
    while (tecla == TEC4X4_NINGUNA_PULSADA);
    
    /* El bucle do-while anterior también puede cambiarse por este while
     * incluyendo la asignación a tecla dentro de la expresión de la condición.
     *
     *     while ((tecla = tec4x4_leer()) == TEC4X4_NINGUNA_PULSADA) {}
     */

    /* Retornar la pulsación detectada.
     */
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
