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


void *sumatoria (void *);

typedef struct arr{
    int tamaño;
    int *vector;
    int result;
}arr;


int main (int argc, char *argv[]) {
    if (argc < 2 || argc > 2) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    if(argc == 2){
        pthread_t h1,h2;
        int cont = 1, leidos;
        char cadena[MAXLON];
        int *valores;
        int fd;
        clock_t start = clock();
        fd= open(argv[1],O_RDONLY);
        while ((leidos = read(fd,cadena,MAXLON)) != 0) {
            char *cad = strtok(cadena, " ");
            valores = (int *)malloc(sizeof(int)*1);
            valores[0] = atoi(cad);
            while(cad != NULL){
                cad = strtok(NULL, " ");
                if(cad != NULL){
                    valores = realloc(valores, sizeof(int)*(cont + 1));
                    valores[cont] = atoi(cad);
                    cont++;
                }
            }
        }
        int tam1, tam2;
        if(cont%2 == 0){
            tam1 = cont/2;
            tam2 = cont/2;   
        }else{
            tam1 = (cont/2)+1;
            tam2 = cont/2;
        }
        int vec1[tam1];
        int vec2[tam2];
        for (int i = 0; i < tam1; i++){
            vec1[i] = valores[i];
        }
        for (int i = tam1; i < cont; i++){
            vec2[i-tam1] = valores[i];
        }
        arr ar1 = {tam1, vec1};
        arr ar2 = {tam2, vec2};
        close(fd);
        pthread_create(&h1,NULL,sumatoria, &ar1);
        pthread_create(&h2,NULL,sumatoria, &ar2);
        pthread_join(h1, NULL);
        pthread_join(h2, NULL);
        printf("resultado hilo 1 = %d\n", ar1.result);
        printf("resultado hilo 2 = %d\n", ar2.result);
        printf("La suma total es = %d\n", (ar1.result + ar2.result));
        clock_t end = clock();
        printf("El tiempo es = %f\n", (((double)(end - start))/CLOCKS_PER_SEC));
    }
    return 0;
}

void *sumatoria(void *vec){
    arr *ar = (arr *)vec;
    int *sum = (int *)malloc(sizeof(int));
    *sum = 0;
    int *b = ar->vector;
    for (int i = 0; i < ar->tamaño; i++){
        *sum = *sum + b[i];
    }
    ar->result = *sum;
    pthread_exit(NULL);
}