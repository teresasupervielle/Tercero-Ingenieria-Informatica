;===============================================================================
; Fichero: uint_a_cadena_binario.S
;-------------------------------------------------------------------------------
; char * uint_a_cadena_binario(unsigned int dato, char * buffer);
;===============================================================================
global _uint_a_cadena_binario
section .text

_uint_a_cadena_binario:
	push ebp
	mov ebp, esp

	%define dato [ebp+8]
	%define buffer [ebp+12]

	push esi
	mov ecx, dato ;cargamos dato
	mov esi, buffer ;cargamos buffer

	test esi, esi ;comprobamos que el buffer no tenga ningun error
	jz error

	mov edx, 32 ;contador

bucle: 	xor al, al
		shl byte dato, 1 ;desplazamiento a 1 bit
		adc al, '0'
		mov [esi], al ;movemos al a la posicion de memoria de esi
		inc esi ;incrementamos esi
		dec edx ;decrementa y pone la flag a cero(cuando edx llegue a zero)
		jnz bucle ;salta al bucle si no es cero la flag

		mov byte[esi], 0 ;movemos a esi el 0

error:	pop esi ;pop esi porque hicimos un push
		pop ebp
		ret
