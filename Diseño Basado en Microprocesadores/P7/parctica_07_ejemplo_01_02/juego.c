/***************************************************************************//**
 */

#include "juego.h"
#include "bloque.h"
#include "pieza.h"
#include "cuveta.h"
#include "glcd.h"
#include "timer0.h"
#include "timer1.h"
#include "marcador.h"
#include <stdint.h>
#include <stdlib.h>

/***************************************************************************//**
 */
void juego(void)
{
    static pieza_t pieza_actual;
    static pieza_t pieza_siguiente;
    static cuveta_t cuveta;
    static int32_t x_pieza_actual;
    static int32_t y_pieza_actual;

    int32_t filas_completadas = 0;
    int32_t puntos = 0;
    int32_t nivel = 1;
    int32_t tiempo_paso = 750 - (nivel - 1)*50;
    int32_t temp_tiempo_paso = tiempo_paso;

    extern volatile int32_t contador_ms;

    glcd_borrar(BLACK);

    srand(contador_ms);

    cuveta_inicializar(&cuveta);
    cuveta_pintar(&cuveta);
    marcador_pintar();

    pieza_inicializar(&pieza_actual, (pieza_tipo_t)(rand()%PIEZA_NUM_PIEZAS));
    x_pieza_actual = (CUVETA_ANCHO + pieza_actual.tamano - 4)/2;
    y_pieza_actual = -pieza_actual.tamano;

    pieza_inicializar(&pieza_siguiente, (pieza_tipo_t)(rand()%PIEZA_NUM_PIEZAS));

    cuveta_pintar_pieza(&cuveta, &pieza_actual,
            x_pieza_actual, y_pieza_actual);

    marcador_siguiente(&pieza_siguiente);
    marcador_lineas(filas_completadas);
    marcador_puntos(puntos);
    marcador_nivel(nivel);

    while (TRUE)
    {
        int32_t t;

        if (contador_ms >= tiempo_paso)
        {
            bool_t toca = FALSE;
          
            contador_ms = 0;

            cuveta_hay_interseccion(&cuveta, &pieza_actual,
                                    x_pieza_actual, y_pieza_actual + 1,
                                    &toca);
            if (!toca)
            {
                cuveta_borrar_pieza(&cuveta, &pieza_actual,
                                    x_pieza_actual, y_pieza_actual);
                y_pieza_actual++;
                cuveta_pintar_pieza(&cuveta, &pieza_actual,
                                    x_pieza_actual, y_pieza_actual);
            }
            else
            {
                bool_t hay_desbordamiento;
                cuveta_hay_desbordamiento(&cuveta, &pieza_actual,
                                          x_pieza_actual, y_pieza_actual,
                                          &hay_desbordamiento);
                if (!hay_desbordamiento)
                {
                    int32_t filas_eliminadas = 0;
                  
                    cuveta_fijar_pieza(&cuveta, &pieza_actual,
                                       x_pieza_actual, y_pieza_actual);

                    cuveta_revisar_filas(&cuveta, &filas_eliminadas);

                    if (filas_eliminadas > 0)
                    {
                        cuveta_pintar(&cuveta);

                        filas_completadas += filas_eliminadas;

                        puntos += filas_eliminadas*10*nivel;

                        marcador_lineas(filas_completadas);
                        marcador_puntos(puntos);
                        
                        if (nivel < 9)
                        {
                            nivel = filas_completadas / 10 + 1;
                            marcador_nivel(nivel);
                            tiempo_paso = 750 - (nivel - 1)*50;
                        }
                    }
                    
                    pieza_actual = pieza_siguiente;
                    x_pieza_actual = (CUVETA_ANCHO + pieza_actual.tamano - 4)/2;
                    y_pieza_actual = -pieza_actual.tamano;                
                    cuveta_pintar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                    pieza_inicializar(&pieza_siguiente,
                                      (pieza_tipo_t)(rand() % PIEZA_NUM_PIEZAS));
                    marcador_siguiente(&pieza_siguiente);
                }
                else
                {
                    int32_t p;
                                    
                    glcd_texto(cuveta.x_pantalla + 3*BLOQUE_TAMANO/4,
                               BLOQUE_TAMANO*8,
                               RED,
                               BLACK,
                               FONT8X16,
                               "G A M E  O V E R");
                    while (leer_pulsacion() != 0);

                    do
                    {
                        p = leer_pulsacion();
                    }
                    while (p == 0 || p >= 0x10);
                    
                    return;
                }
            }                                            
        }
        else if ((t = leer_pulsacion()) != 0)
        {
            tiempo_paso = temp_tiempo_paso;
            if (t == 1)
            {
                bool_t hay_interseccion = FALSE;
                            
                pieza_t pieza_temp = pieza_actual;
                pieza_rotar(&pieza_temp, DERECHA);
                cuveta_hay_interseccion(&cuveta, &pieza_temp,
                                        x_pieza_actual, y_pieza_actual,
                                        &hay_interseccion);
                if (!hay_interseccion)
                {
                    cuveta_borrar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                    pieza_rotar(&pieza_actual, DERECHA);
                    cuveta_pintar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                }
            }
            else if (t == 5)
            {
                bool_t hay_interseccion = FALSE;              
                pieza_t pieza_temp = pieza_actual;
                pieza_rotar(&pieza_temp, IZQUIERDA);
                cuveta_hay_interseccion(&cuveta, &pieza_temp,
                                        x_pieza_actual, y_pieza_actual,
                                        &hay_interseccion);
                if (!hay_interseccion)
                {
                    cuveta_borrar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                    pieza_rotar(&pieza_actual, IZQUIERDA);
                    cuveta_pintar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                }
            }
            else if (t == 3)
            {                
                bool_t hay_interseccion = FALSE;
                cuveta_hay_interseccion(&cuveta, &pieza_actual,
                                    x_pieza_actual - 1, y_pieza_actual,
                                    &hay_interseccion);
                if (hay_interseccion == 0)
                {
                    cuveta_borrar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                    x_pieza_actual--;
                    cuveta_pintar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                }                
            }
            else if (t == 4)
            {                
                bool_t hay_interseccion = FALSE;
                cuveta_hay_interseccion(&cuveta, &pieza_actual,
                                        x_pieza_actual + 1, y_pieza_actual,
                                        &hay_interseccion);
                if (hay_interseccion == 0)
                {
                    cuveta_borrar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                    x_pieza_actual++;
                    cuveta_pintar_pieza(&cuveta, &pieza_actual,
                                        x_pieza_actual, y_pieza_actual);
                }                
            }
            else if (t == 2)
            {
                temp_tiempo_paso = tiempo_paso;
                tiempo_paso = 50;
            }
            /*
            else// if (t == 0x12)
            {
                tiempo_paso = temp_tiempo_paso;
            }
            */
        }        
    }
}
