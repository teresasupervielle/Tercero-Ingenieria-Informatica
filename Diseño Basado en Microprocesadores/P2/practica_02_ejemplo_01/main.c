/*==============================================================================
* Fichero: main.c
*------------------------------------------------------------------------------
* Fichero en C para el programa de ejemplo.
* =============================================================================
*/
#include <stdio.h>
#include <string.h>
char * uint_a_cadena_binario(unsigned int dato, char * buffer);
int main(){
	unsigned int dato = 5;
	int i = 0;
	char *buffer, *cad;

	setvbuf(stdout, NULL, _IONBF, 0);
	*buffer = uint_a_cadena_binario(dato, &cad);

	for (i = 0; i < sizeof(buffer); i++){
		printf ("%d ", buffer[i]);
	}

return 0;
}
