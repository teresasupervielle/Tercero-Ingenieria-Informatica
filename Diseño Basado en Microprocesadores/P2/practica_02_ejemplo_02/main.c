/*==============================================================================
* Fichero: main.c
*------------------------------------------------------------------------------
* Fichero en C para el programa de ejemplo.
* =============================================================================
*/

#include <stdio.h>

void convertir_celcius_fahrenheit(int temperatura_entrada, int sentido_conversion, int *temperatura_salida);
int main(){
	int temperatura_entrada, sentido_conversion, *temperatura_salida;
	setvbuf(stdout, NULL, _IONBF, 0);

	printf ("Escriba [0] si quiere convertir a Fahrenheit o [1] si quiere convertir a Celcius \n");
	scanf ("%d", &sentido_conversion);
	printf ("Escriba la temperatura a convertir:\n");
	scanf("%d", &temperatura_entrada);

	convertir_celcius_fahrenheit(temperatura_entrada, sentido_conversion, &temperatura_salida);

	printf ("%i", temperatura_salida);
return 0;
}
