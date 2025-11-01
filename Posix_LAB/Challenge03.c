/****************************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Sincronización de Hilos
 * Descripción: Programa que demuestra el uso de variables
 *              de condición (condition variables) junto con
 *              mutex para sincronizar la ejecución de hilos.
 * 
 ****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>


// Variables globales para sincronización

// Mutex (bloqueos) para controlar el acceso a recursos compartidos
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condition_mutex = PTHREAD_MUTEX_INITIALIZER;

// Variable de condición para notificar cambios en el estado del contador
pthread_cond_t condition_cond = PTHREAD_COND_INITIALIZER;

// Contador compartido y valores límite
int count = 0;
#define COUNT_DONE  15  // Valor final del contador
#define COUNT_HALT1 4   // Límite inferior de pausa
#define COUNT_HALT2 11  // Límite superior de pausa

/**
 * Función count01
 * Este hilo incrementa el contador global, pero se detiene
 * cuando el valor está entre COUNT_HALT1 y COUNT_HALT2.
 * Mientras tanto, espera una señal de count02 para continuar.
 */
void* count01(void* arg)
{
    for (; ; )
    {
        // Bloquear antes de verificar el rango
        pthread_mutex_lock(&condition_mutex);

        // Mientras el contador esté en el rango de pausa, esperar señal
        while (count >= COUNT_HALT1 && count <= COUNT_HALT2)
        {
            pthread_cond_wait(&condition_cond, &condition_mutex);
        }

        // Desbloquear para permitir acceso a otros hilos
        pthread_mutex_unlock(&condition_mutex);

        // incrementar contador con protección de mutex
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Valor del contador (función 01): %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Terminar si alcanza el valor final
        if (count >= COUNT_DONE) return NULL;
    }
}

/**
 * Función count02
 * Este hilo incrementa el contador global,su rol
 * principal es enviar la señal de "despertar" a count01 cuando
 * el contador sale del rango de pausa.
 */
void* count02(void* arg)
{
    for (; ; )
    {
        // Bloquear antes de verificar el estado
        pthread_mutex_lock(&condition_mutex);

        // Si el contador está fuera del rango de pausa, enviar señal
        if (count < COUNT_HALT1 || count > COUNT_HALT2)
        {
            pthread_cond_signal(&condition_cond);
        }

        pthread_mutex_unlock(&condition_mutex);

        // incrementar contador
        pthread_mutex_lock(&count_mutex);
        count++;
        printf("Valor del contador (función 02): %d\n", count);
        pthread_mutex_unlock(&count_mutex);

        // Terminar si se alcanza el valor máximo
        if (count >= COUNT_DONE) return NULL;
    }
}

/**
 * Función principal 
 * Crea los dos hilos (count01 y count02), los ejecuta al mismo tiempo
 * y espera a que ambos finalicen. 
 * Imprime el valor final del contador.
 */
int main(void)
{
    pthread_t thread1, thread2; // Identificadores de los hilos

    // Crear los dos hilos
    pthread_create(&thread1, NULL, count01, NULL);
    pthread_create(&thread2, NULL, count02, NULL);

    // Esperar a que ambos hilos terminen su ejecución
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    // Mostrar el valor final del contador
    printf("\nValor final del contador: %d\n", count);

    // Finalizar el programa
    exit(0);
}
