;===============================================================================
; Fichero: det.S
;-------------------------------------------------------------------------------
; Fichero con la funci?n mayor en ensamblador que devuelve el mayor de dos
; n?meros enteros pasados como par?metros.
;
; Versi?n para Windows.
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
