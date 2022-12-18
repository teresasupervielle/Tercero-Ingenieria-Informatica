;===============================================================================
; Fichero: convertir_celcius_fahrenhiet.S
;-------------------------------------------------------------------------------
; char * uint_a_cadena_binario(unsigned int dato, char * buffer);
;===============================================================================

global _convertir_celcius_fahrenheit
section .text

_convertir_celcius_fahrenheit:
	push ebp
	mov ebp, esp

	;definicion de los datos de la pila
	%define temp_entrada [ebp + 8]
	%define sentido_conversion [ebp + 12]
	%define p_temp_salida [ebp + 16]

	push esi
	mov esi, p_temp_salida ;movemos la temperatura de salida a esi
	test esi, esi ;comprobamos que este vacia
	jz final ;saltamos a final porque seria un error

	mov eax, temp_entrada ;movemos a eax la temperatura que queramos convertir
	cmp dword sentido_conversion, 0 ;si recibe 0 el sentido_conversion se cambiara de celcius a fahrenheit, si es 1 al reves
	je c_a_f

c_f_a:
	mov ecx, 5 ;aplicamos la formula matematica
	sub eax, 32
	imul eax, ecx
	mov ecx, 9
	idiv ecx

	jmp fin

c_a_f:
	mov ecx, 9 ;igual aqui
	imul eax, ecx
	mov ecx, 5
	idiv ecx
	add eax, 32

fin:	shl edx, 1 ;redondear
		cmp edx, ecx
		jl result
		add eax, 1
result:	mov [esi], eax ;movemos el resultado de cada conversion a esi para almacenarla en el resultado

final:	pop esi ;pop esi porque hicimos el push
		pop ebp
		ret
