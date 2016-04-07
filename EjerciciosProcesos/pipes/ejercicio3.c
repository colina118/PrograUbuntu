#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void leer(int *fd, int *fd2);
void escribir(int *fd, int *fd2);
int factorial(int);

int main(int argc, const char * argv[])
{
    int tuberia[2];
    int tuberiaReg[2];
    pid_t pid;

    pipe(tuberia);
    pipe(tuberiaReg);

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

        leer(tuberia, tuberiaReg);
    }
    else {
        /* Padre */

        printf(" Soy el padre y estoy escribiendo ... \n");

        escribir(tuberia, tuberiaReg);
    }

    return 0;
}

void leer(int *fd, int *fd2)
{
    int c;
    int fact;

    while (1)
    {
      close(fd[1]);
      read(fd[0], &c, sizeof(int));
      fact = factorial(c);
      close(fd2[0]);
      write(fd2[1], &fact, sizeof(int));
    }

}

void escribir(int *fd, int *fd2)
{
    int c = -1;
    int fact;

    while (c != 0) {
      printf("Entre un numero: \n");
      scanf("%d", &c);
      close(fd[0]);
      fprintf("Factorial es: %d \n", c);
      write(fd[1], &c, sizeof(int));
      close(fd2[1]);
      read(fd2[0], &fact, sizeof(int));
      printf("Factorial es = %d\n", fact);
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
