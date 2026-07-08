#include <stdio.h>

char tabuleiro[3][3];

void inicializarTabuleiro(){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            tabuleiro[i][j] = ' ';
        }
    }
}

void exibirTabuleiro(){
    printf("\n  1   2   3\n");
    printf("A %c | %c | %c\n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("  ---------\n");
    printf("B %c | %c | %c\n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("  ---------\n");
    printf("C %c | %c | %c\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
    printf("\n");
}

int verificarVencedor(char marca){

    for(int i = 0; i < 3; i++){
        if(tabuleiro[i][0] == marca && tabuleiro[i][1] == marca && tabuleiro[i][2] == marca){
            return 1;
        }    
    }

    for(int j = 0; j < 3; j++){
        if(tabuleiro[0][j] == marca && tabuleiro[1][j] == marca && tabuleiro[2][j] == marca){
            return 1;
        }
    }

    if(tabuleiro[0][0] == marca && tabuleiro[1][1] == marca && tabuleiro[2][2] == marca){
        return 1;
    }
    if(tabuleiro[0][2] == marca && tabuleiro[1][1] == marca && tabuleiro[2][0] == marca){
        return 1;
    }
    return 0;
}

int tabuleiroCheio(){
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(tabuleiro[i][j] == ' ') return 0;
    return 1;
}

int lerJogada(int *linha, int *coluna){
    char jogada[5];
    printf("Informe sua jogada (ex: A1): ");
    scanf("%s", jogada);

    
    if(jogada[0] == 'A' || jogada[0] == 'a'){ 
        *linha = 0;
    }else if(jogada[0] == 'B' || jogada[0] == 'b'){
        *linha = 1;
    }else if(jogada[0] == 'C' || jogada[0] == 'c'){
        *linha = 2;
    }else{ 
        return 0; 
    }

    if     (jogada[1] == '1') *coluna = 0;
    else if(jogada[1] == '2') *coluna = 1;
    else if(jogada[1] == '3') *coluna = 2;
    else return 0; 

    return 1;
}

int main(){
    inicializarTabuleiro();

    int jogadorAtual = 1;
    char marca;
    int linha, coluna;
    int jogadas = 0;

    printf("=== JOGO DA VELHA ===\n");

    while(1){
        exibirTabuleiro();

        marca = (jogadorAtual == 1) ? 'X' : '0';
        printf("Jogador %d, informe sua jogada:\n", jogadorAtual);

        if(!lerJogada(&linha, &coluna)){
            printf("Célula inválida! Tente novamente.\n");
            continue;
        }

        if(tabuleiro[linha][coluna] != ' '){
            printf("Célula já ocupada! Tente novamente.\n");
            continue;
        }

        tabuleiro[linha][coluna] = marca;
        jogadas++;

        if(verificarVencedor(marca)){
            exibirTabuleiro();
            printf("Jogador %d venceu!\n", jogadorAtual);
            break;
        }
        
        if(tabuleiroCheio()){
            exibirTabuleiro();
            printf("Empate! Não houve vencedor.\n");
            break;
        }

        jogadorAtual = (jogadorAtual == 1) ? 2 : 1;
    }

    return 0;
}