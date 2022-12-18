global sse_sumar_filas
section .text

sse_sumar_filas:
	test rcx, rcx
	jz error
	test rcx, 15
	jnz error
	test rdx, rdx
	jz error
	test rdx, 15
	jnz error

	movaps xmm0, [rcx]
	movaps xmm1, [rcx+16]
	movaps xmm2, [rcx+32]
	movaps xmm3, [rcx+48]

	addps xmm0, xmm1
	addps xmm0, xmm2
	addps xmm0, xmm3

	movaps [rdx], xmm0

	mov eax, 1
	jmp fin

error:
	xor eax, eax
