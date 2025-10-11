/**************************************************************
*             Pontificia Universidad Javeriana               *
*   ------------------------------------------------------   *
*                                                            *
* Autor: Juan Diego Ariza                                    *
* Fecha: 21 de Agost 2025                                    *
* Docente: J. Corredor                                       *
* Objetivo: Challenge01                                      *
**************************************************************/
#include <stdio.h>// librería para printf
#include <stdlib.h>// libreria para menejo de memoria
#include <string.h> // librería para strcpy

int main() {

    char *p;// crear un puntero p de tipo char
    char *q = NULL;// crea un puntero q de tipo char que apunta a NULL

    // Se reserva la  memoria suficiente antes de usar los punteros
    p = (char*) malloc(strlen("Hello, I'm the best in Operating Systems!!!") + 1);
    q = (char*) malloc(strlen("Goodbye") + 1);

    printf("Address of p = %s\n", p); //imprimir la direccion de p

    strcpy(p, "Hello, I'm the best in Operating Systems!!!"); //copia el texto en p
    printf("%s\n", p);//muestras lo que se copio en p
    printf("About to copy \"Goodbye\" to q\n");//se copia Goodbye en q
    strcpy(q, "Goodbye");//intenta escribir en q
    printf("String copied\n");//muestra 
    printf("%s\n", q);

    return 0;
}
