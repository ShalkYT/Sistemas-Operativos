/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: J. Corredor, PhD
* Materia: Sistemas Operativos
* Tema: Multiplicación de matrices algoritmo clásico con procesos Fork
* Descripción:
*  - Módulo con funciones auxiliares para la multiplicación de matrices usando procesos hijos.
*  - Incluye inicialización, impresión y medición de tiempos.
**************************************************************************************************/

#include "moduloClasicaFork.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

/* Variables globales para medir el tiempo de ejecución */
struct timeval inicio, fin;

/* Marca el instante en el que empieza la medición del tiempo */
void InicioMuestra(void){
    gettimeofday(&inicio, (void *)0);
}

/* Calcula el tiempo transcurrido desde InicioMuestra y lo imprime en microsegundos */
void FinMuestra(void){
    gettimeofday(&fin, (void *)0);
    fin.tv_usec -= inicio.tv_usec;
    fin.tv_sec  -= inicio.tv_sec;
    double tiempo = (double)(fin.tv_sec*1000000 + fin.tv_usec);
    printf("%.0f", tiempo);
}

/* 
 * Multiplica un subconjunto de filas (filaI a filaF-1) de A por la matriz B
 * y almacena el resultado en C.
 */
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF) {
    double Suma, *pA, *pB;
    for (int i = filaI; i < filaF; i++) {
        for (int j = 0; j < D; j++) {
            Suma = 0.0;
            pA = mA + i*D; // Apuntador a la fila i de A
            pB = mB + j;   // Apuntador a la columna j de B
            for (int k = 0; k < D; k++, pA++, pB += D) {
                Suma += *pA * *pB;
            }
            mC[i*D + j] = Suma;
        }
    }
}

/* Imprime la matriz si su tamaño es pequeño (D < 9) para visualizarla */
void impMatrix(double *matrix, int D) {
    if (D < 9) {
        printf("\nImpresión...\n");
        for (int i = 0; i < D*D; i++, matrix++) {
            if(i % D == 0) printf("\n");
            printf(" %.2f ", *matrix);
        }
        printf("\n");
    }
}

/* Inicializa las matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *mA, double *mB, int D){
    for (int i = 0; i < D*D; i++, mA++, mB++){
        *mA = (double)rand()/RAND_MAX*(5.0 - 1.0); 
        *mB = (double)rand()/RAND_MAX*(9.0 - 5.0); 
    }
}
