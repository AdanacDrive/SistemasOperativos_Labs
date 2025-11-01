/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Hilos con API POSIX
 * Descripción: Programa que crea 3 hilos que ejecutan una función
 *             que tiene un ciclo largo mientras
 *              incrementan un contador
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

// Variables globales
pthread_t tid[3];      // Array de identificadores de hilos
int counter;           // Contador compartido
pthread_mutex_t lock;  // Mutex para proteger el contador

/**
 * Función compute:
 * Realiza una operación computacionalmente intensiva (ciclo largo)
 * e incrementa el contador de forma segura
 */
void* compute(void* arg)
{
    unsigned long i = 0;

    // Incrementar contador al inicio usando mutex como proteccion
    pthread_mutex_lock(&lock) ;
    counter += 1;
    printf("\n Job %d has started\n", counter);
    pthread_mutex_unlock(&lock) ;

    // Ciclo grande que tarda un tiempo en ejecutarse
    for (i = 0; i < (0xFFFFFFFF); i++)
    {
        // Operación adicional para hacer el ciclo más pesado
        volatile unsigned long temp = i * i;
        (void)temp;  // Evitar que el compilador optimice
    }

    // Mostrar finalización
    pthread_mutex_lock(&lock) ;
    printf("\n Job %d has finished\n", counter);
    pthread_mutex_unlock(&lock) ;

    return NULL;
}

/**
 * Función principal
 * Crea 3 hilos UNO POR UNO (secuencialmente).
 * Cada hilo debe terminar antes de crear el siguiente.
 */
int main(void)
{
    int i = 0;
    int error;

    // Inicializar el mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("\n Error: fallo al inicializar el mutex\n");
        return 1;
    }

    // Crear y esperar cada hilo SECUENCIALMENTE
    while (i < 3)
    {
        // Crear el hilo
        error = pthread_create(&(tid[i]), NULL, &compute, NULL);
        if (error != 0)
        {
            printf("\n Error: no se pudo crear el hilo : [%s]", strerror(error));
        }

        // Esperar a que el hilo termine antes de crear el siguiente
        pthread_join(tid[i], NULL);

        i++;
    }

    // Destruir el mutex
    pthread_mutex_destroy(&lock) ;

    printf("\nTodos los hilos terminaron correctamente\n");

    return 0;
}
