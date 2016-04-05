
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#define ENANITOS 7
#define SILLAS 4
#define P 2

pthread_mutex_t lugar =   PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t desocupado = PTHREAD_COND_INITIALIZER;
pthread_cond_t comiendo = PTHREAD_COND_INITIALIZER;
pthread_cond_t esperando = PTHREAD_COND_INITIALIZER;

int sentados = 0, total = 0, sinComida = 0;

void* Enanos(void* args)
{
  int i = 0;
  while(i++ < P)
  {
    sleep(rand()%10);
    int enanito = (intptr_t) args;
    printf("Llego el enanito numero: %d\n", enanito);
    pthread_mutex_lock(&lugar);

    if(sentados == SILLAS)
    {
      pthread_cond_wait(&desocupado, &lugar);
    }
    printf("Ya hay lugar para el enano numero: %d\n", enanito);
    sentados++;
    sinComida++;

    if(sinComida == 1)
    {
      pthread_cond_signal(&esperando);
    }
    pthread_cond_wait(&comiendo, &lugar);
    sinComida--;
    printf("Ya esta comiendo el enanto numero: %d\n", enanito);
    pthread_mutex_unlock(&lugar);
    sleep(rand()%5);
    pthread_mutex_lock(&lugar);
    printf("Se fue el enano numero: %d\n", enanito);
    sentados--;
    if(sentados == SILLAS-1)
    {
      pthread_cond_signal(&desocupado);
    }
    pthread_mutex_unlock(&lugar);

  }
}

void* Blanca(void* args)
{
  while(total < ENANITOS)
  {
    pthread_mutex_lock(&lugar);
    if(sinComida == 0)
    {
      printf("La principesca blanca nieves se fue de parranda\n");
      pthread_cond_wait(&esperando, &lugar);
      printf("La principesca blanca nieves retorno\n");
    }
    pthread_mutex_unlock(&lugar);
    sleep(10);
    pthread_mutex_lock(&lugar);
    pthread_cond_signal(&comiendo);
    pthread_mutex_unlock(&lugar);
  }
}

int main(int argc, char** argv)
{
  int i;

  srand((int) time(NULL));
  pthread_t blanquita;
  pthread_create(&blanquita, NULL, Blanca, NULL);
  pthread_t ena[ENANITOS];
  for(i = 0; i < ENANITOS; i++)
  {
    pthread_create(&ena[i], NULL, Enanos, (void*)(intptr_t)i);
  }
  for (i = 0; i < ENANITOS; i++)
  {
		pthread_join(ena[i], NULL);
		total++;
	}
}
