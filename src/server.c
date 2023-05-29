#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#include "search.h"

float search(int data[3]);
void archLog(char* addr, int* data, float res);
int main();

#define PORT 3535
#define BACKLOG 32

int main(){
    
    int server_id,r, client_id, num_clientes = 0; 
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
    // Escuchar por conexiones entrantes máximo 32 conexiones entrantes en pila

    if (listen(server_id, BACKLOG) < 0) {
        perror("Error al escuchar por conexiones entrantes");
        exit(EXIT_FAILURE);
    }
    
    printf("Esperando conexiones entrantes (max 32)...\n");
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
        char* clientIpAdd = inet_ntoa(clientAddress.sin_addr);
        printf("Cliente conectado: %s:%d\n", clientIpAdd, ntohs(clientAddress.sin_port));
        num_clientes ++;

        // Recibir datos del cliente
        int data[3];

        if (recv(client_id, data, sizeof(data), 0) < 0) { // recibir datos
            perror("Error al recibir datos del cliente");
            exit(EXIT_FAILURE);
        }
        //Descomentar si desea ver los datos recibidos
        
        /*printf("Datos recibidos del cliente:\n");
        for (int i = 0; i < 3; i++) {
            printf("Dato %d: %d\n", i+1, data[i]);
        }*/


        resultado = search(data);
        //Descomentar si desea ver el resultado de la busqueda
        //printf("Resultado busqueda %f \n",resultado);   

        //Creación del archivo log
        archLog(clientIpAdd, data, resultado);

        // Enviar datos al cliente  
        char message[1024];
        if(resultado < 0){
            sprintf(message, "Resultado busqueda: NA\n");  
        }else{
            sprintf(message, "El tiempo medio de viaje es: %f\n", resultado);
        }
        

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
 
void archLog(char* addr, int* data, float res) {
    //Aca va la funcion de log de gestionar un archivo log

    FILE *fileLog = fopen("../data/serverlog.txt", "r+"); //Se abre el archivo con permisos de lectura y escritura

    //Se verifica si existe el archivo
    if(fileLog == NULL){
        fileLog = fopen("../data/serverlog.txt", "w+");
    }
    fseek(fileLog, 0, SEEK_END);

    // obtener y formatear fecha como YYYYMMDDTHHMMSS
    time_t t = time(NULL);
    struct tm tiempoLocal = *localtime(&t);
    // El lugar en donde se pondrá la fecha y hora formateadas
    char fechaHora[70];
    // El formato. Mira más en https://en.cppreference.com/w/c/chrono/strftime

    char *formato = "%Y%m%dT%H%M%S";
    
    // Intentar formatear
    int bytesEscritos = strftime(fechaHora, sizeof fechaHora, formato, &tiempoLocal);
    if (bytesEscritos != 0) {

        char message[250];

        sprintf(message, "[Fecha %s] Cliente [%s] [Resultado búsqueda:%f - origen: %d - destino: %d]\n", fechaHora, addr, res, data[0], data[1]);
        // Revisar la cadena cómo se guarda en ubuntu en el archivo

        fwrite(message, sizeof(char), strlen(message) ,fileLog);       

    } else {
        printf("Error formateando fecha");
    }
    
    fclose(fileLog); 

    return;
}