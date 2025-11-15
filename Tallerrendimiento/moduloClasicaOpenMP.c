/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: J. Corredor, PhD
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices clásico con OpenMP
* Descripción:
*  - Incluye funciones para inicialización, impresión, multiplicación y medición de tiempo.
*  - Implementa paralelismo usando OpenMP para la multiplicación de matrices NxN.
**************************************************************************************************/

#include "moduloClasicaOpenMP.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <omp.h>

/* Variables globales para medir el tiempo de ejecución */
struct timeval inicio, fin;

/* Marca el inicio de la medición de tiempo */
void InicioMuestra(){
    gettimeofday(&inicio, (void *)0);
}

/* Calcula y muestra el tiempo transcurrido en microsegundos */
void FinMuestra(){
    gettimeofday(&fin, (void *)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec*1000000 + fin.tv_usec); 
    printf("%.0f;", tiempo);
}

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 9) para visualizarla */
void impMatrix(double *matrix, int D){
    if(D < 9){
        printf("\n");
        for(int i = 0; i < D*D; i++){
            if(i % D == 0) printf("\n");
            printf("%.2f ", matrix[i]);
        }
        printf("\n**-----------------------------**\n");
    }
}

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *m1, double *m2, int D){
    for(int i = 0; i < D*D; i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);  
        *m2 = (double)rand()/RAND_MAX*(9.0-2.0);  
    }
}

/* Multiplica matrices usando el algoritmo clásico y paralelismo OpenMP */
void multiMatrix(double *mA, double *mB, double *mC, int D){
    double Suma, *pA, *pB;

    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0; i < D; i++){
            for(int j = 0; j < D; j++){
                pA = mA + i*D; // Apuntador a la fila i de A
                pB = mB + j;   // Apuntador a la columna j de B
                Suma = 0.0;
                for(int k = 0; k < D; k++, pA++, pB += D){
                    Suma += *pA * *pB;
                }
                mC[i*D + j] = Suma;
            }
        }
    }
}
