/**************************************************************
*             Pontificia Universidad Javeriana               *
*   ------------------------------------------------------   *
*                                                            *
* Autor: Juan Diego Ariza                                    *
* Fecha: 21 de Agosto 2025                                   *
* Docente: J. Corredor                                       *
* Objetivo: Challenge03                                      *
**************************************************************/
#include <stdio.h>   //libreria para imprimir mensajes
#include <stdlib.h>  //libreria para manejo de memoria dinamica

int main() {
    int *ptr; //Se declara un puntero de tipo entero

    ptr = (int *)malloc(15 * sizeof(*ptr)); // Pedimos memoria para 15 enteros seguidos 
    // devuelve memoria en bytes, multiplicamos 15 * tamaño de int

    if (ptr != NULL) {   // Se revisa que la  memoria no sea NULL

        *(ptr + 5) = 480;   // El  puntero  muéve 5 posiciones y guarda ahi el numero 480

        printf("Value of the 6th integer is %d\n", *(ptr + 5)); // ImprimE el valor que guardamos en esa posición
        free(ptr);  // Se libera la memoria
    } else {
        printf("Error: No se pudo asignar memoria.\n"); //si la memeria es NULL muestra error
    }

    return 0; 
}
