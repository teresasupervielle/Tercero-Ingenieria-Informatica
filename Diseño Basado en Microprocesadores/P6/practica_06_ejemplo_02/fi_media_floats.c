/*
 * fi_media_floats.c
 *
 *  Created on: 15 abr. 2021
 *      Author: Teresa
 */

#include <immintrin.h>
#include <stdio.h>

int fi_media_floats(float *ptr_datos, unsigned int longitud_array, float *ptr_resultado);

int main(){
	float datos[4]__attribute__((alligner(32))) = {1.0, 2.0, 3.0, 4.0};
	float resultado = 0.0;
	int comprobar;

	comprobar = fi_media_floats(*datos, 5, *resultado);

	if (comprobar != 0){
		printf ("%f", resultado);
	} else
		printf ("Error");

return 0;
}

int fi_media_floats(float *ptr_datos, unsigned int longitud_array, float *ptr_resultado){
	if (ptr_datos == NULL || longitud_array == 0 || ptr_resultado == NULL)
		return 0;
	else {
		__m256 v, inter;
		__m128 resultado;

		int N = longitud_array, cont = longitud_array / 8;
		float res;
		v = _mm256_set1_ps(0.0);

		while (cont > 0){
			inter = _mm256_load_ps(ptr_datos);
			v = _mm256_add_ps(v, inter);
			longitud_array -= 8;
			ptr_datos += 8;
			cont--;
		}

		v = _mm256_hadd_ps(v, v);
		v = _mm256_hadd_ps(v, v);

		inter = _mm256_permute2f128_ps(v, v, 1);

		resultado = _mm256_castps256_ps128(inter);
		_mm_store_ss(&res, resultado);

		while (longitud_array > 0){
			res += *ptr_datos;
			ptr_datos++;
			longitud_array--;
		}

		*ptr_resultado = res / N;
		return 1;
	}
}
