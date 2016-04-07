#include <pthread.h>
#include <unistd.h>

int numero =4;

pthread_mutex_t mutex;

typedef struct params
{
  int n;
}param;

void * duplicaN(void *p)
{
  pthread_mutex_lock(&mutex);
  int i;
  int temp = numero;
  for(i =0; i < ((param*)p)->n; i++)
  {
    temp *= 2;
    printf("Duplica %d \n", temp);
    sleep(5);
  }
  numero = temp;
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

void * divideN(void *p)
{
  pthread_mutex_lock(&mutex);
  int i;
  int temp = numero;
  for(i = 0; i < ((param *)p)->n; i++)
  {
    temp /= 2;
    printf("Divide %d \n", temp);
    sleep(5);
  }
  numero = temp;
  pthread_mutex_unlock(&mutex);
  pthread_exit(NULL);
}

int main()
{
  pthread_t hilo1;
  pthread_t hilo2;

  param p;
  p.n = 5;

  pthread_create(&hilo1, NULL, duplicaN, &p);
  pthread_create(&hilo2, NULL, divideN, &p);

  pthread_join(hilo1, NULL);
  pthread_join(hilo2, NULL);
}
