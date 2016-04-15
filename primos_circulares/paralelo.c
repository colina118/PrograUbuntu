#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <omp.h>

#define N 10000
#define M 100

int primoCircular(int num)
{
  int rotado;
  int i;

  int tam = tamano(num);
  if(!primo(num))
  {
    return 0;
  }
  for(i=1; i < tam; i++)
  {
    rotado=(pow(10, tam-i) * (num%(int)pow(10, i))) + floor(num / pow(10, i));
    if(!primo(rotado))
    {
      return 0;
    }
  }
  return 1;
}

int primo(int num)
{
  int i;
  if(num/2)
  {
    return 0;
  }
  for(i = 2; i <= sqrt(num); i++)
  {
    if(num%i == 0)
    {
      return 0;
    }
  }
  return 1;
}

int tamano(int num)
{
  int cont = 0;
  while (num >= 1)
  {
    cont++;
    num /= 10;
  }
  return cont;
}

int main(int argv, char** argc)
{
  int i;
  int j;

  short** matrizNumeros = (short**) malloc(N * sizeof(short*));
	short** matrizPrimos = (short**) malloc(N * sizeof(short*));

  #pragma omp parallel shared(i, j, matrizPrimos, matrizNumeros)
  {
    int tid = omp_get_thread_num();
    #pragma omp for schedule(auto)

    for(i = 0; i < N; i++)
    {
      matrizNumeros[i] =(short*)malloc(N * sizeof(short*));
      matrizPrimos[i] = (short*)malloc(N * sizeof(short*));
      for(j = 0; j < N; j++)
      {
        matrizNumeros[i][j] = rand_r(&tid)%10000;
        matrizPrimos[i][j] = 0;
      }
    }

  }

  #pragma omp parallel shared(i, j, matrizPrimos, matrizNumeros)
  {
    #pragma omp for schedule(auto)

    for(i = 0; i < N; i++)
    {
      for(j = 0; j < N; j++)
      {
        if(primoCircular(matrizNumeros[i][j]))
        {
          matrizPrimos[i][j] = 1;
        }
      }
    }
  }

  for(i = 0; i < N; i++)
  {
    for(j = 0; j < N; j++)
    {
      if(primoCircular(matrizNumeros[i][j]))
      {
        matrizPrimos[i][j] = 1;
      }
    }
  }
}
