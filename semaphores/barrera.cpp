#include<pthread.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>

static pthread_barrier_t barrier;

void * action(void * arg)
{
  int * id = (int*)arg;
  for(int i = 0; i < 10; i++)
  {
    printf("Hilo %i ejecutando accion\n", *id);
    sleep(rand()%5);
  }
  pthread_barrier_wait(&barrier);

  printf("Hilo %i termino\n", *id);

  pthread_exit(NULL);
}

int main()
{
  srand(time(NULL));
  int num_threads = 5;
  int i;
  pthread_t threads[num_threads];

  pthread_barrier_init(&barrier, NULL, 5);

  int * ids = new int[5];

  for(i = 0; i < num_threads; i++)
  {
    ids[i] = i;
    pthread_create(&threads[i], NULL, action, (void *)(ids+i));
  }
  for(i = 0; i < num_threads; i++)
  {
    pthread_join(threads[i], NULL);
  }
}
