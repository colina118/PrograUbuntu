#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#define N 5
#define ROB 7

int pesoMax[N], pesoSeccion[N];

pthread_mutex_t peso = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t sobrepeso[N];

void* entrarSeccion(void* args)
{
  int robot =(intptr_t) args;
  int i;

  int pesoOrden = (rand()%50);
  printf("LLego el robot %d y su peso de ordenes es %d\n", robot, pesoOrden);
  for(i = 0; i < N; i++)
  {
    pthread_mutex_lock(&peso);
    while(pesoSeccion[i] + pesoOrden > pesoMax[i])
    {
      printf("Robot %d esperando para pasar a seccion\n", robot);
      pthread_cond_wait(&sobrepeso[i], &peso);
    }
    printf("Robot %d entrando a seccion %d\n", robot, i);
    pesoSeccion[i] += pesoOrden;
    pthread_mutex_unlock(&peso);
    sleep(rand()%5);
    pthread_mutex_lock(&peso);
    printf("Robot %d saliendo de seccion %d\n", robot, i);
    pesoSeccion[i]-= pesoOrden;
    pthread_cond_broadcast(&sobrepeso[i]);
		pthread_mutex_unlock(&peso);
  }
  printf("Se fue el robot %d\n", robot);
}


int main(int argc, char** argv)
{
  int i;
  for(i = 0; i < N; i++)
  {
    pthread_cond_init(&sobrepeso[i], NULL);
    pesoMax[i] = 50;
    pesoSeccion[i] = 0;
  }
  srand((int) time(NULL));
  pthread_t robots[ROB];

  for(i = 0; i < ROB; i++)
  {
    sleep(rand()%3);
    pthread_create(&robots[i], NULL, entrarSeccion, (void*)(intptr_t)i);
  }
  for(i = 0; i < ROB; i++)
  {
    pthread_join(robots[i], NULL);
  }
}
