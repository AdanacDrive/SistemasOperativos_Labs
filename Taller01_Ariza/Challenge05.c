/**************************************************************
*             Pontificia Universidad Javeriana               *
*   ------------------------------------------------------   *
*                                                            *
* Autor: Juan Diego Ariza                                    *
* Fecha: 21 de Agosto 2025                                   *
* Docente: J. Corredor                                       *
* Objetivo: Challenge01                                      *
*************************************************************/
#include <stdio.h>    // Librería para imprimir en pantalla
#include <stdlib.h>   // Libreria para manejo de la memoria

int main() {


    int *ptr, i, n1, n2;                     // Se crea un puntero, una variable i, n1, n2 todos de tipo intiger
   printf("Enter size: ");                  // Pide al usuario el tamaño inicial
    scanf("%d", &n1);                        // Guarda el tamaño en n1

    ptr = (int*) malloc(n1 * sizeof(int));   // Reserva la  memoria para n1 enteros

    printf("Addresses of previously allocated memory: "); // Muestra las direcciones de la memoria
    for (i = 0; i < n1; ++i)                 
        printf("\n\np = %p\n", ptr+i);      // Imprime la dirección de cada posición reservada


    printf("\nEnter the new size: ");        // Se pide un nuevo tamaño
    scanf("%d", &n2);                        // Guarda el nuevo tamaño en n2


    ptr = realloc(ptr, n2 * sizeof(int));    // Cambia el tamaño de la memoria reservada

    printf("Addresses of newly allocated memory: "); // Muestra las  direcciones con el nuevo tamaño
    for (i = 0; i < n2; ++i)                 
      printf("\n\np = %p\n", ptr+i);         // Imprime  las direcciones

   free(ptr);                               // Liberar la memoria que se  reservo
}
