#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>


void manejador(int ids)
{
    printf("--- Oprimiste Ctrl+C ...\n");
}

void manejador_ctrlz(int ids)
{
  printf("Ctrl+Z no hace nada\n");
}

int main(int argc, char **argv)
{
  if(signal(SIGTSTP, manejador_ctrlz) == SIG_ERR)
  {
    printf("ERROR: No se pudo establecer el manejador de senal\n");
  }
  int pid;
  int estado;
  int i;
  pid = fork();
  if(pid == -1)
  {
    printf("Se produjo un error al crear al hijo");
  }
  else if(pid == 0)
  {
    if (signal(SIGINT, manejador) == SIG_ERR)
    {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
    }
    sleep(2);
    printf("Estamos en el proceso hijo con PID = %d y su padre es PPID = %d \n", getpid(), getppid());
    for(i = 10; i > 0; i--)
    {
      printf("%d\n",i);
      sleep(1);
    }
    exit(0);
  }
  else
  {
    printf("Si preciona Ctrl+C solo morira el padre");
    if (signal(SIGINT, SIG_DFL) == SIG_ERR)
    {
        printf("ERROR: No se pudo establecer el manejador de la señal\n");
    }
    printf("El pid del proceso padre es = %d \n", getpid());
    sleep(50);
    if (waitpid(pid, &estado, 0) != -1)
        {
            if (WIFEXITED(estado))
                printf("Ya terminó el hijo con PID %d con valor de retorno %d \n", pid, WEXITSTATUS(estado));
        }
  }
}
