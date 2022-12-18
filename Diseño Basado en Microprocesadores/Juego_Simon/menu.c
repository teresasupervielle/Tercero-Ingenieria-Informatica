#include "menu.h"
#include "glcd.h"
#include "font.h"

void menu(void){
	glcd_inicializar();
	
	glcd_fondo_texto(BLUE);
	
	
	glcd_xprintf (GLCD_X_SIZE/3, GLCD_Y_SIZE/3, WHITE, BLUE, FONT12X24, "JUEGO DEL SIMON");
	
	glcd_xprintf (GLCD_X_SIZE/8, 2*GLCD_Y_SIZE/3, GREEN, BLUE, FONT8X16, "NIVEL FACIL");
	glcd_xprintf (3.2*GLCD_X_SIZE/8, 2*GLCD_Y_SIZE/3, GREEN, BLUE, FONT8X16, "NIVEL MEDIO");
	glcd_xprintf (5.5*GLCD_X_SIZE/8, 2*GLCD_Y_SIZE/3, GREEN, BLUE, FONT8X16, "NIVEL DIFICIL");
}
