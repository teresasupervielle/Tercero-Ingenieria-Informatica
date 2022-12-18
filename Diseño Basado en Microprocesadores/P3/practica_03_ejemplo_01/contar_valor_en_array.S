; int contar_valor_en_array (int valor, int *array, unsigned int longitud, int *resultado);

global _contar_valor_en_array
section .text

_contar_valor_en_array:
	xor eax, eax ;inicializamos eax
	test rdx, rdx ;comprobamos que esta bien el registro rdx
	jz error
	test r9, r9 ;comprobamos que esta bien el registro r9
	jz error

bucle: cmp [rdx], ecx ;comparamos la direccion de memoria de rdx con el valor dado
	   jnz no_incr
	   add eax, 1 ;sumamos una a la solucion si coinciden

no_incr: add rdx, 4 ;desplazamos dentro del array
		 dec r8 ;decrementamos el iterador
		 jnz bucle

		 mov [r9], eax ;movemos la solucion a su direccion de memoria
		 mov eax, 1 ;devuelve 1 si esta todo bien
error:   ret ;return
