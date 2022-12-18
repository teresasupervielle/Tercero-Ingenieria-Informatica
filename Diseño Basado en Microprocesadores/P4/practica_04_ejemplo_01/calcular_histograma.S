;
;int calcular_histograma(const unsigned char *ptr_datos, unsigned int num_datos, unsigned int *ptr_histograma);
;

global calcular_histograma
section .text

calcular_histograma:
	test rcx, rcx ;comprueba que los punteros no sean nulos
	jz error
	test r8, r8
	jz error

;r8 y r10 puntero al histograma
;rcx puntero a los datos
;rdx contador
;r9 valor 256

	mov r9, 256
	mov r10, r8

bucle_histograma:
	mov dword[r8], 0
	add r8, 4
	dec r9
	jnz bucle_histograma

	xor r11, r11 ;acumulador a 0
bucle:
	mov r11b, [rcx]
	add dword[r10+r11*4], 1
	inc rcx
	dec rdx
	jnz bucle


	mov eax, 1
	jmp fin
error: xor eax, eax

fin: ret
