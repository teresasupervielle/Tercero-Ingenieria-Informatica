/*==============================================================================
* Fichero: main.c
*------------------------------------------------------------------------------
* Fichero en C para el programa de ejemplo.
* =============================================================================
*/
#include <stdio.h>
int mayor(int x, int y);
int main(int argc, char *argv[]){
	int a, b, c;
	char t;
	/* Desactivar el buffer de stdout para facilitar la depuraci�n a trav�s de
	* la consola de Eclipse.
	*/
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("\nIntroduzca un n�mero entero: ");
	scanf("%d", &a);
	printf("\nIntroduzca otro n�mero entero: ");
	scanf("%d", &b);
	c = mayor(a, b);
	printf("\nEl mayor de los n�meros es el %d", c);
	printf("\nPulse �s� y ENTER para salir.");
	do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');
return 0;
}
