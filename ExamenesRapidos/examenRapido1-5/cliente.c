#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TCP_PORT 8000

int main(int argc, const char * argv[])
{
    struct sockaddr_in direccion;
    char buffer[1000];
    int i = -1, cont=1, j;
    int periodo;
    int cliente;

    clock_t start;

    int * lecturas =(int *)malloc(1*sizeof(int));

    ssize_t leidos, escritos;

    if (argc != 2) {
        printf("Use: %s IP_Servidor \n", argv[0]);
        exit(-1);
    }

    // Crear el socket
    cliente = socket(PF_INET, SOCK_STREAM, 0);

    // Establecer conexión
    inet_aton(argv[1], &direccion.sin_addr);
    direccion.sin_port = htons(TCP_PORT);
    direccion.sin_family = AF_INET;

    escritos = connect(cliente, (struct sockaddr *) &direccion, sizeof(direccion));

    if (escritos == 0) {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));
    while(i != 0)
    {
      start = clock();
      periodo = rand()%10;
      cont = 1;
        while((int)start-clock() >= periodo)
        {
          realloc(lecturas, cont*sizeof(int));
          *(lecturas+cont) = rand()%5;
          cont++;
          usleep(50);
        }

        for(j = 0; j < cont; j++)
        {
          if(*(lecturas+j) != 0)
          {
            break;
          }
        }

        if(j == cont)
        {
          i = 0;
        }
        // Escribir datos en el socket
        while (cont > 0)
        {
            write(cliente, &buffer, *(lecturas+cont));
        }
    }
  }

    // Cerrar sockets
    close(cliente);

    return 0;
}
