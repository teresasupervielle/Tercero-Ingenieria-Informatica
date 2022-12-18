/***************************************************************************//**
 * \brief   Funciones de manejo del LCD de 4.3" desde la tarjeta Embedded Artist
 *          Developer's Kit.
 */
 
#include <LPC407x_8x_177x_8x.h>
#include "glcd.h"
#include "sdram.h"
#include "font.h"
#include "error.h"
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

/* Punteros a font definidos en otros ficheros fuente.
 */
extern font_t font_8x16;
extern font_t font_12x24;
extern font_t font_16x32;

/* Tabla para obtener un puntero a font a partir de un número de font.
 */
static font_t *tabla_fonts[NUMERO_FONTS] =
{
    &font_8x16,
    &font_12x24,
    &font_16x32
};

/* Variables estáticas que determinan el color, font y posición para la salida
 * de texto actual mediante glcd_printf.
 */
static uint16_t color_texto_actual = WHITE;
static uint16_t color_fondo_texto_actual = BLACK;
static uint32_t font_actual = FONT16X32;
static int32_t x_texto_actual = 0;
static int32_t y_texto_actual = 0;
static bool_t desplazamiento_activado = TRUE;

/* ###################### COMENTAR */
FILE __stdout;
FILE __stdin;
FILE __stderr;

/***************************************************************************//**
 * \brief       Función de retardo empleando el timer 0. Usada durante la
 *              inicialización del controlador de LCD.
 *
 * \param[in]   ms  retardo en milisegundos.
 *
 */
static void glcd_timer0_retardo_ms(uint32_t ms)
{
    if (ms == 0) return;
    
    LPC_TIM0->TCR = 0;
    LPC_TIM0->PC = 0;
    LPC_TIM0->TC = 0;
    LPC_TIM0->PR = PeripheralClock/1000000 - 1;
    LPC_TIM0->MR0 = 1000*ms - 1;
    LPC_TIM0->MCR |= 7;
    LPC_TIM0->IR = 1;
    LPC_TIM0->TCR = 1;
    while ((LPC_TIM0->IR & 1) == 0);
}

/***************************************************************************//**
 * \brief       Inicializar el interfaz I2C 0 del como máster.
 *
 * \param[in]   scll    valor para el registro SCLL.
 * \param[in]   sclh    valor para el registro SCLH.
 */
static void glcd_i2c0_inicializar(uint32_t scll, uint32_t sclh) 
{
    /* Aplicar alimentación al módulo I2C0.
     */ 
    LPC_SC->PCONP |= (1 << 7);
    
    /* Configurar P0.27 como SDA0 y P0.28 como SCL0.
     */
    LPC_IOCON->P0_27 |= 1;
    LPC_IOCON->P0_28 |= 1;
	
    /* Borrar flags.
     */
    LPC_I2C0->CONCLR = (1 << 6) | (1 << 5) | (1 << 3) | (1 << 2);    

    /* Configurar velocidad.
     */
    LPC_I2C0->SCLL   = scll;
    LPC_I2C0->SCLH   = sclh;

    /* Habilitar el interfaz.
     */
    LPC_I2C0->CONSET = 1 << 6; 
}

/***************************************************************************//**
 * \brief   Crear condición de start.
 *
 * \return  Valor del registro I2C0STAT.
 */
static int glcd_i2c0_start(void)
{
    uint32_t contador = 0;
    
    /* Crear condición START.
     */
    LPC_I2C0->CONSET = 1 << 5;
 
    /* Esperar hasta que se transmita START o expire el I2C0_TIMEOUT.
     */
    while ((LPC_I2C0->CONSET & (1 << 3)) == 0)
    {
        contador++;
        if (contador > 0x01000000) return -1;
    }

    LPC_I2C0->CONCLR = 1 << 5;

    return LPC_I2C0->STAT;
}

/***************************************************************************//**
 * \brief   Crear condición de stop.
 */
static void glcd_i2c0_stop(void)
{
    LPC_I2C0->CONCLR = 1 << 3;     
    LPC_I2C0->CONSET = 1 << 4; 
                
    while (LPC_I2C0->CONSET & (1 << 4));    
}

/***************************************************************************//**
 * \brief       Transmitir un byte a un esclavo a través del I2C 0.
 *
 * \param[in]   dato    byte a transmitir.
 *
 * \return      Valor del registro I2C0STAT.
 *
 */
static int glcd_i2c0_transmitir_byte(uint8_t dato) 
{
    LPC_I2C0->CONCLR = 1 << 3;    
    
    LPC_I2C0->DAT = dato;

    while ((LPC_I2C0->CONSET & (1 << 3)) == 0);

    return LPC_I2C0->STAT;
}

