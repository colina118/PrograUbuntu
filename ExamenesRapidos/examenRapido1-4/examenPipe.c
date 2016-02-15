#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void leer(int *fd, int *fd2, pid_t pid;);
void escribir(int *fd, int *fd2);


int main(int argc, const char ** argv)
{
  int c;
  int n;
  int i;

  int tuberia[2];
  pid_t pid;

  while((c = getopt(argc, argv, "n:")) != -1)
  {
    switch(c)
    {
      case 'n':
        n = atoi(optarg);
        break;
      default:
        return 1;
    }
  int * arregloPipes =(int *)malloc(n * sizeof(int));

  for(i = arregloPipes; i < arregloPipes+n; i++)
  {
    (i) = tuberia;
  }

  }
  for(i =arregloPipes; i < arregloPipes+n; i++)
  {
    pid = fork();
    if(pid == -1)
    {
      printf("hubo un error al crear al hijo\n");
      exit(-1);
    }
    else if(pid == 0)
    {
        leer(i, i+1, getpid());
    }

  }
  printf("%d", n);
}



void leer(int *fd, int *fd2, pid_t pid;)
{
    char c ='#';
    int fact;

    while (1)
    {
      close(fd[1]);
      read(fd[0], &c, sizeof(int));
      printf("soy el proceso con pid: %d y recibi al testigo %c", pid, c);
      sleep(5);
      close(fd2[0]);
      write(fd2[1], &c, sizeof(int));
      printf("soy el proceso padre con pid: %d y acabo de mandar el testigo", pid);
    }

}
