/*********************************************************
 * Nombre: Juan Diego Ariza López
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 06/11/2025
 * Tema: Programación Paralela – Introducción OpenMP
 * Descripción:
 *   Programa que calcula la sumatoria de la función seno
 *   usando paralelismo con OpenMP. se puede indicar:
 *     - Número de hilos.
 *     - Cantidad de repeticiones del ciclo for.
 *   El programa mide el tiempo total de ejecución y
 *   muestra la sumatoria y el tiempo asociado.
 *********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))  // Macro de utilidad (no esencial aquí)

/*---------------------------------------------------------
  f(i): Calcula la sumatoria de senos desde:
        start = i*(i+1)/2  hasta  finish = start + i - 1
----------------------------------------------------------*/
double f(int i) {
    double start = i * (i + 1) / 2.0;
    double finish = start + i;
    int j;
    double return_val = 0.0;

    for (j = (int)start; j < (int)finish; j++) {
        return_val += sin(j);
    }

    return return_val;
}

int main(int argc, char *argv[]) {
    // Validación de parámetros: [1] número de hilos, [2] repeticiones del for
    if (argc != 3) {
        printf("Uso: %s <num_hilos> <num_iteraciones>\n", argv[0]);
        return 1;
    }

    int num_hilos = atoi(argv[1]);       // Número de hilos a usar
    int n = atoi(argv[2]);              // Cantidad de iteraciones del ciclo for

    if (num_hilos <= 0 || n <= 0) {
        printf("Error: <num_hilos> y <num_iteraciones> deben ser enteros positivos.\n");
        return 1;
    }

    // Configura el número de hilos para OpenMP según la entrada del usuario
    omp_set_num_threads(num_hilos);

    double sum = 0.0;
    int i;

    // Toma el tiempo inicial (reloj en segundos de OpenMP)
    double t_inicio = omp_get_wtime();

    // Región paralela: se calcula la sumatoria en paralelo
    #pragma omp parallel
    {
        int threads = omp_get_num_threads();  // Número real de hilos creados

        // Solo el hilo maestro imprime esta información
        #pragma omp master
        {
            printf("Numero de hilos usados: %d\n", threads);
            printf("Iteraciones del ciclo for: %d\n", n);
        }

        // Paraleliza el ciclo for y acumula en 'sum' usando reduction
        #pragma omp for reduction(+:sum)
        for (i = 0; i < n; i++) {
            sum += f(i);
        }
    }

    // Toma el tiempo final
    double t_fin = omp_get_wtime();
    double tiempo_total = t_fin - t_inicio;

    // Imprime la sumatoria y el tiempo total de ejecución
    printf("La sumatoria es: %.6f\n", sum);
    printf("Tiempo total de ejecucion: %.6f segundos con %d hilos.\n",
           tiempo_total, num_hilos);

    return 0;
}