/***************************************************************************//**
 * \brief
 *
 * \param[in]
 * \param[in]
 * \param[in]
 */
static int glcd_i2c0_transmitir_buffer(uint8_t addr, uint8_t* buf, uint32_t len) 
{
    int i;
	
	glcd_i2c0_start();
    glcd_i2c0_transmitir_byte(addr << 1);
	for (i = 0; i < len; i++)
	{
        glcd_i2c0_transmitir_byte(*buf);
		buf++;
	}
    glcd_i2c0_stop();
		
	return 0;
}

/***************************************************************************//**
 * \brief   Inicializar el controlador LCD.
 */
void glcd_inicializar(void)
{
    uint32_t i;
    uint8_t buffer[5];
    
    /* Inicializar el interfaz I2C 0. El interfaz I2C 0 se usará para comunicar
     * con el ...
     */
    glcd_i2c0_inicializar(300, 300);
    
    /* Inicializar el controlador de SDRAM. El framebuffer se mantiene en la
     * SDRAM conectada al LPC4088 en la tarjeta de desarrollo.
     */
    sdram_inicializar();

    /* Configurar la función de los pines del LPC4088 que se usan para controlar
     * la pantalla LCD.
     */    
    LPC_IOCON->P0_4 |= 7;   /* P0[4] --> LCD_VD_0 */
    LPC_IOCON->P0_5 |= 7;   /* P0[5] --> LCD_VD_1 */
    LPC_IOCON->P0_6 |= 7;   /* P0[6] --> LCD_VD_8 */
    LPC_IOCON->P0_7 |= 7;   /* P0[7] --> LCD_VD_9 */
    LPC_IOCON->P0_8 |= 7;   /* P0[8] --> LCD_VD_16 */
    LPC_IOCON->P0_9 |= 7;   /* P0[9] --> LCD_VD_17 */
    LPC_IOCON->P0_10 |= 7;  /* P0[10] --> LCD_VD_5 */

    LPC_IOCON->P1_20 |= 7;  /* P1[20] --> LCD_VD_10 */
    LPC_IOCON->P1_21 |= 7;  /* P1[21] --> LCD_VD_11 */
    LPC_IOCON->P1_22 |= 7;  /* P1[22] --> LCD_VD_12 */
    LPC_IOCON->P1_23 |= 7;  /* P1[23] --> LCD_VD_13 */
    LPC_IOCON->P1_24 |= 7;  /* P1[24] --> LCD_VD_14 */
    LPC_IOCON->P1_25 |= 7;  /* P1[25] --> LCD_VD_15 */
    LPC_IOCON->P1_26 |= 7;  /* P1[26] --> LCD_VD_20 */
    LPC_IOCON->P1_27 |= 7;  /* P1[27] --> LCD_VD_21 */
    LPC_IOCON->P1_28 |= 7;  /* P1[28] --> LCD_VD_22 */
    LPC_IOCON->P1_29 |= 7;  /* P1[29] --> LCD_VD_23 */

    LPC_IOCON->P2_0 |= 7;   /* P2[0] --> LCD_PWR */
    LPC_IOCON->P2_1 |= 7;   /* P2[1] --> LCD_LE */
    LPC_IOCON->P2_2 |= 7;   /* P2[2] --> LCD_DCLK */
    LPC_IOCON->P2_3 |= 7;   /* P2[3] --> LCD_FP */
    LPC_IOCON->P2_4 |= 7;   /* P2[4] --> LCD_ENAB_M */
    LPC_IOCON->P2_5 |= 7;   /* P2[5] --> LCD_LP */
    LPC_IOCON->P2_6 |= 7;   /* P2[6] --> LCD_VD_4 */  
    LPC_IOCON->P2_8 |= 7;   /* P2[8] --> LCD_VD_6 */
    LPC_IOCON->P2_9 |= 7;   /* P2[9] --> LCD_VD_7 */

    LPC_IOCON->P2_11 |= 7;  /* P2[11] --> LCD_CLKIN */
    LPC_IOCON->P2_12 |= 5;  /* P2[12] --> LCD_VD_3. Señal marcada como LCD_VD_18
                             * en la tarjeta base, pero que llevará la señal
                             * LCD_VD_3
                             */
    LPC_IOCON->P2_13 |= 7;  /* P2.13 -->LCD_VD_19 */   

    /*
     */
    LPC_IOCON->P2_22 = 0;
	LPC_IOCON->P2_23 = 0;
	LPC_IOCON->P2_25 = 0;
	LPC_IOCON->P2_26 = 0;
	LPC_IOCON->P2_27 = 0;      
    
    /*
     */
    buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
    buffer[1] = 0;
    buffer[2] = 1;
    buffer[3] = 0;
    buffer[4] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);
  
    /*
     */  
    buffer[0] = GLCD_PCA9532_PWM0;
    buffer[1] = 255;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

    /*
     */    
    buffer[0] = GLCD_PCA9532_PSC0;
    buffer[1] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

    /*
     */    
    buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
    buffer[1] = 0;
    buffer[2] = 1;
    buffer[3] = 2;
    buffer[4] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

    /*
     */    
    buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
    buffer[1] = 0;
    buffer[2] = 1;
    buffer[3] = 2;
    buffer[4] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

    /*
     */    
    glcd_timer0_retardo_ms(100);
   
    /*
     */   
    buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
    buffer[1] = 1;
    buffer[2] = 1;
    buffer[3] = 2;
    buffer[4] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

    /*
     */    
    glcd_timer0_retardo_ms(100);

    /*
     */    
    buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
    buffer[1] = 1;
    buffer[2] = 0;
    buffer[3] = 2;
    buffer[4] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);

    /*
     */    
    glcd_timer0_retardo_ms(10);

    /*
     */    
    LPC_SC->PCONP |= 0x00000001;
        
    LPC_LCD->CTRL &= ~1;
    
    LPC_LCD->TIMH = 0x27040174;
    LPC_LCD->TIMV = 0x0808050F;
    LPC_LCD->POL = 0x01DF180C;
    LPC_LCD->LE = 0x00000000;
    LPC_LCD->INTMSK = 0x00000000;
    LPC_LCD->CTRL = 0x12c;
    for (i = 0; i < 256; i++) LPC_LCD->PAL[i] = 0;
    LPC_SC->LCD_CFG = 0x0;
    
    LPC_LCD->CTRL |= 1;
    LPC_LCD->CTRL |= 1 << 11;
    LPC_LCD->UPBASE = GLCD_VRAM_BASE_ADDR & ~7UL;
	LPC_LCD->LPBASE = GLCD_VRAM_BASE_ADDR & ~7UL;

    /*
     */    
    glcd_borrar(0);   

    /*
     */    
    buffer[0] = GLCD_PCA9532_PWM0;
    buffer[1] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

    /*
     */    
    buffer[0] = GLCD_PCA9532_PSC0;
    buffer[1] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 2);

    /*
     */    
    buffer[0] = GLCD_PCA9532_LS0 | GLCD_PCA9532_AUTO_INC;
    buffer[1] = 1;
    buffer[2] = 0;
    buffer[3] = 2;
    buffer[4] = 0;
    glcd_i2c0_transmitir_buffer(GLCD_PCA9532_I2C_ADDR, buffer, 5);
}

