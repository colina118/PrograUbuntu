#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>

int generateChild(int n, int p, int cont);

int main(int argc, char** argv)
{
  int p;
  int n;
  int c;

  while((c = getopt(argc, argv, "n:p:")) != -1)
  {
    switch(c)
    {
      case 'n':
        n = atoi(optarg);
        break;
      case 'p':
        p = atoi(optarg);
        break;
      default:
        return 1;
    }
  }


  generateChild(n, p, 0);
  return 0;
}

int generateChild(int n, int p, int cont)
{
  if(cont++ < n)
  {
    int *arregloProcesos =(int*) malloc(p * sizeof(int));
    int estado;
    int *i;

    for(i = arregloProcesos; i < arregloProcesos + p; i++)
    {
      *i = fork();
      if(*i == -1)
      {
        printf("Se ocaciono un error");
        return 2;
      }
      else if( *i ==0)
      {
        generateChild(n, p, cont);
        exit(0);
      }
    }

    int temp = p;

    while(temp > 0)
    {
      wait(&estado);
      --temp;
    }

    for(temp = 1; temp < cont; temp++)
    {
      printf("*****");
    }

    printf("%d======>", getpid());

    for(i = arregloProcesos; i < arregloProcesos + p; i++)
    {
      printf("%d ", *i);
    }

    printf("\n");

    free(arregloProcesos);
  }
}
