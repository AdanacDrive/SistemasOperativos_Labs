/*************************************************************************************************
 * 
 * PONTIFICIA UNIVERSIDAD JAVERIANA
 * 
 * Autor: Juan Diego Ariza
 * Profesor: John Corredor, Ph.D.
 * Materia: Sistemas Operativos
 * Tema: Sistema de Ficheros
 * Fecha: 13/11/2025
 * Descripción: Programa que lee el nombre de un directorio y muestra información
 *              detallada de sus archivos incluyendo permisos y fecha de modificación
 * 
 * 
 ************************************************************************************************/
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main() {
    int er;
    char nomdir[100], nomfich[100], resp[30];
    struct stat atr;
    DIR *d;
    struct dirent *rdl;
    time_t fecha;
    
    // Solicitar nombre del directorio al usuario
    printf("Nombre directorio\n");
    fgets(nomdir, sizeof(nomdir), stdin);
    
    // Hay que quitar el \n del nombre del directorio
    nomdir[strlen(nomdir)-1]='\0';
    
    // Obtener la fecha actual
    fecha=time(&fecha);
    
    // Intentar abrir el directorio
    if ((d=opendir(nomdir))==NULL) {
        printf("No existe ese directorio \n");
        return -1;
    }
    else {
        // Leer todas las entradas del directorio
        while ((rdl=readdir(d)) != NULL) {
            // Filtrar entradas "." y ".."
            if ((strcmp(rdl->d_name, ".")!=0) && (strcmp(rdl->d_name, "..")!=0)) {
                // Construir ruta completa del archivo
                strcpy(nomfich, nomdir);
                strcat(nomfich, "/");
                strcat(nomfich, rdl->d_name);
                
                // Mostrar nombre del archivo
                printf("fichero :%s: ", nomfich);
                
                // Obtener estadísticas del archivo
                er=stat(nomfich, &atr);
                
                // Mostrar modo/permisos del archivo
                printf("modo :%o: ", atr.st_mode);
                
                // Verificar si tiene permiso de lectura para propietario
                if ((atr.st_mode & 0400) != 0)
                    printf(" permiso R para propietario\n");
                else
                    printf(" No permiso R para propietario\n");
                
                // Verificar si es un directorio
                if (S_ISDIR(atr.st_mode)) 
                    printf(" Es un directorio \n");
                
                // Verificar si es un archivo regular
                if (S_ISREG(atr.st_mode)) 
                    printf(" Es un archivo regular \n");
                
                // Mostrar ficheros modificados en los últimos 10 días
                if ((fecha - 10*24*60*60) < atr.st_mtime) {
                    printf("FICHERO:%s: fecha de acceso %s, en sgdos %ld\n",
                           rdl->d_name,
                           ctime(&(atr.st_mtime)), atr.st_mtime);
                }
            }
        } // fin while
        
        // Cerrar el directorio
        closedir(d);
    }
    
    return 0;
} // fin main

