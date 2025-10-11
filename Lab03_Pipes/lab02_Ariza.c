/****************************************************
 * Pontificia Universidad Javeriana
 * Autor: Juan Diego Ariza Lopez
 * Fecha: 9/10/2025
 * Materia: Sistemas Operativos
 * Tema: Creación de procesos fork
 * Objetivo:
 * - Identificación del proceso padre e hijo
 * - Procesos duplicados
 ****************************************************/

#include <stdio.h>
#include <unistd.h> /* Libreria para uso del fork */

int main() {

    /* Mensaje de inicio del programa */
    printf("\n\n Programa Principal!!! \n");

    /* Se invoca la creación del proceso por medio del fork para crear un nuevo proceso (hijo) */
    int procesoID = fork();

    /* Se valida el resultado del fork */
    if (procesoID == 0) {
        /* Aqui este bloque se ejecuta en el proceso hijo */
        printf("\nSoy Luke Skywalker!!!\n");
        printf("PID del HIJO = %d\n", getpid());
        printf("PID del PADRE = %d\n\n", getppid());

        /* Este ciclo imprime valores ascendentes (0 a 5) */
        for (int i = 0; i <= 5; i++) {
            printf(" Valor HIJO: %d\n", i);
        }

    } else if (procesoID > 0) {
        /* Aqui este bloque lo ejecuta el proceso padre */
        printf("\nLuck Soy tu PADRE!!!\n");
        printf("PID del PADRE = %d\n", getpid());
        printf("PID del HIJO = %d\n\n", procesoID);

        /* Ciclo que imprime valores descendentes (5 a 0) */
        for (int j = 5; j >= 0; j--) {
            printf(" Valor PADRE: %d\n", j);
        }

    } else {
        /* Si el fork llega a fallar se muestra un mensaje de error */
        printf("Error al crear el proceso con fork()\n");
    }

    /* Ambos procesos llegan a este punto (padre e hijo) */
    printf("\nFin del programa.\n\n");

    return 0;
}
