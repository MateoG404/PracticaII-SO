#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#include "search.h"

float search(int data[3]);
void log();
int main();
#define PORT 3535
#define BACKLOG 3
int main(){
    
    int server_id,r, client_id; 
    struct sockaddr_in serverAddress, clientAddress; // Conexión a servidor
    float resultado = -1;
    int sourceid,dstid,hod;

    // Creación del socket

    server_id = socket(AF_INET,SOCK_STREAM,0); 

    if (server_id < 0 ){
        perror("Error creación cliente");
        exit(-1);
    }

    // Configuracion del servidor por medio de BIND

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Escucha cualquier direccion IP
    serverAddress.sin_port = htons(PORT);
    bzero(serverAddress.sin_zero,8);

    r = bind(server_id,(struct sockaddr*)&serverAddress,sizeof(serverAddress));

    if (r < 0 ){
        perror("Error configuración servidor \n");
        exit(-1);
    }


    // Creación listen
    // Escuchar por conexiones entrantes máximo 3 conexiones entrantes en pila

    if (listen(server_id, BACKLOG) < 0) {
        perror("Error al escuchar por conexiones entrantes");
        exit(EXIT_FAILURE);
    }
    
    printf("Esperando conexiones entrantes...\n");
    while (1)
    {
        // Creación Accept
        // Aceptar conexiones de clientes entrantes

        socklen_t clientAddressLength = sizeof(clientAddress);
        client_id = accept(server_id, (struct sockaddr*)&clientAddress, &clientAddressLength);

        if (client_id < 0) {
            perror("Error al aceptar la conexión del cliente");
            exit(EXIT_FAILURE);
        }
        log();
        printf("Cliente conectado: %s:%d\n", inet_ntoa(clientAddress.sin_addr), ntohs(clientAddress.sin_port));
        

        // Recibir datos del cliente
        int data[3];

        if (recv(client_id, data, sizeof(data), 0) < 0) { // recibir datos
            perror("Error al recibir datos del cliente");
            exit(EXIT_FAILURE);
        }
        //Descomentar si desea ver los datos recibidos
        /*
        printf("Datos recibidos del cliente:\n");
        for (int i = 0; i < 3; i++) {
            printf("Dato %d: %d\n", i+1, data[i]);
        }*/


        resultado = search(data);
        //Descomentar si desea ver el resultado de la busqueda
        //printf("Resultado busqueda %f \n",resultado);   

        // Enviar datos al cliente  
        char message[1024];
        sprintf(message, "El tiempo medio de viaje es: %f\n", resultado);

        // Creación Send 
        if (send(client_id, message, strlen(message), 0) < 0) {
            perror("Error al enviar datos al cliente");
            exit(EXIT_FAILURE);
        }
        
        // Cerrar la conexión con el cliente
        close(client_id);
    }   
    close(server_id);
    return 0;
}
 
void log() {
    //Aca va la funcion de log de gestionar un archivo log
    //que se guarde la info en el formato [Fecha YYYYMMDDTHHMMSS] Cliente [IP] [búsqueda - origen - destino]
    return;
}