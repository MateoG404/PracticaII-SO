#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define PATH "../data/hash_table.bin"
#define RECORD_SIZE sizeof(travel_t) 

unsigned int hash(int key);//funcion de hash

typedef struct
{
    int sourceid;//identificador del origen
    int dstid;//identificador del destino
    int hod;//hora del dial
    float mean_travel_time;//tiempo de viaje medio
    long int next_offset;//posicion del siguiente registro en la lista enlazada en el archivo
    int first;

} travel_t;

// función de hash
unsigned int hash(int key)
{
    return key;
}


// función para buscar un registro en la tabla hash
float buscar(int sourceid, int dstid, int hod){
    FILE *file;
    char *filename = PATH;
    float result = -1;//variable para almacenar el resultado de la busqueda

    // Abrir el archivo en modo de lectura binaria

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    int key = sourceid;
    unsigned int index = hash(key);
    travel_t record;//almacenar en memoria el registro que se va a leer

    fseek(file, index*RECORD_SIZE, SEEK_SET);//poner el puntero en la posicion del registro que se va a leer
    
    while (record.next_offset!=-1){
        fread(&record,sizeof(travel_t), 1, file);//leer el registro
        if(record.sourceid==sourceid && record.dstid==dstid && record.hod==hod){
            return record.mean_travel_time;
        }
        fseek(file, record.next_offset,SEEK_SET);
    }

    return -1;

}

