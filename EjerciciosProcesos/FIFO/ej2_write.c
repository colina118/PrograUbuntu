#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[])
{
    int error = mkfifo("/home/mcolina/fifo_sum", 0777);

    if (error) {
        printf("Error al crear el FIFO\n");
        exit(-1);
    }

    int fd = open("/home/mcolina/fifo_sum", O_WRONLY);

    int num = -1;

    while (num != 0) {
        printf("Entre un numero\n");
        scanf("%d", &num);
        write(fd, &num, sizeof(int));
    }

    close(fd);
    unlink("/home/mcolina/fifo_sum");

    return 0;
}