/***************************************************************************//**
 * \brief       Borrar la pantalla LCD rellenándola con el color indicado.
 *
 * \param[in]   color   color con el que rellenar la pantalla LCD.
 */
void glcd_borrar(uint16_t color)
{ 
    int i;
    volatile uint16_t *ptr = (uint16_t*)GLCD_VRAM_BASE_ADDR;

    for (i = 0; i < GLCD_TAMANO_X*GLCD_TAMANO_Y; i++)
    {
        *ptr++ = color;
    }
}

/***************************************************************************//**
 * \brief       Función análoga a printf para imprimir texto en la pantalla LCD.
 *
 * \param[in]   format  cadena de caracteres a imprimir incluyendo opcionalmente
 *                      especificadores de formato que serán reemplazados por
 *                      los valores de los argumentos adicionales subsiguientes
 *                      y formateados como se indique.
 *
 * \param[in]   ...     argumentos adicionales. Dependiendo de los
 *                      especificadores de formato incluidos en la cadena de
 *                      formato, la función espera una secuencia de argumentos
 *                      adicionales cuyos valores se usan para reemplazar dichos
 *                      especificadores. Debe haber, al menos, tantos argumentos
 *                      adicionales como especificadores de formato. Los
 *                      argumentos extra a los necesarios son ignorados.
 *
 * \return      Si la función tiene éxito, retorna el número de caracteres que
 *              ha impreso. En caso de error, se retorna un número negativo.
 */
int32_t glcd_printf(const char *format, ...)
{
    int32_t retval;
    
    va_list args;
    va_start(args, format);
    retval = vprintf(format, args);
    va_end(args);
    
    return retval;
}

