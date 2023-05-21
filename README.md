# Segunda práctica de Sistemas Operativos 2023-I

## Código para compilar y ejecutar el programa

Esto hay que cambiarlo por un make que haga todo, por ahora para ejecutar el programa se debe hacer lo siguiente:

### Ejecutar el servidor


```console
user@bar:~$ gcc server.c search.c -o ../bin/server
user@bar:~$ ../bin/server
```

Para detener el servidor oprima Ctrl+C.
### Ejecutar un cliente

```console
user@bar:~$ gcc client.c interfaz.c -o ../bin/client
user@bar:~$ ../bin/client
```
# Integrantes 

* Mateo Gutiérrez Melo -mgutierrezca@unal.edu.co
* Jhon Jairo Silva Zabala -jhsilvaz@unal.edu.co
* Laura Andrea Castiblanco Suarez - lcastiblancos@unal.edu.co