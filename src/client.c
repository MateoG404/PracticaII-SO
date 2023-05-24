#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "interfaz.h"

int* input();

#define PORT 3535
#define serverIP "127.0.0.1"

int main(){

    // Definicion de variables

    int client_fd, r ; //  
    struct sockaddr_in serverAddress;



    printf("Inicio cliente\n");

    // Creacion socket cliente

    client_fd = socket(AF_INET,SOCK_STREAM,0);

    if (client_fd < 0 ){
        perror("Error creacion socket cliente \n");
        exit(-1);
    }
    
    // Configuracion del servidor para el cliente
    
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    
    // Convertir dirección IP a formato valido para serverAddress

    if (inet_pton(AF_INET, serverIP, &(serverAddress.sin_addr)) < 0 ){
        perror("Error configuracion servidor \n");
        exit(-1);
    }

    // Creación conexión cliente al servidor

    if (connect(client_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        perror("Error al conectar al servidor");
        exit(EXIT_FAILURE);
    }
    //Llamar a interfaz para pedir los datos al usuario
    int data[3];
    int *data2 = input();
    
    for (int i = 0; i < 3; i++)
    {
        data[i] = *(data2+i);
    }

    if(data[2] == 24){
        printf("El usuario ha salido del programa, se cerrará el cliente\n");
        close(client_fd);
    }else{
        // Envío de los datos al servidor
        if (send(client_fd, data, sizeof(data), 0) < 0) {
            perror("Error al enviar datos al servidor");
            exit(EXIT_FAILURE);
        }

        // Recibir datos
        char buffer[1024];

        r = recv(client_fd,buffer,sizeof(buffer),0);
        buffer[r] = 0 ;

        printf(buffer);
        // Cerrar la conexión
        close(client_fd);
    }

    return 0;
}
