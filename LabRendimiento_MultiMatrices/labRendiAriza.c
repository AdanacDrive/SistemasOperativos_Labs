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
#include <sys/time.h>
#include "modulo.h"

int main(int argc, char *argv[]) {
/* Se hace verificacion y se espera al menos un argumento (dimension de la matriz */
    if(argc< 2){
        printf("Error: Numero de argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe DIM \n");
        return -1;
    }
/* Convertir el valor ingresado de string a entero */
    int n = atoi(argv[1]);
    if(n<=0){
        printf("\nError: La dimension de la matriz debe ser un entero positivo\n");
        return -1;
    };
/* Se reserva la memoria dinamica para las matrices (A,B,C)*/
    mA = (double *) malloc(n*n*sizeof(double));
    mB = (double *) malloc(n*n*sizeof(double));
    mC = (double *) calloc(n*n,sizeof(double));

	/* Se inicializan las 2 matrices (A Y B) */
	iniMatriz(n, mA, mB);
	printf("\n===== MATRIZ A (n=%d) =====\n", n);
	/* Se imprimen las matrices de entrada (A y B) */
	imprMatrices(n, mA);
	printf("\n===== MATRIZ B (n=%d) =====\n", n);
	imprMatrices(n, mB);
	/* Se multiplican las matrices */
	printf("\n=== Calculando: C = A x B ===\n");
	InicioMuestra();
	multiMatrizClasica(mA, mB, n);
	/* Se muestra  la matriz resultado C */
	printf("\n===== RESULTADO C = A x B (n=%d) =====\n", n);
	imprMatrices(n, mC);
	/* Se mide el tiempo de ejecucion */
	FinMuestra();
        printf("\n\tFin del programa.............!\n");
	/* Se libera la memoria utilizada */
        free(mA);
        free(mB);
        free(mC);

        return 0;

}
