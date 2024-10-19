#include <stdio.h>
int main(){
	int nota1, nota2, nota3, media;
	//coletar notas
	printf("Digite o resultado da avaliacao 1: \n");
	scanf("%d", &nota1);
	printf("digite o resultado da avaliacao 2: \n");
	scanf("%d", &nota2);
	printf("Digite o resultado da avaliacao 3: \n");
	scanf("%d", &nota3);
	//calcular e exibir média
	media = (nota1 + nota2 + nota3)/3;
	printf("media final: %d\n", media);
	//exibir resultado
	if (media >= 6)
	  printf("Aprovado.");
	if (media < 6)
	  printf("Reprovado.");
	return 0;
	
}
