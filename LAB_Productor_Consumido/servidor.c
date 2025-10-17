                                                                                                                                                                                                                     servidor.c                                                                                                                                                                                                                                 
/****************************************************
 * Nombre: Juan Diego Ariza López
 * Materia: Sistemas Operativos
 * Profesor: J. Corredor
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 16/10/2025
 * Descripción: - Servidor FIFO que recibe cadenas, las invierte
 * y las reenvia por el mismo FIFO
 ****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>


/* Nombre del archivo FIFO usado para la comunicación */
#define FIFO_FILE "/tmp/PIPE_COMUNICADOR"

/* Prototipo de la función que invierte una cadena */
void reverse_string(char *);


/* Función principal: inicia el servidor FIFO */
int main() {
   int fd;
   char readbuf[80];
   char end[10];
   int to_end;
   int read_bytes;

   /* Create the FIFO if it does not exist (ignora error si ya existe) */
   mkfifo(FIFO_FILE, S_IFIFO | 0640);
   /* Copiar la palabra clave "end" en la variable de control */
   strcpy(end, "end");
   /* Abrir el FIFO en modo lectura/escritura */
   fd = open(FIFO_FILE, O_RDWR);
   if (fd < 0) {        // Verificar si ocurrió error al abrir el FIFO
      perror("open");
      return 1;
   }
   /* Mostrar mensaje de estado antes de empezar a leer */
   printf("FIFOSERVER: Esperando mensajes del cliente...\n");
   /* Bucle principal de atención al cliente */
   while (1) {
      /* Leer los datos enviados desde el cliente */
      read_bytes = read(fd, readbuf, sizeof(readbuf) - 1);
      if (read_bytes <= 0) {
         /* Si no hay datos, esperar un corto tiempo antes de reintentar */
         usleep(100000);
         continue;
      }
        /* Agregar el carácter nulo al final para formar una cadena válida */
      readbuf[read_bytes] = '\0';

      /* Quitar el salto de línea final si viene incluido */
      if (read_bytes > 0 && readbuf[read_bytes - 1] == '\n') {
         readbuf[read_bytes - 1] = '\0';
      }
      /* Mostrar la cadena recibida por pantalla */
      printf("FIFOSERVER: Received string: \"%s\" and length is %d\n",
             readbuf, (int)strlen(readbuf));
      /* Verificar si el cliente envió "end" para terminar la comunicación */
      to_end = strcmp(readbuf, end);
      if (to_end == 0) {
         close(fd);
         break;
      }
       /* Invertir la cadena recibida */
      reverse_string(readbuf);

      /* Mostrar la cadena invertida en consola antes de enviarla */
      printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n",
             readbuf, (int)strlen(readbuf));
      /* Enviar la cadena invertida de vuelta al cliente */
      write(fd, readbuf, strlen(readbuf));
      /* Pausa para asegurar que el cliente lea la respuesta */
      sleep(2);
   }
   /* Finalizar el programa correctamente */
   return 0;
}

/* --------------------------------------------------
 * Funcion: reverse_string
 * Descripción: Invierte el contenido de una cadena.
 * Parámetros:
 *   - str: puntero a la cadena que será invertida.
 * -------------------------------------------------- */

void reverse_string(char *str) {
   int last, first; // Índices para recorrer la cadena desde ambos extremos
   char temp;       // Variable temporal para intercambio de caracteres

   last = (int)strlen(str) - 1; // Último índice de la cadena
   first = 0;                   // Primer índice

   /* Intercambia los caracteres de los extremos hacia el centro */
   while (first < last) {
      temp = str[first];
      str[first] = str[last];
      str[last] = temp;
      first++;
      last--;
   }
}

