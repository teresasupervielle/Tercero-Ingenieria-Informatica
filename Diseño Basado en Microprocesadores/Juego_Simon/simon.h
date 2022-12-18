#ifndef SIMON_H
#define SIMON_H

#include "tipos.h"

void imprimir_juego(void);
void imprimir_ganado(void);
void imprimir_perdido(void);
void inicializar_nivel(void);

void parpadeo_rojo(void);
void parpadeo_verde(void);
void parpadeo_azul(void);
void parpadeo_amarillo(void);

void nivel_facil(void);
void nivel_medio(void);
void nivel_dificil(void);

int comprobar_ganado_facil(int32_t joystick_juego, int numero);
int comprobar_ganado_medio(int32_t joystick_juego[3], int numero[3]);
int comprobar_ganado_dificil(int32_t joystick_juego[50], int numero[50],int ncolores);

#endif
