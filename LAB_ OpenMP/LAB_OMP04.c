/*********************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 06/11/2025
 * Tema: Programación Paralela – Introducción OpenMP
 * Descripción: Codigo corregido del uso de variables en OpenMP.
 *              Se usa 'lastprivate' para conservar el valor de
 *              la última iteración
 *********************************************************/

#include <omp.h>    // Librería para usar directivas OpenMP
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;                 // Variable de control del ciclo
    const int N = 1000;    // Número de iteraciones
    int a = 50;            // Variable base
    int b = 0;             // Resultado esperado: 1049

    /* Cada hilo tiene su propia 'i', todos comparten 'a=50'
     y 'b' conserva el valor de la última iteración (i=N-1) al finalizar.*/
    #pragma omp parallel for private(i) shared(a) lastprivate(b)
    for (i = 0; i < N; i++) {
        b = a + i;  // Cada hilo calcula su propio b local
    }

    // Al final, b toma el valor de la última iteración (a + 999 = 1049)
    printf("a = %d b = %d (Se espera a=50 b = 1049)\n", a, b);

    return 0;
}
