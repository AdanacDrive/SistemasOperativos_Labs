/*******************************************************************
 * Nombre: Juan Diego Ariza Lopez
 * Materia: Sistemas Operativos
 * Profesor: John Corredor, Ph.D.
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 30/10/2025
 * Tema: Hilos con API POSIX
 * Descripción: Programa que crea dos hilos independientes que
 *              ejecutan una función que imprime un mensaje.
 *
 *****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

/**
 * Función que ejecutará cada hilo
 * Imprime el mensaje recibido como parámetro
 */
void* print_message_function(void* ptr)
{
    char* message;
    message = (char*)ptr;
    printf("%s \n", message);
    return NULL;
}

/**
 * Función principal
 * Crea dos hilos que imprimen mensajes diferentes
 */
int main(void)
{
    pthread_t thread1, thread2;// Identificadores de los dos hilos
    char* message1 = "Hilo 1";// Mensaje del primer hilo
    char* message2 = "Hilo 2";// Mensaje del segundo hilo
    int iret1, iret2;         // Variables para guardar el código de retorno

    /* Crear hilos independientes, cada uno ejecutará la función de imprimir mensaje*/
    iret1 = pthread_create(&thread1, NULL, print_message_function, (void*)message1);
    iret2 = pthread_create(&thread2, NULL, print_message_function, (void*)message2);

    /* Esperar a que ambos hilos terminen antes de continuar*/
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    /*
     * Imprimir los códigos de retorno de la creación de los hilos.
     * Si pthread_create tuvo éxito, devolverá 0.
     */
    printf("Hilo 1 returns: %d\n", iret1);
    printf("Hilo 2 returns: %d\n", iret2);

    // Terminar el programa
    exit(0);
}
