#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct pregunta
{
	char* pregu;
	char ** res;
}pregunta;

typedef struct persona
{
	char * nombre;
	int * edad;
	int * respuestas;
	int * respondido;
}persona;

// Funciones para reservar memoria
persona * agregarParticipante(persona * participantes, int cant);
pregunta * iniciarPregunta(pregunta * preguntas, int cant);

// Funciones para liberar memoria
void eliminarParticipantes(persona * p, int cant);
void eliminarPreguntas(pregunta * preguntas, int cant);

int main(int argc, char **argv)
{
	srand(time(NULL));
	pregunta * preguntas = NULL;
	persona * participantes = NULL;
	
	int cantParticipantes = 0;
	int cantPreguntas = 0;
	
	int opcion = -1;
	
	while(opcion != 0)
	{
		printf("1. Agregar Participante\n2. Poner preguntas y respuestas\n3. Listar Participantes\n4. Listar preguntas y posibles respuestas\n5. Responder preguntas (apleatorio)\n6. Histograma\n7. Histograma con edades\n0. Salir\n");

		scanf("%d", &opcion);
		switch(opcion)
		{
			case 1:
			{
				int edad;
				printf("Edad del participante: ");
				scanf("%d", &edad);
				
				if(edad >= 18 && edad <= 119)
				{
					participantes = agregarParticipante(participantes, cantParticipantes);
					*((participantes+cantParticipantes)->edad) = edad;
					printf("Escriba el nombre del aprticipante: ");
					scanf("\n%[^\n]", (participantes+cantParticipantes)->nombre);
					++cantParticipantes;					
				}
				else
				{
					printf("El participante debe ser mayor de 17 anos y menor de 120.\n");
				}
				
								
				
				break;
			}
			case 2:
			{
				if(cantPreguntas > 0)
				{
					printf("Ya se hicieron las preguntas.\n");
				}
				else
				{
					int k = 0;
					for(; k < 10; ++k)
					{
						preguntas = iniciarPregunta(preguntas, cantPreguntas);
						printf("Pregunta %d: ", k+1);
						scanf("\n%[^\n]", (preguntas+k)->pregu);
						int j = 0;
						for(; j < 6; ++j)
						{
							printf("Opcion de respuesta para la pregunta: ");
							scanf("\n%[^\n]", *((preguntas+k)->res+j));
						}
						++cantPreguntas;
					}
				}
				break;
			}
			case 3:
			{
				if(cantParticipantes == 0)
				{
					printf("No se ha registrado ningun participante\n");
				}
				else
				{
					int i = 0;
					for(; i < cantParticipantes; ++i)
					{
						printf("Participante %d:\n", i);
						printf("Nombre: %s\n", (participantes+i)->nombre);
						printf("Edad: %d\n", *(participantes+i)->edad);
						if(*(participantes+i)->respondido)
						{
							int j = 0;
							for(; j < 10; ++j)
							{
								printf("Respuesta a la pregunta %d: %d\n", j+1, *((participantes+i)->respuestas+j)+1);
							}
						}
						else
						{
							printf("Aun no ha respondido.\n" );
						}
						printf("\n");
					}
				}
				break;
			}
			case 4:
			{
				int i = 0;
				for(; i < 10; ++i)
				{
					printf("Pregunta %d: %s\n", i+1, (preguntas+i)->pregu);
					int j = 0;
					for(; j < 6; ++j)
					{
						printf("Respuesta %d: %s\n", j+1, *((preguntas+i)->res+j));
					}
				}
				break;
			}
			case 5:
			{
				if(cantParticipantes == 0)
				{
					printf("Aun no hay ningun participante\n");
				}
				else if(cantPreguntas == 0)
				{
					printf("Todavia no se ponen las preguntas.\n");
				}
				else
				{
					int i = 0;
					for(; i < cantParticipantes; ++i)
					{
						int j = 0;
						for(; j < 10; ++j)
						{
							*((participantes+i)->respuestas+j) = rand()%6;
						}
						*(participantes+i)->respondido = 1;
					}
				}
				break;
			}
			case 6:
			{
				int ** totales = (int**)malloc(10*sizeof(int*));
				int k = 0;
				for(; k < 10; ++k)
				{
					*(totales+k) = (int*)malloc(6*sizeof(int));
					int l = 0;
					for(; l < 6; ++l)
					{
						// Iniciar los totales en 0
						*(*(totales+k)+l) = 0;
					}
				}
				
				k = 0;
				for(; k < cantParticipantes; ++k)
				{
					int l = 0;
					for(; l < 10; ++l)
					{
						*(*(totales+l)+(*((participantes+k)->respuestas+l))) += 1;
					}
				}
				
				printf("Histograma: \n");
				int i = 0;
				for(; i < 10; ++i)
				{
					printf("Pregunta %d:\n", i+1);
					printf("Opcion\tTotal\tHistograma\n");
					int j = 0;
					for(; j < 6; ++j)
					{
						printf("%d\t%d\t", j+1, *(*(totales+i)+j));
						int r = 0;
						for(; r < *(*(totales+i)+j); ++r)
						{
							printf("%c", '*');
						}
						printf("\n");
					}
					
				}
				k = 0;
				for(; k < 10; ++k)
				{
					free(*(totales+k));
				}
				free(totales);
				break;
			}
			case 7:
			{
				int * edades = (int*)malloc(5*sizeof(int));
				char ** strings = (char**)malloc(5*sizeof(char*));
				int i;
				for(i = 0; i < 5; ++i)
				{
					*(edades+i) = 0;
					*(strings+i) = (char*)malloc(7*sizeof(char));
				}
				
				strcpy(*(strings), "18-25");
				strcpy(*(strings+1), "26-35");
				strcpy(*(strings+2), "36-45");
				strcpy(*(strings+3), "46-65");
				strcpy(*(strings+4), "65-119");
								
				for(i = 0; i < cantParticipantes; ++i)
				{
					int edad = *(participantes->edad);
					if(edad >= 18 && edad <= 25)
					{
						*(edades) += 1;
					}
					else if(edad >= 26 && edad <= 35)
					{
						*(edades+1) += 1;
					}
					else if(edad >= 36 && edad <= 45)
					{
						*(edades+2) += 1;
					}
					else if(edad >= 46 && edad <= 65)
					{
						*(edades+3) += 1;
					}
					else
					{
						*(edades+4) += 1;
					}
				}
				
				printf("Histograma edad\n");
				printf("Rango\tCantidad\tHistograma\n");
				int j;
				for(j = 0; j < 5; ++j)
				{
					printf("%s\t%d\t", *(strings+j), *(edades+j));
					int k;
					for(k = 0; k < *(edades+j); ++k)
					{
						printf("%c", '*');
					}
					printf("\n");
				}
				
				for(i = 0; i < 5; ++i)
				{
					free(*(strings+i));
				}
				free(strings);
				free(edades);
				break;
			}
			case 0:
			{
				printf("Adios gracias por utilizar el sistema de encuestas");
				break;
			}
		}
	}
	eliminarParticipantes(participantes, cantParticipantes);
	eliminarPreguntas(preguntas, cantPreguntas);
	return 0;
}


