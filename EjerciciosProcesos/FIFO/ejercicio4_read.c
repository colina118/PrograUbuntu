#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int factorial(int n);

int main(int argc, const char * argv[])
{
    int fd;

    fd = open("/home/mcolina/fifo_fac", O_RDONLY);

    int i = -1;

    while (1) {
        read(fd, &i, sizeof(int));
        if(i == 0)
        {
          break;
        }
        printf("%d\n", factorial(i));
    }

    close(fd);

    return 0;
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
