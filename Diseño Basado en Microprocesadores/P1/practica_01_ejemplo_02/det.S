;===============================================================================
; Fichero: det.S
;-------------------------------------------------------------------------------
; Fichero con la función mayor en ensamblador que devuelve el mayor de dos
; números enteros pasados como parámetros.
;
; Versión para Windows.
;===============================================================================
global _det
section .text
_det:
	push ebp
	mov ebp, esp

	mov eax, [ebp + 8]
	mov ebx, [ebp + 12]

	imul eax, [ebp+20]
	imul ebx, [ebp+16]

	sub eax, ebx

	pop ebp
	ret
