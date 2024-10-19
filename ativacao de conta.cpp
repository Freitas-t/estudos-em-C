#include <stdio.h>
int main (){
	int cadastro, ativo, logado;
	char opcao;
	
	cadastro = ativo = logado = 0;
	
	printf("deseja cadastrar a conta? s/n \n");
	scanf(" %c", &opcao);
	
	if (opcao == 's'){
		cadastro = 1;
		printf("\nConta cadastrada\n");
	}
	printf("deseja ativar a conta? s/n \n");
	scanf(" %c", &opcao);
	
	if (opcao == 's'){
		ativo = 1;
		printf("\nConta ativadaada\n");
	}
	printf("deseja logar a conta? s/n \n");
	scanf(" %c", &opcao);
	
	if (opcao == 's'){
		logado = 1;
		printf("\nConta logada\n");
	}
	
	if ((cadastro == 1) && (ativo == 1) || (logado == 1)){
		printf("\nSeja bem vindo.\n");
	} else {
		printf("\nNão se preocupe, algo deu errado mas voce pode tentar novamente\n");
	}
}

