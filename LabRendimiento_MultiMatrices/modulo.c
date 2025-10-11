/**************************************************************************************
 * Fecha:11 de septiembre de 2025
 * Autor: Juan Diego Ariza Lopez
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas, es decir, la dimensión de filas es igual a la de columnas.
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "modulo.h"

/* Definicion de las variables  de tipo global declaradas en modulo.h */
double *mA, *mB, *mC;
struct timeval ini,fin;

/* Funcion para tomar tiempo inicial*/
void InicioMuestra(){
	gettimeofday(&ini, NULL);
}
/* Funcion para tomar el tiempo final, se calcula la diferencia y el resultado se muestra en milisegundos*/
void FinMuestra(){
    gettimeofday(&fin, NULL);
    double tiempo = (double)(fin.tv_sec - ini.tv_sec) * 1000.0 +
                    (double)(fin.tv_usec - ini.tv_usec) / 1000.0;
    printf("\n\nTiempo de ejecución: %9.3f ms\n", tiempo);
}

/* Funcion para inicializar matrices */
void iniMatriz(int n, double *m1, double *m2){
    for(int i = 0; i < n * n; i++){
        m1[i] = i * 1.2 + 3;
        m2[i] = i * 1.5 + 2;
    }
}
/* Funcion para imprimir matrices, imprime en consola solo si n<9 */
void imprMatrices(int n, double *matriz){
    printf("\n#######################################################\n");
    if (n < 9) {
        for(int i = 0; i < n * n; i++){
            if(i % n == 0) printf("\n");
            printf(" %8.2f ", matriz[i]);	/* imprime el valor con 2 decimales */
        }
        printf("\n");
    } else {
        printf("\n\tMatriz de dimensión %dx%d (demasiado grande para imprimir).\n", n, n);
    }
    printf("#######################################################\n");
}

/* Funcion de multiplicacion de matrices de forma clasica */
void multiMatrizClasica(double *m1, double *m2, int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            double sumaTemp = 0.0;
            double *pA = m1 + i * n; // Puntero al inicio de la fila i de A
            double *pB = m2 + j;     // Puntero al inicio de la columna j de B
            for(int k = 0; k < n; k++, pA++, pB += n){
                sumaTemp += (*pA) * (*pB);
            }
            mC[j + i * n] = sumaTemp; // Almacenar resultado en C[i][j]
        }
    }
}
