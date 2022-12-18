#include <stdio.h>

typedef struct{
	short a;
	char b[3];
	int c;
	long long d;
} estructura;

typedef struct __attribute((packed))__{
	short a;
	char b[3];
	int c;
	long long d;
} estructura_empaquetada;

int desempaquetar(const estructura_empaquetada *origen, estructura *destino);
int empaquetar(const estructura *origen, estructura_empaquetada *destino);


int main (){
	int comprobar;
	estructura_empaquetada b;
	estructura a;

	b.a = 1;
	b.b[0] = 'a';
	b.b[1] = 'b';
	b.b[2] = '\0';
	b.c = 420;
	b.d = 1337;

	comprobar = desempaquetar(&b, &a);
	if (comprobar != 0)
		printf ("%d \n%s \n%d \n%I64d", a.a, a.b, a.c, a.d);
	else printf ("\n Error");

return 0;
}
