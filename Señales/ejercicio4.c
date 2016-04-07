#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

void manejador(int ids)
{
    printf("Estoy aprendiendo a manejar señales\n");
}

void manejador2(int ids)
{
  printf("Ahora cambie de manejador\n");
}

int main(int argc, char **argv)
{
  int i;

  struct sigaction gestor;

  if(signal(SIGINT, manejador) == SIG_ERR)
  {
    printf("ERROR: No se pudo establecer el manejador de senal\n");
  }
  for(i = 0; i <= 10; i++)
  {
    printf("Ovejita numero: %d\n", i);
    sleep(1);
  }
  gestor.sa_handler = manejador;
  if(signal(SIGINT, manejador2) == SIG_ERR)
  {
    printf("ERROR: No se pudo establecer el manejador de senal\n");
  }

  for(i = 0; i <= 10; i++)
  {
    printf("Trineo numero: %d\n", i);
    sleep(1);
  }

  if(signal(SIGINT, gestor.sa_handler) == SIG_ERR)
  {
    printf("ERROR: No se pudo establecer el manejador de senal\n");
  }

  for(i = 0; i <= 10; i++)
  {
    printf("Cabrita numero: %d\n", i);
    sleep(1);
  }

}
