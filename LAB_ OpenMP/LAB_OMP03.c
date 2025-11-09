
/*********************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 06/11/2025
 * Tema: Programación Paralela – Introducción OpenMP
 * Descripción: Ejemplo de uso de variables privadas en OpenMP.
 *              Este programa muestra el problema al declarar
 *              variables privadas sin control de concurrencia.
 *********************************************************/

#include <omp.h>    // Librería para usar directivas OpenMP
#include <stdio.h>
#include <stdlib.h>

int main() {
    int i;                 // Variable de control del ciclo
    const int N = 1000;    // Límite superior del ciclo
    int a = 50;            // Variable base para la suma
    int b = 0;             // Variable acumuladora

    // Cada hilo tiene su propia copia de 'i' y 'a'; 'b' es compartida,
    // generando condición de carrera al escribir simultáneamente.
    #pragma omp parallel for private(i) private(a)
    for (i = 0; i < N; i++) {
        b = a + i;  // Cada hilo modifica la misma variable 'b'
    }

    // Fuera de la región paralela se imprime el resultado final
    printf("a = %d b = %d (Se espera a=50 b = 1049)\n", a, b);

    return 0;
}
