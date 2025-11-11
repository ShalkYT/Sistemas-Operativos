/**********************************************
* Pontificia Universidad javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Tema: Introduccion a OpenMP
* Descripcion:
* 	- Paralelismo para el calculo de la funcion seno
***********************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// Definicion de funcion que saca el valor minimo
#define MIN(x,y) (((x) < (y))?x:y)

// Variables para la medicion de tiempo
struct timeval inicio, fin; 

// Funcion para iniciar la medicion del tiempo de ejecucion
void InicioMuestra(){
	gettimeofday(&inicio, (void *)0);
}

// Funcion para terminar la medicion del tiempo de ejecucion
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= inicio.tv_usec;
	fin.tv_sec  -= inicio.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("Tiempo de ejecucion: %0.4fs\n", tiempo/1000000);
}


// Funcion de sumatorio
double funcSum(int i){
	// Declaracion del incio del ciclo
	int inicio = i*(i+1)/2;
	// Declaracion del final del ciclo
	int fin = inicio + i;
	// Declaracion de variable que almacena el valor
	double resultado = 0;
	// Ciclo para realizar la parte de la sumatoria correspondiente
	for(double j = inicio; j < fin; j++){
		resultado += sin(j);
	}
	// Retorno de la funcion
	return resultado;
}

int main(int argc, char *argv[]){
	//Declaracion de variable que contendra valores de la sumatoria
	double resSumatoria = 0;

	// Confirmaciond de argumentos
	if(argc != 3){
		printf("ERROR: \n\t $../ejecutable numHilos numRepeticiones\n");
		return 0;
	}
	// Transformacin del primer argumento en el numero de hilos (entero)
	int numHilos = (int) atoi(argv[1]);
	// Transformacin del primer argumento en el numero de repeticiones (entero)
	int repeticiones = (int) atoi(argv[2]);

	// Fijacion del numero de hilos deseados
	omp_set_num_threads(numHilos);
	printf("Numero de hilos fijados a %d \n", numHilos);
	InicioMuestra();
	// Region paralela por OMP
	#pragma omp parallel
	{
		// Ciclo para cada uno de los hilos y que el resultado obtenido en estos se guarde en resSumatoria
		#pragma omp parallel for reduction(+: resSumatoria)
		for(int i = 0; i < repeticiones; i++){
			resSumatoria += funcSum(i);
		}
	}
	FinMuestra();
	printf("Resultado de la sumatoria de la funcion seno: %0.2f \n", resSumatoria);

	// Fin del programa
	return 0;
}
