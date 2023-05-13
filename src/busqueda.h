#ifndef MI_LIB_H
#define MI_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define PATH "../data/hash_table.bin"
#define RECORD_SIZE sizeof(travel_t) 

unsigned int hash(int key); // Función de hash

typedef struct
{
    int sourceid;               // Identificador del origen
    int dstid;                  // Identificador del destino
    int hod;                    // Hora del día
    float mean_travel_time;     // Tiempo de viaje medio
    long int next_offset;       // Posición del siguiente registro en la lista enlazada en el archivo
    int first;

} travel_t;

unsigned int hash(int key); // Declaración de la función de hash

float find_record(FILE *file, int sourceid, int dstid, int hod); // Declaración de la función para buscar un registro en la tabla hash

float buscar(); // Declaración de la función buscar

#endif
