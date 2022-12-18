#include <stdio.h>

int es_palindromo (const char *cadena);

int main(){
	char cadena [10] = "reconocer";
	int ret;

	ret = es_palindromo(cadena);
	if (ret) printf ("Si es palindromo");
	else printf ("No es palindromo");
	if (ret < 0) printf ("Error");

return 0;
}
