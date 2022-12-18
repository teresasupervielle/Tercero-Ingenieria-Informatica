;
; int sse_imagen_a_blanco_y_negro(unsigned char *ptr_imagen, int ancho, int alto, unsigned char umbral);
;
;	ptr_imagen => rcx
;	ancho => edx
;	alto => r8
;	umbral => r9
;

global sse_imagen_a_blanco_y_negro
section .text

sse_imagen_a_blanco_y_negro:
	xor eax, eax

	test rcx, rcx
	jz error ;comprueba que el puntero no es nulo

	test rcx, 15
	jnz error ;comprueba si esta alineado

	cmp edx, 0
	jle error ;comprueba el ancho

	cmp r8d, 0
	jle error ;comprueba el alto

	imul r8d, edx
	mov eax, edx ;ancho * alto (numero de pixeles)

	movd xmm1, r9d
	pxor xmm0, xmm0
	pshufb xmm1, xmm0 ;reparte el valor r9 a todos los valores de los bytes de xmm1


	shr eax, 4
	mov r10d, eax
	cmp eax, 0
	jz menor_16_pixeles

bucle:
	movdqa xmm0, [rcx]
	pminub xmm0, xmm1
	pcmpeqb xmm0, xmm1

	movdqa [rcx], xmm0
	add rcx, 16
	dec r10d

	jnz bucle

menor_16_pixeles:
	and edx, 0b1111
	jz salir

bucle_:
	mov al, [rcx]
	cmp al, r9b
	jnb valor_negro
	mov byte[rcx], 0
	jmp no_negro
valor_negro:
	mov byte[rcx], 255
no_negro:
	inc rcx
	dec edx
	jnz bucle_

salir:
	mov eax, 1
	jmp fin

error:
	xor eax, eax
fin:
	ret
