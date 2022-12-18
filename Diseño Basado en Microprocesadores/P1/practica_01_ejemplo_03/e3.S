;===============================================================================
; Fichero: e3.S
;-------------------------------------------------------------------------------
; Fichero con la función mayor en ensamblador que devuelve el mayor de dos
; números enteros pasados como parámetros.
;
; Versión para Windows.
;===============================================================================

global _e3
section .text
_e3:
	push ebp
	mov ebp, esp
	mov esi, 0

	mov eax, [ebp + 8]
	mov ebx, [ebp + 12]

	and eax, 0x1000
	and ebx, 0x0111

	or eax, ebx

	pop ebp
	ret
