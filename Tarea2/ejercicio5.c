#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <ctype.h>


int main(int argc, char** argv)
{
  char* p;
  int n;
  int pid;
  int c;
  int i;
  int estado;

  while((c = getopt(argc, argv, "n:p:")) != -1)
  {
    switch(c)
    {
      case 'n':
        n = atoi(optarg);
        break;
      case 'p':
        p = optarg;
        break;
      default:
        return 1;
    }
  }


  for(i = 0; i < n; i++)
  {
      pid = fork();
      if(pid == -1)
      {
        printf("Hubo un error en el programa");
        return 2;
      }
      else if(pid == 0)
      {
        execlp(p, p, (char *)NULL);
        exit(0);
      }
  }

  while(n > 0)
  {
    printf("Termino el proceso %d\n", wait(&estado));
    --n;
  }

  return 0;
}
