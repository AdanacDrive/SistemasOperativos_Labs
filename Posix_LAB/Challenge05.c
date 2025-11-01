/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Hilos con API POSIX
 * 
 * Descripción: Suponer que x*x es altamente costoso en cálculo computacional.
 *  Se desea calcular la suma de los cuadrados de una cantidad de números.
 *  Se aplica paralelizar el cálculo de cada cuadrado usando hilos.
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

// Variable global compartida entre los hilos
int acumulado = 0;

/**
 * Función que ejecutará cada hilo.
 * Calcula el cuadrado del número recibido y lo acumula en una variable global.
 */
void* cuadrado(void* x)
{
    // Convertir el puntero  a un entero
    int x1 = (intptr_t)x;
    acumulado += x1 * x1; // Sumar el cuadrado del número al acumulado global
    return NULL; // nada que retornar
}

/**
 * Función principal del programa.
 * Crea 20 hilos, cada uno calcula el cuadrado de un número (1 a 20)
 * y acumula el resultado en la variable global 'acumulado'.
 */
int main(int argc, char* argv[])
{
   
    pthread_t hilos[20];// Arreglo que almacenará los identificadores de los 20 hilos

    // Crear 20 hilos
    for (int i = 0; i < 20; i++)
    {
        pthread_create(&hilos[i], NULL, cuadrado, (void*)(intptr_t)(i + 1));
    }
    // Esperar a que todos los hilos terminen su ejecución
    for (int i = 0; i < 20; i++)
    {
        void* resultado;
        pthread_join(hilos[i], &resultado);
    }
    // Mostrar el resultado final
    printf("Acumulado = %d\n", acumulado);
    // Finalizar el programa
    return 0;
}
