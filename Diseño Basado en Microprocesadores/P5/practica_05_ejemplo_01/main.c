#include <stdio.h>
#include <time.h>

#include "qdbmp.h"

int sse_imagen_a_blanco_y_negro(unsigned char *ptr_imagen, int ancho, int alto, unsigned char umbral);

int main(int argc, char* argv[]){
    BMP* bmp;
    unsigned int ancho, alto;

    /* Leer la imagen original.
     */

    bmp = BMP_ReadFile("imagen_grises.bmp");
    BMP_CHECK_ERROR(stdout, -1);

    /* Obtener el ancho y el alto.
     */

    ancho = BMP_GetWidth(bmp);
    alto = BMP_GetHeight(bmp);

    /* Convertir a blanco y negro.
     */

    sse_imagen_a_blanco_y_negro(bmp->Data, ancho, alto, 100);

    /* Escribir en disco la imagen resultante.
     */

    BMP_WriteFile(bmp, "imagen_blanco_y_negro.bmp");
    BMP_CHECK_ERROR(stdout, -2);

    BMP_Free(bmp);

return 0;
}
