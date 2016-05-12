#include<stdio.h>
#include<stdlib.h>
#include<iterator>
#include<vector>
#include<signal.h>
#include<cstdlib>
#include <pthread.h>
#include <unistd.h>

#define N 4
#define T 4

std::vector<std::vector<int> > laberinto{N, std::vector<int>(N, 0)};

struct arg_struct {
    std::vector<std::vector<int> > lab{N, std::vector<int>(N, 0)};

    int arg2;
};

void* resolver(void* args);

void print(std::vector<std::vector<int> >);

void manejador(int ids)
{
  print(laberinto);
}

bool solve(int,int, std::vector<std::vector<int> > );

int main()
{
  //el manejador de señal esta comentado porque sino marca segmentation fault
  if (signal(SIGUSR1, manejador) == SIG_ERR)
  {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
  }

  int prob;
  bool completo=false;
  int r=0, c=0;
  for(int i=0; i < N; i++)
  {
    for(int j=0; j < N; j++)
    {
      prob = rand()%10;
      if(prob < 2)
      {
        laberinto[i][j]=1;
      }
      else
      {
        laberinto[i][j]=0;
      }
    }
  }
  print(laberinto);

  struct arg_struct args;
  std::copy(laberinto.begin(), laberinto.end(), args.lab.begin());

  pthread_t laberynth[T];

  for(int i=0; i < T; i++)
  {
    args.arg2 = i;
    pthread_create(&laberynth[i], NULL, resolver, (void *)&args);
  }

  /*for(int i=0; i < T; i++)
  {
    pthread_join(laberynth[i], NULL);
  }*/



}

void print(std::vector<std::vector<int> > lab)
{
  for(int i=0; i < N; i++)
  {
    for(int j=0; j < N; j++)
    {
      printf(" %d",lab[i][j]);
    }
    printf("\n");
  }
}

bool solve(int X, int Y, std::vector<std::vector<int> > lab)
{
    lab[Y][X] = 2;

    printf("\n");
    print(lab);



    if (X == N && Y == N)
    {
        return true;
    }


    if (X > 0 && lab[Y][X - 1] == 0 && solve(X - 1, Y, lab))
    {
        return true;
    }
    if (X < N && lab[Y][X + 1] == 0 && solve(X + 1, Y, lab))
    {
        return true;
    }
    if (Y > 0 && lab[Y - 1][X] == 0 && solve(X, Y - 1, lab))
    {
        return true;
    }
    if (Y < N && lab[Y + 1][X] == 0 && solve(X, Y + 1, lab))
    {
        return true;
    }

    lab[Y][X] = 0;


    return false;
}


void* resolver(void*args)
{
  struct arg_struct *argumentos = (struct arg_struct *)args;
  int n = argumentos->arg2;
  std::vector<std::vector<int> > laberin{N, std::vector<int>(N, 0)};
  std::copy(argumentos->lab.begin(), argumentos->lab.end(), laberin.begin());
  solve(n, n, laberin);

}
