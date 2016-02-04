#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define N 10

int main(int argc, char **argv)
{
  int i;
  int a=0, b=0, c=0;
  int * arreglo =(int *)malloc(N * sizeof(int));
  int pid, pid2;
  int estado;
  pid = fork();

  for(i =0; i < N; i++)
  {
    *(arreglo+i) = rand()%10;
  }

  /*for(i =0; i < 6; i++)
  {
    printf("%d",*(arreglo+i));
    printf("\n");
  }*/

  if (pid == -1)
  {
      printf("Error al crear el proceso hijo \n");
  }
  else if (pid == 0)
  {
      // Estamos en el hijo
      printf("Estamos en el primer hijo\n");
      for(i = 0; i < N/2; i++)
      {
          a +=*(arreglo+i);
      }
      for(i =0; i < N/2; i++)
      {
        printf("%d, ",*(arreglo+i));
      }
      printf("\n");
      free(arreglo);
      exit(a);
  }
  else
  {
    pid2 = fork();
    if(pid2 == -1)
    {
      printf("Error al crear el proceso hijo\n");
    }
    else if(pid2 == 0)
    {
        printf("Estamos en el segundo hijo\n");
        for(i =N/2; i < N; i++)
        {
          b +=*(arreglo+i);
        }
        for(i =N/2; i < N; i++)
        {
          printf("%d, ",*(arreglo+i));
        }
        printf("\n");
        free(arreglo);
        exit(b);
    }
    else
    {
      if (waitpid(pid2, &estado, 0) != -1)
        {
            if (WIFEXITED(estado))
                printf("Ya terminó el hijo con PID %d con valor de retorno %d \n", pid, WEXITSTATUS(estado));
                c += WEXITSTATUS(estado);
        }
    }
    if (waitpid(pid, &estado, 0) != -1)
      {
          if (WIFEXITED(estado))
              printf("Ya terminó el hijo con PID %d con valor de retorno %d \n", pid, WEXITSTATUS(estado));
              c += WEXITSTATUS(estado);
      }
  }

  printf("La suma total es = %d\n", c);
  printf("\n");
  free(arreglo);
}
