/**********************************************
* Pontificia Universidad javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Tema: Introduccion a OpenMP
* Descripcion:
* 	- Uso de la directiva y funcion para hcaer uso de OpenMP
***********************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	// Declaracion de variable que contiene el numero maximo de cores
	int maxCores = omp_get_max_threads();
	// Mensaje en pantalla que indica la cantidad maxima de cores
	printf("OpenMP ejecutando con %d hilos \n", maxCores);

	// Region paralela por OMP
	#pragma omp parallel
	{
		// Declaracion de variable que contiene el numero identificador del hilo actual
		int numCore = omp_get_thread_num();
		// Mensaje en pantalla que indica el numero de identificacion del hilo actual
		printf("Hola mundo desde el thread %d \n", numCore);
	}

	// Fin del programa
	return 0;
}
