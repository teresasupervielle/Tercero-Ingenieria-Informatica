;int desempaquetar(const estructura_empaquetada *origen, estructura *destino);
;
;int empaquetar(const estructura *origen, estructura_empaquetada *destino)
;
;Estructura desempaquetada
;	short 2bytes {0, 1}
;	char[3] 1bytesx3 {2, 4}
;	int 4bytes {8, 11}
;	long 8bytes {16, 23}
;
;Estrucura empaquetada
;	short 2bytes {0, 1}
;	char[3] 1bytesx3 {2, 4}
;	int 4bytes {5, 8}
;	long 8bytes {9, 16}

global desempaquetar
section .text

desempaquetar:
	xor rax, rax
	test rcx, rcx ;comprobar que los punteros no sean nulos
	jz fin
	test rdx, rdx
	jz fin

	xor r8, r8
	mov r8w, [rcx] ;lee short
	mov [rdx], r8w ;escribe short
	mov r8d, [rcx+2] ;lee cadena
	mov [rdx+2], r8w ;escribe 2 bytes
	shr r8, 16
	mov [rdx+4], r8b ;escribe 1 byte

	mov r8d, [rcx+5] ;lee int
	mov [rdx+8], r8d ;escribe int

	mov r8, [rcx+9] ;lee long
	mov [rdx+16], r8 ;escribe long

	mov rax, 1
fin: ret
