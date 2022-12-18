;
;int es_palindromo (const char *cadena);
;

global es_palindromo
section .text

es_palindromo:
	xor eax, eax ;comprueba que el puntero no sea nulo
	test rcx, rcx ;longitud cadena
	jz error

	mov r11, rcx

	mov rcx, -1
	repne scasb

palindromo:
	mov eax, 1
	jmp fin

error:
	mov eax, -1
	jmp fin

no_pal:
	xor eax, eax

fin: ret
