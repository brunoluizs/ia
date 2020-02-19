#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define GA 10
#define GB 8
#define FO 14
#define CO 13

#define TAMANHO 7


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
    int gramaCortada = 1;
    int cortadorX = 0, cortadorY = 0;
    int lastPosX = 0, lastPosY = 0;

    mat[0][0] = CO;

    system("pause");
    system("cls");

    printMatriz(mat);

   do {
        mat[cortadorX][cortadorY] = GB;

        if (cortadorY > 0 && mat[cortadorX][cortadorY-1] == GA) { lastPosX = cortadorX; lastPosY = cortadorY; cortadorY--; }

        else if (cortadorX > 0 && mat[cortadorX-1][cortadorY] == GA) { lastPosX = cortadorX; lastPosY = cortadorY; cortadorX--; }

        else if (cortadorX < TAMANHO-1 && mat[cortadorX+1][cortadorY] == GA) { lastPosX = cortadorX; lastPosY = cortadorY; cortadorX++; }

        else if (cortadorY < TAMANHO-1 && mat[cortadorX][cortadorY+1] == GA) { lastPosX = cortadorX; lastPosY = cortadorY; cortadorY++; }

		else {
			cortadorX = lastPosX;
			cortadorY = lastPosY;
		}

        mat[cortadorX][cortadorY] = CO;

        Sleep(300);
        system("cls");
        printMatriz(mat);

        printf("cortadorPos: [%d][%d]\n", cortadorX, cortadorY);
        printf("lastPos: [%d][%d]\n", lastPosX, lastPosY);

        gramaCortada = isGramaCortada(mat);
    } while (gramaCortada);


    return 0;
};

int main(){
    int **mat;
    int i, j;

    mat = (int*) malloc (TAMANHO * sizeof(int*));

    for (i = 0; i < TAMANHO; i++)
        mat[i] = (int*) malloc (TAMANHO * sizeof(int));

    for (i = 0; i < TAMANHO; i++)
        for (j = 0; j < TAMANHO; j++)
            mat[i][j] = GA;

    mat[2][1] = FO;
    mat[3][2] = FO;
    mat[1][4] = FO;
    mat[2][5] = FO;
    mat[5][5] = FO;

    printMatriz(mat);

    cortadorDeGrama(mat);

}
