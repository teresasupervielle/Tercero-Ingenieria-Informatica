;===============================================================================
; Fichero: copiar_bloque_memoria.S
;-------------------------------------------------------------------------------
; void copiar_bloque_memoria(int *dest, int *org, unsigned int long_bytes);
;===============================================================================
global _copiar_bloque_memoria
section .text

_copiar_bloque_memoria:
	push ebp
	mov ebp, esp

	%define long_bytes [ebp + 16] ;definimos el dato

	push esi
	mov ecx, long_bytes
	shr ecx, 2 ;desplazamiento hacia la derecha
	jz long_menor_4

	rep movsd

long_menor_4:
	mov ecx, long_bytes
	and ecx, 3
	jz fin
	rep movsb

	mov [esi], eax
fin: 	pop esi ;pop esi porque ya hicimos el push
		pop ebp
		ret
