#include <stdio.h>

int ordenar(int *array, unsigned int longitud);
int main(){
int array[6] = {2,1,3,4,6,5};
int ret, i;
	for (i = 0; i < 6; i++){
		printf ("%d", array[i]);
	}

	printf ("\n");

	ret = ordenar (array, 6);
	if (ret != 0){
		for (i = 0; i < 6; i++){
			printf ("%d", array[i]);
		}
	}else
		printf("\nError");
return 0;
}
