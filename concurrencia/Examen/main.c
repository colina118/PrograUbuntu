#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <pthread.h>

int tabacoA=0, papelA=0, fosforoA=0;
int tabacoB=0, papelB=0, fosforoB=0;
int tabacoC=0, papelC=0, fosforoC=0;
int recT=0, recP=0, recF=0;

pthread_mutex_t fumadorA = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fumadorB = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t fumadorC = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mesa = PTHREAD_MUTEX_INITIALIZER;

void* fumar(void* args)
{
  int id=(int) args;
  while(true)
  {
    if(tabacoA==1 && papelA==1 && fosforoA==1 && id == 1)
    {
      pthread_mutex_lock(&fumadorA);
      printf("El fumador A esta fumando\n");
      tabacoA=0;
      papelA=0;
      fosforoA=0;
      sleep(10);
      pthread_mutex_unlock(&fumadorA);
      sleep(20);
    }
    else if(tabacoB==1 && papelB==1 && fosforoB==1 && id == 2)
    {
      pthread_mutex_lock(&fumadorB);
      printf("El fumador B esta fumando\n");
      tabacoB=0;
      papelB=0;
      fosforoB=0;
      sleep(10);
      pthread_mutex_unlock(&fumadorB);
      sleep(20);
    }
    else if(tabacoC==1 && papelC==1 && fosforoC==1 && id == 3)
    {
      pthread_mutex_lock(&fumadorC);
      printf("El fumador C esta fumando \n");
      tabacoC=0;
      papelC=0;
      fosforoC=0;
      sleep(10);
      pthread_mutex_unlock(&fumadorC);
      sleep(20);
    }
    else
    {
      int ran = rand()%3;
      if(ran == 1)
      {
        if(pthread_mutex_trylock(&mesa) != 0)
        {
          tabacoA=1;
          papelA=1;
          fosforoA=1;
        }
        else
        {
            pthread_mutex_unlock(&mesa);
        }
      }
      else if(ran == 2)
      {
        if(pthread_mutex_trylock(&mesa) != 0)
        {
          tabacoB=1;
          papelB=1;
          fosforoB=1;
        }
        else
        {
            pthread_mutex_unlock(&mesa);
        }
      }
      else if(ran == 3)
      {
        if(pthread_mutex_trylock(&mesa) != 0)
        {
          tabacoC=1;
          papelC=1;
          fosforoC=1;
        }
        else
        {
            pthread_mutex_unlock(&mesa);
        }
      }
    }
  }
}

void colectar(void* args)
{
  while(true)
  {
    if(recT==0 && recP==0 && recF==0)
    {
      pthread_mutex_lock(&mesa);
      if(pthread_mutex_lock(&fumadorA)==0)
      {
        recT=1;
        printf("Agente pidiendo tabaco\n")
        pthread_mutex_unlock(&fumadorA);
      }
      if(pthread_mutex_lock(&fumadorB)==0)
      {
        recP=1;
        printf("Agente pidiendo papel\n")
        pthread_mutex_unlock(&fumadorB);
      }
      if(pthread_mutex_lock(&fumadorC)==0)
      {
        recF=1;
        printf("Agente pidiendo tabaco\n")
        pthread_mutex_unlock(&fumadorC);
      }

    }
  }
}

int main(int argc, char** argv)
{

}
