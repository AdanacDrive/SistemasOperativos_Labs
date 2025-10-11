#ifndef __MODULO_H__
#define __MODULO_H__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Imprime la cabecera del programa
int printFunction();
// Calcula el índice de masa corporal (IMC)
float imcFuncion(float masa, float altura);
// Imprime una matriz de NxN
void impMatrix(float matriz[10][10], int N);
// Llena una matriz NxN con valores aleatorios
void llenarMatriz(int N, float matriz[10][10]);
// Multiplica dos matrices y guarda el resultado en una tercera
void matrixMult(int N, float mA[10][10], float mB[10][10], float mC[10][10]);

#endif
