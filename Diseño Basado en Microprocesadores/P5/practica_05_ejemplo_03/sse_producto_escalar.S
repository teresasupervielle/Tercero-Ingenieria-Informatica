global sse_producto_escalar
section .text

sse_producto_escalar:
	test rcx, rcx
	jz error
	test rcx, 15
	jnz error
	test rdx, rdx
	jz error
	test rdx, 15
	jnz error

	mov r11, rdx
	cmp r8d, 16
	jb menor_16

	mov eax, r8d
	mov r10d, 16
	div r10d ;edx resto componentes sueltos
	pxor xmm2, xmm2
	mov r8d, edx
	mov rdx, r11

bucle:
	movaps xmm0, [rcx]
	movaps xmm1, [rdx]
	mulps xmm0, xmm1
	addps xmm2, xmm0
	add rcx, 16
	add rdx, 16
	dec eax
	jnz bucle

	haddps xmm2, xmm2
	haddps xmm2, xmm2

menor_16:
	movss xmm0, [rcx]
	movss xmm1, [rdx]
	mulss xmm0, xmm1
	addss xmm2, xmm0
	add rcx, 16
	add rdx, 16
	dec r8d
	jnz bucle

	movss [r9d], xmm2

	mov eax, 1
	jmp fin
error:
	xor eax, eax
fin:
	ret
