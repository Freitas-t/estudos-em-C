#include <stdio.h>
#include <stdlib.h>

// Defini��o de uma estrutura para representar os n�s da �rvore de decis�o
typedef struct Node {
    char* descricao;  // Texto da situa��o ou escolha
    struct Node* escolha1;  // Pr�ximo n� se escolher a op��o 1
    struct Node* escolha2;  // Pr�ximo n� se escolher a op��o 2
    int final;  // 1 se o n� � um final da hist�ria, 0 caso contr�rio
} Node;

// Fun��o para criar um novo n�
Node* criarNo(char* descricao, int final) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->descricao = descricao;
    novoNo->escolha1 = NULL;
    novoNo->escolha2 = NULL;
    novoNo->final = final;
    return novoNo;
}

// Fun��o para navegar pela �rvore de decis�o
void navegarNaArvore(Node* atual) {
    int escolha;
    
    // Se o n� for um final, exibe o resultado e encerra
    if (atual->final == 1) {
        printf("\n%s\n", atual->descricao);
        printf("Fim do jogo.\n\n");
        return;
    }

    // Exibe a situa��o atual
    printf("\n%s\n", atual->descricao);
    printf("1. Se dedicou meuito e abdicou de lazer em alguns momentos.\n2. Escolheu o prazer, afinal vida e para aproveitar.\nEscolha: ");
    scanf("%d", &escolha);

    // Verifica se a escolha � v�lida e navega para o pr�ximo n�
    if (escolha == 1 && atual->escolha1 != NULL) {
        navegarNaArvore(atual->escolha1);
    } else if (escolha == 2 && atual->escolha2 != NULL) {
        navegarNaArvore(atual->escolha2);
    } else {
        printf("Escolha invalida! Tente novamente.\n");
        navegarNaArvore(atual);  // Pergunta novamente
    }
}

int main() {
    // Criar n�s da �rvore de decis�es
    Node* inicio = criarNo("Voce esta na infancia. Como voce era na escola?", 0);
    Node* adolescencia1 = criarNo("Adolescencia: Voce se concentrou nos estudos. O que deseja fazer agora?", 0);
    Node* adolescencia2 = criarNo("Adolescencia: Voce curtiu sua vida social. O que deseja fazer agora?", 0);
    Node* vidaAdulta1 = criarNo("Vida Adulta: Voce seguiu uma carreira estavel. E agora?", 0);
    Node* vidaAdulta2 = criarNo("Vida Adulta: Voce seguiu uma carreira arriscada. E agora?", 0);
    Node* finalSucesso = criarNo("Voce teve uma vida plena, com sucesso pessoal e profissional!", 1);
    Node* finalDificuldades = criarNo("Voce enfrentou dificuldades, mas conseguiu encontrar paz e satisfacao no fim.", 1);
    Node* finalFracasso = criarNo("Suas escolhas levaram a uma vida cheia de arrependimentos.", 1);

    // Conectar os n�s (�rvore de decis�es)
    inicio->escolha1 = adolescencia1;
    inicio->escolha2 = adolescencia2;

    adolescencia1->escolha1 = vidaAdulta1;
    adolescencia1->escolha2 = vidaAdulta2;
    
    adolescencia2->escolha1 = vidaAdulta2;
    adolescencia2->escolha2 = vidaAdulta1;

    vidaAdulta1->escolha1 = finalSucesso;
    vidaAdulta1->escolha2 = finalDificuldades;
    
    vidaAdulta2->escolha1 = finalDificuldades;
    vidaAdulta2->escolha2 = finalFracasso;

    // Iniciar o jogo
    printf("Bem-vindo ao jogo da vida! Suas escolhas determinarao o seu destino.\n");
    navegarNaArvore(inicio);

    return 0;
}

