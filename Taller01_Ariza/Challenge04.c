/**************************************************************
*             Pontificia Universidad Javeriana               *
*   ------------------------------------------------------   *
*                                                            *
* Autor: Juan Diego Ariza                                    *
* Fecha: 21 de Agost 2025                                    *
* Docente: J. Corredor                                       *
* Objetivo: Challenge04                                      *
**************************************************************/
#include <stdio.h>   // libreria para imprimir
#include <stdlib.h>  // libreria para manejo de memoria

int main() {
    int n, i, *ptr, sum = 0;// se declara n de tipo entero un puntero de tipo entero y sum de tipo entero inicializado en 0
    printf("Enter number of elements: ");// se pide al usuario cuantos elementos quiere ingresar
    scanf("%d", &n);// guarda la cantidad en n

   
    ptr = (int*) calloc(n, sizeof(int));// Reservar memoria para n enteros para inicializarlos en 0

    
    if (ptr == NULL) {// Verificar si la memoria se asignó bien
        printf("Error! memory not allocated.\n");
        exit(0); // termina el programa si no tenemos mas memoria
    }

    printf("Enter elements:\n");//Se piden los elementos al usuario y se van almacenadno en memoria
    for (i = 0; i < n; ++i) {
        printf("Element %d: ", i + 1);
        scanf("%d", ptr + i);   // Guarda el valor ingresado en la posición de memoria correspondiente
        sum += *(ptr + i);      // acumulamos el valor en sum
    }

    
    printf("Sum = %d\n", sum);// Muestra el resultado de la suma

    free(ptr);// Libera la memoria que se reservo anteriormente

    return 0;
}

