//-----------------------------------------------------------------------------------------------------
/// \file	fi_seleccionar_rgb.h
//

#include "fi_seleccionar_rgb.h"
#include <immintrin.h>

//-----------------------------------------------------------------------------------------------------
/// \brief          Seleccionar componentes de color de una imagen RGB.
///
/// \param[in,out]  ptr_imagen      Puntero a los datos de la imagen. Cada pixel ocupa tres bytes
///                                 con las componentes azul, verde y roja (en ese orden). El puntero
///                                 debe estar alineado a una posición divisible entre 32. 
///
/// \param[in]      ancho           ancho de la imagen en pixels.
///
/// \param[in]      alto            alto de la imagen en pixels.
///
/// \param[in]      seleccion_rgb   máscara para seleccionar qué componentes de color se conservan:
///                                 Si el bit 0 de seleccion_rgb está a 1 se conserva la componente azul.
///                                 Si está a 0 se elimina.
///                                 Si el bit 1 de seleccion_rgb está a 1 se conserva la componente verde.
///                                 Si está a 1 se elimina.
///                                 Si el bit 2 de seleccion_rgb está a 1 se conserva la componente roja.
///                                 Si está a 2 se elimina.
///
/// \return			0 => error (ptr_imagen nulo o no alineado o ancho == 0 o alto == 0), 1 => éxito.
//

int fi_seleccionar_rgb(unsigned char *ptr_imagen,
                       unsigned int ancho,
                       unsigned int alto,
                       unsigned char seleccion_rgb)
{

	unsigned int i, num_pixeles = ancho * alto;
	unsigned int numero_bloques_32_pixeles = num_pixeles / 32;
	unsigned int numero_pixeles_restantes;

	__mm256i mskblanco, mskblanco1, mckblanco2;
	__mm256i *ptr = (__mm256i*)ptr_imagen;

	unsigned char a1[] = {0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF,
			0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0};
	unsigned char a2[] = { 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0,
			0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF};
	unsigned char a3[] = { 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0,
			0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0, 0xFF, 0, 0};

	if (ptr_imagen == NULL || ancho <= 0 || alto <= 0 || seleccion_rgb == NULL)
		return 1;
	else{
		mskblanco = _mm256_setzero_si256();
		mskblanco1 = _mm256_setzero_si256();
		mskblanco2 = _mm256_setzero_si256();

		if (numero_bloques_32_pixeles > 0){
			if ((seleccion_rgb & 1) != 0){
				mskblanco = _mm256_or_si256(mskblanco, *(__mm256i*));
			}
		}
	}


}

