#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#define MAXLON 1000

void cuenta (void *);

int main (int argc, char *argv[]) { 
    pthread_t t[argc-1];
    if (argc < 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    if(argc >= 2){
        for (int i = 0; i < argc-1; i++){
        pthread_create(&t[i], NULL, (void *)cuenta, argv[i+1]);
        }
        for (int i = 0; i < argc-1; i++){
            pthread_join(t[i], NULL);
        }
    }
    return 0;
}

void cuenta (void *nom) {
    char *nombre = nom;
    int pos, cont= 0, leidos;
    char cadena[MAXLON];
    int fd;
    fd= open(nombre,O_RDONLY);
    while ((leidos =read(fd,cadena,MAXLON))!= 0) {
    for (pos= 0; pos< leidos; pos++) {
        if ((cadena[pos]== 'a') || (cadena[pos]== 'A')) {
        cont++;
        }
    }
    }
    printf("Fichero %s: %d caracteres 'a' o 'A' encontrados\n", nombre, cont);
    close(fd);
}