/**************************************************************************************
 * Fecha: 11/09/2025
 * Autor: Andres Eduardo Meneses Rincon
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Aprender el uso de modularización usando un archivo .c para la 
 * implementacion de las funciones declaradas en un archivo .h
*************************************************************************************/

// Solo es necesario incluir el archivo .h porque este ya incluye las librerias necesarias
#include "modulo.h"

// Declaracion de variables de tipo struct timeval
struct timeval ini, fin;

// Función para tomar el tiempo inicial
void InicioMuestra(){
	gettimeofday(&ini, (void *)0);
}

// Funcion para tomar el tiempo final
void FinMuestra(){
	gettimeofday(&fin, (void *)0);
	fin.tv_usec -= ini.tv_usec;
	fin.tv_sec -= ini.tv_sec;
	double tiempo = (double) (fin.tv_sec*1000000 + fin.tv_usec);
	printf("%9.0f \n", tiempo);
}

// Funcion para llenar 2 matrices con varios valores
void iniMatriz(int n, double *m1, double *m2){
   	for(int i=0; i<n*n; i++){
	        m1[i] = i*2.3 + 1.3;
	        m2[i] = i*2.3;
	}
};

// Funcion para imprimir una matriz
void imprMatrices(int n, double *matriz){
    if(n<9){
        printf("\n#######################################################\n");
   		for(int i=0; i<n*n; i++){
                if(i%n==0) printf("\n");
	        printf(" %f ", matriz[i]);
   		}
    }
};

// Funcion clasica que multiplica 2 matrices
void multiMatrizClasica(int N, double* m1, double* m2, double* m3){

	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			double sumaTemp, *pA, *pB;
			sumaTemp = 0.0;
			pA = m1 + i*N;
			pB = m2 + j;
			for(int k=0; k<N; k++, pA++, pB+=N){
				sumaTemp += *pA * *pB;
			}
			m3[j+i*N] = sumaTemp;
		}
	}
}
