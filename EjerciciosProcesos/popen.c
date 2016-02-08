#include <stdio.h>

int main(int argc, const char * argv[])
{

    FILE * file;
    int i = 0;

    file = popen("cat", "w");

    while(1)
    {
        fprintf(file, "%d\n", ++i);
    }

    pclose(file);

    return 0;
}
