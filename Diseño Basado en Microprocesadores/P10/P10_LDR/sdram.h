/***************************************************************************//**
 * \brief   
 */
 
#ifndef SDRAM_H
#define SDRAM_H

#include "tipos.h"

#define SDRAM_SPEED_48 0
#define SDRAM_SPEED_50 1
#define SDRAM_SPEED_60 2
#define SDRAM_SPEED_72 3
#define SDRAM_SPEED_80 4

#define SDRAM_SPEED SDRAM_SPEED_60

#define SDRAM_CONFIG_32BIT
#define SDRAM_SIZE               0x2000000

#define SDRAM_BASE               0xA0000000 /*CS0*/

uint32_t sdram_inicializar(void);

#endif /* SDRAM_H */
