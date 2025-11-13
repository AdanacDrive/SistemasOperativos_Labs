/*****************************************************************************************************
 *
 * - PONTIFICIA UNIVERSIDAD JAVERIANA
 *
 * Autor: Juan Diego Ariza
 * Profesor: John Corredor, Ph.D.
 * Fecha: 13/11/2025
 * Materia: Sistemas Operativos
 * Tema: Sistema de Ficheros
 * Descripción: Programa que lee de teclado el nombre de un directorio 
 *              y muestre en pantalla el nombre y el tamaño y lo que contiene los ficheros
 *
 *
 ***************************************************************************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

int main(){
    // Puntero para manejar el directorio
    DIR *d;
    
    // Buffer para almacenar el nombre del directorio
    char nomdir[90], nomfich[90];
    
    // Estructuras para almacenar información de archivos
    struct stat datos;
    struct dirent *direc;
    
    // Solicitar al usuario el nombre del directorio
    printf("Introduzca el Nombre de un Directorio: ");
    fgets(nomdir, sizeof(nomdir), stdin);
    
    // Eliminar el salto de línea del nombre del directorio
    nomdir[strlen(nomdir)-1]='\0'; // Eliminamos el \n del Nombre del Fichero
    
    // Intentar abrir el directorio
    if ((d=opendir(nomdir))==NULL){
        printf("El directorio no existe\n");
        return -1;
    }
    
    // Leer cada entrada del directorio
    while ((direc=readdir(d)) !=NULL) {
        // Copiar el nombre del directorio al buffer
        strcpy(nomfich, nomdir);
        
        // Agregar el separador de directorio
        strcat(nomfich, "/");
        
        // Agregar el nombre del archivo
        strcat(nomfich, direc->d_name);
        
        // Obtener información del archivo
        stat(nomfich, &datos);
        
        // Verificar si es un archivo regular
        if (S_ISREG(datos.st_mode))
            // Imprimir nombre y tamaño del archivo
            printf("Nombre: %s\t Tamaño: %d\n", direc->d_name, datos.st_size);
    } // Fin del While
    
    // Cerrar el directorio
    closedir(d);
    
    return 0;
}
/********************************************************************************************
 * NOTAS:
 * 
 * El programa lista todos los archivos de un directorio con su tamaño en bytes.
 * Solo muestra archivos regulares, no muestra carpetas ni archivos especiales.
 * Hay que escribir el nombre del directorio correctamente o dará error.
 * Es útil para ver rápidamente qué archivos hay en una carpeta y cuánto pesan.
 ******************************************************************************************/
