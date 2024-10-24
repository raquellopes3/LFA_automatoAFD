#include "automato.h"

//função que le o alfabeto do arquivo de texto
//Pré-Condição: Um arquivo aberto de configuração de automato apontando para a linha do alfabeto, um ponteiro para automato existente
//Pós-condição:o alfabeto do arquivo é lido e gravado no automato
void ler_alfabeto (Automato* aut, FILE* f) {
    char letra;
    int i;
    aut->n_alfabeto = 0;
    fscanf (f,"alfabeto={"); 
    for (i = 0; fscanf (f, "%c", &letra) != EOF && letra != '}'; i++){ //percorre cada caractere até "}".
        if (isalnum(letra) != 0){
            aut->alfabeto[aut->n_alfabeto] = letra; //armazena em um vetor contendo o alfabeto.
            aut->n_alfabeto = aut->n_alfabeto + 1;
        }
    }
    aut->alfabeto[aut->n_alfabeto+1] = '\0';
}

//função que le os estados do arquivo de texto
//Pré-condição:Um arquivo aberto de configuração de automato apontando para a linha dos estados, um ponteiro para automato existente
//Pós-condição:os estados do arquivo é lido e gravado no automato
void ler_estados (Automato* aut, FILE* f) {

    char linha[100];
    int aux= 0, i, j;
    fscanf (f, "%[^}]}\n", linha);
    for(i = 0; linha[i]; i++){
        if(linha[i] == 'q'){
            for(j = i; linha[j] != ',' && linha[j] ; j++);
            aux++;
            i = j;
        }
    }
    aut->n_estados = aux; //guarda o número de estados na variável da struct 
 }


//função que le os finais do arquivo de texto
//Pré-condiçãoUm arquivo aberto de configuração de automato apontando para a linha dos estados finais, um ponteiro para automato existente
//Pós-condição:os estados finais do arquivo é lido e gravado no automato
void ler_finais (Automato* aut,FILE* f) {

    char linha[100], num[100];
    int aux= 0, i, j;
    
    // Esta forma de ler do arquivo funciona com estados com números de mais de dois dígitos, atualizar na função ler estados
    fscanf (f, "%[^}]}\n", linha);
    linha[strlen(linha)+1]= 0;

    for(i = 0; linha[i]; i++){
       // printf("%d",i);
        if(linha[i] == 'q'){
            i++;
            for(j = i; (linha[j] != ',') && linha[j] ; j++){
                //printf("%c\n",linha[j]);
                num[j - i] = linha[j];
            }
            num[j - i] = '\0';
            //printf("%d %s\n",i,num);
            aut->estado_final[aux] = atoi(num);
            aux++;
          // printf("(%s)\n",linha);
            i = j;
        }
    }
    aut->n_final= aux;
   // printf("%d",aux);
}


//função para retornar o indice que a letra esta no vetor do alfabeto 
//Pré-condição:o alfabeto e uma letra
//Pós-condição: retorna a posição que a letra esta naquele vetor de alfabeto 
int indice_letra (char alfabeto [], char letra) {
    for (int i = 0; alfabeto[i] != '\0'; i++) {
        if (alfabeto[i] == letra) 
        return i;
        //transforma a letra do alfabeto no número do índice do vetor, por exemplo
        //se {a,b,c}, a=0, b=1, c=2.
    }
    return -1;
}


//função que le as trasições do arquivo de texto
//Pré-condição:Um arquivo aberto de configuração de automato apontando para a linha das transições, um ponteiro para automato existente
//Pós-condição:as trasições do arquivo é lido e gravado no automato
void ler_transicoes (Automato* aut, FILE* f) {                                                              

    int estado, dst, posicao,aux=0;
    char linha[100], letra;
    for(int i=0; i<100; i++){// percorre a linha (quantidade de estados).
        for(int j=0; j < 100; j++){// percorre a coluna (quantidade de letras no alfabeto).
            aut->transicoes[i][j]= -1;

        }
    }
    for (int i = 0; fscanf (f,"%[^\n]%*c", linha) != EOF; i++){
        sscanf(linha, "(q%d,%c)= q%d", &estado, &letra, &dst);
        posicao = indice_letra(aut->alfabeto, letra);
        if (posicao != -1)
            aut->transicoes[estado][posicao] = dst; 
        //a posição do próximo estado será na linha do estado que estiver e na transição do mesmo.
       // a subtração trata casos de excesso da tabela ascii. 
        aux++;
    }
    aut->n_transicoes = aux;
    //printf("%d",aux);

}


//função que verifica se a transição existe e atualiza a transição
//Pré-condição:o automato e a letra do alfabeto do automato
//Pós-condição: o estado atual atualizado com a nova transição
int verificar_transicao (Automato*aut, char letra){
    int posLetra;
    posLetra = indice_letra(aut->alfabeto, letra); //verifica se a letra ta no alfabeto 
    aut->estado_atual = aut->transicoes[aut->estado_atual][posLetra];//atualiza o estado atual, com o indice da matriz 
    //o novo estado atual recebe o próximo estado que a transição indica.
    if(aut->estado_atual == -1){  //verifica se o estado atual não é -1.
        return -1; 
    }
    return  1;
}


