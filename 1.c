#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h>
#include <string.h>

void *factorial (void *);

void *res1;
void *res2;

int main (int argc, char *argv[]) {
  srand(time(0));
  pthread_t t1, t2;
  if (argc == 3) {
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    pthread_create(&t1, NULL, factorial, &a);
    pthread_create(&t2, NULL, factorial, &b);
    pthread_join(t1, res1);
    pthread_join(t2, res2);
  }else if(argc == 2){
    int a = atoi(argv[1]);
    //int *b = factorial(&a);
    pthread_create(&t1, NULL, factorial, &a);
    pthread_join(t1, res1);
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
  void *res = (void *)&resultado;
  return res;
}