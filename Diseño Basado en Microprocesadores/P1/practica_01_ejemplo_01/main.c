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
	/* Desactivar el buffer de stdout para facilitar la depuración a través de
	* la consola de Eclipse.
	*/
	setvbuf(stdout, NULL, _IONBF, 0);
	printf("\nIntroduzca un número entero: ");
	scanf("%d", &a);
	printf("\nIntroduzca otro número entero: ");
	scanf("%d", &b);
	c = mayor(a, b);
	printf("\nEl mayor de los números es el %d", c);
	printf("\nPulse ’s’ y ENTER para salir.");
	do{
		scanf("%c", &t);
	}while(t != 's' && t != 'S');
return 0;
}
