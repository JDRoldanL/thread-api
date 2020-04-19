#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

void *factorial (void *);

int res;
int* restmp;

int main (int argc, char *argv[]) {
  srand(time(0));
  pthread_t t[argc-1];
  if(argc >= 2){
    //res=realloc(res,(argc-1)*sizeof(void));
    int args[argc-1]; 
    for (int i=0;i<argc-1;i++){
    	args[i] = atoi(argv[i+1]);
    	printf("arg :%d",args[i]);
    	pthread_create(&t[i], NULL, factorial, &args[i]);
    }
    for (int i=0;i<argc-1;i++){
    	//pthread_join(t[i],(void*)&res[i]);
	pthread_join(t[i],NULL);
    	//res[i]=*restmp;
	//printf("resultado: %d",res[i]);    	
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
    printf ("Factorial de %d, resultado parcial %lld\n", *n, resultado);
    sleep (0.5);
  }
  //int *tmp = (void *)&resultado;
  return NULL;
}
