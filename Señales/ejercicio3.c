#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

void manejador(int ids)
{
  if(ids == SIGTSTP)
  {
    printf("Se pulso Ctrl-Z\n");
  }
  else if(ids == SIGINT)
  {
    printf("Se pulso Ctrl-C\n");
  }

}

int main(int argc, char **argv)
{
  if (signal(SIGINT, manejador) == SIG_ERR)
  {
      printf("ERROR: No se pudo establecer el manejador de la señal\n");
  }
  if(signal(SIGTSTP, manejador) == SIG_ERR)
  {
      printf("ERROR: No se pudo establecer el manejador de la señal\n");
  }
  int i;

  for(i = 10; i > 0; i--)
  {
    printf("%d\n", i);
    sleep(1);
  }
}
