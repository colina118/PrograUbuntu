#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

int rec[3];
int fuming[3];

pthread_mutex_t fumar = PTHREAD_MUTEX_INITIALIZER;

void* fumando(void* args)
{
  int fumador = (intptr_t)args;
  while(1)
  {
    pthread_mutex_lock(&fumar);
    if(rec[0] && rec[1] && rec[2])
    {
      rec[0] = 0;
      rec[1] = 0;
      rec[2] = 0;
      fuming[fumador] = 1;
      printf("Fumador %d esta fumando\n", fumador);
      pthread_mutex_unlock(&fumar);
      sleep(10);
      pthread_mutex_lock(&fumar);
      fuming[fumador] = 0;
      pthread_mutex_unlock(&fumar);
      sleep(20);
    }
    else
    {
      pthread_mutex_unlock(&fumar);
    }
  }
}

void* colectar(void* args)
{
  int i;
  while(1)
  {
    for(i=0;i<3;i++)
    {
        pthread_mutex_lock(&fumar);
        if(!fuming[i])
        {
          pthread_mutex_unlock(&fumar);
          sleep(3);
          pthread_mutex_lock(&fumar);
          rec[i]=1;
          if(i == 0)
          {
            printf("Fumador %d dando tabaco\n", i);
          }
          else if(i == 1)
          {
            printf("Fumador %d dando papel\n", i);
          }
          else if(i == 2)
          {
            printf("Fumador %d dando fosforos\n", i);
          }
        }
        pthread_mutex_unlock(&fumar);
    }
  }
}


int main(int argc, char** argv)
{
  int i;

  for(i=0;i< 3; i++)
  {
    fuming[i]=0;
    rec[i]=1;
  }

  pthread_t agente;
  pthread_create(&agente, NULL, colectar, NULL);
  pthread_t fumador[3];

  for(i=0;i<3;i++)
  {
    pthread_create(&fumador[i], NULL, fumando, (void*)(intptr_t)i);
  }
  for(i=0;i<3;i++)
  {
    pthread_join(fumador[i], NULL);
  }
  pthread_join(agente, NULL);
}
