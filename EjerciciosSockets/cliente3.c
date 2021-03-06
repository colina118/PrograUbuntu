#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define TCP_PORT 8000

int main(int argc, const char * argv[])
{
    struct sockaddr_in direccion;
    char buffer[1000];

    int cliente;
    int random = -1;

    srand (time(NULL));

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

    if (escritos == 0)
    {
        printf("Conectado a %s:%d \n",
               inet_ntoa(direccion.sin_addr),
               ntohs(direccion.sin_port));

        // Escribir datos en el socket
        while (random != 0)
        {
            printf("entre una vez");
            random = rand()%10;
            write(cliente, &buffer, random);
            printf(random);
            /* Lee del buffer y escribe en pantalla */
        }
    }

    // Cerrar sockets
    close(cliente);

    return 0;
}
