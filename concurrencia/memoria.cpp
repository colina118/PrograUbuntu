#include <stdio.h>
#include <pthread.h>

pthread_key_t var;


void destructor(void* args)
{
	delete args;
}

void * Hilo1(void * id)
{
	char* valor;
	int res;

	if((valor = (char*)pthread_getspecific(var)) == NULL)
	{
		valor = new char[10];
		sprintf(valor, "hola");
	}
	res = pthread_setspecific(var, (void*)valor);

	printf("En el hilo 1 var = %s \n", (char *) pthread_getspecific(var));
	printf("TID1 en hilo 1 = %ld\n", pthread_self());
}


void * Hilo2(void * id)
{
	int* valor;
	int res;

	if((valor = (int*)pthread_getspecific(var)) == NULL)
	{
		valor = new int(50);
	}
	res = pthread_setspecific(var, (void*)valor);

	printf("En el hilo 2 var = %i \n", *(int*) pthread_getspecific(var));
	printf("TID1 en hilo 2 = %ld\n", pthread_self());
}

int main(int argc, char **argv)
{
	pthread_t tid1, tid2;

	pthread_key_create(&var, destructor);

	pthread_create(&tid1, NULL, Hilo1, (void *) &var);
	printf("TID1 = %ld\n", tid1);

	pthread_create(&tid2, NULL, Hilo2, (void *) &var);
	printf("TID2 = %ld\n", tid2);

	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	return 0;
}
