/*==============================================================================
* Fichero: main.c
*------------------------------------------------------------------------------
* Fichero en C para el programa de ejemplo.
* =============================================================================
*/
#include <stdio.h>
int det(int a11, int a12, int a21, int a22);
int main(){
	int a11 = 1, a12 = 2, a21 = 3, a22 = 4, c;
	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	* la consola de Eclipse.
	*/
	setvbuf(stdout, NULL, _IONBF, 0);
	c = det(a11, a12, a21, a22);
	printf("\nEl determinante sería: %d", c);
return 0;
}
