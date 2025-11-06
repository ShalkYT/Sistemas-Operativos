/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas Operativos
* Tema: Uso de interfaz de creacion de hilos PTRHEAD
* Descripción:
**************************************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static void *funcion(void *arg){
	int tarea = *(int*)arg;
	printf("TAREA: %d \n", tarea);
	return NULL;
}

int main(int argc, char *argv[]){
	if(argc < 2){
		printf("\t $\ejecutable NUM\n");
		exit(0);
	}
	int n = (int) atoi(argv[1]);
	int tareas[n];
	pthread_t hilos[n];

	for(int i = 0; i<n; i++){
		tareas[i] = i;
		pthread_create(&hilos[i], NULL, funcion, tareas+i);
	}

	for(int i = 0; i<n; i++){
		pthread_join(hilos[i], NULL);
	}

	return 0;
}

