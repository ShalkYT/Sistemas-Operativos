/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas Operativos
* Tema: Implementación de Productor Consumidor a partir de pipe named
* Descripción:
*  - Servidor que recibe cadenas de texto desde un cliente a través de una pipe nombrada (FIFO),
**************************************************************************************************/

// Inclusion de los modulos necesarios
#include "modulo.h"

// Declaracion y nombramiento de la pipe
#define FIFO_FILE "/tmp/PIPE_COMUNICATOR"

int main() {
    // Declaracion de variables
    int fd;
    char readbuf[80];
    char end[10];
    int to_end;
    int read_bytes;

    // Creacion de la pipe
    mkfifo(FIFO_FILE, S_IFIFO|0640);
    // Inicializacion de variable end 
    strcpy(end, "end");
    // Apertura de la pipe en modo lectura y escritura
    fd = open(FIFO_FILE, O_RDWR);

    // Ciclo infinito para la lectura y escritura de la pipe
    while(1) {
        // Lectura de la pipe
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';
        // Impresion de la cadena recibida y su tamaño
        printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        // Comparacion de la cadena recibida con la cadena de fin para saber si se debe terminar el proceso
        to_end = strcmp(readbuf, end);
        // Condicion de salida del ciclo
        if (to_end == 0) {
            close(fd);
            break;
        }
        // Utilizacion de la funcion para invertir la cadena
        reverse_string(readbuf);
        // Impresion de la cadena invertida y su tamaño
        printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));
        // Escritura de la cadena invertida en la pipe
        write(fd, readbuf, strlen(readbuf));

        // Espera de 2 segundos para no saturar la consola y la pipe
        sleep(2);
    }
    // Fin de la funcion main
    return 0;
}


