#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int espera = 0;

void manejador(int ids)
{
  printf("El comando CtrlC esta siendo ignorado");
}

void manejadorTiempo(int ids)
{
  espera = 1;
}

int main(int argc, const char * argv[])
{
  int param = atoi(argv[1]);
  if(argc < 2 || param <= 5 || param >= 9)
  {
    printf("Los parametros deben de estar entre 5 y 9");
    return 2;
  }

  int * arreglo = (int *)malloc(param * sizeof(int));
  int * i;
  int cont = 1;

  signal(SIGINT, manejador);
  signal(SIGALRM, manejadorTiempo);

  alarm(3);

  for(i = arreglo; i < arreglo + param; i++)
  {
    if(espera)
    {
      printf("Dese prisa. ");
    }
    printf("Dato %d:", cont);
    scanf("%d", i);
    printf("\n");
    cont++;
  }

  cont = 1;

  for(i = arreglo; i < arreglo + param; i++)
  {
    printf("Dato %d: %d\n", cont, *i);
    cont++;
  }

  free(arreglo);

  return 0;
}
