/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
* Materia: Sistemas Operativos
* Tema: Multiplicación de matrices algoritmo clásico con Pthreads
* Descripción:
*  - Programa principal que multiplica dos matrices NxN usando paralelismo con hilos POSIX (Pthreads).
*  - Cada hilo calcula un bloque de filas de la matriz resultado.
**************************************************************************************************/

#include "moduloClasicaPosix.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

// Función principal
int main(int argc, char *argv[]){
    // Validar argumentos de entrada
    if (argc < 3){
        printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
        exit(0);	
    }

    int N = atoi(argv[1]);        // Tamaño de las matrices
    int n_threads = atoi(argv[2]); // Número de hilos a usar

    pthread_t p[n_threads];        // Vector de hilos
    pthread_attr_t atrMM;          // Atributos de hilos

    // Reservar memoria para matrices
    matrixA = (double *) calloc(N*N, sizeof(double));
    matrixB = (double *) calloc(N*N, sizeof(double));
    matrixC = (double *) calloc(N*N, sizeof(double));

    if(matrixA == NULL || matrixB == NULL || matrixC == NULL){
        fprintf(stderr, "Error reservando memoria\n");
        return 1;
    }

    iniMatrix(matrixA, matrixB, N); // Inicializar matrices A y B
    // impMatrix(matrixA, N);
    // impMatrix(matrixB, N);

    InicioMuestra(); // Iniciar medición de tiempo

    // Inicializar mutex y atributos de hilos
    pthread_mutex_init(&MM_mutex, NULL);
    pthread_attr_init(&atrMM);
    pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    // Crear hilos y asignarles bloques de filas a calcular
    for (int j = 0; j < n_threads; j++){
        struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
        datos->idH = j;       // ID del hilo
        datos->nH  = n_threads; // Total de hilos
        datos->N   = N;       // Tamaño de la matriz

        pthread_create(&p[j], &atrMM, multiMatrix, (void *)datos);
    }

    // Esperar a que todos los hilos terminen
    for (int j = 0; j < n_threads; j++)
        pthread_join(p[j], NULL);

    FinMuestra(); // Finalizar medición de tiempo
    printf(";%d;%d \n", N, n_threads); // Mostrar tamaño de matriz y número de hilos

    // impMatrix(matrixC, N);

    // Liberar memoria
    free(matrixA);
    free(matrixB);
    free(matrixC);

    // Destruir atributos y mutex
    pthread_attr_destroy(&atrMM);
    pthread_mutex_destroy(&MM_mutex);
    pthread_exit(NULL); // Salida del programa

    return 0;
}
