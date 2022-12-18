/***************************************************************************//**
 * \file    sonido.h
 *
 * \brief   Funciones básicas de sonido.
 */

#ifndef SONIDO_H
#define SONIDO_H

#include "tipos.h"

/*===== Constantes =============================================================
 */

/* Símbolos para notas según la notación anglosajona.
 */
#define NOTA_A0      1
#define NOTA_AS0     2
#define NOTA_B0      3
#define NOTA_C1      4
#define NOTA_CS1     5
#define NOTA_D1      6
#define NOTA_DS1     7
#define NOTA_E1      8
#define NOTA_F1      9
#define NOTA_FS1    10
#define NOTA_G1     11
#define NOTA_GS1    12
#define NOTA_A1     13
#define NOTA_AS1    14
#define NOTA_B1     15
#define NOTA_C2     16
#define NOTA_CS2    17
#define NOTA_D2     18
#define NOTA_DS2    19
#define NOTA_E2     20
#define NOTA_F2     21
#define NOTA_FS2    22
#define NOTA_G2     23
#define NOTA_GS2    24
#define NOTA_A2     25
#define NOTA_AS2    26
#define NOTA_B2     27
#define NOTA_C3     28
#define NOTA_CS3    29
#define NOTA_D3     30
#define NOTA_DS3    31
#define NOTA_E3     32
#define NOTA_F3     33
#define NOTA_FS3    34
#define NOTA_G3     35
#define NOTA_GS3    36
#define NOTA_A3     37
#define NOTA_AS3    38
#define NOTA_B3     39
#define NOTA_C4     40
#define NOTA_CS4    41
#define NOTA_D4     42
#define NOTA_DS4    43
#define NOTA_E4     44
#define NOTA_F4     45
#define NOTA_FS4    46
#define NOTA_G4     47
#define NOTA_GS4    48
#define NOTA_A4     49
#define NOTA_AS4    50
#define NOTA_B4     51
#define NOTA_C5     52
#define NOTA_CS5    53
#define NOTA_D5     54
#define NOTA_DS5    55
#define NOTA_E5     56
#define NOTA_F5     57
#define NOTA_FS5    58
#define NOTA_G5     59
#define NOTA_GS5    60
#define NOTA_A5     61
#define NOTA_AS5    62
#define NOTA_B5     63
#define NOTA_C6     64
#define NOTA_CS6    65
#define NOTA_D6     66
#define NOTA_DS6    67
#define NOTA_E6     68
#define NOTA_F6     69
#define NOTA_FS6    70
#define NOTA_G6     71
#define NOTA_GS6    72
#define NOTA_A6     73
#define NOTA_AS6    74
#define NOTA_B6     75
#define NOTA_C7     76
#define NOTA_CS7    77
#define NOTA_D7     78
#define NOTA_DS7    79
#define NOTA_E7     80
#define NOTA_F7     81
#define NOTA_FS7    82
#define NOTA_G7     83
#define NOTA_GS7    84
#define NOTA_A7     85
#define NOTA_AS7    86
#define NOTA_B7     87
#define NOTA_C8     88

/* Silencio.
 */
#define NOTA_PAUSA  0

/* Marcador de fin de melodía.
 */
#define NOTA_FIN    255

/*===== Prototipos de funciones ================================================
 */


void sonido_emitir_pitido(uint32_t frecuencia, uint32_t duracion_ms);
void sonido_reproducir_nota(uint8_t nota, uint32_t duracion_ms);
void sonido_reproducir_melodia(const uint8_t *melodia, uint32_t duracion_nota_ms);

void sonido_inicializar(void);
void sonido_reproducir_melodia_2(const uint8_t *melodia, uint32_t duracion_nota_ms);

#endif  /* SONIDO_H */
