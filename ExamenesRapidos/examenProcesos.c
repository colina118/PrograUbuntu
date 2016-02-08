#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>



int main(int argc, const char * argv[]) {

    int pid;
    int n;
    int i;
    int prom;

    printf("Entre un numero: \n");
    scanf("%d", &n);


    for(i =0; i < n; i++)
    {

        pid = fork();

        if (pid == -1)
        {
            printf("Error al crear el proceso hijo \n");
            printf("Se han creado %d hijos hasta ahora", i);
            break;
        }
        else if (pid == 0)
        {
            // Estamos en el hijo
            prom = (getpid() + getppid())/2;
            printf("%d \n", prom);
            exit(0);
        }
        else {
            wait(NULL);

        }
    }


    return 0;
}
