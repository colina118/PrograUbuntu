#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define N 10

pthread_mutex_t banio =   PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t desocupadoMen = PTHREAD_COND_INITIALIZER;
pthread_cond_t desocupadoWomen = PTHREAD_COND_INITIALIZER;

int contHombres=0, contMujeres =0, mInside=0, wInside=0;

void* men(void * args)
{
  pthread_mutex_lock(&banio);
  printf("Nuevo hombre en la fila, actualmente hay %d hombres esperando\n", ++contHombres);

  if(wInside)
  {
    pthread_cond_wait(&desocupadoMen, &banio);
  }
  mInside++;

  if(mInside ==1)
  {
    printf("Los hombres estan en el banio ahora\n");
  }
  printf("Pasa un hombre al banio, actualmente hay %d hombres esperando\n", --contHombres);
  pthread_mutex_unlock(&banio);

  sleep(10);
  pthread_mutex_lock(&banio);
  mInside--;
  printf("Salio un hombre del banio\n");
  if(mInside ==0)
  {
    printf("Sanitario Vacio\n");
    pthread_cond_broadcast(&desocupadoWomen);
  }

  pthread_mutex_unlock(&banio);
}

void* women(void* args)
{
  pthread_mutex_lock(&banio);
  printf("Nueva mujer en la fila, actualmente hay %d mujeres esperando\n", ++contMujeres);

  if(mInside)
  {
    pthread_cond_wait(&desocupadoWomen, &banio);
  }
  wInside++;

  if(wInside == 1)
  {
    printf("Las mujeres estan en el banio ahora\n");
  }
  printf("Pasa una mujer al banio, actualmente hay %d mujeres esperando\n", --contMujeres);
  pthread_mutex_unlock(&banio);

  sleep(10);
  pthread_mutex_lock(&banio);
  mInside--;
  printf("Salio una mujer del banio\n");
  if(wInside ==0)
  {
    printf("Sanitario Vacio\n");
    pthread_cond_broadcast(&desocupadoMen);
  }

  pthread_mutex_unlock(&banio);
}

int main(int argc, char** argv)
{
  int i, tipo;
	printf("Sanitario vacío\n");

	srand((int) time(NULL));
	pthread_t personas[N];
	for (i = 0; i < N; ++i) {
		sleep(rand() % 5);
		tipo = rand() % 2;
		if (tipo)
			pthread_create(&personas[i], NULL, men, NULL);
		else
			pthread_create(&personas[i], NULL, women, NULL);
	}

	for (i = 0; i < N; ++i) {
		pthread_join(personas[i], NULL);
	}
}
