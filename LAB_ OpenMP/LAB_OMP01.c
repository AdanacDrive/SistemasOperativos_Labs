/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 06/11/2025
 * Tema: Programación Paralela - Introducción OpenMP
 * Descripción: Programa crea hilos de ejecución para cada core
 *              e imprime cadena de caracteres por cada llamada.
 ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>        // Biblioteca necesaria para usar OpenMP

int main(int argc, char *argv[]){
    // Obtiene el número máximo de hilos disponibles en el sistema
    int maxCores = omp_get_max_threads();
    
    // Imprime la cantidad de cores/hilos disponibles
    printf("Número máximo de cores del SO: %d \n", maxCores);
    
    // Directiva de OpenMP que crea una región paralela
    // El código dentro de las llaves será ejecutado por múltiples hilos simultáneamente
#pragma omp parallel
    {
        // Cada hilo imprime su ID único
        // omp_get_thread_num() retorna el identificador del hilo actual
        printf("Hilo ID en Región Paralela: %d \n", omp_get_thread_num());
    }
    
    return 0;
}
