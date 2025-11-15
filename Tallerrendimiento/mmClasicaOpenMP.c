/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
* Materia: Sistemas Operativos
* Tema: Multiplicación de matrices algoritmo clásico con OpenMP
* Descripción:
*  - Programa principal que multiplica dos matrices NxN usando paralelismo con OpenMP.
*  - Se permite definir el número de hilos para la ejecución.
**************************************************************************************************/

#include "moduloClasicaOpenMP.h"
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

    // Reservar memoria para las matrices
    double *matrixA = (double *) calloc(N*N, sizeof(double));
    double *matrixB = (double *) calloc(N*N, sizeof(double));
    double *matrixC = (double *) calloc(N*N, sizeof(double));

    if(matrixA == NULL || matrixB == NULL || matrixC == NULL){
        fprintf(stderr, "Error reservando memoria\n");
        return 1;
    }

    srand(time(NULL)); // Inicializar semilla aleatoria

    omp_set_num_threads(TH); // Configurar número de hilos para OpenMP

    iniMatrix(matrixA, matrixB, N); // Inicializar matrices A y B

    // impMatrix(matrixA, N);
    // impMatrix(matrixB, N);

    InicioMuestra();              // Iniciar medición de tiempo
    multiMatrix(matrixA, matrixB, matrixC, N); // Multiplicación paralela de matrices
    FinMuestra();                 // Finalizar medición de tiempo

    printf("%d;%d \n", N, TH);    // Mostrar tamaño de la matriz y número de hilos

    // impMatrix(matrixC, N);

    // Liberar memoria
    free(matrixA);
    free(matrixB);
    free(matrixC);

    return 0;
}
