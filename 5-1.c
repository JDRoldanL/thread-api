#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <time.h>

#define MAXLON 1000

void sumatoria (void *);

int main (int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    if(argc == 2){
        clock_t start = clock();
        sumatoria(argv[1]);
        clock_t end = clock();
        printf("El tiempo es = %f\n", (((double)(end - start))/CLOCKS_PER_SEC));
    }
    return 0;
}

void sumatoria (void *nom) {
    char *nombre = nom;
    int cont = 1, leidos;
    char cadena[MAXLON];
    int fd;
    int acumular = 0;
    int *valores;
    fd= open(nombre,O_RDONLY);
    while ((leidos = read(fd,cadena,MAXLON)) != 0) {
        char *cad = strtok(cadena, " ");
        valores = (int *)malloc(sizeof(int)*1);
        valores[0] = atoi(cad);
        acumular = valores[0];
        while(cad != NULL){
            cad = strtok(NULL, " ");
            if(cad != NULL){
                valores = realloc(valores, sizeof(int)*(cont + 1));
                valores[cont] = atoi(cad);
                acumular = acumular + valores[cont];
                cont++;
            }
        }
        printf("La sumatoria es = %d\n", acumular);
        /*
        for (int i = 0; i < cont; i++){
            printf("Valores %d = %d\n", i , valores[i]);
        }
        */
    }
    close(fd);
}