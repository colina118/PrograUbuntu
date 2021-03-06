#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void leer(int *fd);
void escribir(int *fd);
int factorial(int);

int main(int argc, const char * argv[])
{
    int tuberia[2];
    pid_t pid;

    pipe(tuberia);

    pid = fork();

    if (pid == -1)
    {
        printf("Error al crear el proceso hijo");
        exit(-1);
    }
    else if (pid == 0)
    {
        /* Hijo */

        printf(" Soy el hijo y estoy leyendo ... \n");

        leer(tuberia);
    }
    else {
        /* Padre */

        printf(" Soy el padre y estoy escribiendo ... \n");

        escribir(tuberia);
    }

    return 0;
}

void leer(int *fd)
{
    int c;

    while (1)
    {
      close(fd[1]);
      read(fd[0], &c, sizeof(int));
      printf("%d! = %d\n", c, factorial(c));
    }

}

void escribir(int *fd)
{
    int c;

    while (1) {
      printf("Entre un numero: \n");
      scanf("%d", &c);
      close(fd[0]);
      fprintf("Factorial es: %d \n", c);
      write(fd[1], &c, sizeof(int));
    }

}

int factorial(int n)
{
    int f = 2;
    int i = 3;

    if(n == 0 || n == 1)
    {
        return 1;
    }
    for(; i <=n; f*=i, ++i);
    return f;
}
