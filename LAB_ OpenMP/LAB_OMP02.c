/****************************************************
 * Pontificia Universidad Javeriana
 * Autor: Juan Diego Ariza
 * Profesor: John Corredor, Ph.D.
 * Materia: Sistemas Operativos
 * Noviembre 6 de 2025
 * Tema: Introducción a OPENMP
 * Descripción: Uso de la directiva y función para hacer uso de OpenMP
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]){
    // Validación: verifica que se pase el número de hilos como argumento
    if(argc != 2){
        printf("Error: Inlts./ejecutable numHilos\n");
        exit(0);
    }
    
    // Convierte el argumento de entrada a entero
    int numHilos = (int) atoi(argv[1]);
    
    // Obtiene el número máximo de hilos disponibles en el sistema
    int maxCores = omp_get_max_threads();
    printf("Número máximo de Cores del SO: %d \n", maxCores);
    printf("numero maximo de Cores del estado: numHilos*/");  // ERROR: debería ser */
    
    // Se fija el número de hilos deseados
    omp_set_num_threads(numHilos);
    printf("Numero hilos fijados: %d \n", numHilos);
    
    // Región Paralela por OMP
#pragma omp parallel
    {
        // Cada hilo imprime su ID
        printf("Hilo ID en Región Paralela: %d \n", omp_get_thread_num());
    }
    
    return 0;
}
