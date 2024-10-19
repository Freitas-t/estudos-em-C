#include <stdio.h>
#include <stdlib.h>

// Definição de uma estrutura para representar os nós da árvore de decisão
typedef struct Node {
    char* descricao;  // Texto da situação ou escolha
    struct Node* escolha1;  // Próximo nó se escolher a opção 1
    struct Node* escolha2;  // Próximo nó se escolher a opção 2
    int final;  // 1 se o nó é um final da história, 0 caso contrário
} Node;

// Função para criar um novo nó
Node* criarNo(char* descricao, int final) {
    Node* novoNo = (Node*)malloc(sizeof(Node));
    novoNo->descricao = descricao;
    novoNo->escolha1 = NULL;
    novoNo->escolha2 = NULL;
    novoNo->final = final;
    return novoNo;
}

// Função para navegar pela árvore de decisão
void navegarNaArvore(Node* atual) {
    int escolha;
    
    // Se o nó for um final, exibe o resultado e encerra
    if (atual->final == 1) {
        printf("\n%s\n", atual->descricao);
        printf("Fim do jogo.\n\n");
        return;
    }

    // Exibe a situação atual
    printf("\n%s\n", atual->descricao);
    printf("1. Se dedicou meuito e abdicou de lazer em alguns momentos.\n2. Escolheu o prazer, afinal vida e para aproveitar.\nEscolha: ");
    scanf("%d", &escolha);

    // Verifica se a escolha é válida e navega para o próximo nó
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
    // Criar nós da árvore de decisões
    Node* inicio = criarNo("Voce esta na infancia. Como voce era na escola?", 0);
    Node* adolescencia1 = criarNo("Adolescencia: Voce se concentrou nos estudos. O que deseja fazer agora?", 0);
    Node* adolescencia2 = criarNo("Adolescencia: Voce curtiu sua vida social. O que deseja fazer agora?", 0);
    Node* vidaAdulta1 = criarNo("Vida Adulta: Voce seguiu uma carreira estavel. E agora?", 0);
    Node* vidaAdulta2 = criarNo("Vida Adulta: Voce seguiu uma carreira arriscada. E agora?", 0);
    Node* finalSucesso = criarNo("Voce teve uma vida plena, com sucesso pessoal e profissional!", 1);
    Node* finalDificuldades = criarNo("Voce enfrentou dificuldades, mas conseguiu encontrar paz e satisfacao no fim.", 1);
    Node* finalFracasso = criarNo("Suas escolhas levaram a uma vida cheia de arrependimentos.", 1);

    // Conectar os nós (árvore de decisões)
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

