#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <stdio.h> 
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    int estado_atual;
    int estado_final[100];
    char alfabeto[100];
    int transicoes[100][100];
    int n_transicoes;
    int n_alfabeto;
    int n_final;
    int n_estados;
}Automato;


//função que le o alfabeto do arquivo de texto
//Pré-Condição: Um arquivo aberto de configuração de automato apontando para a linha do alfabeto, um ponteiro para automato existente
//Pós-condição:o alfabeto do arquivo é lido e gravado no automato
void ler_alfabeto (Automato* aut,FILE* f);

//função que le os estados do arquivo de texto
//Pré-condição:Um arquivo aberto de configuração de automato apontando para a linha dos estados, um ponteiro para automato existente
//Pós-condição:os estados do arquivo é lido e gravado no automato
void ler_estados (Automato* aut,FILE* f);

//função que le os finais do arquivo de texto
//Pré-condiçãoUm arquivo aberto de configuração de automato apontando para a linha dos estados finais, um ponteiro para automato existente
//Pós-condição:os estados finais do arquivo é lido e gravado no automato
void ler_finais (Automato* aut,FILE* f);

//função que le as trasições do arquivo de texto
//Pré-condição:Um arquivo aberto de configuração de automato apontando para a linha das transições, um ponteiro para automato existente
//Pós-condição:as trasições do arquivo é lido e gravado no automato
void ler_transicoes (Automato*aut,FILE* f);

//função que verifica se a transição existe e atualiza a transição
//Pré-condição:o automato e a letra do alfabeto do automato
//Pós-condição: o estado atual atualizado com a nova transição
int verificar_transicao(Automato*aut, char letra);

//Gera a gramatica do automato presente 
//Pre-condição: Um automato presente 
//Pos-condição: Se o automato for inexistente retorna NULL, caso ao contrario é gerada uma gramatica do automato 
void geraGramatica(Automato *aut);


//função que verifica se o estado atual chegou no estado final 
//Pré-condição:o automato
//Pós-condição: retorna 1 se é o estado final ou 0 se não é
int estado_final(Automato* aut );

//função para printar o automato 
//Pré-condição:o automato e uma palavra 
//Pós-condição:retorna se aceita ou não a palavra e as palvras q ela gera 
void printar_AFD (Automato*aut, char cadeia[]);

//função para retornar o indice que a letra esta no vetor 
//Pré-condição:o alfabeto e uma letra
//Pós-condição: retorna a posição que a letra esta naquele vetor de alfabeto 
int indice_letra (char alfabeto [], char letra);

//função para verificar se a letra esta no alfabeto 
//Pré-condição:o alfabeto do automato e uma letra 
//Pós-condição: retorna 1 se pertence ao alfabeto 0 se não 
int verifica_alfabeto(char alfabeto[], char letra);

#endif