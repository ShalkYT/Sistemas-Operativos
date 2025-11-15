/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: J. Corredor, PhD
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices usando transpuesta (Filas x Filas) con OpenMP
* Descripción:
*  - Incluye funciones para inicialización, impresión, multiplicación y medición de tiempo.
*  - La multiplicación se realiza usando la transpuesta de la segunda matriz para mejorar la localidad de memoria.
*  - Implementa paralelismo con OpenMP.
**************************************************************************************************/

#include "moduloFilasOpenMP.h"
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
    printf("%.0f", tiempo);
}

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 6) */
void impMatrix(double *matrix, int D, int t){
    int aux = 0;
    if(D < 6){
        switch(t){
            case 0: // Impresión por filas
                for(int i = 0; i < D*D; i++){
                    if(i % D == 0) printf("\n");
                    printf("%.2f ", matrix[i]);
                }
                printf("\n  - \n");
                break;
            case 1: // Impresión por columnas
                while(aux < D){
                    for(int i = aux; i < D*D; i += D)
                        printf("%.2f ", matrix[i]);
                    aux++;
                    printf("\n");
                }   
                printf("\n  - \n");
                break;
            default:
                printf("Sin tipo de impresión\n");
        }
    }
}

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *m1, double *m2, int D){
    for(int i = 0; i < D*D; i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0);  
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0);      
    }
}

/* Multiplicación de matrices usando transpuesta de B para mejorar localidad de memoria */
void multiMatrixTrans(double *mA, double *mB, double *mC, int D){
    double Suma, *pA, *pB;

    #pragma omp parallel
    {
        #pragma omp for
        for(int i = 0; i < D; i++){
            for(int j = 0; j < D; j++){
                pA = mA + i*D;   // Apuntador a la fila i de A
                pB = mB + j*D;   // Apuntador a la fila j de la matriz B transpuesta
                Suma = 0.0;
                for(int k = 0; k < D; k++, pA++, pB++){
                    Suma += *pA * *pB;
                }
                mC[i*D + j] = Suma;
            }
        }
    }
}
