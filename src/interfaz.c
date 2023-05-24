#include <stdio.h>
#include <stdlib.h>
#include "interfaz.h" 

int* input(){
        
    /*Asignar a un puntero la direccion de la memoria compartida*/
    
    int op, end = 0;
    int* arrayData = NULL;

    arrayData = (int*) malloc(3 * sizeof(int));

    if (arrayData == NULL) {
        printf("Error: no se pudo asignar memoria");
        exit(1);
    }

    while(!end){
        /*Imprimir interfaz del home*/
        printf("Bienvenido\n"
                "1. Ingresar origen\n"
                "2. Ingresar destino\n"
                "3. Ingresar hora\n"
                "4. Buscar tiempo de viaje medio\n"
                "5. Salir\n");
        
        printf("Ingrese el número de la opción que desea realizar: ");
        scanf("%d", &op);

        switch(op){   
            /*Pedir al usuario que ingrese los datos y almacenarlos en las direcciones 0,1,2 de la memoria compartida*/
            case 1:
                printf("Ingrese ID del origen: ");
                scanf("%d", &arrayData[0]);
                errors((&arrayData[0]), 1, 1160);

                getchar(); //Getchar adicional para que consuma el "\n" del int escaneado
                printf("Presione cualquier tecla para continuar...\n");
                getchar();
                break;

            case 2:
                printf("Ingrese ID del destino: ");
                scanf("%d", &arrayData[1]);    
                errors(&arrayData[1], 1, 1160);

                getchar(); //Getchar adicional para que consuma el "\n" del int escaneado

                printf("Presione cualquier tecla para continuar...\n");
                getchar();
                break;

            case 3:
                printf("Ingrese hora: ");
                scanf("%d", &arrayData[2]);
                errors(&arrayData[2], 0, 23);

                getchar(); //Getchar adicional para que consuma el "\n" del int escaneado
                printf("Presione cualquier tecla para continuar...\n");
                getchar(); //solo funciona con enter
                break;

            case 4:
                getchar(); //Getchar adicional para que consuma el "\n" de la opcion elegida
                if (arrayData[0] != 0 || arrayData[1] != 0){
                    printf("Se realizará la busqueda con los datos dados\n ");

                    //printf("Origen: %d, Destino: %d, Hora: %d\n", arrayData[0], arrayData[1], arrayData[2]);
                    printf("Presione cualquier tecla para continuar...");
                    getchar(); //solo funciona con enter


                    return arrayData;
                }else{
                    printf("\nNo se han ingresado la totalidad de los datos necesarios para la busqueda\n\n ");
                    break;
                }
                

            case 5:
                printf("Saliendo del programa...\n");
                end = 1;
                arrayData[0] = 0;
                arrayData[1] = 0;
                arrayData[2] = 24;
                return arrayData;               

            default:
                printf("Opción inválida. Por favor, seleccione una opción válida.\n");
                printf("Presione cualquier tecla para continuar...");
                getchar(); //solo funciona con enter
                break;
        
        }
    }
};

void errors(int *value, int left, int right){
    while (*value<left || *value>right){
        printf("Error, ingrese un valor válido, entre %d y %d:", left, right);
        scanf("%d", value);
    }
}

