#include "menu.h"
#include <stdio.h>
#include "automato.h"

//Função para ler as configurações de um automato de um arquivo
//Pré-condição: Um ponteiro para automato alocado, um ponteiro para um arquivo contendo as configurações formatado corretamente
//Pós condição: As configurações do automato descrito no arquivo são copiadas para o automato
void ler_arquivo (Automato*aut, FILE *f){
    ler_alfabeto (aut,f);
    ler_estados (aut,f);
    ler_finais (aut,f);
    ler_transicoes (aut,f);
}


//função que executa a rotina padrão do programa
//Pré-condição: Nenhuma
//Pós-condição: Nenhuma
void menu_afd () {

    int opcao;
    char palavra[500];
    Automato* aut;
    FILE *f;

    aut = (Automato *) malloc(sizeof(Automato)); 
    while (1) {
    printf("\nInforme o que deseja fazer:\n");
    printf ("0- sair\n"); 
    printf ("1- ler o arquivo\n"); // lê o arquivo texto com a especificação do AFD
    printf ("2- testar palavra\n"); // processa a cadeia de acordo com o arquivo texto
    printf ("3- gerar gramatica\n");
    scanf ("%d%*c", &opcao);
    

    switch (opcao) {

        case 0:
        
        printf ("programa finalizado.\n");
        return;
        break;
        
        case 1:
        printf ("digite o nome do arquivo:");
        scanf ("%s", palavra); 
        f = fopen (palavra,"r");
        ler_arquivo (aut,f); //função que lê o arquivo.
        printf ("lido\n");
        break;

        case 2:
        printf ("digite a palavra:");
        scanf ("%s",palavra);
        printar_AFD (aut,palavra); //função que testa o AFD.
        break;

        case 3:
        geraGramatica(aut);
        break;
        
        default:
        printf ("opcao invalida.\n");
        printf("Enter para continura...\n");
        scanf("%*c");
        break;
        }
    }
    fclose(f);
}