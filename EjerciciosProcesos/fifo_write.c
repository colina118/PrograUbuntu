#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[])
{

    int error = mkfifo("/Users/mcolina/fifo", 0777);

    if (error) {
        printf("Error al crear el FIFO\n");
        exit(-1);
    }

    int fd = open("/Users/vcubells/fifo", O_WRONLY);

    int i = 0;

    while (i++ < 10) {
        write(fd, &i, sizeof(int));
    }

    close(fd);
    unlink("/Users/vcubells/fifo");

    return 0;
}
