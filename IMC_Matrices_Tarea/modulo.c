#include "modulo.h"
// Función: printFunction
// Entrada: Ninguna
// Salida: Entero (0)
// Descripción: Imprime la cabecera de la calculadora de IMC.
int printFunction(){
    printf("*************************************\n");
    printf("*   Calculadora de Masa Corporal    *\n");
    printf("*************************************\n");
    return 0;
}
// Función: imcFuncion
// Entrada: masa (kg), altura (m)
// Salida: índice de masa corporal (IMC)
// Descripción: Calcula el IMC dividiendo la masa entre la altura al cuadrado.
float imcFuncion(float masa, float altura){
    return masa / (altura * altura);
}
// Función: impMatrix
// Entrada: matriz NxN, tamaño N
// Salida: Ninguna
// Descripción: Imprime una matriz de tamaño NxN.
void impMatrix(float matriz[10][10], int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf("%6.2f ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
// Función: llenarMatriz
// Entrada: tamaño N, matriz NxN
// Salida: Ninguna
// Descripción: Llena una matriz NxN con valores aleatorios entre 0 y 9.
void llenarMatriz(int N, float matriz[10][10]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            matriz[i][j] = rand() % 10;
        }
    }
}
// Función: matrixMult
// Entrada: tamaño N, dos matrices de entrada A y B, matriz de salida C
// Salida: Ninguna
// Descripción: Multiplica las matrices A y B, guarda el resultado en C.
void matrixMult(int N, float mA[10][10], float mB[10][10], float mC[10][10]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            mC[i][j] = 0;
            for(int k = 0; k < N; k++){
                mC[i][j] += mA[i][k] * mB[k][j];
            }
        }
    }
}
