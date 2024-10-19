#include <stdio.h>
#include <stdlib.h>
#include <conio.h>  // Para _kbhit() e _getch()

#define WIDTH 20
#define HEIGHT 20

// Define o labirinto com mais 10 linhas de altura (1 é parede, 0 é caminho, 'P' é o jogador, 'E' é a saída)
char labirinto[HEIGHT][WIDTH] = {
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'},
    {'#', 'P', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', ' ', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', ' ', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', '#', ' ', ' ', ' ', '#', ' ', '#'},
    {'#', ' ', '#', '#', '#', '#', ' ', '#', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', ' ', '#', '#', '#', '#'},
    {'#', ' ', ' ', ' ', '#', ' ', ' ', '#', '#', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', '#', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', '#', ' ', ' ', '#', '#', '#', '#', ' ', '#'},
    {'#', ' ', ' ', '#', ' ', '#', ' ', ' ', ' ', '#'},
    {'#', ' ', ' ', ' ', ' ', ' ', '#', ' ', ' ', '#'},
    {'#', ' ', '#', ' ', ' ', ' ', ' ', ' ', ' ', '#'},
    {'#', 'E', ' ', ' ', '#', '#', ' ', ' ', ' ', '#'},
    {'#', '#', '#', '#', '#', '#', '#', '#', '#', '#'}
};

// Posição do jogador
int jogadorX = 1;
int jogadorY = 1;

// Função para desenhar o labirinto
void desenhaLabirinto() {
    system("cls");  // Limpa a tela
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", labirinto[i][j]);
        }
        printf("\n");
    }
}

// Função para mover o jogador
void moveJogador(char direcao) {
    int novoX = jogadorX;
    int novoY = jogadorY;

    // Atualiza a posição de acordo com a tecla pressionada
    if (direcao == 'w') {
        novoX--;  // Mover para cima
    } else if (direcao == 's') {
        novoX++;  // Mover para baixo
    } else if (direcao == 'a') {
        novoY--;  // Mover para esquerda
    } else if (direcao == 'd') {
        novoY++;  // Mover para direita
    }

    // Verifica se a nova posição é um caminho válido (espaço ou a saída)
    if (labirinto[novoX][novoY] == ' ' || labirinto[novoX][novoY] == 'E') {
        // Atualiza a posição do jogador no labirinto
        labirinto[jogadorX][jogadorY] = ' ';  // Remove o jogador da posição atual
        jogadorX = novoX;
        jogadorY = novoY;
        labirinto[jogadorX][jogadorY] = 'P';  // Coloca o jogador na nova posição
    }
}

int main() {
    char input;
    int jogoAtivo = 1;

    while (jogoAtivo) {
        desenhaLabirinto();

        // Verifica se o jogador chegou na saída
        if (labirinto[jogadorX][jogadorY] == 'E') {
            printf("Parabéns! Você encontrou a saída!\n");
            jogoAtivo = 0;
            break;
        }

        // Espera a entrada do jogador (teclas W, A, S, D)
        input = _getch();

        moveJogador(input);

        // Se o jogador pressionar 'q', o jogo termina
        if (input == 'q') {
            printf("Você saiu do jogo.\n");
            break;
        }
    }

    return 0;
}