/***************************************************************************//**
 * \brief       Función de salida de caracteres que es llamada internamente
 *              desde la familia de funciones printf y por tanto por glcd_printf
 *              (que usa vprintf). Reconoce los caracteres de control '\b',
 *              '\f', '\n', '\r', '\t' y '\v'.
 *
 * \param[in]   c       carácter a imprimir.
 * \param[in]   stream  puntero a estructura FILE que indentifica al stream al
 *                      que enviar la salida. Sólo se reconoce stdout.
 *
 * \return      Si el fichero de salida indicado es stdout, retorna c. En caso
 *              contrario retorna EOF.
 */
int32_t fputc(int32_t c, FILE *stream)
{
    font_t *font_ptr = NULL;
    int32_t incremento_x = 0;
    int32_t incremento_y = 0;
    
    font_ptr = tabla_fonts[font_actual];
    
    if (stream == stdout)
    {
        switch (c)
        {
        case '\b':  /* Backspace */
            incremento_x = -font_ptr->pixels_ancho;
            break;
        case '\f':  /* Form feed */
            x_texto_actual = 0;
            incremento_y = GLCD_TAMANO_Y;
            break;
        case '\n':  /* Line feed */
            x_texto_actual = 0;
            incremento_y = font_ptr->pixels_alto;
            break;
        case '\r':  /* Carriage return */
            x_texto_actual = 0;
            break;
        case '\t':  /* Horizontal tab */
            x_texto_actual = ((x_texto_actual / (8*font_ptr->pixels_ancho)) + 1)*8*font_ptr->pixels_ancho;
            break;
        case '\v':  /* Vertical tab */
            incremento_y = font_ptr->pixels_alto;
            break;
        default:
            break;
        }
        
        x_texto_actual += incremento_x;
        if (x_texto_actual < 0)
        {
            x_texto_actual = 0;
        }        
        else if (x_texto_actual > GLCD_X_MAXIMO)
        {
            x_texto_actual = 0;
            if (incremento_y < font_ptr->pixels_alto)
            {
                incremento_y = font_ptr->pixels_alto;
            }
        }
        
        y_texto_actual += incremento_y;
        if (y_texto_actual + font_ptr->pixels_alto - 1 > GLCD_Y_MAXIMO)
        {
            if (desplazamiento_activado)
            {
                if (incremento_y > GLCD_TAMANO_Y)
                {
                    incremento_y = GLCD_TAMANO_Y;
                    y_texto_actual = 0;
                }
                else if (incremento_y < GLCD_TAMANO_Y)
                {
                    y_texto_actual -= incremento_y;
                    if (y_texto_actual < 0) y_texto_actual = 0;
                }
                else
                {
                    y_texto_actual = 0;
                }
                glcd_desplazar(incremento_y);                            
            }
            else
            {
                y_texto_actual = 0;
            }
        }
        
        if (c >= font_ptr->primer_caracter && c <= font_ptr->ultimo_caracter)
        {
            glcd_caracter(c,
                          x_texto_actual,
                          y_texto_actual,
                          color_texto_actual,
                          color_fondo_texto_actual,
                          font_actual);
            x_texto_actual += font_ptr->pixels_ancho;
        }
               
        return c;
    }
    else
    {
        return EOF;
    }
}

/***************************************************************************//**
 * \brief       Función de entrada de caracteres que es llamada internamente
 *              desde la familia de funciones scanf. No implementada de momento.
 *
 * \param[in]   stream  puntero a estructura FILE que indentifica al stream del
 *                      que se quiere leer.
 *
 * \return      Siempre retorna EOF.
 */
int32_t fgetc(FILE *file)
{
    return EOF;
}

/***************************************************************************//**
 * \brief       Comprueba el estado del indicador de error de un stream.
 *
 * \param[in]   stream  puntero a estructura FILE que indentifica al stream cuyo
 *                      estado de error se quiere comprobar.
 *
 *
 * \return      retorna un valor distinto de 0 si la operación anterior sobre
 *              el stream produjo un error y un valor igual a 0 en caso
 *              contrario. En esta implementación, si el stream es stdout
 *              siempre se retorna 0 y en caso contrario siempre se retorna
 *              un valor distinto de 0.
 *
 */
int32_t ferror(FILE *stream)
{
    if (stream == stdout) return 0;
    else return 1;
}

/***************************************************************************//**
 * \brief       Al realizar el retarget de las funciones de la familia printf,
 *              el compilador del Kil MDK precisa que se defina la función
 *              _sys_exit que corresponde a la llamada del sistema sys_exit que
 *              termina el proceso actual. En esta implementación no se retorna
 *              al sistema (ya que no hay) sino que se deja encerrado al
 *              programa en un bucle infinito.
 *
 * \param[in]   return_code     código que debe retornarse al sistema.
 */
