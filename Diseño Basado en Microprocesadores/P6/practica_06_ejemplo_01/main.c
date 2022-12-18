/*
 * main.c
 *
 *  Created on: 15 abr. 2021
 *      Author: Teresa
 */

#include <immintrin.h>
#include <stdio.h>

int main(){
	double array1[4][4]__attribute__((alligner(32))) = {{9.0, 2.0, 1.0, 2.0}, {3.0, 2.0, 7.0, 2.0}, {4.0, 4.0, 6.0, 4.0}, {1.0, 2.0, 9.0, 8.0}};
	double array2[4][4]__attribute__((alligner(32))) = {{1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}, {1.0, 1.0, 1.0, 1.0}};
	double resultado[4][4]__attribute__((alligner(32))) = {{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}};
	int comprobar = 0;

	comprobar = fi_sumar_matrices_4x4_double(*array2, *array2, *resultado);

	if (comprobar != 0){
		for (int i = 0; i < 4; i++){
			for (int j = 0; j < 4; j++){
				printf ("%f \t", resultado[i][j]);
			}
			printf ("\n");
		}
	} else
		printf ("Error");
return 0;
}

int fi_sumar_matrices_4x4_double(const double *ptr_matriz_1, const double *ptr_matriz_2, double *ptr_matriz_suma){
	if(ptr_matriz_1 == NULL || ptr_matriz_2 == NULL || ptr_matriz_suma == NULL)
		return 0;
	else {
		__m256d a, b;

		for (int i = 0; i < 4; i++){
			a = _mm256_load_pd(ptr_matriz_1);
			b = _mm256_load_pd(ptr_matriz_2);
			_mm256_store_pd(ptr_matriz_suma, _mm256_add_pd(a,b));

			ptr_matriz_1 = ptr_matriz_1 + 4;
			ptr_matriz_2 = ptr_matriz_2 + 4;
			ptr_matriz_suma = ptr_matriz_suma + 4;
		}
		return 1;
	}

}

