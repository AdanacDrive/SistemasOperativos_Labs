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

#ifndef _MODULO_H_
#define _MODULO_H_
#include <sys/time.h>

/* Declaración de variables globales */
extern double *mA, *mB, *mC;
extern struct timeval ini,fin;

/* Funcion para tomar tiempo inicial*/
void InicioMuestra();
/* Funcion para tomar tiempofinal y presenta el rsultado en ms*/
void FinMuestra();
/* Funcion para inicializar matrices A y B con valores determinados */
void iniMatriz(int n, double *m1, double *m2);
/* Funcion para imprimir una matriz en consola */
void imprMatrices(int n, double *matriz);
/* Funcion para multiplicación clásica de matrices: C = A x B */
void multiMatrizClasica(double *m1, double *m2, int n);

#endif
