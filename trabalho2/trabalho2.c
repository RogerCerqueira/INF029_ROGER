// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome: Roger Cerqueira
//  email: 20242160036@ifba.edu.br
//  Matrícula: 20242160036
//  Semestre: 2026.1

#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"


static estruAux **getVetPrincipal(void){
    static estruAux *vetPrincipal[TAM];
    return vetPrincipal;
}

int criarEstruturaAuxiliar(int posicao, int tamanho){
    estruAux **vetPrincipal = getVetPrincipal();
    int retorno = 0;
    
    if(tamanho < 1){
        retorno = TAMANHO_INVALIDO;
        return retorno;
    }

    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }
    
    if(vetPrincipal[posicao-1] != NULL){
        return JA_TEM_ESTRUTURA_AUXILIAR;
        
    }

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

int inserirNumeroEmEstrutura(int posicao, int valor){
    if (posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }
    else{
        estruAux **vetPrincipal = getVetPrincipal();
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

int excluirNumeroDoFinaldaEstrutura(int posicao){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux **vetPrincipal = getVetPrincipal();
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

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux **vetPrincipal = getVetPrincipal();
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

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }
    
    estruAux **vetPrincipal = getVetPrincipal();
    estruAux *estrut = vetPrincipal[posicao - 1];
    
    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for(int i = 0; i < estrut->qtd; i++){
        vetorAux[i] = estrut->chave[i];
    }

    return SUCESSO;
}

int compare(const void *a, const void *b){
    return (*(int*)a - *(int*)b);
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux **vetPrincipal = getVetPrincipal();
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

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    estruAux **vetPrincipal = getVetPrincipal();
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

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]){
    estruAux **vetPrincipal = getVetPrincipal();
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

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux **vetPrincipal = getVetPrincipal();
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
    
    if(estrut->qtd > estrut->tamanho){
        estrut->qtd = estrut->tamanho;
    }

    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao){
    if(posicao < 1 || posicao > TAM){
        return POSICAO_INVALIDA;
    }

    estruAux **vetPrincipal = getVetPrincipal();
    estruAux *estrut = vetPrincipal[posicao - 1];

    if(estrut == NULL){
        return SEM_ESTRUTURA_AUXILIAR;
    }
    
    if(estrut->qtd == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    return estrut->qtd;
}

No *montarListaEncadeadaComCabecote(){
    No *cabecote = malloc(sizeof(No)); 
    if(cabecote == NULL){   
        return NULL;
    } 
    cabecote->prox = NULL;
    No *atual = cabecote;

    estruAux **vetPrincipal = getVetPrincipal();
    for(int i =0; i < TAM; i++){
        estruAux *estrut = vetPrincipal[i];
        if(estrut != NULL && estrut->qtd > 0){
            for(int j = 0; j < estrut->qtd; j++){
               No *novo = malloc(sizeof(No));
                if(novo == NULL){
                    No *atualLimpeza = cabecote;
                    while(atualLimpeza != NULL){
                        No *temp = atualLimpeza->prox;
                        free(atualLimpeza);
                        atualLimpeza = temp;
                    }
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

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]){
    int i = 0;
    No *atual = inicio->prox;
    while(atual != NULL){
        vetorAux[i] = atual->conteudo;
        i++;
        atual = atual->prox;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio){
    No *atual = *inicio;
    while(atual != NULL){
        No *temp = atual->prox;
        free(atual);
        atual = temp;
    }
    *inicio = NULL;
}

void inicializar(){
    estruAux **vetPrincipal = getVetPrincipal();
    for(int i = 0; i < TAM; i++){
        vetPrincipal[i] = NULL;
    }
}

void finalizar(){
    estruAux **vetPrincipal = getVetPrincipal();
    for(int i = 0; i < TAM; i++){
        if(vetPrincipal[i] != NULL){
            free(vetPrincipal[i]->chave);
            free(vetPrincipal[i]);
        }
    }
}

/*
Objetivo: dobrar o valor de um inteiro, passado por referência (ponteiro).
Retorno void.
*/
void dobrar(int *x){
    *x = *x * 2;
}
