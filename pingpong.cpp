#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>  // Para _kbhit() e _getch()

#define WIDTH 40
#define HEIGHT 20
#define PADDLE_SIZE 4
#define DELAY 100  // Milissegundos de atraso entre os movimentos da bolinha
#define WIN_SCORE 5  // Pontua��o m�nima para ganhar, mas com 2 de diferen�a

typedef struct {
    int x, y;
    int velX, velY;
} Ball;

typedef struct {
    int y;
} Paddle;

void inicializaJogo(Ball *ball, Paddle *paddlePlayer, Paddle *paddleAI) {
    // Inicializa a bolinha no centro
    ball->x = WIDTH / 2;
    ball->y = HEIGHT / 2;
    ball->velX = -1; // A bolinha come�a indo para a esquerda
    ball->velY = (rand() % 2 == 0) ? 1 : -1; // Dire��o vertical aleat�ria

    // Inicializa as raquetes (player e AI) no centro
    paddlePlayer->y = HEIGHT / 2 - PADDLE_SIZE / 2;
    paddleAI->y = HEIGHT / 2 - PADDLE_SIZE / 2;
}

void desenhaJogo(Ball *ball, Paddle *paddlePlayer, Paddle *paddleAI, int pontosPlayer, int pontosAI) {
    system("cls");  // Limpa a tela

    // Desenha a borda superior
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("-");
    }
    printf("\n");

    // Desenha o campo de jogo, raquetes e bolinha
    for (int i = 0; i < HEIGHT; i++) {
        printf("|");  // Borda esquerda
        if (i >= paddlePlayer->y && i < paddlePlayer->y + PADDLE_SIZE) {
            printf("#");  // Raquete do jogador
        } else {
            printf(" ");  // Espa�o vazio
        }

        for (int j = 1; j < WIDTH; j++) {
            if (i == ball->y && j == ball->x) {
                printf("O");  // Desenha a bolinha
            } else if (i >= paddleAI->y && i < paddleAI->y + PADDLE_SIZE && j == WIDTH - 2) {
                printf("#");  // Raquete do computador (AI)
            } else {
                printf(" ");
            }
        }

        printf("|\n");  // Borda direita
    }

    // Desenha a borda inferior
    for (int i = 0; i < WIDTH + 2; i++) {
        printf("-");
    }

    // Placar de pontos
    printf("\nJogador: %d | Computador: %d\n", pontosPlayer, pontosAI);
}

void moveBola(Ball *ball, Paddle *paddlePlayer, Paddle *paddleAI, int *pontosPlayer, int *pontosAI) {
    // Verifica colis�o com as bordas superiores e inferiores
    if (ball->y <= 0 || ball->y >= HEIGHT - 1) {
        ball->velY *= -1;
    }

    // Verifica colis�o com a raquete do jogador
    if (ball->x == 1 && ball->y >= paddlePlayer->y && ball->y < paddlePlayer->y + PADDLE_SIZE) {
        ball->velX *= -1;  // Inverte a dire��o horizontal
    }

    // Verifica colis�o com a raquete do computador (AI)
    if (ball->x == WIDTH - 2 && ball->y >= paddleAI->y && ball->y < paddleAI->y + PADDLE_SIZE) {
        ball->velX *= -1;  // Inverte a dire��o horizontal
    }

    // Verifica se a bolinha passou pela raquete do jogador (ponto do computador)
    if (ball->x <= 0) {
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
        ball->velX = 1;  // Reseta a dire��o
        (*pontosAI)++;
    }

    // Verifica se a bolinha passou pela raquete do computador (ponto do jogador)
    if (ball->x >= WIDTH - 1) {
        ball->x = WIDTH / 2;
        ball->y = HEIGHT / 2;
        ball->velX = -1;  // Reseta a dire��o
        (*pontosPlayer)++;
    }

    // Movimento da bolinha
    ball->x += ball->velX;
    ball->y += ball->velY;
}

void moveRaquete(Paddle *paddlePlayer, Paddle *paddleAI, Ball *ball) {
    // Movimenta a raquete do jogador com base nas teclas W (para cima) e S (para baixo)
    if (_kbhit()) {
        char tecla = _getch();
        if (tecla == 'w' && paddlePlayer->y > 0) {
            paddlePlayer->y--;
        } else if (tecla == 's' && paddlePlayer->y < HEIGHT - PADDLE_SIZE) {
            paddlePlayer->y++;
        }
    }

    // Movimenta a raquete do computador (AI) para seguir a bolinha
    if (ball->y < paddleAI->y && paddleAI->y > 0) {
        paddleAI->y--;
    } else if (ball->y > paddleAI->y + PADDLE_SIZE - 1 && paddleAI->y < HEIGHT - PADDLE_SIZE) {
        paddleAI->y++;
    }
}

int verificaVitoria(int pontosPlayer, int pontosAI) {
    // Ganha o jogador que atingir ao menos 5 pontos e estiver com uma diferen�a de 2 pontos
    if (pontosPlayer >= WIN_SCORE && (pontosPlayer - pontosAI) >= 2) {
        return 1;  // Jogador venceu
    } else if (pontosAI >= WIN_SCORE && (pontosAI - pontosPlayer) >= 2) {
        return -1;  // Computador venceu
    }
    return 0;  // Ainda n�o h� vencedor
}

int main() {
    Ball ball;
    Paddle paddlePlayer, paddleAI;
    int pontosPlayer = 0, pontosAI = 0;
    int vencedor = 0;  // 0 = sem vencedor, 1 = jogador, -1 = computador

    srand(GetTickCount());  // Inicializa o gerador de n�meros aleat�rios com o tempo atual

    inicializaJogo(&ball, &paddlePlayer, &paddleAI);

    while (vencedor == 0) {
        desenhaJogo(&ball, &paddlePlayer, &paddleAI, pontosPlayer, pontosAI);
        moveBola(&ball, &paddlePlayer, &paddleAI, &pontosPlayer, &pontosAI);
        moveRaquete(&paddlePlayer, &paddleAI, &ball);

        vencedor = verificaVitoria(pontosPlayer, pontosAI);

        Sleep(DELAY);  // Controla a velocidade da bolinha

        // Se o jogador pressionar 'q', sai do jogo
        if (_kbhit() && _getch() == 'q') {
            break;
        }
    }

    // Resultado final
    system("cls");
    if (vencedor == 1) {
        printf("Parab�ns! Voc� venceu o jogo com %d a %d.\n", pontosPlayer, pontosAI);
    } else {
        printf("O computador venceu o jogo com %d a %d.\n", pontosAI, pontosPlayer);
    }

    return 0;
}

