#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int tiempo = 3;
int contC = 0;
int contZ = 0;

void manejador(int ids)
{
	if (ids == SIGINT)
  {
		++tiempo;
		contC++;
	}
	else
  {
		contZ++;
		if (tiempo > 1)
			--tiempo;
	}
}

void manejadorFin(int ids)
{
	printf("Se ha pulsado %d veces Ctrl+C y %d veces Ctrl+Z. Terminando...\n", contC, contZ);
	kill(SIGKILL, 0);
	raise(SIGKILL);
}

void manejadorAlarma(int ids)
{
	printf("Aparezco cada %d segundos\n", tiempo);
}

int main(int argc, const char * argv[])
{
  int pid;
  pid = fork();

  if (pid == -1)
  {
  printf("Error al crear el proceso\n");
  return 1;
  }
  else if (pid == 0)
  {
		signal(SIGINT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		sleep(10);
		kill(getppid(), SIGUSR1);
	}
  else
  {
		signal(SIGUSR1, manejadorFin);
		signal(SIGINT, manejador);
		signal(SIGTSTP, manejador);
		signal(SIGALRM, manejadorAlarma);

		while (1) {
			alarm(tiempo);
			pause();
		}
	}
  return 0;
}
