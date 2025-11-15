/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
* Materia: Sistemas Operativos
* Tema: Multiplicación de matrices (Filas x Filas) usando transpuesta con OpenMP
* Descripción:
*  - Programa principal que multiplica dos matrices NxN utilizando el algoritmo de matriz transpuesta.
*  - Se implementa paralelismo con OpenMP, permitiendo definir el número de hilos.
**************************************************************************************************/

#include "moduloFilasOpenMP.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

// Función principal
int main(int argc, char *argv[]){
    // Validar argumentos de entrada
    if(argc < 3){
        printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
        exit(0);
    }

    int N  = atoi(argv[1]); // Tamaño de las matrices
    int TH = atoi(argv[2]); // Número de hilos

    // Reservar memoria para matrices
    double *matrixA = (double *) calloc(N*N, sizeof(double));
    double *matrixB = (double *) calloc(N*N, sizeof(double));
    double *matrixC = (double *) calloc(N*N, sizeof(double));

    if(matrixA == NULL || matrixB == NULL || matrixC == NULL){
        fprintf(stderr, "Error reservando memoria\n");
        return 1;
    }

    srand(time(NULL));      // Inicializar semilla aleatoria
    omp_set_num_threads(TH); // Configurar número de hilos para OpenMP

    iniMatrix(matrixA, matrixB, N); // Inicializar matrices A y B

    // impMatrix(matrixA, N, 0);
    // impMatrix(matrixB, N, 1);

    InicioMuestra(); // Iniciar medición de tiempo
    multiMatrixTrans(matrixA, matrixB, matrixC, N); // Multiplicación usando transpuesta
    FinMuestra();    // Finalizar medición de tiempo

    printf(";%d;%d \n", N, TH); // Mostrar tamaño de matriz y número de hilos

    // impMatrix(matrixC, N, 0);

    // Liberar memoria
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}
