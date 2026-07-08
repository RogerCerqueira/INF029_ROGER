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
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{
    DataQuebrada dq = quebraData(data);

    if(!dq.valido) return 0;
    if(dq.iMes < 1 || dq.iMes > 12) return 0;
    if(dq.iDia < 1) return 0;

    int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};

    
    if((dq.iAno % 4 == 0 && dq.iAno % 100 != 0) || dq.iAno % 400 == 0)
        diasMes[1] = 29;

    if(dq.iDia > diasMes[dq.iMes - 1]) return 0;

    return 1;
}



/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[]){
    DiasMesesAnos dma;

    if(q1(datainicial) == 0){ dma.retorno = 2; return dma; }
    if(q1(datafinal)   == 0){ dma.retorno = 3; return dma; }

    DataQuebrada di = quebraData(datainicial);
    DataQuebrada df = quebraData(datafinal);

    // verifica se data inicial > data final
    if(di.iAno > df.iAno ||
      (di.iAno == df.iAno && di.iMes > df.iMes) ||
      (di.iAno == df.iAno && di.iMes == df.iMes && di.iDia > df.iDia)){
        dma.retorno = 4; return dma;
    }

    int anos  = df.iAno - di.iAno;
    int meses = df.iMes - di.iMes;
    int dias  = df.iDia - di.iDia;

    if(dias < 0){
        meses--;
        int mesAnterior = df.iMes - 1 == 0 ? 12 : df.iMes - 1;
        int anoAnterior = df.iMes - 1 == 0 ? df.iAno - 1 : df.iAno;
        int diasMes[] = {31,28,31,30,31,30,31,31,30,31,30,31};
        if((anoAnterior % 4 == 0 && anoAnterior % 100 != 0) || anoAnterior % 400 == 0)
            diasMes[1] = 29;
        dias += diasMes[mesAnterior - 1];
    }

    if(meses < 0){
        anos--;
        meses += 12;
    }

    dma.qtdAnos  = anos;
    dma.qtdMeses = meses;
    dma.qtdDias  = dias;
    dma.retorno  = 1;
    return dma;
}


/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *txt, char c, int caseSensitive){
    
    int contador = 0;
    
    for(int i = 0; txt[i]; i++){
        if(caseSensitive == !1){
            if(txt[i] == c){
                contador++;
            }
        } else {
            if(txt[i] == c || txt[i] == c - 32 || txt[i] == c + 32){
                contador++;
            }
        }
    }
    return contador;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int q4(char *txt, char *palavra, int posicoes[30]){

    int tamPalavra = strlen(palavra);
    int qtdeLetras = 0;
    int posFinal = 0;
    int qtdOcorrencias = 0;
    
    for(int i = 0; i < strlen(txt); i++){
        if(txt[i] == palavra[0]){
            qtdeLetras = 1;
            for(int j = 1; j < tamPalavra; j++){
                if(txt[i + j] == palavra[j]){
                    qtdeLetras++;
                    posFinal = i + j;
                } else {
                    break;
                }
            }
        }
        if(qtdeLetras == tamPalavra){
            posicoes[qtdOcorrencias * 2] = i + 1;
            posicoes[qtdOcorrencias * 2 + 1] = posFinal + 1;
            qtdOcorrencias++;
            qtdeLetras = 0;
        }
    }
    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int n){

    char num[10];
    sprintf(num, "%d", n);
    int tam = strlen(num);
    int zeroEsq = 0;
    for (int i = tam -1; i>=0; i--){
        if(num[i]!=0 || zeroEsq){
            printf("%c", num[i]);
            zeroEsq = 1;
        }
    }
    if(!zeroEsq){
        printf("0");
    }
    return n;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int num, int numBusca){

    char txtNum[10];
    sprintf(txtNum, "%d", num);
    char txtBusca[10];
    sprintf(txtBusca, "%d", numBusca);

    int tamBusca = strlen(txtBusca);
    int qtdeDigitos  = 0;
    int qtdOcorrencias = 0;

    for (int i = 0; i < strlen(txtNum); i++){
        if(txtNum[i] == txtBusca[0]){
            qtdeDigitos = 1;
            for(int j = 1; j < tamBusca; j++){
                if(txtNum[i + j] == txtBusca[j]){
                    qtdeDigitos++;
                }else {
                    break;
                }
            }
        }
        if(qtdeDigitos == tamBusca){
            qtdOcorrencias++;
            qtdeDigitos = 0;
        }
    }
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5]){

    int linhas = 8, colunas = 10;
    int tamPalavra = strlen(palavra);

    
    int direcoes[8][2] = {
        {0, 1},   // horizontal direita
        {0, -1},  // horizontal esquerda
        {1, 0},   // vertical baixo
        {-1, 0},  // vertical cima
        {1, 1},   // diagonal baixo-direita
        {1, -1},  // diagonal baixo-esquerda
        {-1, 1},  // diagonal cima-direita
        {-1, -1}  // diagonal cima-esquerda
    };

    for(int l = 0; l < linhas; l++){
        for(int c = 0; c < colunas; c++){
            for(int d = 0; d < 8; d++){
                int dl = direcoes[d][0];
                int dc = direcoes[d][1];
                int k;
                for(k = 0; k < tamPalavra; k++){
                    int nl = l + k * dl;
                    int nc = c + k * dc;
                    if(nl < 0 || nl >= linhas || nc < 0 || nc >= colunas) break;
                    if(matriz[nl][nc] != palavra[k]) break;
                }
                if(k == tamPalavra) return 1;
            }
        }
    }
    return 0;
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}