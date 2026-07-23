#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

estruAux *vetPrincipal[TAM];

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho){

    int retorno = 0;
    
    // o tamanho nao pode ser menor que 1
    if(tamanho < 1){
        retorno = TAMANHO_INVALIDO;
        return retorno;
    }

    // se posição é um valor válido {entre 1 e 10}
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }
    
    // a posicao pode já existir estrutura auxiliar
    if(vetPrincipal[posicao-1] != NULL){
        return JA_TEM_ESTRUTURA_AUXILIAR;
        
    }

    // o tamanho ser muito grande
    vetPrincipal[posicao-1] = (estruAux*)malloc(sizeof(estruAux));

    if(vetPrincipal[posicao-1] == NULL){
        return SEM_ESPACO_DE_MEMORIA; 
    }

    vetPrincipal[posicao-1]->tamanho = tamanho;
    vetPrincipal[posicao-1]->qtd = 0;
    vetPrincipal[posicao-1]->chave = (int*)malloc(tamanho * sizeof(int));

    if(vetPrincipal[posicao-1]->chave == NULL){
        free(vetPrincipal[posicao-1]);
        vetPrincipal[posicao-1] = NULL;
        return SEM_ESPACO_DE_MEMORIA;
    }

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor){
    if (posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }
    else{
        // testar se existe a estrutura auxiliar
        estruAux *estrut = vetPrincipal[posicao -1];
    
        if (estrut != NULL){
            if (estrut->qtd < estrut->tamanho){
                estrut->chave[estrut->qtd] = valor;
                estrut->qtd++;

                return SUCESSO;
            }
            else{
                return SEM_ESPACO;
            }
        }
        else{
            return SEM_ESTRUTURA_AUXILIAR;
        }
    }
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux *estrut = vetPrincipal[posicao - 1];

    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if(estrut->qtd == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    estrut->qtd--;
    return SUCESSO;
    
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux *estrut = vetPrincipal[posicao - 1];
    
    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    if(estrut->qtd == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }else{
    
        int i, j;
        for(i = 0; i < estrut->qtd; i++){
            if(estrut->chave[i] == valor){
                for(j = i; j < estrut->qtd - 1; j++){
                    estrut->chave[j] = estrut->chave[j + 1];
                }
                estrut->qtd--;
                return SUCESSO;
            }
        }
        return NUMERO_INEXISTENTE;    
    }
}

/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }
    
    estruAux *estrut = vetPrincipal[posicao - 1];
    
    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for(int i = 0; i < estrut->qtd; i++){
        vetorAux[i] = estrut->chave[i];
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux *estrut = vetPrincipal[posicao -1];

    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for(int i = 0; i < estrut->qtd; i++){
        vetorAux[i] = estrut->chave[i];
    }
    
    qsort(vetorAux, estrut->qtd, sizeof(int), compare);

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int k = 0;
    for(int i = 0; i < TAM; i++){
        estruAux *estrut = vetPrincipal[i];
        if(estrut != NULL && estrut->qtd > 0){
            for(int j = 0; j < estrut->qtd; j++){
                vetorAux[k] = estrut->chave[j];
                k++;
            }
        }
    }
    if(k == 0){
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }else{
        return SUCESSO;
    }
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    int k = 0;
    for(int i = 0; i < TAM; i++){
        estruAux *estrut = vetPrincipal[i];
        if(estrut != NULL && estrut->qtd > 0){
            for(int j = 0; j < estrut->qtd; j++){
                vetorAux[k] = estrut->chave[j];
                k++;
            }
        }
    }
    if(k == 0){
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }else{
        qsort(vetorAux, k, sizeof(int), compare);
        return SUCESSO;
    }
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux *estrut = vetPrincipal[posicao - 1];

    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    if(estrut->tamanho + novoTamanho < 1){
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novoVet = realloc(estrut->chave, (estrut->tamanho + novoTamanho) * sizeof(int));
    
    if(novoVet == NULL){
        return SEM_ESPACO_DE_MEMORIA;
    }
    
    estrut->chave = novoVet;
    estrut->tamanho = estrut->tamanho + novoTamanho;

    return SUCESSO;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux *estrut = vetPrincipal[posicao - 1];

    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    if(estrut->qtd == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    return estrut->qtd;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote(){
    No *cabecote = malloc(sizeof(No)); 
    if(cabecote == NULL){   
        return NULL;
    } 
    cabecote->prox = NULL;
    No *atual = cabecote;

    for(int i =0; i < TAM; i++){
        estruAux *estrut = vetPrincipal[i];
        if(estrut != NULL && estrut->qtd > 0){
            for(int j = 0; j < estrut->qtd; j++){
                No *novo = malloc(sizeof(No));
                if(novo == NULL){
                    return NULL; 
                } 
                novo->conteudo = estrut->chave[j]; 
                novo->prox = NULL;
                atual->prox = novo;
                atual = novo;
            }
        }    
    }
    if(cabecote->prox == NULL){
        free(cabecote);
        return NULL;
    }
    return cabecote;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    int i = 0;
    No *atual = inicio->prox;
    while(atual != NULL){
        vetorAux[i] = atual->conteudo;
        i++;
        atual = atual->prox;
    }
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio){
    No *atual = *inicio;
    while(atual != NULL){
        No *temp = atual->prox;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar(){
    for(int i = 0; i < TAM; i++){
        vetPrincipal[i] = NULL;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar(){
    for(int i = 0; i < TAM; i++){
        if(vetPrincipal[i] != NULL){
            free(vetPrincipal[i]->chave);
            free(vetPrincipal[i]);
        }
    }
}

int main(){


}
