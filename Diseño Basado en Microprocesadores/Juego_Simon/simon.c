#include "simon.h"
#include "glcd.h"
#include "joystick.h"
#include "timer_lpc40xx.h"
#include <stdlib.h>
//#include <time.h>

void imprimir_juego(void){
	glcd_inicializar();
	
	glcd_fondo_texto(BLACK);
	
	glcd_rectangulo_relleno(GLCD_X_SIZE/3, GLCD_Y_MINIMO, 2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, RED); //COLOR ROJO ARRIBA EN EL CENTRO
	
	glcd_rectangulo_relleno(GLCD_X_MINIMO, GLCD_Y_SIZE/3, GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, GREEN); //COLOR VERDE A LA IZQUIERDA
	
	glcd_rectangulo_relleno(2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, GLCD_X_MAXIMO, 2*GLCD_Y_SIZE/3, BLUE); //COLOR AZUL A LA DERECHA
	
	glcd_rectangulo_relleno(GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, 2*GLCD_X_SIZE/3, GLCD_Y_MAXIMO, YELLOW); //COLOR AMARILLO ABAJO EN EL CENTRO

}

void imprimir_ganado(void){
	glcd_inicializar();
	
	glcd_fondo_texto(BLACK);
	
	glcd_rectangulo_relleno(GLCD_X_SIZE/3, GLCD_Y_MINIMO, 2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, RED); //COLOR ROJO ARRIBA EN EL CENTRO
	
	glcd_rectangulo_relleno(GLCD_X_MINIMO, GLCD_Y_SIZE/3, GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, GREEN); //COLOR VERDE A LA IZQUIERDA
	
	glcd_rectangulo_relleno(2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, GLCD_X_MAXIMO, 2*GLCD_Y_SIZE/3, BLUE); //COLOR AZUL A LA DERECHA
	
	glcd_rectangulo_relleno(GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, 2*GLCD_X_SIZE/3, GLCD_Y_MAXIMO, YELLOW); //COLOR AMARILLO ABAJO EN EL CENTRO
	
	glcd_xprintf (GLCD_X_SIZE/3, GLCD_Y_SIZE/3, WHITE, BLACK, FONT12X24, "HAS GANADO!");		// Imprimimos el texto de haber ganado 
}

void imprimir_perdido(void){
	glcd_inicializar();
	
	glcd_fondo_texto(BLACK);
	
	glcd_rectangulo_relleno(GLCD_X_SIZE/3, GLCD_Y_MINIMO, 2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, RED); //COLOR ROJO ARRIBA EN EL CENTRO
	
	glcd_rectangulo_relleno(GLCD_X_MINIMO, GLCD_Y_SIZE/3, GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, GREEN); //COLOR VERDE A LA IZQUIERDA
	
	glcd_rectangulo_relleno(2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, GLCD_X_MAXIMO, 2*GLCD_Y_SIZE/3, BLUE); //COLOR AZUL A LA DERECHA
	
	glcd_rectangulo_relleno(GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, 2*GLCD_X_SIZE/3, GLCD_Y_MAXIMO, YELLOW); //COLOR AMARILLO ABAJO EN EL CENTRO
	
	glcd_xprintf (GLCD_X_SIZE/3, GLCD_Y_SIZE/3, WHITE, BLACK, FONT12X24, "HAS PERDIDO :(!");  //Imprimimos el texto de haber perdido 
}

void parpadeo_rojo(void) {			//Función para realizar el parpadeo en el color rojo 
				timer_inicializar(TIMER0);
				glcd_rectangulo_relleno(GLCD_X_SIZE/3, GLCD_Y_MINIMO, 2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, WHITE);
				timer_iniciar_ciclos_ms(TIMER0, 1000);
				timer_esperar_fin_ciclo(TIMER0);
				glcd_rectangulo_relleno(GLCD_X_SIZE/3, GLCD_Y_MINIMO, 2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, RED);
}

void parpadeo_verde(void) {		//Función para realizar el parpadeo en el color verde 
				timer_inicializar(TIMER0);
				glcd_rectangulo_relleno(GLCD_X_MINIMO, GLCD_Y_SIZE/3, GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, WHITE);
				timer_iniciar_ciclos_ms(TIMER0, 1000);
				timer_esperar_fin_ciclo(TIMER0);
				glcd_rectangulo_relleno(GLCD_X_MINIMO, GLCD_Y_SIZE/3, GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, GREEN);
}

