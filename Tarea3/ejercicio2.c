#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define Iteraciones 5
#define Tiempo 3

int grabar = 1;

void manejador(int ids)
{
  grabar = 0;
}

int main(int argc, const char * argv[])
{
  int i;
  int fd;
  int length;
  struct stat arch;
  length = ((Iteraciones-1 / 10)+9);
  char * archivo =(char *)malloc(length * sizeof(char));

  signal(SIGALRM, manejador);

  DIR* directorio = opendir("datos");
	if (directorio)
  {
		system("rm -R datos");
		closedir(directorio);
	}
	system("mkdir datos");

  for(i = 0; i < Iteraciones; i++)
  {
    grabar = 1;
		snprintf(archivo, length, "datos/a%d", i); // Nombre del archivo
		fd = open(archivo, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    alarm(Tiempo);

    while (grabar)
    {
			write(fd, "x", sizeof(char));
    }

    fstat(fd, &arch);
    printf("a%d   %d\n", i, (int)arch.st_size);

    close(fd);
  }

  free(archivo);
  return 0;
}
