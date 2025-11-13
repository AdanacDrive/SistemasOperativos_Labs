/********************************************************************************************
 * 
 * - PONTIFICIA UNIVERSIDAD JAVERIANA
 * 
 * Autor: Juan Diego Ariza
 * Profesor: John Corredor, Ph.D.
 * Materia: Sistemas Operativos
 * Fecha: 13/11/2025
 * Tema: Sistema de Ficheros
 * Descripción: Crear un programa en C que lea el contenido de un fichero readme.txt
 * 
 * 
 ******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    // Nombre del archivo a leer
    char *nombrefichero = "readme.txt";
    
    // Abrir el archivo en modo lectura
    FILE *fp = fopen(nombrefichero, "r");
    
    // Validar si el archivo se pudo abrir correctamente
    if (fp==NULL){
        printf("Error: no se puede abrir el fichero\n");
        return 1;
    }
    
    // Imprimir encabezado
    printf("\n =========================================\n");
    printf("\n LECTURA DE FICHERO readme.txt\n");
    printf("\n =========================================\n");
    
    // Lectura de fichero, máximo 256 bytes por línea
    // Lectura de línea por línea (buscar \n)
    const unsigned LARGO_MAX_LINEA = 256;
    char buffer[LARGO_MAX_LINEA];
    
    // Leer línea por línea hasta el final del archivo
    while(fgets(buffer, LARGO_MAX_LINEA, fp))
        printf("%s", buffer);
    
    // Cerrar el fichero
    fclose(fp);
    
    return 0;
}
