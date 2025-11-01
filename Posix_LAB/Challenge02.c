/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Hilos con API POSIX
 * Descripción: Programa que crea 10 hilos que incrementan un
 *              contador compartido usando mutex para sincronización.
 *
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NTHREADS 10  // Número total de hilos a crear

// Variable global compartida entre los hilos
int counter = 0;

// Declaración e inicialización del mutex (bloqueo)
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;


/**
 * Función que ejecutará cada hilo
 * Cada hilo incrementa el contador de forma segura usando mutex
 */
void* thread_function(void* arg)
{
    // Se recibe el número del hilo como argumento
    int i = *(int*)(arg);

    // Mostrar número e identificador del hilo
    printf("Hilo numero: %d | Hilo ID %ld\n", i, pthread_self());

    // Bloquear el mutex antes de modificar el contador
    pthread_mutex_lock(&mutex1);
    counter++;
    // Desbloquear el mutex para que otros hilos puedan entrar
    pthread_mutex_unlock(&mutex1);

    // Terminar hilo
    return NULL;
}

/**
 * Función principal
 * Crea 10 hilos, espera a que terminen y muestra el resultado
 */
int main(void)
{
    pthread_t thread_id[NTHREADS];// Vector para los IDs de los hilos
    int i, j;
    int thread_args[NTHREADS];     // Arreglo para pasar un número único a cada hilo

    // Crear 10 hilos
    for (i = 0; i < NTHREADS; i++)
    {
        thread_args[i] = i + 1; // Guardar número de hilo (1 a 10)
        pthread_create(&thread_id[i], NULL, thread_function, &thread_args[i]);
    }

    // Esperar a que todos los hilos terminen
    for (j = 0; j < NTHREADS; j++)
    {
        pthread_join(thread_id[j], NULL);
    }

    // Ahora que todos los hilos han terminado, imprimir el resultado
    printf("Contador final: %d\n", counter);

    return 0;
}
