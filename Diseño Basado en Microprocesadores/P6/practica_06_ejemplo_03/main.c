#include "qdbmp.h"
#include <stdio.h>
#include <time.h>
#include "fi_seleccionar_rgb.h"

int main(int argc, char* argv[])
{
    BMP*    bmp;
    unsigned int ancho, alto;

    /* Leer la imagen original.
     */

    bmp = BMP_ReadFile("imagen_rgb.bmp");
    BMP_CHECK_ERROR(stdout, -1);

    /* Obtener el ancho y el alto.
     */

    ancho = BMP_GetWidth(bmp);
    alto = BMP_GetHeight(bmp);

    /* Seleccionar las componentes roja y azul.
     */

    fi_seleccionar_rgb(bmp->Data, ancho, alto, SELECCIONAR_VERDE | SELECCIONAR_ROJO);

    /* Escribir en disco la imagen resultante.
     */

    BMP_WriteFile(bmp, "imagen_modificada.bmp");
    BMP_CHECK_ERROR(stdout, -2);

    BMP_Free(bmp);

	return 0;
}
