#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>



int main(int argc, const char * argv[])
{
    int fd;

    fd = open("/home/mcolina/fifo_sum", O_RDONLY);

    int i = -1;
    int suma = 0;
    while (read(fd, &i, sizeof(int))) {

        if(i != 0)
        {
          suma += i;
        }
        else
        {
          printf("El resultado de la suma es: %d", suma);
        }
    }

    close(fd);

    return 0;
}