void _sys_exit(int32_t return_code)
{
    for (;;) {}
}

/***************************************************************************//**
 * \brief       Fijar el color que se usará para la salida de texto con
 *              glcd_printf.
 *
 * \param[in]   color   color de texto que usará glcd_printf.
 */
void glcd_color_texto(uint16_t color)
{
    color_texto_actual = color;
}

/***************************************************************************//**
 * \brief       Fijar el color de fondo que se usará para la salida de texto con
 *              glcd_printf.
 *
 * \param[in]   color   color de fondo que usará glcd_printf.
 */
void glcd_fondo_texto(uint16_t bkcolor)
{
    color_fondo_texto_actual = bkcolor;
}

/***************************************************************************//**
 * \brief       Fijar las coordenadas en las que se mostrará el texto en la
 *              siguiente llamada a glcd_printf. Sólo tiene efecto si las
 *              coordenadas indicadas están dentro de la pantalla.
 *
 * \param[in]   x       coordenada x de la pantalla.
 * \param[in]   y       coordenada x de la pantalla.
 */
void glcd_xy_texto(int32_t x, int32_t y)
{
    if (x < 0 || x > GLCD_X_MAXIMO || y < 0 || y > GLCD_Y_MAXIMO) return;
    x_texto_actual = x;
    y_texto_actual = y;
}

/***************************************************************************//**
 * \brief       Desplazar hacia arriba el contenido de la pantalla un
 *              determinado número de líneas. Las líneas inferiores se rellenan
 *              con el color del fondo de texto actual.
 *
 * \param[in]   lienas  líneas a desplazar.
 */
void glcd_desplazar(uint32_t lineas)
{
    uint32_t i;
    volatile uint16_t *ptr = (uint16_t*)GLCD_VRAM_BASE_ADDR;

    if (lineas > GLCD_TAMANO_Y) lineas = GLCD_TAMANO_Y;
    
    memmove((void*)ptr,
            (void*)(ptr + lineas*GLCD_TAMANO_X),
            GLCD_TAMANO_X*(GLCD_TAMANO_Y - lineas)*2);
            
    ptr += GLCD_TAMANO_X*(GLCD_TAMANO_Y - lineas);
    for (i = 0; i < GLCD_TAMANO_X*lineas; i++)
    {
        *ptr++ = color_fondo_texto_actual;
    }
}

/***************************************************************************//**
 * \brief       Activar o desactivar el desplazamiento automático hacia arriba
 *              de del contenido de la pantalla cuando la salida de texto
 *              mediante glcd_printf sobrepasa la linea de texto inferior.
 *
 * \param[in]   activar     TRUE => activar, FALSE => desactivar.
 */
void glcd_activar_desplazamiento(bool_t activar)
{
    desplazamiento_activado = activar;
}

/***************************************************************************//**
 * \brief       Seleccionar el font de caracteres que se usará para la salida de
 *              texto mediante la función glcd_printf.
 *
 * \param[in]   font    número del font a seleccionar.
 */
void glcd_seleccionar_font(uint32_t font)
{
    ASSERT(font < NUMERO_FONTS, "Font incorrecto");
    font_actual = font;
}

/***************************************************************************//**
 * \brief       Función parecida a glcd_printf pero pudiendo indicar las
 *              coordedadas donde aparece el texto, el color del texto y el
 *              font.
 *
 * \param[in]   x           coordenada x de pantalla en la que se imprimirá.
 * \param[in]   y           coordenada y de pantalla en la que se imprimirá.
 * \param[in]   color       color con el que se imprimirá el carácter.
 * \param[in]   color_fondo coordenada x de pantalla en la que se imprimirá.
 * \param[in]   font        font de caracteres con el que se imprimirá.
 * \param[in]   format      cadena de caracteres a imprimir incluyendo
 *                          opcionalmente especificadores de formato que serán
 *                          reemplazados por los valores de los argumentos
 *                          adicionales subsiguientes y formateados como se
 *                          indique.
 *
 * \param[in]   ...         argumentos adicionales. Dependiendo de los
 *                          especificadores de formato incluidos en la cadena de
 *                          formato, la función espera una secuencia de
 *                          argumentos adicionales cuyos valores se usan para
 *                          reemplazar dichos especificadores. Debe haber, al
 *                          menos, tantos argumentos adicionales como
 *                          especificadores de formato. Los argumentos extra a
 *                          los necesarios se ignoran.
 *
 * \return                  Si la función tiene éxito, retorna el número de
 *                          caracteres que ha impreso. En caso de error, se
 *                          retorna un número negativo.
 */