pregunta * iniciarPregunta(pregunta * preguntas, int cant)
{
	if(cant == 0)
	{
		preguntas = (pregunta *)malloc(sizeof(pregunta));
	}
	else
	{
		preguntas = realloc(preguntas, (cant+1)*sizeof(pregunta));
	}
	(preguntas+cant)->pregu = (char*)malloc(50*sizeof(char));
	(preguntas+cant)->res = (char**)malloc(6*sizeof(char*));
	int i = 0;
	for(; i < 6; ++i)
	{
		*((preguntas+cant)->res+i) = (char*)malloc(50*sizeof(char));
	}
	return preguntas;
}

persona * agregarParticipante(persona * participantes, int cant)
{
	if(cant == 0)
	{
		participantes = (persona *)malloc(sizeof(persona));
	}
	else
	{
		participantes = realloc(participantes, (cant+1)*sizeof(persona));
	}
	(participantes+cant)->edad = (int *)malloc(sizeof(int));
	(participantes+cant)->nombre = (char *)malloc(30*sizeof(char));
	(participantes+cant)->respuestas = (int *)malloc(10*sizeof(int));
	(participantes+cant)->respondido = (int *)malloc(sizeof(int));
	*(participantes+cant)->respondido = 0;
	return participantes;
}

void eliminarPreguntas(pregunta * preguntas, int cant)
{
	int i = 0;
	for(; i < cant; ++i)
	{
		int j = 0;
		for(; j < 6; ++j)
		{
			free(*((preguntas+i)->res+j));
		}
		free((preguntas+i)->res);
		free((preguntas+i)->pregu);
	}
	free(preguntas);
}



void eliminarParticipantes(persona * p, int cant)
{
	int i = 0;
	for(; i < cant; ++i)
	{
		free((p+i)->edad);
		free((p+i)->nombre);
		free((p+i)->respuestas);
		free((p+i)->respondido);
	}
	free(p);
}





