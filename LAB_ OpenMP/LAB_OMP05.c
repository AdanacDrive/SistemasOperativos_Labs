/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 06/11/2025
 * Tema: OpenMP - Cálculo de Sumatorias de función SENO
 * Descripción: Programa que calcula la sumatoria de la función
 *              seno usando paralelización con OpenMP y reduction.
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

// Macro para calcular el mínimo entre dos valores
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

// Función que calcula la sumatoria de seno
double f(int i) {
    double j, start = i * (i + 1) / 2, finish = start + i;
    int j_int;
    double return_val = 0;
    for (j_int = start; j_int < finish; j_int++)
        return_val += sin(j_int);
    return return_val;
}

int main() {
    double sum = 0;
    int i, n = 30000;
    
    // Región paralela
#pragma omp parallel
    {
        // Obtiene el número de hilos
        int threads = omp_get_num_threads();
        
        // Directiva master: solo el hilo maestro ejecuta esto
#pragma omp master
        printf("Número maximo de hilos del SO: %d\n", threads);
        
        // Directiva for con reduction: paraleliza el for y suma los resultados
#pragma omp for reduction(+: sum)
        for (i = 0; i < n; i++){
            sum += f(i);
        }
    }
    
    printf("La sumatoria es: %.2f\n", sum);
    
    return 0;
}
