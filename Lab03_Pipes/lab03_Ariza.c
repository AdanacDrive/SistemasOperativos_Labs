/****************************************************
 * Pontificia Universidad Javeriana
 * Autor: Juan Diego Ariza Lopez
 * Fecha: 9/10/2025
 * Materia: Sistemas Operativos
 * Tema: Creación de procesos fork con tuberías
 * Objetivo:
 * - Comunicación entre procesos padre e hijo
 * - Procesos duplicados
 * - Comunicacion entre procesos con PIPE
 ****************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipefd[2];        /* Creación de tubería de comunicación */
    pid_t pid_hijo;      /* Id del hijo como proceso */

    /* Verificación si del PIPE */
    if (pipe(pipefd) == -1) {
        perror("Error creando el PIPE");
        exit(EXIT_FAILURE);
    }

    /* Se invoca la creación del proceso */
    pid_hijo = fork();
    /* Verificación creación del proceso */
    if (pid_hijo < 0) {
        perror("Error en el FORK!!!");
        exit(EXIT_FAILURE);
    }
 /* Lógica de cada proceso */
    if (pid_hijo == 0) {
        /* El proceo hijo lee el mensaje que el padre deje en la tubería */

        /* Se cierra el extremo de escritura porque el hijo solo va a leer */
        close(pipefd[1]);

        char mensaje[100];           /* buffer para el texto */
        int leidos = read(pipefd[0], mensaje, sizeof(mensaje));

        if (leidos == -1) {
            perror("Lectura falló");
            close(pipefd[0]);
            exit(EXIT_FAILURE);
        }
	/* Se agrega '\0' al final para que el texto se imprima bien*/
        if (leidos >= 0 && leidos < (int)sizeof(mensaje)) {
            mensaje[leidos] = '\0';
        } else {
            mensaje[sizeof(mensaje) - 1] = '\0';
        }

        printf("\n[HIJO  PID=%d] Recibí: \"%s\"\n", getpid(), mensaje);

        // Cierro el extremo de lectura
        close(pipefd[0]);

    } else {
        /* El proceso padre escribe el mensaje en la tubería */

        /* Se cierra el extremo de lectura porque el padre solo escribe
        close */

        const char *texto = "Hola hijo, soy tu PADRE. Estudia y toma tinto :)";
        int escritos = write(pipefd[1], texto, (int)strlen(texto));

        if (escritos == -1) {
            perror("Escritura falló");
            close(pipefd[1]);
            exit(EXIT_FAILURE);
        }

        printf("\n[PADRE PID=%d] Envié %d bytes al hijo (PID=%d)\n",
               getpid(), escritos, pid_hijo);

        /* cerrar la salida para que el hijo deje de bloquearse */
        close(pipefd[1]);
    }

    printf("Fin del programa.\n");
    return 0;
}
