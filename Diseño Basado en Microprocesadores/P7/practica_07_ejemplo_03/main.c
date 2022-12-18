#include <LPC407x_8x_177x_8x.h>
#include "juego.h"
#include "glcd.h"
#include "timer0.h"
#include "timer1.h"
#include "leds.h"
#include "menu.h"
#include <stdint.h>

const uint32_t OscRateIn = 12000000;

int main(void)
{
    glcd_inicializar();

    timer0_inicializar();
    timer1_inicializar();
		
	leds_inicializar();
		
    while (TRUE)
    {
        glcd_borrar(BLACK);
        menu();
        juego();
    }   
}

