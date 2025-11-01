/****************************************************
 * Nombre: Juan Diego Ariza
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Hilos con API POSIX 
 * 
 * Descripción: Este programa corrige el problema de sincronización del Challenge07.
 * La asignación de la variable 'valor' ahora está protegida dentro del mutex,
 * garantizando que no haya condición de carrera entre los hilos.
 ****************************************************/
#include <stdio.h>      
#include <stdlib.h>     
#include <pthread.h>
#include <stdbool.h>

// Variable de condición: permite que un hilo espere una señal de otro hilo
pthread_cond_t var_cond = PTHREAD_COND_INITIALIZER;

// Mutex: protege las variables compartidas entre hilos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Variable global compartida entre hilos
int valor = 0;

// Bandera que indica si se debe notificar al hilo que espera
bool notificar = false;

/**
 * Función reportar
 * Este hilo espera hasta que otro hilo lo "despierte" mediante
 * una señal sobre la variable de condición.
 * Luego imprime el valor compartido.
 */
void* reportar(void* nousado)
{
    // Bloquear antes de acceder a las variables compartidas
    pthread_mutex_lock(&mutex);
    
    // Mientras 'notificar' sea falso, el hilo se suspende
    // y espera una señal en la variable de condición.
    while (!notificar)
    {
        pthread_cond_wait(&var_cond, &mutex);
    }
    
    // Cuando recibe la señal, imprime el valor compartido
    printf("El valor es: %d\n", valor);
    
    // Libera el mutex para permitir que otros hilos accedan
    pthread_mutex_unlock(&mutex);
    
    // No devuelve nada
    return NULL;
}

/**
 * Función asignar
 * Este hilo asigna un nuevo valor a la variable compartida
 * y luego "notifica" al hilo que está esperando para que
 * continúe su ejecución.
 * 
 * Ahora la asignación de 'valor' está DENTRO del mutex,
 * eliminando la condición de carrera que existía.
 */
void* asignar(void* nousado)
{
    // CORRECCIÓN: Bloquear el mutex ANTES de modificar la variable compartida
    pthread_mutex_lock(&mutex);
    
    // Asignar el nuevo valor a la variable (ahora protegido por el mutex)
    valor = 20;
    
    // Cambiar la bandera para indicar que ya se puede notificar
    notificar = true;
    
    // Enviar la señal a la variable de condición (despierta al hilo que espera)
    pthread_cond_signal(&var_cond);
    
    // Liberar el mutex
    pthread_mutex_unlock(&mutex);
    
    // No devuelve nada
    return NULL;
}

/**
 * Función principal (main)
 * Crea dos hilos: uno que asigna un valor y otro que espera a ser notificado.
 * Luego, espera a que ambos hilos terminen su ejecución.
 */
int main(int argc, char* argv[])
{
    pthread_t reporte, asigne; // Identificadores de los dos hilos
    
    // Crear el hilo que espera la señal
    pthread_create(&reporte, NULL, reportar, NULL);
    
    // Crear el hilo que asigna el valor y envía la señal
    pthread_create(&asigne, NULL, asignar, NULL);
    
    void* nousado; // Variable auxiliar para pthread_join 
    
    // Esperar a que ambos hilos finalicen
    pthread_join(reporte, &nousado);
    pthread_join(asigne, &nousado);
    
    // Limpieza de recursos: destruir el mutex y la variable de condición
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&var_cond);
    
    // Fin del programa
    return 0;
}
