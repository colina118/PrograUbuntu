#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main(int argc, char **argv)
{
  int num;
  int *pid;
  int estado;


  printf("escriba la cantidad de hijos a crear\n");
  scanf("%d", &num);
  int * arregloProcesos =(int *)malloc(num * sizeof(int));

  for(pid = arregloProcesos; pid < arregloProcesos + num; pid++)
  {
    *pid = fork();
    if(*pid == -1)
    {
      printf("se produjo un error\n");
    }
    else if(*pid == 0)
    {
      sleep(rand() % 20);
      exit(0);
    }

  }
  while(num > 0)
  {
    printf("Termino el proceso %d\n", wait(&estado));
    --num;
  }

  free(arregloProcesos);

}
