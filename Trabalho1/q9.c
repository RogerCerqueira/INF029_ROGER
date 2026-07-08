#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAMANHO 10
#define NUM_NAVIOS 5

#define MAR     ' '
#define NAVIO   'N'
#define ABATIDO '0'
#define ERRO    'X'

char tabuleiro1[TAMANHO][TAMANHO];
char tabuleiro2[TAMANHO][TAMANHO];

int tamanhosNavios[NUM_NAVIOS] = {4, 3, 1, 1, 1};

void inicializarTabuleiro(char tab[TAMANHO][TAMANHO]){
    for(int i = 0; i < TAMANHO; i++)
        for(int j = 0; j < TAMANHO; j++)
            tab[i][j] = MAR;
}

void exibirTabuleiro(char tab[TAMANHO][TAMANHO], int mostrarNavios){
    printf("   ");
    for(int j = 0; j < TAMANHO; j++)
        printf("%2d", j + 1);
    printf("\n");

    for(int i = 0; i < TAMANHO; i++){
        printf("%2d ", i + 1);
        for(int j = 0; j < TAMANHO; j++){
            if(tab[i][j] == NAVIO && !mostrarNavios)
                printf(" %c", MAR);
            else
                printf(" %c", tab[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int posicionarNavio(char tab[TAMANHO][TAMANHO], int tamanho){
    int tentativas = 0;
    while(tentativas < 100){
        int linha   = rand() % TAMANHO;
        int coluna  = rand() % TAMANHO;
        int direcao = rand() % 2;

        if(direcao == 0 && coluna + tamanho > TAMANHO){ tentativas++; continue; }
        if(direcao == 1 && linha  + tamanho > TAMANHO){ tentativas++; continue; }

        int livre = 1;
        for(int k = 0; k < tamanho; k++){
            int nl = linha  + (direcao == 1 ? k : 0);
            int nc = coluna + (direcao == 0 ? k : 0);
            if(tab[nl][nc] != MAR){ livre = 0; break; }
        }

        if(!livre){ tentativas++; continue; }

        for(int k = 0; k < tamanho; k++){
            int nl = linha  + (direcao == 1 ? k : 0);
            int nc = coluna + (direcao == 0 ? k : 0);
            tab[nl][nc] = NAVIO;
        }
        return 1;
    }
    return 0;
}

void posicionarTodosNavios(char tab[TAMANHO][TAMANHO]){
    for(int i = 0; i < NUM_NAVIOS; i++)
        posicionarNavio(tab, tamanhosNavios[i]);
}

int atirar(char tab[TAMANHO][TAMANHO], int linha, int coluna){
    if(tab[linha][coluna] == NAVIO){
        tab[linha][coluna] = ABATIDO;
        return 1;
    } else if(tab[linha][coluna] == MAR){
        tab[linha][coluna] = ERRO;
        return 0;
    }
    return -1;
}

int todosAfundados(char tab[TAMANHO][TAMANHO]){
    for(int i = 0; i < TAMANHO; i++)
        for(int j = 0; j < TAMANHO; j++)
            if(tab[i][j] == NAVIO) return 0;
    return 1;
}

int lerPosicao(int *linha, int *coluna){
    printf("Informe linha e coluna (ex: 3 5): ");
    scanf("%d %d", linha, coluna);
    (*linha)--;
    (*coluna)--;
    if(*linha < 0 || *linha >= TAMANHO || *coluna < 0 || *coluna >= TAMANHO)
        return 0;
    return 1;
}

int main(){
    srand(time(NULL));

    inicializarTabuleiro(tabuleiro1);
    inicializarTabuleiro(tabuleiro2);

    posicionarTodosNavios(tabuleiro1);
    posicionarTodosNavios(tabuleiro2);

    int jogadorAtual = 1;
    int linha, coluna, resultado;

    printf("=== BATALHA NAVAL ===\n");
    printf("Navios posicionados automaticamente!\n\n");

    while(1){
        printf("--- Jogador %d ---\n", jogadorAtual);

        if(jogadorAtual == 1){
            printf("Seu tabuleiro:\n");
            exibirTabuleiro(tabuleiro1, 1);
            printf("Tabuleiro do oponente:\n");
            exibirTabuleiro(tabuleiro2, 0);
        } else {
            printf("Seu tabuleiro:\n");
            exibirTabuleiro(tabuleiro2, 1);
            printf("Tabuleiro do oponente:\n");
            exibirTabuleiro(tabuleiro1, 0);
        }

        if(!lerPosicao(&linha, &coluna)){
            printf("Posição inválida! Tente novamente.\n");
            continue;
        }

        if(jogadorAtual == 1)
            resultado = atirar(tabuleiro2, linha, coluna);
        else
            resultado = atirar(tabuleiro1, linha, coluna);

        if(resultado == -1){
            printf("Você já atirou aqui! Tente novamente.\n");
            continue;
        } else if(resultado == 1){
            printf("Acertou!\n");
        } else {
            printf("Errou!\n");
        }

        if(jogadorAtual == 1 && todosAfundados(tabuleiro2)){
            printf("\nJogador 1 venceu!\n"); break;
        }
        if(jogadorAtual == 2 && todosAfundados(tabuleiro1)){
            printf("\nJogador 2 venceu!\n"); break;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
    }

    return 0;
}