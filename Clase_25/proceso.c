/************************************************
* Autor: Andres Eduardo Meneses Rincon
* Fecha
* Materia
* Tema: Creacion de procesos con la biblioteca unistd.h
* la idea es crear procesos y ver su comportamiento
*************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char* argv[]){
	// El argumento de entrada sera el valor de procesos a publicar
	int x = atoi(argv[1]); // Transformacion de un ASCII a un int
	for(int i = 0; i < x ; i++){
		fork(); // Levanta o crea un proceso
		printf("Proceso con id %d \n", getpid()); // Imprimir el pid del proceso
	}
	return 0; // Fin del programa
}
