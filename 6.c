#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define MAXLON 1000


void *sumatoria (void *);
void *meanSquare (void *);
float calculate_standard_deviation(float*,int,int);

float mean=0;

typedef struct arr{
    int tamaño;
    float* vector;
    float result;
}arr;


int main (int argc, char *argv[]) {
    if (argc < 3 || argc > 3) {
        printf ("Indica el nombre de un fichero.\n");
        exit(0);
    }
    if(argc == 3){
        float *notas = (float *)malloc(sizeof(float)*1);
        int nhilos=atoi(argv[2]);
        int cont = 0, leidos;
        char cadena[MAXLON];
        int fd;
        fd= open(argv[1],O_RDONLY);
        while ((leidos = read(fd,cadena,MAXLON)) != 0) {
            char *cad = strtok(cadena, ",");
            notas = realloc(notas, sizeof(float *)*(cont+1));
            notas[cont] = atof(cad);
            cont++;
            while(cad != NULL){
                cad = strtok(NULL, ",");
                if(cad != NULL){
                    notas = realloc(notas, sizeof(float)*(cont + 1));
                    notas[cont] = atof(cad);
                    cont++;
                }
            }
        }
    close(fd);    
    float std=calculate_standard_deviation(notas,cont,nhilos);
    printf("Desviación estandar: %f\n", std);
    }
    return 0;
}
float calculate_standard_deviation(float* notas,int cont,int nhilos){
    pthread_t h[nhilos];
    float** vecs = (float **)malloc(sizeof(float *)*(nhilos));
    int size=cont/nhilos;
    int sizelast=size+(cont%nhilos);
    for (int i = 0; i < nhilos-1; i++){
        vecs[i] = (float*)malloc(sizeof(float)*size);
    }
    vecs[nhilos-1] = (float*)malloc(sizeof(float)*sizelast);

    for (int i = 0; i < nhilos-1; i++){
        for (int j = 0; j < size; j++){
            vecs[i][j] = notas[i*size+j];
        }            
    }
    for (int i = 0; i < sizelast; i++){
            vecs[nhilos-1][i] = notas[size*(nhilos-1)+i];
    }
    arr arrs[nhilos];
    for (int i = 0; i < nhilos-1; i++){
        arrs[i].tamaño=size;
        arrs[i].vector=vecs[i];
    }
    arrs[nhilos-1].tamaño=sizelast;
    arrs[nhilos-1].vector=vecs[nhilos-1];
    for (int i = 0; i < nhilos; i++){
        pthread_create(&h[i],NULL,sumatoria, &arrs[i]);
    }
    for (int i = 0; i < nhilos; i++){
        pthread_join(h[i], NULL);
    }
    for (int i = 0; i < nhilos; i++){
        mean+=arrs[i].result;
    }
    mean=mean/cont;
    for (int i = 0; i < nhilos; i++){
        pthread_create(&h[i],NULL,meanSquare, &arrs[i]);
    }
    for (int i = 0; i < nhilos; i++){
        pthread_join(h[i], NULL);
    }
    float stdDev=0;

    for (int i = 0; i < nhilos; i++){
        stdDev+=arrs[i].result;
    }
    stdDev=sqrt((1/((float)cont-1))*stdDev);
    return stdDev;
}

void *sumatoria(void *vec){
    arr *ar = (arr *)vec;
    float *sum = (float *)malloc(sizeof(float));
    *sum = 0;
    float *b = ar->vector;
    for (int i = 0; i < ar->tamaño; i++){
        *sum = *sum + b[i];
    }
    ar->result = *sum;
    pthread_exit(NULL);
}

void *meanSquare(void *vec){
    arr *ar = (arr *)vec;
    int *sum = (int *)malloc(sizeof(int));
    *sum = 0;
    float *b = ar->vector;
    for (int i = 0; i < ar->tamaño; i++){
        *sum = *sum + pow((b[i]-mean),2);
    }
    ar->result = *sum;
    pthread_exit(NULL);
}