void parpadeo_azul(void) {		//Función para realizar el parpadeo en el color azul 
				timer_inicializar(TIMER0);
				glcd_rectangulo_relleno(2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, GLCD_X_MAXIMO, 2*GLCD_Y_SIZE/3, WHITE);
				timer_iniciar_ciclos_ms(TIMER0, 1000);
				timer_esperar_fin_ciclo(TIMER0);
			  glcd_rectangulo_relleno(2*GLCD_X_SIZE/3, GLCD_Y_SIZE/3, GLCD_X_MAXIMO, 2*GLCD_Y_SIZE/3, BLUE);
}

void parpadeo_amarillo(void) {		//Función para realizar el parpadeo en el color amarillo 
				timer_inicializar(TIMER0);
				glcd_rectangulo_relleno(GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, 2*GLCD_X_SIZE/3, GLCD_Y_MAXIMO, WHITE);
				timer_iniciar_ciclos_ms(TIMER0, 1000);
				timer_esperar_fin_ciclo(TIMER0);
				glcd_rectangulo_relleno(GLCD_X_SIZE/3, 2*GLCD_Y_SIZE/3, 2*GLCD_X_SIZE/3, GLCD_Y_MAXIMO, YELLOW);
}


void nivel_facil(void){		//En el nivel facil se considera ganado acertando solo el color que sale, no saldrá más de 1 color. 
	int numero;
	int ganado = 0; //0 = TRUE
	int32_t joystick_juego = JOYSTICK_NADA;
	
	imprimir_juego();		//Imprimimos el juego 
	timer_inicializar(TIMER0);	//Inicializamos los timers 
	timer_inicializar(TIMER1);
	timer_inicializar(TIMER2);
	
	timer_iniciar_conteo_ms (TIMER2);
	srand(timer_leer(TIMER2)); 
	
	numero = rand() % 4;	//Inicializamos numero al numero aleatorio 
	
	while (ganado == 0){		// Hasta que no falle sigue jugando 
		timer_iniciar_ciclos_ms(TIMER0, 4000);
		timer_iniciar_ciclos_ms(TIMER1, 1000);
		switch(numero){
			case 0:
				parpadeo_rojo();
			break;
			case 1:
				parpadeo_verde();				
			break;
			case 2:
				parpadeo_azul();				
			break;
			case 3:
				parpadeo_amarillo();				
			break;
		}
		
		timer_esperar_fin_ciclo(TIMER0);
		
		joystick_juego = leer_joystick();		//leemos el Joystick 
		ganado = comprobar_ganado_facil(joystick_juego, numero);	//Comprobamos si hemos ganado 
		if(ganado == 0) {		//Si hemos ganado nos crea otro numero aleatorio nos imprime ganado y nos vuelve a imprimir el juego 
			numero = rand() % 4;
			imprimir_ganado();
			timer_esperar_fin_ciclo(TIMER1);
			imprimir_juego();
		}
		if (ganado == 1){		//Si hemos perdido nos sacará por pantalla y no volverá a salir el juego 
			imprimir_perdido();
		}
	}
}

