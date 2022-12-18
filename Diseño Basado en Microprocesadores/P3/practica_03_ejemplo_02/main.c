#include <stdio.h>

int sumar_diagonal(long *matriz, unsigned int num_filas_columnas, long *resultado);
int main(){
	long matriz[9]= {1,2,3,4,5,6,7,8,9};
	unsigned int num_filas_columnas = 9;
	long resultado;
	int ret;

	ret = sumar_diagonal (matriz, num_filas_columnas, &resultado);
	if (ret != 0)
		printf("\n %ld", resultado);
	else
		printf("\nError");
return 0;
}

