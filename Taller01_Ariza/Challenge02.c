/**************************************************************
*             Pontificia Universidad Javeriana               *
*   ------------------------------------------------------   *
*                                                            *
* Autor: Juan Diego Ariza                                    *
* Fecha: 21 de Agosto 2025                                    *
* Docente: J. Corredor                                       *
* Objetivo: Challenge02                                      *
**************************************************************/
#include <stdio.h>   // librería para imprimir en pantalla
#include <stdlib.h>  // librería para manejar memoria
#include <string.h>  // librería para funciones

int main() {
    char *q = NULL; // Se crea un puntero q de tipo char que apunta a NULL

    printf("Requesting space for \"Goodbye!\" \n"); // Mensaje para decir que va a guardar memoria

    q = (char *)malloc(strlen("Goodbye") + 1);   //se pide memoria suficiente para la palabra "Goodbye" mas el carácter nulo

    if (!q) { 
        perror("Failed to allocate space because");// si  falla se muestra menasje de error 
        exit(1); // sale con código de error
    }

    printf("About to copy \"Goodbye\" to q at address %p \n", (void *)q);  // muestra la dirección de memoria donde se guardara la palabra

    strcpy(q, "Goodbye"); // se copia la palabra "Goodbye" dentro del espacio de memoria que se pidio

    printf("String copied\n"); // se confirma que se copió
    printf("%s \n", q); // muestra la palabra que quedó guardada en q

    free(q); // Se libera la memoria que se pidio antes

    return 0; // fin del programa
}