void nivel_medio(void){		//Estamos ante el nivel medio, se considerará ganado si acertamos los 3 colores sin fallar ninguno 
	int numero[3], i;
	int ganado = 0;
	int32_t joystick_juego[3];
	
	imprimir_juego();
	timer_inicializar(TIMER0);
	timer_inicializar(TIMER1);
	timer_inicializar(TIMER2);
	
	timer_iniciar_conteo_ms (TIMER2);
	srand(timer_leer(TIMER2)); 
	
	while (ganado == 0){
		timer_iniciar_ciclos_ms(TIMER0, 1000);
		timer_iniciar_ciclos_ms(TIMER1, 1000);
		for (i = 0; i < 3; i++){			//Controlamos que solo sean 3 parpadeos 
			numero[i] = rand() % 4;
			switch(numero[i]){
				case 0:
					parpadeo_rojo();
				break;
				case 1:
					parpadeo_verde();				
				break;
				case 2:
					parpadeo_azul();				
				break;
				case 3:
					parpadeo_amarillo();				
				break;
			}
		}
		
		i = 0;
		
		
		while (i < 3){
			timer_iniciar_ciclos_ms(TIMER0, 1000);
			if (leer_joystick() == JOYSTICK_ARRIBA){		//Leemos el Joystick y guardamos el valor en el vector
				joystick_juego[i] = JOYSTICK_ARRIBA;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
			else if (leer_joystick() == JOYSTICK_ABAJO){		//Leemos el Joystick y guardamos el valor en el vector
				joystick_juego[i] = JOYSTICK_ABAJO;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
			else if (leer_joystick() == JOYSTICK_DERECHA){		//Leemos el Joystick y guardamos el valor en el vector
				joystick_juego[i] = JOYSTICK_DERECHA;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
			else if (leer_joystick() == JOYSTICK_IZQUIERDA){		//Leemos el Joystick y guardamos el valor en el vector
				joystick_juego[i] = JOYSTICK_IZQUIERDA;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
		}
			
		ganado = comprobar_ganado_medio(joystick_juego, numero);	//Comprobamos si hemos acertado 

		if(ganado == 0) {			//Si hemos ganado nos imprime ganado y volveríamos a sacar el juego por pantalla 
			imprimir_ganado();
			timer_esperar_fin_ciclo(TIMER1);
			imprimir_juego();
		}
		if (ganado == 1){		//Si hemos perdido nos saldría el mensaje y ya no volvería a salir el juego 
			imprimir_perdido();
		}
	}
}


void nivel_dificil(void){ //En el nivel dificil empezaremos con 1 parpadeo e iremos incrementando los parpadeos a medida que vayamos obteniendo victorias, si perdemos se reinicia el progreso.
	int numero[50], i;
	int ganado = 0;
	int32_t joystick_juego[50];
	int ncolores = 1;		//ncolores va a ser la variable que nos va a controlar el numero de parpadeos 
	
	imprimir_juego();
	timer_inicializar(TIMER0);
	timer_inicializar(TIMER1);
	timer_inicializar(TIMER2);
	
		while (ganado == 0){
		timer_iniciar_ciclos_ms(TIMER0, 1000);
		timer_iniciar_ciclos_ms(TIMER1, 1000);
		for (i = 0; i < ncolores; i++){  //Controlamos que sean ncolores parpadeos 
			numero[i] = rand() % 4;
			switch(numero[i]){
				case 0:
					parpadeo_rojo();
				break;
				case 1:
					parpadeo_verde();				
				break;
				case 2:
					parpadeo_azul();				
				break;
				case 3:
					parpadeo_amarillo();				
				break;
			}			
		}
		
		i = 0;
		
		while (i < ncolores){
			timer_iniciar_ciclos_ms(TIMER0, 1000);
			if (leer_joystick() == JOYSTICK_ARRIBA){
				joystick_juego[i] = JOYSTICK_ARRIBA;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
			else if (leer_joystick() == JOYSTICK_ABAJO){
				joystick_juego[i] = JOYSTICK_ABAJO;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
			else if (leer_joystick() == JOYSTICK_DERECHA){
				joystick_juego[i] = JOYSTICK_DERECHA;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
			else if (leer_joystick() == JOYSTICK_IZQUIERDA){
				joystick_juego[i] = JOYSTICK_IZQUIERDA;
				i++;
				timer_esperar_fin_ciclo(TIMER0);
			}
		}
			
		ganado = comprobar_ganado_dificil(joystick_juego, numero, ncolores);

		if(ganado == 0) {		
			imprimir_ganado();
			timer_esperar_fin_ciclo(TIMER1);
			imprimir_juego();
			ncolores++;
		}
		if (ganado == 1){
			imprimir_perdido();
		}
	}
}

int comprobar_ganado_facil(int32_t joystick_juego, int numero){		//Se considera ganado acertando el color que ha parpadeado 
	
	if( (numero == 0 && joystick_juego == JOYSTICK_ARRIBA) ||
		  (numero == 1 && joystick_juego == JOYSTICK_IZQUIERDA) ||
	    (numero == 2 && joystick_juego == JOYSTICK_DERECHA) ||
	    (numero == 3 && joystick_juego == JOYSTICK_ABAJO) ) return 0;
	else 
		return 1;		
}

int comprobar_ganado_medio(int32_t joystick_juego[3], int numero[3]){		//Se considera ganado acertando los 3 colores que han parpadeado sin fallar ninguno 
	int i;
	
	for (i = 0; i < 3; i++) 
		 if(comprobar_ganado_facil(joystick_juego[i], numero[i]) == 1) return 1;
	
	return 0;	// TRUE
}


int comprobar_ganado_dificil(int32_t joystick_juego[50], int numero[50], int ncolores){  //Se considera ganado cuando acertamos todos los colores que parpadeen. 
	int i;
	
	for (i = 0; i < ncolores; i++) 
		 if(comprobar_ganado_facil(joystick_juego[i], numero[i]) == 1) return 1;
	
	return 0;
}
