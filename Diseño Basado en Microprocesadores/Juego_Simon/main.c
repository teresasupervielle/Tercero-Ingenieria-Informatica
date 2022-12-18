#include "glcd.h"
#include "menu.h"
#include "simon.h"
#include "tipos.h"
#include "joystick.h"

int main (void){
	// VARIABLES
	
	int32_t joystick;
	
	//INICIALIZACIONES
	menu();
	
	while (TRUE){
		joystick = leer_joystick();
		switch (joystick){
			case JOYSTICK_IZQUIERDA: //NIVEL F�CIL
				nivel_facil();
			break;
			case JOYSTICK_CENTRO: //NIVEL INTERMEDIO
				nivel_medio();
			break;
			case JOYSTICK_DERECHA: //NIVEL DIF�CIL
				nivel_dificil();
			break;
		}
	}
	//return 0;
}

