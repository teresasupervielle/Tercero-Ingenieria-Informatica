;===============================================================================
; Fichero: mayor.S
;-------------------------------------------------------------------------------
; Fichero con la función mayor en ensamblador que devuelve el mayor de dos
; números enteros pasados como parámetros.
;
; Versión para Windows.
;===============================================================================
global _mayor
section .text
_mayor:
	push ebp
	mov ebp, esp
	mov eax, [ebp + 8]
	cmovl  eax, [ebp + 12]
el_primero_es_mayor:
	pop ebp
	ret
