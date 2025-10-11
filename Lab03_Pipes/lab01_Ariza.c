/****************************************************
 * Pontificia Universidad Javeriana
 * Autor: Juan Diego Ariza Lopez
 * Fecha: 09/10/2025
 * Materia: Sistemas Operativos
 * Tema: Creación de procesos fork
 * Objetivo:
 * Identificación del proceso padre e hijo
 ****************************************************/

#include <stdio.h>
#include <unistd.h> /* Libreria para poder usar fork */

int main() {

    /* Se invoca la creación del proceso en  y se guarda en una variable del tipo entero */
    int procesoID = fork();

    /* Se hace verificacion de que el fork se halla echo correctamente */
     if (procesoID < 0) {
        printf("Error al crear el proceso.\n");
        return 1; /* Termina el programa si hubo un error */
    }

    /* Si el ID es 0, significa que este bloque lo ejecuta el proceso hijo */
    if (procesoID == 0) {
        printf(" Soy el proceso hijo.\n");
        printf("   Mi nombre es Juan Diego Ariza!\n");
        printf("   Mi PID es: %d\n", getpid());
        printf("   El PID de mi padre es: %d\n\n", getppid());
    }
    /* Si el ID no es 0, este bloque lo ejecuta el proceso padre */
    else {
        printf(" Soy el proceso padre.\n");
        printf("   Mi PID es: %d\n", getpid());
        printf("   El PID de mi hijo es: %d\n\n", procesoID);
    }

    /* Ambos procesos llegan a esta línea y se muestra este mensaje de salida */
    printf("Fin del programa.\n");
    return 0;
}
