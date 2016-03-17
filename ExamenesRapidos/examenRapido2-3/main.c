#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define N 10
#define N2 5

sem_t sem_generales;
sem_t sem_empresariales;

void* general(void*);
void* empresarial(void*);

struct empresarial
{
	int id;
	int cont;
	int id_u;

};				/* ----------  end of struct empresarial  ---------- */
typedef struct empresarial Empresarial;


struct general
{
	int id;
	int cont;
	int id_u;
};				/* ----------  end of struct general  ---------- */
typedef struct general General;

int main() {
	sem_init(&sem_generales, 0, 5);
	sem_init(&sem_empresariales, 0, 3);

	srand((int) time(NULL));
	pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));
	pthread_t* aux;
	int i;

	for (aux = threads, i = 0; aux < (threads + N); ++aux, ++i) {
		pthread_create(aux, NULL, general, (void*) i);
	}

	for (aux = threads; aux < (threads + N2); ++aux) {
		pthread_create(*aux, NULL, empresarial, (void*) i);
	}

	sem_destroy(&sem_generales);
	sem_destroy(&sem_empresariales);

	free(threads);
	return 0;
}

void* general(void* p)
{
	int id = (int) p;
	sem_wait(&sem_generales);
	printf("El id del cliente es %d\n", id);
	sleep((rand() % 16) + 5);
	printf("Acabé de atender%d\n", id);
	sem_post(&sem_generales);

	pthread_exit(NULL);
}

void* empresarial(void* p)
{
  int id = (int) p;
	sem_wait(&sem_empresariales);
	printf("El id del cliente es %d\n", id);
	sleep((rand() % 16) + 5);
	printf("Acabé de atender%d\n", id);
	sem_post(&sem_empresariales);

	pthread_exit(NULL);
}
