/*********************************************
* Pontificia universidadjaveriana *
* Autor: Andres Eduardo Meneses Rincon *
* Fecha: 9/10/2025 *
* Materia: Sistemas operatvos *
* Tema: 
*	- Identificacion de pocesos padre e hijo
	- Procesos duplicados
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	// Se invoca la creacion del proceso en un entero para identificarlo
	int proccesID = fork();
	printf("\n\nInicio del programa principal\n"); // Mensaje para mostrar informar del inicio del programa

	// Se duplica el proceso
	if(proccesID == 0) { // Si el fork() retorna un 0 este proceso es el hijo
		printf("fork() devuelve 0, ese es el proceso hijo con ID:%d \n\n", getpid()); // Mensaje para identificar al hijo

		// Le asignamos una tarea al hijo
		for(int i = 5; i<=10; i++){ // ciclo de 5 a 9
			printf("Ciclo Padre: %d\n", i); // impresion del indice
		}
	}else{ // Si el fork() retorna un valor diferente a 0 este es el proces padre
		printf("fork() devuelve un valor diferente de 0, ese es el proceso padre con ID: %d \n\n", getpid()); // Mensaje para identificar al padre

		// Le asignamos una tarea al padre
		for(int i = 0; i<5; i++){ // ciclo de 0 a 4
			printf("Ciclo Hijo: %d\n", i); // impresion del indice
		}
	}

	// Finaizacion del programa
	printf("Fin del programa\n\n");
	return 0;
}