int32_t glcd_xprintf(int32_t x,
                     int32_t y,                
                     uint16_t color,
                     uint16_t color_fondo,
                     uint32_t font,
                     const char *format, ...)
{
    int32_t x_texto_salvado;
    int32_t y_texto_salvado;
    uint16_t color_texto_salvado;
    uint16_t color_fondo_salvado;
    uint32_t font_salvado;
    int32_t retval;
    va_list args;
 
    x_texto_salvado = x_texto_actual;
    y_texto_salvado = y_texto_actual;    
    color_texto_salvado = color_texto_actual;
    color_fondo_salvado = color_fondo_texto_actual;
    font_salvado = font_actual;

    x_texto_actual = x;
    y_texto_actual = y;    
    color_texto_actual = color;
    color_fondo_texto_actual = color_fondo;
    font_actual = font;
   
    va_start(args, format);
    retval = vprintf(format, args);
    va_end(args);

    x_texto_actual = x_texto_salvado;
    y_texto_actual = y_texto_salvado;
    color_texto_actual = color_texto_salvado;
    color_fondo_texto_actual = color_fondo_salvado;
    font_actual = font_salvado;
    
    return retval;
}

/***************************************************************************//**
 * \brief                   Imprimir un carácter en pantalla. No se interpretan
 *                          caracteres de control.
 *
 * \param[in]   c           carácter a imprimir. Sólo se imprimirá si es uno de
 *                          los caracteres definidos en el font indicado por el
 *                          argumento fonty las coordenadas indicadas por los
 *                          argumentos x e y están dentro de la pantalla. En caso
 *                          contrario no se imprimirá nada.
 * \param[in]   x           coordenada x de pantalla en la que se imprimirá.
 * \param[in]   y           coordenada y de pantalla en la que se imprimirá.
 * \param[in]   color       color con el que se imprimirá el carácter.
 * \param[in]   color_fondo coordenada x de pantalla en la que se imprimirá.
 * \param[in]   font        font de caracteres con el que se imprimirá.
 */
void glcd_caracter(char c,
                   int32_t x,
                   int32_t y,
                   uint16_t color,
                   uint16_t color_fondo,
                   uint32_t font)
{
    font_t *font_ptr;
    uint32_t pixels_ancho;
    uint32_t pixels_alto;
    const uint8_t *ptr_df;
    uint32_t bytes_por_fila;
	uint16_t i, j;
    uint8_t b;
    volatile uint16_t *ptr_fb;
    uint32_t salto_en_fb;
    uint8_t mascara;
    
    ASSERT(font < NUMERO_FONTS, "Font incorrecto");
    
    if (x < 0 || x > GLCD_X_MAXIMO || y < 0 || y > GLCD_Y_MAXIMO) return;
    
    font_ptr = tabla_fonts[font];
    
    if (c < font_ptr->primer_caracter || c > font_ptr->ultimo_caracter)
        return;
    
    pixels_ancho = font_ptr->pixels_ancho;
    pixels_alto  = font_ptr->pixels_alto;
    bytes_por_fila = pixels_ancho >> 3;
    if ((pixels_ancho & 7) != 0) bytes_por_fila++;
    
    ptr_df = font_ptr->datos +
        (c - font_ptr->primer_caracter)*bytes_por_fila*pixels_alto;
    
    ptr_fb = (uint16_t*)GLCD_VRAM_BASE_ADDR + y*GLCD_TAMANO_X + x;
    salto_en_fb =  GLCD_TAMANO_X - font_ptr->pixels_ancho;
    
    for (i = 0; i < pixels_alto; i++)
    {
        for (j = 0; j < pixels_ancho; j++)
        {            
            if ((j & 7) == 0)
            {   
                b = *ptr_df++;
                mascara = 0x80;
            }
            else
            {
                mascara >>= 1;
            }
           
            if (b & mascara)
            {
                *ptr_fb++ = color;
            }
            else
            {
                *ptr_fb++ = color_fondo;
            }
        }
        ptr_fb += salto_en_fb;
    }
}

