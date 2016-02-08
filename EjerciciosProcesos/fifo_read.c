#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, const char * argv[])
{
    int fd;

    fd = open("/Users/mcolina/fifo", O_RDONLY);

    int i = -1;

    while (1) {
        read(fd, &i, sizeof(int));
        printf("%d\n", i);
    }

    close(fd);

    return 0;
}
