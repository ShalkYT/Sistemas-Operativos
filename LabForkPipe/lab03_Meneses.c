/*********************************************
* Pontificia universidadjaveriana *
* Autor: Andres Eduardo Meneses Rincon *
* Fecha: 9/10/2025 *
* Materia: Sistemas operatvos *
* Tema: 
*	- Identificacion de pocesos padre e hijo
	- Procesos duplicados
	- Comunicacion entre procesos con pipe sencillo
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){

	// Creacion de tuberia de comunicacion
	int pipefd[2];
	pid_t pHijo_PID; // Id del hijo como el proceso

	// Verificacion si del pipe
	if(pipe(pipefd) == -1){
		perror("PIPE");
		exit(EXIT_FAILURE);
	}

	// Se invoca la creacion del proceso en un entero para identificarlo
	pHijo_PID = fork();

	// Verificacion de creacion del proceso en un int para verificar
	if(pHijo_PID == -1){
		perror("FORK");
		exit(EXIT_FAILURE);
	}

	// Se duplica el proceso
	if(pHijo_PID == 0) { // Si el fork() retorna un 0 este proceso es el hijo
		close(pipefd[1]); // Cerrar la salida para lectura
		char mensaje[100]; // Capacidad del lector de caracteres
		int lecturaB = read(pipefd[0], mensaje, sizeof(mensaje)); // Recepcion del mensaje utilizando la funcion read() y la tuberia

		// Verificacion de lectura del mensaje
		if(lecturaB == -1){ // Verificacion de error al leer el mensaje
			perror("LECTURA");
			exit(EXIT_FAILURE);
		}
		printf("Hijo recibe: %.*s \n", lecturaB, mensaje); // Confirmacion de la recepcion del mesaje por parte del hijo
		close(pipefd[0]); // Cerrar entrada
	}else{
		close(pipefd[0]); // Cerrar entrada
		char mensaje[] = "Hijo trae el pan y las gaseosas, porfavor"; // Mensaje que el padre le va a enviar al hijo
		int escrituraB = write(pipefd[1], mensaje, sizeof(mensaje)); // Envio del mensaje utilizando la funcion write() y la tuberia
		// Verificacion de escritura del mensaje
		if(escrituraB == -1){ // Verificacion de error all escribir
			perror("ESCRITURA");
			exit(EXIT_FAILURE);
		}
		printf("El padre ya le escribio al hijo\n"); // Confirmacion de que el padre envio el mensaje
		close(pipefd[1]); // Cerrar salida
	}

	// Finalizacion del programa
	printf("Fin del programa\n\n");
	return 0;
}
