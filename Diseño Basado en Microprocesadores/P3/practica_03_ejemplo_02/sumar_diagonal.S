; int sumar_diagonal(long *matriz, unsigned int num_filas_columnas, long *resultado);

global sumar_diagonal
section .text

sumar_diagonal:
	xor eax, eax ;inicializamos a 0 el registro eax
	test rcx, rcx ;comprobamos que no haya fallos en el registro rcx
	jz error
	test r8, r8 ;igual con el r8
	jz error
	cmp edx, 0 ;comprobamos que el numero de filas y columnas no sea 0
	jz error

	xor r9, r9 ;inicializamos r9 y r10
	xor r10, r10

bucle: add rax, [rcx] ;le sumamos al resultado lo que haya en la direccion de memoria de rcx
	   add r9, 1 ;incrementamos r9 a 1
	   mov r10, r9 ;movemos r9 a r10
	   shl r10, 2 ;desplazamos r10
	   add rcx, r10 ;sumamos r10 a rcx

	   dec rdx ;decrementamos el numero de filas y columnas
	   jnz bucle

	   mov [r8], rax ;movemos la solucion a la direccion de memoria correspondiente
	   mov rax, 1 ;devolvemos 1 si no hay ningun fallo

error:	ret ;return
