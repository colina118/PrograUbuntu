#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	int edad;
	char* nombre;
	char* apellido;
	char* telefono;
}persona;

typedef struct
{
	int numero;
	int ocupada;
	persona* ocupante;
}cama;

void agregarPaciente(cama *pers, int num);
int agregarCamas(cama** camas, int** available, int numCamas, int* numDisponible, int n);
int agregarDisponible(int** available, int id, int total);
int encontrarDisponible(int** available, int* total);
char* consigueString(char* car, int tam);
void printCama(cama* camas, int actual);
void listaDePacientes(cama* camas, int numCamas);
void darDeAlta(cama* camas, int actual, int** available, int* numDisponible);
void liberaMemoria(cama* camas, int numCamas);

int main(int argc, char **argv)
{
	int opcion = -1;
	int numCamas = 0;
	int actual;
	int numDisponible = 0;
	cama * camas =NULL;
	int* available = NULL;
	int pacPorCama;
	int i;
	
	numCamas = agregarCamas(&camas, &available, numCamas, &numDisponible, 3);
	
	while(opcion != 0)
	{
		printf("1.Incorporar Paciente\n2.Paciente por Cama\n3.Dar de alta Paciente\n4.Listar Paciente\n5.Camas Disponibles\n0.Salir\n");
		scanf("%d", &opcion);
		switch(opcion)
		{
			case 1:
			{
				if (numDisponible == 0)
				{
					
					numCamas = agregarCamas(&camas, &available, numCamas, &numDisponible, 5);
				}
				actual = encontrarDisponible(&available, &numDisponible);
				agregarPaciente(camas, actual);
			break;
			}
			case 2:
			{
				printf("Que id de cama desea buscar");
				scanf("%d", &actual);
				getchar();
				if (actual >= 1 && actual <= numCamas)
				{
					printCama(camas, actual);
				}
				else 
				{
					printf("No hay una cama con ese ID\n");
					return -1;
				}
				break;
			}
			case 3:
			{
				printf("Que id de cama se dara de baja");
				scanf("%d", &actual);
				getchar();
				if (actual >= 1 && actual <= numCamas)
				{
					darDeAlta(camas, actual, &available, &numDisponible); 
				}
				else
				{
					printf("Esa cama no existe");
				}
				break;
			}
			case 4:
			{
				listaDePacientes(camas, numCamas);			
				break;
			}
			case 5:
			{
				printf("Camas disponibles: %d\n", numDisponible);
				printf("Camas no disponibles: %d\n", numCamas - numDisponible);
				break;
			}
			case 0:
			{
				printf("Adios gracias por utilizar el sistema\n");
				break;
			}
			default:
			{
				printf("esa opcion no es valida");
				break;
			}
		}
		
	}
	
	liberaMemoria(camas, numCamas);
	free(available);
	free(camas);
	return 0;
}

void agregarPaciente(cama* pers, int actual)
{
	cama* p = pers + actual -1;
	
	p->ocupante = (persona*) malloc(sizeof(persona));

	p->ocupante->nombre =(char *)malloc(30*sizeof(char));
	p->ocupante->apellido =(char *)malloc(30*sizeof(char));
	p->ocupante->telefono =(char *)malloc(30*sizeof(char));
	getchar();
	printf("Introduzca el telefono del paciente: ");
	consigueString(p->ocupante->telefono, 30);
	printf("Introduzca la edad del paciente\n");
	scanf("%d", &p->ocupante->edad);
	getchar();
	printf("Introduzca el nombre del paciente\n");
	consigueString(p->ocupante->nombre, 30);
	printf("Introduzca el apellido del paciente\n");
	consigueString(p->ocupante->apellido, 30);
	printf("Al paciente se le asigno la cama: %d \n", actual);
	return;
}



char* consigueString(char* car, int tam) 
{
	fgets(car, tam, stdin);
	*(car + strcspn(car, "\n")) = 0;
}

void printCama(cama* camas, int actual) 
{
	cama* c = camas + actual - 1;
	if (c->ocupante)
	{	
		printf("Paciente: \n");
		printf("Nombre: %s \n", c->ocupante->nombre);
		printf("Apellido: %s \n", c->ocupante->apellido);
		printf("Telefono: %s \n", c->ocupante->telefono);
		printf("Edad: %d \n", c->ocupante->edad);
	}
	else
	{
		printf("No hay paciente en esa cama\n");
	}
}

int agregarDisponible(int** available, int id, int total) 
{
	*available = realloc(*available, (total + 1) * sizeof(int));
	*(*available + total) = id;
	return total + 1;
}

int encontrarDisponible(int** available, int* total) 
{
	int id = *(*available + --(*total));
	*available = realloc(*available, *total * sizeof(int));
	return id;
}

int agregarCamas(cama** camas, int** available, int numCamas, int* numDisponible, int n)
 {
	*camas = realloc(*camas, (numCamas+n) * sizeof(cama));
	cama *c, *end = *camas + numCamas + n;

	for (c = *camas + numCamas; c < end; ++c) 
		{
		c->numero = ++numCamas;
		c->ocupante = NULL;
		*numDisponible = agregarDisponible(available, c->numero, *numDisponible);
	}
	return numCamas;
}

void listaDePacientes(cama* camas, int numCamas) 
{
	cama* c;
	for (c = camas; c < camas + numCamas; ++c)
	{
		if (c->ocupante)
		{	
			printf("Cama: %d \n", c->numero);
			printf("Nombre: %s \n", c->ocupante->nombre);
			printf("Apellido: %s \n", c->ocupante->apellido);
			printf("Telefono: %s \n", c->ocupante->telefono);
			printf("Edad: %d \n", c->ocupante->edad);
		}
	}
}

void darDeAlta(cama* camas, int actual, int** available, int* numDisponible)
{
	cama * c = camas + actual -1;
	free(c->ocupante->nombre);
	free(c->ocupante->apellido);
	free(c->ocupante->telefono);
	free(c->ocupante);
	c->ocupante = NULL;
	*numDisponible = agregarDisponible(available, actual, *numDisponible);

	printf("Se dio de baja exitosamente\n");
}

void liberaMemoria(cama* camas, int numCamas)
{
	cama* c;
	for(c = camas; c < camas + numCamas; ++c)
	{
		if(c->ocupante)
		{
			free(c->ocupante->nombre);
			free(c->ocupante->apellido);
			free(c->ocupante->telefono);
			free(c->ocupante);
		}
	}
}









