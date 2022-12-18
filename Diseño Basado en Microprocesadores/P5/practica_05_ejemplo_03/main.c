/*
 * main.c
 *
 *  Created on: 8 abr. 2021
 *      Author: Teresa
 */


#include <stdio.h>

int sse_producto_escalar(const float *vector_1, const float *vector_2, unsigned int dimension, float *resultado);

int main(){

	const float vector_1[4] = {0, 1, 2, 3}, vector_2[4] = {4, 5, 6, 7};
	float resultado[4];
	unsigned int dimension = 4;
	int ret;

	ret = sse_producto_escalar(vector_1, vector_2, dimension, resultado);

	if (ret != 0)
		for (unsigned int i = 0; i < dimension; i++) printf ("%f", resultado[i]);
	else
		printf ("Error");

return 0;
}
