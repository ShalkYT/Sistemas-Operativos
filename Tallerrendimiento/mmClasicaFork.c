/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
* Materia: Sistemas Operativos
* Tema: Multiplicación de matrices usando fork()
* Descripción:
*  - Programa principal que multiplica dos matrices NxN usando múltiples procesos hijos.
*  - Cada proceso calcula un bloque de filas de la matriz resultado.
**************************************************************************************************/

#include "moduloClasicaFork.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

// Función principal
int main(int argc, char *argv[]) {
    // Validar argumentos de entrada
    if (argc < 3) {
        printf("\n \t\tUse: $./mmClasicaFork Size Hilos \n");
        exit(0);
    }

    int N     = atoi(argv[1]); // Tamaño de las matrices
    int num_P = atoi(argv[2]); // Número de procesos hijos

    // Reservar memoria para las matrices
    double *matA = (double *) calloc(N*N, sizeof(double));
    double *matB = (double *) calloc(N*N, sizeof(double));
    double *matC = (double *) calloc(N*N, sizeof(double));

    if (matA == NULL || matB == NULL || matC == NULL) {
        fprintf(stderr, "Error reservando memoria\n");
        return 1;
    }

    srand(time(0)); // Inicializar semilla aleatoria
    iniMatrix(matA, matB, N); // Inicializar matrices A y B

    int rows_per_process = N / num_P; // Filas asignadas por proceso

    InicioMuestra(); // Iniciar medición de tiempo

    // Crear procesos hijos y repartir filas de la matriz resultado
    for (int i = 0; i < num_P; i++) {
        pid_t pid = fork();

        if (pid == 0) {
            // Definir el rango de filas que este hijo debe calcular
            int start_row = i * rows_per_process;
            int end_row   = (i == num_P - 1) ? N : start_row + rows_per_process;

            // Multiplicación de matrices en el rango asignado
            multiMatrix(matA, matB, matC, N, start_row, end_row); 

            // Imprimir la parte calculada de matC si la matriz es pequeña
            if (N < 9) {
                for (int r = start_row; r < end_row; r++) {
                    for (int c = 0; c < N; c++) {
                        // printf(" %.2f ", matC[N*r+c]);
                    }
                    // printf("\n");
                }
            }
            exit(0); // Finalizar proceso hijo
        } else if (pid < 0) {
            perror("fork failed");
            exit(1);
        }
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < num_P; i++) {
        wait(NULL);
    }

    FinMuestra(); // Finalizar medición de tiempo
    printf(";%d;%d\n", N, num_P); // Mostrar N y número de procesos

    // Liberar memoria
    free(matA);
    free(matB);
    free(matC);

    return 0;
}
