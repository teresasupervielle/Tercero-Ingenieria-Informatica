/*==============================================================================
* Fichero: main.c
*------------------------------------------------------------------------------
* Fichero en C para el programa de ejemplo.
* =============================================================================
*/
#include <stdio.h>
int e3(unsigned int a, unsigned int b);
int main(){
	unsigned int a = 0x0007, b = 0x0003, c;
	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	* la consola de Eclipse.
	*/
	setvbuf(stdout, NULL, _IONBF, 0);
	c = e3(a, b);
	printf("\nEl número resultante sería: %d", c);
return 0;
}
