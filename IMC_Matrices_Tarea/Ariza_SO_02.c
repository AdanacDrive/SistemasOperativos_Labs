/**************************************************************
*             Pontificia Universidad Javeriana               *
*   ------------------------------------------------------   *
*                                                            *
* Autor: Juan Diego Ariza                                    *
* Fecha: 31 de julio 2025                                    *
* Docente: J. Corredor                                       *
* Objetivo: Punteros en C - Programa Principal               *
**************************************************************/

#include "modulo.h"

int main(int argc, char* argv[]){
    if(argc < 4){
        printf("Uso: ./programa altura masa N\n");
        return 1;
    }

    float altura = atof(argv[1]);
    float masa = atof(argv[2]);
    int N = atoi(argv[3]);

    float mA[10][10], mB[10][10], mC[10][10];

    srand(time(NULL));

    printFunction();

    float imc = imcFuncion(masa, altura);
    printf("El índice de masa corporal es %.2f\n", imc);
    printf("***********************************\n\n");

    printf("***********************************\n");
    printf("*            Matrices             *\n");
    printf("***********************************\n");

    llenarMatriz(N, mA);
    llenarMatriz(N, mB);

    printf("Matriz A:\n");
    impMatrix(mA, N);

    printf("Matriz B:\n");
    impMatrix(mB, N);

    matrixMult(N, mA, mB, mC);

    printf("Resultado A x B:\n");
    impMatrix(mC, N);

    return 0;
}
