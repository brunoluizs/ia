#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define GA 10
#define GB 8
#define FO 14
#define CO 13

#define TAMANHO 5

/* PILHA DE POSICOES PERCORRIDAS */

typedef struct posicao{
    int x;
    int y;
}Pos;

typedef struct nodePilha{
    Pos pos;
    struct nodePilha *anterior;
}nodePilha;

nodePilha *alocarNode(){
    nodePilha *node;

    node = (nodePilha*) malloc(sizeof(nodePilha));

    node->pos.x = 0;
    node->pos.y = 0;

    node->anterior = NULL;
}

void iniciarPilha(nodePilha **topo){
    (*topo) = alocarNode();
}

void push(nodePilha **topo, int x, int y){
    nodePilha *node = alocarNode();

    node->pos.x = x;
    node->pos.y = y;

    node->anterior = (*topo);
    (*topo) = node;
}

Pos pop(nodePilha **topo){
    nodePilha *node = *topo;

    (*topo) = (*topo)->anterior;

    return node->pos;
}

/* MANIPULACAO E EXIBICAO DA MATRIZ */

void printMatriz(int **mat){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;

    int i, j;

    for (i = 0; i < 7; i++){

        for (j = 0; j < 7; j++){
            SetConsoleTextAttribute(hConsole, 7);
            printf("[");

            if (mat[i][j] == GA){
                SetConsoleTextAttribute(hConsole, mat[i][j]);
                printf("GA");
            }

            else if (mat[i][j] == GB){
                SetConsoleTextAttribute(hConsole, mat[i][j]);
                printf("GB");
            }

            else if (mat[i][j] == FO){
                SetConsoleTextAttribute(hConsole, mat[i][j]);
                printf("FO");
            }

            else if (mat[i][j] == CO){
                SetConsoleTextAttribute(hConsole, mat[i][j]);
                printf("CO");
            }

            SetConsoleTextAttribute(hConsole, 7);
            printf("]");
        }
        printf("\n");
    }

    SetConsoleTextAttribute(hConsole, 7);


}

void inserirFormigueiros(int **mat, int n){
    int i, x, y;

    for (i = 0; i < n; i++){
        x = (rand() + n) % TAMANHO;
        y = rand() % TAMANHO;

        if(mat[x][y] == GA || mat[x][y] == FO || mat[x][y] == CO)
            mat[x][y] = FO;
        else
            i--;
    }
}

Pos inserirCortador(int **mat){
    Pos p;

    p.x = (rand() + rand()) % TAMANHO;
    p.y = rand() % TAMANHO;

    return p;
}

int isGramaCortada(int **mat){
    int i, j;

    for (i = 0; i < TAMANHO; i++)
        for (j = 0; j < TAMANHO; j++)
            if (mat[i][j] == GA)
                return 1;

    return 0;
}

int cortadorDeGrama(int **mat){
    int i, j;
    int cortadorX = 0, cortadorY = 0;
    int lastPosX = 0, lastPosY = 0;
    int passos = 0;

    nodePilha *topo;
    iniciarPilha(&topo);

    Pos p = inserirCortador(mat);
    cortadorX = p.x;
    cortadorY = p.y;

    mat[cortadorX][cortadorY] = CO;

    inserirFormigueiros(mat, 5);

    printMatriz(mat);

    system("pause");
    system("cls");

   do {
        passos++;

        mat[cortadorX][cortadorY] = GB;

        if (cortadorY > 0 && mat[cortadorX][cortadorY-1] == GA) { push(topo, cortadorX, cortadorY); cortadorY--; }

        else if (cortadorX > 0 && mat[cortadorX-1][cortadorY] == GA) { push(topo, cortadorX, cortadorY); cortadorX--; }

        else if (cortadorX < TAMANHO-1 && mat[cortadorX+1][cortadorY] == GA) { push(topo, cortadorX, cortadorY); cortadorX++; }

        else if (cortadorY < TAMANHO-1 && mat[cortadorX][cortadorY+1] == GA) { push(topo, cortadorX, cortadorY); cortadorY++; }

		else {
            Pos lastPos = pop(topo);
			cortadorX = lastPos.x;
			cortadorY = lastPos.y;
		}

        mat[cortadorX][cortadorY] = CO;

        Sleep(300);
        system("cls");
        printMatriz(mat);

        printf("\nSTEPS: [%d]", passos);

    } while (isGramaCortada(mat));


    return 0;
};

int main(){
    int **mat;
    int i, j;

    srand(time(NULL));

    mat = (int*) malloc (TAMANHO * sizeof(int*));

    for (i = 0; i < TAMANHO; i++)
        mat[i] = (int*) malloc (TAMANHO * sizeof(int));

    for (i = 0; i < TAMANHO; i++)
        for (j = 0; j < TAMANHO; j++)
            mat[i][j] = GA;

    cortadorDeGrama(mat);

}