//função que verifica se o estado atual chegou no estado final 
//Pré-condição:o automato
//Pós-condição: retorna 1 se é o estado final ou 0 se não é
int  estado_final (Automato* aut){
    int i;
    //printf("nfinal %d\n", aut->n_final);
    for (i=0; i < aut->n_final; i++){
       // printf("atual %d final %d\n", aut->estado_atual, aut->estado_final[i]);
        if( aut->estado_atual == aut->estado_final[i]){ //se o estado atual for um estado final,
            return 1; //ele retorna 1, significando seu término.

        }
    } 
     return 0;  
     
}


//função para verificar se a letra esta no alfabeto 
//Pré-condição:o alfabeto do automato e uma letra 
//Pós-condição: retorna 1 se pertence ao alfabeto 0 se não 
int verifica_alfabeto(char alfabeto[], char letra){
    int i;
    for (i = 0; alfabeto[i] != '\0'; i++){
        if(alfabeto[i] == letra)  //verifica se a letra pertence ao alfabeto.
            return 1;
    }
    return 0;
}

int pertence(int *v, int n, int x){
  int i;
  for(i = 0; i < n; i++)
    if(v[i] == x) return 1;
  return 0;
}

//Gera a gramatica do automato presente 
//Pre-condição: Um automato presente 
//Pos-condição: Se o automato for inexistente retorna NULL, caso ao contrario é gerada uma gramatica do automato 
void geraGramatica(Automato *aut){
    int nLadoDir[100];
    char terminais[100], ladoDir[100][100] = {""};
    int i, j, k;
    if(aut == NULL){
        printf("Carregue um Automato");
        return;
    }
    for(i = 0; i<aut->n_estados; i++){
        nLadoDir[i] = 0; 
    }
    for(i = 0; i<aut->n_estados; i++){
        for(j = 0; j < 100;j++){
            if (aut->transicoes[i][j] != -1) {
                nLadoDir[i]++;
            }
        }
    }
    terminais[0] = 'A'; 
    for(i = 1; i < aut->n_estados; i++){
        terminais[i] = 'A'+i;
    }
    char aux[50];
    for(j = 0, i = 0; j < aut->n_estados; j++){  
        aux[0] = 0;
        for(i = 0; i < 100; i++){
            char rule [50];
            if(aut->transicoes[j][i] != -1){
                //printf(".%d. ,%d, =%c= +%c+ /%d/\n", i, j, aut->alfabeto[i], aut->transicoes[j][i]);
                
                sprintf(rule, "%c%c" , aut->alfabeto[i], terminais[aut->transicoes[j][i]]);
               // printf("(%s)\n", aux);
                strcat(aux, rule);

                if(nLadoDir[j]-- > 1){
                    strcat(aux, " | ");
                }

            }
        }
        strcat(ladoDir[j], aux);
        if(pertence(aut->estado_final, aut->n_final, j)){
            strcat(ladoDir[j], "| @\n");
        }
        else{
            strcat(ladoDir[j], "\n");
        }
    }
    printf("\n");
    for(i=0; i < aut->n_estados;i++){
        printf("%c -> %s",terminais[i], ladoDir[i]);
    }
    printf("\n");
}


//função para printar o automato 
//Pré-condição:o automato e uma palavra 
//Pós-condição:retorna se aceita ou não a palavra e as palvras q ela gera 
void printar_AFD (Automato*aut, char cadeia[]) {

    int tamanho, i = 0, flag = 1;
    tamanho = strlen (cadeia);
    aut->estado_atual = 0;
    cadeia[strlen(cadeia) + 1] = 0;

    if (cadeia[0] == '@' && tamanho == 1) {
        printf ("[q%d] %s\n",aut->estado_atual, &cadeia[i]);
        if (estado_final (aut)){
            printf ("[q%d]\n",aut->estado_atual);
            printf ("ACEITA\n");
            return;
            //condição para palavra vazia.
        }

        else{
            printf ("[q%d]\n",aut->estado_atual);
            printf ("REJEITA\n");
            return;
        }
    } 
    // Faz a passagem pela cadeia e verifica a transição.
    for (i=0; cadeia[i] ;i++) {
        printf ("[q%d] %s\n",aut->estado_atual, &cadeia[i]);
        if(!verifica_alfabeto (aut->alfabeto, cadeia[i])){
            break;
        }
        if (verificar_transicao(aut,cadeia[i]) != -1){
            //printa a partir do índice da cadeia.
        }
        else{
            flag = 0;
            break;
        }
    }
    //printf("%d %d %d \n",estado_final(aut),cadeia[i] == '\0',flag);

        if ((estado_final(aut) && cadeia[i] == '\0' ) && flag){ 
            printf ("[q%d] %s\n",aut->estado_atual, &cadeia[i]);
            printf ("ACEITA\n");
            //condição para o término do AFD.
            }

        else {
            printf ("[q%d]\n",aut->estado_atual);
            printf ("REJEITA\n");
        }
}  