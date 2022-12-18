;int ordenar(int *array, unsigned int longitud);

global ordenar
section .text

ordenar:
	push rdi
	push rsi
	xor eax, eax ;preparamos eax a 0
	test rcx, rcx ;comprobamos que rcx este bien
	jz error
	xor r9, rcx
	add r9, 4 ;desplazamos r9 una posicion

	mov rdi, rcx ;movemos rcx y r9 a rdi y rsi respectivamente
	mov rsi, r9

	sub rdx, 2 ;longitud - 2
	mov rax, rdx ;movemos la longitud - 2 a rax

	mov r10, rdi ;obtenemos las dos primeras posiciones del vector
	mov r11, r9

bucle:

bucle_int:
	cmp r10, r11 ;comparamos las dos primeras posiciones
	jl no_inter ;si r10 < r11 no se intercambia
	xchg r10, r11 ;si no se intercambia

no_inter:
	add rcx, 1
	add r9, 1
	dec rdx ;decrementamos la longitud
	jnz bucle_int ;si no es igual que 0 volvemos al bucle interno

	mov rcx, rdi ;movemos rdi y rsi a rcx y r9 respectivamente
	mov r9, rsi

	dec rax ;decrementamos la longitud
	mov rdx, rax ;movemos rax a rdx
	cmp rdx, 0 ;lo comparamos con 0
	jnz bucle ;si no es cero, vuelve al bucle
	mov eax, 1 ;devuelve 1 si esta bien
error:  pop rsi
		pop rdi
		ret ;return
