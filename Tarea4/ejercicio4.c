#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

#define N 3

typedef struct {
	int id;
	int* data;
	pthread_cond_t* newData;
	pthread_mutex_t* mutexData;
} data_params_t;

int alarms = 0;

pthread_mutex_t UAD = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t freeData = PTHREAD_COND_INITIALIZER;

void* alarmWriting(void* args)
{
	int id = (intptr_t) args;
	pthread_mutex_lock(&UAD);
	printf("Escribiendo alarma UAD %d\n", id);
	sleep(1); // Tiempo que tarda en escribir
	--alarms;
	printf("faltan %d alarmas\n", alarms);
	if (alarms == 0)
		pthread_cond_broadcast(&freeData);
	pthread_mutex_unlock(&UAD);
}

void* alarmReading(void* args)
{
	int id = (intptr_t) args;
	pthread_t thread;
	while (1)
  {
		sleep(rand() % 10); // Tiempo aleatorio de alarma
		pthread_mutex_lock(&UAD);
		++alarms;
		printf("faltan %d alarmas\n", alarms);
		pthread_create(&thread, NULL, alarmWriting, (void*) (intptr_t) id);
		pthread_mutex_unlock(&UAD);
	}
}

void* dataWriting(void* args)
{
	int id = ((data_params_t*) args)->id;

	while (1)
  {
		pthread_mutex_lock(((data_params_t*) args)->mutexData);
		pthread_cond_wait( ((data_params_t*) args)->newData, ((data_params_t*) args)->mutexData );
		pthread_mutex_unlock(((data_params_t*) args)->mutexData);

		pthread_mutex_lock(&UAD);
		while (alarms)
    {
			pthread_cond_wait(&freeData, &UAD);
    }

		pthread_mutex_lock(((data_params_t*) args)->mutexData);
		printf("Escribiendo datos UAD %d: %d\n", id, *(((data_params_t*) args)->data) );
		sleep(1);
		pthread_mutex_unlock(((data_params_t*) args)->mutexData);
		pthread_mutex_unlock(&UAD);
	}
}

void* dataReading(void* args)
{
	int id = (intptr_t) args;
  int data = 0;
	pthread_t thread;
	pthread_mutex_t mutexData = PTHREAD_MUTEX_INITIALIZER;
	pthread_cond_t newData = PTHREAD_COND_INITIALIZER;

	data_params_t params;
	params.id = id;
	params.mutexData = &mutexData;
	params.newData = &newData;
	params.data = &data;
	pthread_create(&thread, NULL, dataWriting, (void*) &params);

	while (1)
  {
		sleep(5); // Cada 5 segundos se hace una lectura
		pthread_mutex_lock(&mutexData);
		data++;
		printf("Nuevos datos UAD %d\n", id);
		pthread_cond_signal(&newData);
		pthread_mutex_unlock(&mutexData);
	}
	pthread_join(thread, NULL);
}

int main(int argc, char** argv)
{
  int i;
	srand((int) time(NULL));
	pthread_t dataRegistry[N];
	pthread_t alarmRegistry[N];
	for (i = 0; i < N; ++i)
  {
		pthread_create(&dataRegistry[i], NULL, dataReading, (void*) (intptr_t) i);
		pthread_create(&alarmRegistry[i], NULL, alarmReading, (void*) (intptr_t) i);
	}

	for (i = 0; i < N; ++i)
  {
		pthread_join(dataRegistry[i], NULL);
		pthread_join(alarmRegistry[i], NULL);
	}
}
