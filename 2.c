#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

void *factorial (void *);

int main (int argc, char *argv[]) {
  srand(time(0));
  pthread_t t[argc-1];
  if(argc >= 2){
    //res=realloc(res,(argc-1)*sizeof(void));
    int args[argc-1]; 
    for (int i=0;i<argc-1;i++){
    	args[i] = atoi(argv[i+1]);
    	pthread_create(&t[i], NULL, factorial, &args[i]);
    }
    for (int i=0;i<argc-1;i++){
	    pthread_join(t[i],NULL);
    }
  }else{
    printf("Faltan argumentos");
  }
  return 0;
}

void *factorial(void *ar) {
  int *n = ar;
  printf("n = %d\n", *n);
  long long int resultado = 1;
  int num;
  for (num = 2; num <= *n; num++) {
    resultado= resultado*num;
    printf("Factorial de %d, resultado parcial %lld\n", *n, resultado);
    sleep (random()%3);
  }
  printf("El hilo: %lu termino.\n", (unsigned long) pthread_self());
  return NULL;
}