/***************************************************************************//**
 * \brief       Imprimir una cadena de caracteres en la pantalla LCD. No se
 *              interpretan caracteres de control.
 *
 * \param[in]   x           coordenada x de pantalla en la que se imprimirá.
 * \param[in]   y           coordenada y de pantalla en la que se imprimirá.
 * \param[in]   color       color con el que se imprimirá el carácter.
 * \param[in]   color_fondo coordenada x de pantalla en la que se imprimirá.
 * \param[in]   font        font de caracteres con el que se imprimirá.
 * \param[in    str         puntero a la cadena a imprimir. Sólo se imprimirá
 *                          si las coordenadas indicadas por los argumentos x
 *                          e y están dentro de la pantalla. En caso contrario
 *                          no se imprimirá nada.
 */
void glcd_texto(int32_t x,
                int32_t y,                
                uint16_t color,
                uint16_t color_fondo,
                uint32_t font,
                const char *str)
{
    font_t *font_ptr = tabla_fonts[font];
    
    ASSERT(str != NULL, "El puntero a la cadena es nulo");
    ASSERT(font < NUMERO_FONTS, "Font incorrecto");
    
    if (x < 0 || x > GLCD_X_MAXIMO || y < 0 || y > GLCD_Y_MAXIMO) return;
    
    while (*str != 0)
    {
        glcd_caracter(*str, x, y, color, color_fondo, font);
        
        x += font_ptr->pixels_ancho;
        if (x > GLCD_X_MAXIMO)
        {
            x = 0;
            y += font_ptr->pixels_alto;
            if (y > GLCD_Y_MAXIMO)
            {
                y = 0;
            }   
        }   
        str++;
    }
}

/***************************************************************************//**
 * \brief       Dibujar un punto (pixel) en la pantalla LCD.
 *
 * \param[in]   x       coordenada x del punto.
 * \param[in]   y       coordenada y del punto.
 * \param[in]   color   color del punto.
 */
void glcd_punto(int32_t x, int32_t y, uint16_t color)
{
    volatile uint16_t *ptr = (uint16_t*)GLCD_VRAM_BASE_ADDR;
  
    if (x < 0 || x > GLCD_X_MAXIMO || y < 0 || y > GLCD_Y_MAXIMO) return;

    ptr[y*GLCD_TAMANO_X + x] = color;	
}

/***************************************************************************//**
 * \brief       Dibuja en la pantlla LCD un segmento de línea recta definido por
 *              las coordenadas de sus extremos. Si las coordenadas de uno o
 *              ambos extremos del segmento están fuera de la pantalla se dibuja
 *              la porción contenida en la misma (si la hay).
 *
 * \param[in]   x0      coordenada x del primer extremo del segmento.
 * \param[in]   y0      coordenada y del primer extremo del segmento.
 * \param[in]   x1      coordenada x del segundo extremo del segmento.
 * \param[in]   y1      coordenada y del segundo extremo del segmento.
 * \param[in]   color   color del segmento.
 */
void glcd_linea(int32_t x0,
                int32_t y0,
                int32_t x1,
                int32_t y1,
                uint16_t color)
{
    int32_t x, y;
    int32_t dx, dy;
    int32_t p, incE, incNE, stepx, stepy;
    
    /* Mejorar con algoritmo Fast clipping.
    */
    
    dx = x1 - x0;
    dy = y1 - y0;
    
    if (dy < 0)
    { 
        dy = -dy; 
        stepy = -1; 
    } 
    else
    {
        stepy = 1;
    }

    if (dx < 0)
    {  
        dx = -dx;  
        stepx = -1; 
    } 
    else
    {
        stepx = 1;
    }

    x = x0;
    y = y0;
    glcd_punto(x, y, color);
    

    if (dx > dy)
    {
        p = 2*dy - dx;
        incE = 2*dy;
        incNE = 2*(dy - dx);
        while (x != x1)
        {
            x = x + stepx;
            if (p < 0)
            {
                p = p + incE;
            }
            else
            {
                y = y + stepy;
                p = p + incNE;
            }
            glcd_punto(x, y, color);
        }
    }
    else
    {
        p = 2*dx - dy;
        incE = 2*dx;
        incNE = 2*(dx - dy);
        while (y != y1)
        {
            y = y + stepy;
            if (p < 0)
            {
                p = p + incE;
            }
            else
            {
                x = x + stepx;
                p = p + incNE;
            }
            glcd_punto(x, y, color);
        }
    }
} 

/***************************************************************************//**
 * \brief       Dibujar en la pantalla LCD un rectángulo definido por las
 *              coordenadas de los vértices de una diagonal. Se dibuja la
 *              porción del rectángulo contenida entre los límites de la
 *              pantalla.
 *
 * \param[in]   x0      coordenada x de un vértice.
 * \param[in]   y0      coordenada y de un vértice.
 * \param[in]   x1      coordenada x del vértice opuesto al dado por (x0, y0).
 * \param[in]   y1      coordenada y del vértice opuesto al dado por (x0, y0).
 * \param[in]   color   color del rectángulo.
 */
