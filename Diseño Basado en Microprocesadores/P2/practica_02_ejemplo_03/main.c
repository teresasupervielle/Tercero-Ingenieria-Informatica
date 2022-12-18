/*==============================================================================
* Fichero: main.c
*------------------------------------------------------------------------------
* Fichero en C para el programa de ejemplo.
* =============================================================================
*/
#include <stdio.h>

void copiar_bloque_memoria(int *dest, int *org, unsigned int long_bytes);
int main(){
	int *dest = 7, *org;
	unsigned int long_bytes = 10;
	setvbuf(stdout, NULL, _IONBF, 0);
	copiar_bloque_memoria(&dest, &org, long_bytes);

	printf ("%d", org);
return 0;
}
