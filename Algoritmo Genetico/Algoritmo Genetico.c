#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* LISTA ENCADEADA DE VETOR BINARIO */

typedef struct nodeLista{
    struct nodeLista *prox;
    struct nodeLista *ante;
    char vetorBinario[8];
}nodeLista;

nodeLista *alocarNodeLista(){
    nodeLista *node;
    int i;

    node = (nodeLista*) malloc(sizeof(nodeLista));

    for (i = 0; i < 8; i++)
        node->vetorBinario[i] = '0';
    node->vetorBinario[8] = '\0';

    node->prox = NULL;
    node->ante = NULL;

    return node;
}

void iniciarLista(nodeLista **inicio){
    (*inicio) = alocarNodeLista();

    (*inicio)->prox = NULL;
    (*inicio)->ante = NULL;
}

void inserir(nodeLista **inicio, char *vetor){
    nodeLista *node;

    node = alocarNodeLista();

    strcpy(node->vetorBinario, vetor);

    node->prox = (*inicio)->prox;
    node->ante = (*inicio);

    if ((*inicio)->prox != NULL){
        (*inicio)->prox->ante = node;
    }

    (*inicio)->prox = node;
}

void listar(nodeLista **inicio){
    nodeLista *cursor;

    cursor = (*inicio)->prox;

    do{
        printf("[%s]\n", cursor->vetorBinario);
        cursor = cursor->prox;
    } while(cursor != NULL);
}

/* GERADOR DE VALORES */

void geraVetor(char *vetor){
    int i;

    for (i = 0; i < 8; i++){
        if (rand() % 2 == 0)
            vetor[i] = '0';
        else
            vetor[i] = '1';
    }

    vetor[8] = '\0';
}

void preencherLista(){
    int i = 0;
    char vetorGerado[8];

    for (i = 0; i < 10; i++){
        geraVetor(vetorGerado);
        printf("[%s]\n", vetorGerado);
        //inserir(inicio, vetorGerado);
    }
}

int main(){
    srand(time(NULL));
    /*nodeLista *inicio;
    iniciarLista(&inicio);*/

    preencherLista();

    //listar(&inicio);
}