void glcd_rectangulo(int32_t x0,
                     int32_t y0,
                     int32_t x1,
                     int32_t y1,
                     uint16_t color)
{
    glcd_linea(x0, y0, x1, y0, color);
    glcd_linea(x1, y0, x1, y1, color);
    glcd_linea(x1, y1, x0, y1, color);
    glcd_linea(x0, y1, x0, y0, color);
}

/***************************************************************************//**
 * \brief       Dibujar en la pantalla LCD un rectángulo relleno definido por las
 *              coordenadas de los vértices de una diagonal. Se dibuja la
 *              porción del rectángulo contenida entre los límites de la
 *              pantalla.
 *
 * \param[in]   x0      coordenada x de un vértice.
 * \param[in]   y0      coordenada y de un vértice.
 * \param[in]   x1      coordenada x del vértice opuesto al dado por (x0, y0).
 * \param[in]   y1      coordenada y del vértice opuesto al dado por (x0, y0).
 * \param[in]   color   color del rectángulo.
 */
void glcd_rectangulo_relleno(int32_t x0,
                             int32_t y0,
                             int32_t x1,
                             int32_t y1,
                             uint16_t color)
{
    int32_t temp;
    int32_t i, j;
    uint16_t* ptr = (uint16_t*)GLCD_VRAM_BASE_ADDR;
    uint16_t* ptr2;

    if (x0 > x1)
    {
        temp = x0;
        x0 = x1;
        x1 = temp;   
    }

    if (y0 > y1)
    {
        temp = y0;
        y0 = y1;
        y1 = temp;   
    }
    
    if (x0 < 0) x0 = 0;
    if (y0 < 0) y0 = 0;
    if (x1 > GLCD_X_MAXIMO) x1 = GLCD_X_MAXIMO;
    if (y1 > GLCD_Y_MAXIMO) y1 = GLCD_Y_MAXIMO;

    ptr +=  GLCD_TAMANO_X*y0 + x0;
        
    for (i = y0; i <= y1; i++)
    {
        ptr2 = ptr;
        ptr += GLCD_TAMANO_X;
        for (j = x0; j <= x1; j++)
        {
            *ptr2++ = color;
        }
    }
}

/***************************************************************************//**
 * \brief       Dibujar una circunferencia en la pantalla LCD. Se dibuja la
 *              parte de la circunferencia contenida entre los límites de la
 *              pantalla.
 *
 * \param[in]   xc      coordenada x del centro.
 * \param[in]   yc      coordenada y del centro.
 * \param[in]   radio   radio de la circunferencia (en pixels).
 * \pararm[in]  color   color de la circunferencia.
 */
void glcd_circunferencia(int32_t xc,
                         int32_t yc,
                         int32_t radio,
                         uint16_t color)
{
    int32_t x = radio;
    int32_t y = 0;
    int32_t err = 0;

    while (x >= y)
    {
        glcd_punto(xc + x, yc + y, color);
        glcd_punto(xc + y, yc + x, color);
        glcd_punto(xc - y, yc + x, color);
        glcd_punto(xc - x, yc + y, color);
        glcd_punto(xc - x, yc - y, color);
        glcd_punto(xc - y, yc - x, color);
        glcd_punto(xc + y, yc - x, color);
        glcd_punto(xc + x, yc - y, color);

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}

/***************************************************************************//**
 * \brief       Dibujar una circulo relleno en la pantalla LCD. Se dibuja la
 *              parte del cículo contenido entre los límites de la pantalla.
 *
 * \param[in]   xc      coordenada x del centro.
 * \param[in]   yc      coordenada y del centro.
 * \param[in]   radio   radio del círculo (en pixels).
 * \pararm[in]  color   color del cículo.
 */
void glcd_circulo(int32_t xc,
                  int32_t yc,
                  int32_t radio,
                  uint16_t color)
{
    int32_t x = radio;
    int32_t y = 0;
    int32_t err = 0;

    while (x >= y)
    {
        glcd_linea(xc - x, yc - y, xc + x, yc - y, color);
        glcd_linea(xc - x, yc + y, xc + x, yc + y, color);
        glcd_linea(xc - y, yc - x, xc + y, yc - x, color);
        glcd_linea(xc - y, yc + x, xc + y, yc + x, color);        

        if (err <= 0)
        {
            y += 1;
            err += 2*y + 1;
        }
        if (err > 0)
        {
            x -= 1;
            err -= 2*x + 1;
        }
    }
}
