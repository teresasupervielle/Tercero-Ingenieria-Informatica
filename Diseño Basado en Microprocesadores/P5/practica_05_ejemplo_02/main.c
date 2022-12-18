/*
 * main.c
 *
 *  Created on: 8 abr. 2021
 *      Author: Teresa
 */

#include <stdio.h>

int sse_sumar_filas(const float *ptr_matriz, float *ptr_suma);

int main(){
	const float ptr_matriz[][4] _attribute_((aligned(64))) = {{1.0, 2.0, 3.0, 4.0}, {5.0, 6.0, 7.0, 8.0}, {9.0, 10.0, 11.0, 12.0}, {13.0, 14.0, 15.0, 16.0}};
	float ptr_suma[4] _attribute_((aligned(16)) = {0.0, 0.0, 0.0, 0.0};
	int comprobar = 0;

	comprobar = sse_sumar_filas(ptr_matriz, ptr_suma);

	if (comprobar != 0)
		for (int i = 0; i < 4; i++)
			printf ("%f", ptr_suma[i]);
	else
		printf ("Error");
return 0;
}
