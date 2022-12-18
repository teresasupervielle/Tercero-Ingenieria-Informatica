/***************************************************************************//**
 */

#include "menu.h"
#include "bloque.h"
#include "glcd.h"
#include "timer1.h"

static uint16_t rotulo[5][22] =
{
  {RED,   RED, RED,   BLACK, CYAN, CYAN,  CYAN,  BLACK, GREEN, GREEN, GREEN, BLACK, BLUE, BLUE,  BLUE,  BLACK, MAGENTA, BLACK, YELLOW, YELLOW, YELLOW},
  {BLACK, RED, BLACK, BLACK, CYAN, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK, BLACK, BLUE, BLACK, BLUE,  BLACK, MAGENTA, BLACK, YELLOW, BLACK,  BLACK },
  {BLACK, RED, BLACK, BLACK, CYAN, CYAN,  CYAN,  BLACK, BLACK, GREEN, BLACK, BLACK, BLUE, BLUE,  BLUE,  BLACK, MAGENTA, BLACK, YELLOW, YELLOW, YELLOW},
  {BLACK, RED, BLACK, BLACK, CYAN, BLACK, BLACK, BLACK, BLACK, GREEN, BLACK, BLACK, BLUE, BLUE,  BLACK, BLACK, MAGENTA, BLACK, BLACK,  BLACK,  YELLOW},
  {BLACK, RED, BLACK, BLACK, CYAN, CYAN,  CYAN,  BLACK, BLACK, GREEN, BLACK, BLACK, BLUE, BLACK, BLUE,  BLACK, MAGENTA, BLACK, YELLOW, YELLOW, YELLOW}
};

/***************************************************************************//**
 */
int32_t menu(void)
{
    int32_t i, j;
    int32_t p;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 21; j++)
        {
            bloque_pintar(BLOQUE_TAMANO*(5 + j), BLOQUE_TAMANO*(5 + i), rotulo[i][j]);
        }
    }

    glcd_texto(240 - 14*8, 200, WHITE, BLACK, FONT8X16,
               "PULSE EL JOYSTICK PARA COMENZAR");

    do
    {
        p = leer_pulsacion();
    }
    while (p == 0 || p >= 0x10);

    return 1;
}
