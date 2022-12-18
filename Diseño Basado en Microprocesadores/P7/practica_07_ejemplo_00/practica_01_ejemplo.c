/* Programa para parpadear el LED "MCIPWR" de la tarjeta.
* El LED "MCIPWR" se controla mediante el pin P1[5] del microcontrolador.
* El LED se enciende cuando el pin P1[5] está a 0 y se apaga cuando el
* pin P1[5] está a 1.
*/
/* El fichero de cabecera LPC407x_8x_177x_8x.h contiene las definiciones de
* los registros que controlan los periféricos del LPC4088.
*/

#include <LPC407x_8x_177x_8x.h>

int main(void)
{
	volatile int t; /* Variable para el contador de los bucles de retardo.*/
	/* Ponemos a uno el bit 5 del registro DIR del puerto 1 para configurar
	* el pin P1[5] como salida (por defecto, todos los pines de E/S del
	* microcontrolador están configurados como entradas).
	*/
	
	LPC_GPIO1->DIR |= 1u << 5;
	/* Bucle principal del programa que se limita a parpadear el LED.*/
	for (;;)
	{
		LPC_GPIO1->CLR = 1u << 5; /* Encender el LED. */  //Lo pone a 1 enviando un nivel bajo y con ello encendiendo el led
		for (t = 0; t < 1000000; t++) {} /* Retardo de tiempo. */
			
		LPC_GPIO1->SET = 1u << 5; /* Apagar el LED. */
			
		for (t = 0; t < 1000000; t++) {} /* Retardo de tiempo. */
	}
}