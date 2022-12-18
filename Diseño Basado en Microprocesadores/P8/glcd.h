/***************************************************************************//**
 * \brief   Funciones de manejo del LCD de 4.3" desde la tarjeta Embedded Artist
 *          Developer's Kit.
 */

#ifndef GLCD_H 
#define GLCD_H

#include "tipos.h"
#include "sdram.h"
#include "font.h"
#include <stdio.h>

/*===== Dirección de conmienzo del framebuffer =================================
 */

#define GLCD_VRAM_BASE_ADDR (SDRAM_BASE + 0x0010000)

/*===== Tamaño en pixels del LCD ===============================================
 */

#define GLCD_TAMANO_X       480
#define GLCD_TAMANO_Y       272

#define GLCD_X_MINIMO       0
#define GLCD_Y_MINIMO       0
#define GLCD_X_MAXIMO       (GLCD_TAMANO_X - 1)
#define GLCD_Y_MAXIMO       (GLCD_TAMANO_Y - 1)

#define GLCD_X_SIZE         GLCD_TAMANO_X
#define GLCD_Y_SIZE         GLCD_TAMANO_Y
#define PIXELS_PER_LINE     GLCD_X_SIZE

/*===== Configuración del conrolador de LCD ====================================
 */
 
/** Anchura del pulso de sincronismo horizontal. */
#define H_SYNC_PULSE_WIDTH  2

/** Anchura del porche anterior del pulso de sincronismo horizontal. */
#define H_SYNC_FRONT_PORCH  5

/** Anchura del porche posterior del pulso de sincronismo horizontal. */
#define H_SYNC_BACK_PORCH   40

 /** Lineas horizontales en el panel */
#define LINES_PER_PANEL     GLCD_Y_SIZE

/** Anchura del pulso de sincronismo vertical. */
#define V_SYNC_PULSE_WIDTH  2

/** Anchura del porche anterior del pulso de sincronismo vertical. */
#define V_SYNC_FRONT_PORCH  8

/** Anchura del porche posterior del pulso de sincronismo vertical. */
#define V_SYNC_BACK_PORCH   8

/** Frecuencia de la polarizacón AC (no se usa). */
#define AC_BIAS             1

/** Invertir sincronismo horizontal (0 => No, 1 => Sí). */  
#define INVERT_H_SYNC       1

/** Invertir sincronismo vertical (0 => No, 1 => Sí). */
#define INVERT_V_SYNC	      1

/** Invertir reloj de pixels (0 => No, 1 => Sí). */
#define INVERT_PANEL_CLOCK  0


#define CLOCKS_PER_LINE     PIXELS_PER_LINE /* Clock per line */
#define BITS_PER_PIXEL      6           /* Bits per pixel = 6 => 16 bpp 5:6:5 */
#define BGR                 1           /* Swap red and blue */
#define LCDTFT              1           /* LCD TFT panel */
#define OPTIMAL_CLOCK       (9*1000000) /* Reloj óptimo, entre 1 y 8.22 MHz */

#define BYPASS_CLOCK_DIVIDER_BIT    26  /* Bypass pixel clock divider */

/*===== Colores ================================================================
 */
 

#define RGB(r, g, b)    ((((r) & 0xF8) << 8) | (((g) & 0xFC) << 3) | (((b) & 0xF8) >> 3))

/*------------------------------------------------------------------------------
 */

/*----- Nombres de varios colores en inglés ------------------------------------
 */

#define BLACK           RGB(0, 0, 0)
#define DARKBLUE        RGB(0, 0, 128)
#define DARKGREEN       RGB(0, 128, 0)
#define DARKCYAN        RGB(0, 128, 128)
#define MAROON          RGB(128, 0, 0)
#define PURPLE          RGB(128, 0, 128)
#define OLIVE           RGB(128, 255, 0)
#define ORANGE          RGB(255, 128, 0)
#define LIGHTGREY       RGB(192, 192, 192)
#define DARKGREY        RGB(128, 128, 128)
#define BLUE            RGB(0, 0, 255)
#define GREEN           RGB(0, 255, 0)
#define CYAN            RGB(0, 255, 255)
#define RED             RGB(255, 0, 0)
#define MAGENTA         RGB(255, 0, 255)
#define YELLOW          RGB(255, 255, 0)
#define WHITE           RGB(255, 255, 255)

/*----- Nombres de varios colores en español -----------------------------------
 */

