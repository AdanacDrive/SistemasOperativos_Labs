/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Hilos con API POSIX
 * 
 * Descripción:  Este programa corrige el problema de condición de carrera del Challenge05.
 * Se utiliza un mutex para sincronizar el acceso a la variable compartida 'acumulado',
 *  Ahora el resultado siempre será correcto: 2870.
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>

// Variable global
int acumulado = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * Función que ejecutará cada hilo.
 * Calcula el cuadrado del número recibido y lo acumula en una variable global.
 */
void* cuadrado(void* x)
{
    
    int x1 = (intptr_t)x;// Convertir el puntero  a un entero

    pthread_mutex_lock(&mutex);// Bloquear antes de acceder a la variable compartida
    acumulado += x1 * x1;
    pthread_mutex_unlock(&mutex);//Desbloquear para permitir que otros hilos puedan acceder a 'acumulado'.

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
