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

#define MIN(x,y) (((x) < (y))?x:y)

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

int main(){
	//Declaracion de variable que contendra valores de la sumatoria
	double resSumatoria = 0;
	int Repeticiones = 30000;

	// Fijacion del numero de hilos deseados
	int numHilos = omp_get_max_threads();
	//
	printf("Numero de hilos utilizados: %d \n", numHilos);
	// Region paralela por OMP
	#pragma omp parallel
	{
		// Ciclo para cada uno de los hilos y que el resultado obtenido en estos se guarde en resSumatoria
		#pragma omp for reduction(+: resSumatoria)
		for(int i = 0; i < Repeticiones; i++){
			resSumatoria += funcSum(i);
		}
	}

	printf("Resultado de la sumatoria de la funcion seno: %0.2f \n", resSumatoria);

	// Fin del programa
	return 0;
}
