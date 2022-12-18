/*
 * main.c
 *
 *  Created on: 25 mar. 2021
 *      Author: Teresa
 */

#include <stdio.h>

int calcular_histograma(const unsigned char *ptr_datos, unsigned int num_datos, unsigned int *ptr_histograma);

int main(){
	unsigned char array[10] = {1, 5, 4, 4, 4, 4, 1, 2, 1, 0};
	unsigned int histograma[256];
	int comprobar;
	comprobar = calcular_histograma(array, 10, histograma);
	if (comprobar != 0)
		for (int i = 0; i < 10; i++) printf ("%i, ", histograma[i]);
	else printf ("\n Error");
return 0;
}
