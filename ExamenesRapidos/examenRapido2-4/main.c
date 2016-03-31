#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define TAQ 3
#define COMP 10
#define SALAS 3
#define LUGARES 50
#define THREADS 3000
#define BOLETOS 4

typedef struct complejo
{
    int id;
    sem_t * taq;
    int * asien;
    pthread_mutex_t * sal;
}complejo_t;

void * compraBoleto(void * param)
{
    complejo_t * complejos = (complejo_t *)param;
    int cont_sala = rand()%SALAS;
    int lugares;
    int boletos = (rand()%BOLETOS)+1;
    sem_wait(complejos->taq);
    pthread_mutex_lock((complejos->sal)+cont_sala);
    sleep(rand()%2);
    lugares = *((complejos->asien)+cont_sala);
    if(lugares-boletos >= 0)
    {
        *(complejos->asien+cont_sala) -= boletos;
        printf("Cliente %lu compró %d boletos en la sala %d en el cine %d, quedan %d boletos\n",
            pthread_self(), boletos, cont_sala, complejos->id, lugares-boletos);
    }
    else
    {
        printf("Cliente %lu no alcanzo %d boletos en la sala %d en el cine %d, quedan %d boletos\n",
            pthread_self(), boletos, cont_sala, complejos->id, lugares);
    }
    pthread_mutex_unlock((complejos->sal)+cont_sala);
    sem_post(complejos->taq);

    return NULL;
}

int main(int argc, char * argv[])
{
    srand(time(NULL));
    // Reservar memoria
    int i;
    complejo_t * complejos = (complejo_t *) malloc(COMP * sizeof(complejo_t));
    pthread_t * threads = (pthread_t *) malloc(THREADS*sizeof(pthread_t));
    for(i = 0; i < COMP; ++i)
    {
        (complejos+i)->taq = (sem_t *) malloc(TAQ*sizeof(sem_t));
        (complejos+i)->asien = (int *) malloc(SALAS*sizeof(int));
        (complejos+i)->sal = (pthread_mutex_t *) malloc(SALAS*sizeof(pthread_mutex_t));
        (complejos+i)->id = i;
        int j;
        for(j = 0; j < SALAS; ++j)
        {
            *((complejos+i)->asien+j) = LUGARES;
            pthread_mutex_init((complejos+i)->sal+j, NULL);
        }
        sem_init((complejos+i)->taq, 0 , TAQ);
    }

    // Lanzar threads
    for(i = 0; i < THREADS; ++i)
    {
        pthread_create(threads+i, NULL, compraBoleto, complejos+(rand()%COMP));
    }


    // Esperar a todas las threads
    for(i = 0; i < THREADS; ++i)
    {
        pthread_join(*(threads+i), NULL);
    }

    // Liberar memoria
    for(i = 0; i < COMP; ++i)
    {
        free((complejos+i)->taq);
        free((complejos+i)->asien);
        free((complejos+i)->sal);
    }
    free(complejos);
    free(threads);
    return 0;
}