#define NEGRO           RGB(0, 0, 0)
#define AZUL_OSCURO     RGB(0, 0, 128)
#define VERDE_OSCURO    RGB(0, 128, 0)
#define CIAN_OSCURO     RGB(0, 128, 128)
#define MARRON          RGB(128, 0, 0)
#define PURPURA         RGB(128, 0, 128)
#define OLIVA           RGB(128, 255, 0)
#define NARANJA         RGB(255, 128, 0)
#define GRIS_CLARO      RGB(192, 192, 192)
#define GRIS_OSCURO     RGB(128, 128, 128)
#define AZUL            RGB(0, 0, 255)
#define VERDE           RGB(0, 255, 0)
#define CIAN            RGB(0, 255, 255)
#define ROJO            RGB(255, 0, 0)
#define MAGENTA         RGB(255, 0, 255)
#define AMARILLO        RGB(255, 255, 0)
#define BLANCO          RGB(255, 255, 255)

/*===== Fonts ==================================================================
 */
 
#define FONT8X16        0
#define FONT12X24       1
#define FONT16X32       2

#define NUMERO_FONTS    3

/*===== PCA9532 ================================================================ 
 */
#define GLCD_PCA9532_I2C_ADDR   0x64 
 
#define GLCD_PCA9532_INPUT0     0x00
#define GLCD_PCA9532_INPUT1     0x01
#define GLCD_PCA9532_PSC0       0x02
#define GLCD_PCA9532_PWM0       0x03
#define GLCD_PCA9532_PSC1       0x04
#define GLCD_PCA9532_PWM1       0x05
#define GLCD_PCA9532_LS0        0x06
#define GLCD_PCA9532_LS1        0x07
#define GLCD_PCA9532_LS2        0x08
#define GLCD_PCA9532_LS3        0x09
#define GLCD_PCA9532_AUTO_INC   0x10

#define GLCD_LS_MODE_ON         0x01
#define GLCD_LS_MODE_BLINK0     0x02
#define GLCD_LS_MODE_BLINK1     0x03

#define GLCD_CTRL_3V3           0x0001
#define GLCD_CTRL_5V            0x0002
#define GLCD_CTRL_DISP_EN       0x0010
#define GLCD_CTRL_BL_EN         0x0080
#define GLCD_CTRL_BL_C          0x0100

/*==============================================================================
 */

#pragma import(__use_no_semihosting_swi)

struct __FILE
{
    int handle;
};

int32_t fputc(int c, FILE *file);
int32_t fgetc(FILE *file);
int32_t ferror(FILE *file);
void _sys_exit(int32_t return_code);

/*===== Prototipos de funciones ================================================
 */

void glcd_inicializar(void);

void glcd_borrar(uint16_t color);
                                   
int32_t glcd_printf(const char *format, ...);
                
void glcd_color_texto(uint16_t color);

void glcd_fondo_texto(uint16_t color_fondo);

void glcd_xy_texto(int32_t x, int32_t y);

void glcd_seleccionar_font(uint32_t font);

int32_t glcd_xprintf(int32_t x,
                     int32_t y,
                     uint16_t color,
                     uint16_t color_fondo,
                     uint32_t font,
                     const char *fmt, ...);
                
void glcd_caracter(char c,
                   int32_t x,
                   int32_t y,                   
                   uint16_t color,
                   uint16_t color_fondo,
                   uint32_t font);

void glcd_texto(int32_t x,
                int32_t y,                
                uint16_t color,
                uint16_t color_fondo,
                uint32_t font,
                const char *str);                   
                   
void glcd_activar_desplazamiento(bool_t activo);

void glcd_desplazar(uint32_t lineas);

void glcd_punto(int32_t x,
                int32_t y, 
                uint16_t color);

void glcd_linea(int32_t x0,
                int32_t y0,
                int32_t x1,
                int32_t y1,
                uint16_t color);
               
void glcd_rectangulo(int32_t x0,
                     int32_t y0,
                     int32_t x1,
                     int32_t y1,
                     uint16_t color);

void glcd_rectangulo_relleno(int32_t x0,
                             int32_t y0,
                             int32_t x1,
                             int32_t y1,
                             uint16_t color);

void glcd_circunferencia(int32_t xc,
                         int32_t yc,
                         int32_t radio,
                         uint16_t color);

void glcd_circulo(int32_t xc,
                  int32_t yc,
                  int32_t radio,
                  uint16_t color);

#endif  /* GLCD_H */
