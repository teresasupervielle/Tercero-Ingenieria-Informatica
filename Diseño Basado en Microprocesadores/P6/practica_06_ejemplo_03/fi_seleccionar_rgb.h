//-----------------------------------------------------------------------------------------------------
/// \file	fi_seleccionar_rgb.h
//

#ifndef FI_SELECCIONAR_RGB_H
#define FI_SELECCIONAR_RGB_H

#define SELECCIONAR_AZUL	1
#define SELECCIONAR_VERDE	2
#define SELECCIONAR_ROJO	4

int fi_seleccionar_rgb(unsigned char *ptr_imagen,
                       unsigned int ancho,
                       unsigned int alto,
                       unsigned char seleccion_rgb);

#endif	// FI_SELECCIONAR_RGB_H
