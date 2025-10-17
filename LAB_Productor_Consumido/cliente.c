                                                                                                                                                                               cliente.c                                                                                                                                                                                           /****************************************************
 * Nombre: Juan Diego Ariza López
 * Materia: Sistemas Operativos
 * Profesor: J. Corredor
 * Universidad: Pontificia Universidad Javeriana
 * Fecha: 16/10/2025
 * Descripción: Cliente FIFO que envía cadenas al servidor
 *              y recibe las cadenas invertidas.
 ****************************************************/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_FILE "/tmp/PIPE_COMUNICADOR" // Ruta del FIFO que es compartido con el servidor

int main() {
   int fd;              // Descriptor de archivo para el FIFO
   int end_process;     // Bandera para detectar la palabra "end"
   int stringlen;       // Longitud de la cadena ingresada
   int read_bytes;      // Cantidad de bytes leídos desde el FIFO
   char readbuf[80];    // Buffer para almacenar la cadena
   char end_str[5];     // Palabra que finaliza la comunicación

   // Mensaje inicial que ve el usuario
   printf("FIFO_CLIENT: Envíe mensajes; para terminar escriba \"end\"\n");

   // Abrir el FIFO creado por el servidor en modo lectura/escritura
   fd = open(FIFO_FILE, O_RDWR);
   if (fd < 0) {                // Verificar si hubo error al abrir
      perror("open");
      return 1;
   }
   // Inicializar la palabra que finaliza la comunicacion
   strcpy(end_str, "end");

   // Bucle principal de comunicación
   while (1) {
      printf("Ingrese cadena: ");

      // Leer una cadena desde teclado
      if(!fgets(readbuf, sizeof(readbuf), stdin)) {
        break;
        }
        // Calcular la longitud de la cadena ingresada
      stringlen = strlen(readbuf);

        // Eliminar el salto de línea final
      if (readbuf[stringlen - 1] == '\n')
         readbuf[stringlen - 1] = '\0';

        // Comparar con la palabra "end"
      end_process = strcmp(readbuf, end_str);

        // Enviar la cadena al servidor a través del FIFO
      write(fd, readbuf, strlen(readbuf));
      printf("FIFOCLIENT: Enviada cadena: \"%s\" (len=%d)\n", readbuf, (int)strlen(readbuf));

        // Si la cadena es "end", se cierra la conexión y termina el cliente
      if (end_process == 0) {
         close(fd);
         break;
      }
        // Esperar respuesta del servidor
      read_bytes = read(fd, readbuf, sizeof(readbuf) - 1);

        // Si se recibió algo, mostrarlo en pantalla
      if (read_bytes > 0) {
         readbuf[read_bytes] = '\0';
         printf("FIFOCLIENT: Recibida cadena: \"%s\" (len=%d)\n", readbuf, (int)strlen(readbuf));
      }
   }
   // Finalizar el programa correctamente
   return 0;
}

