#ifndef MENU_H
#define MENU_H
#include <stdlib.h>
#include "automato.h"

//função que executa a rotina padrão do programa
//Pré-condição: Nenhuma
//Pós-condição: Nenhuma
void menu_afd();

//Função para ler as configurações de um automato de um arquivo
//Pré-condição: Um ponteiro para automato alocado, um ponteiro para um arquivo contendo as configurações formatado corretamente
//Pós condição: As configurações do automato descrito no arquivo são copiadas para o automato
void ler_arquivo(Automato* aut, FILE *f);

#endif