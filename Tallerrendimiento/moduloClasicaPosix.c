/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices clásico con Pthreads (Posix)
* Descripción:
*  - Implementa inicialización, impresión, medición de tiempo y multiplicación de matrices.
*  - La multiplicación se realiza por bloques de filas asignados a cada hilo.
*  - Incluye uso de mutex para manejo seguro de recursos compartidos.
**************************************************************************************************/

#include "moduloClasicaPosix.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

/* Mutex para sincronización de hilos */
pthread_mutex_t MM_mutex;

/* Matrices globales compartidas */
double *matrixA, *matrixB, *matrixC;

/* Variables globales para medir tiempo */
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

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *m1, double *m2, int D){ 
    for(int i = 0; i < D*D; i++, m1++, m2++){
        *m1 = (double)rand()/RAND_MAX*(5.0-1.0); 
        *m2 = (double)rand()/RAND_MAX*(9.0-5.0); 
    }   
}

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 9) */
void impMatrix(double *matriz, int D){
    if(D < 9){
        for(int i = 0; i < D*D; i++){
            if(i % D == 0) printf("\n");
            printf(" %.2f ", matriz[i]);
        }   
        printf("\n>-------------------->\n");
    }
}

/* Multiplicación de matrices por bloques de filas asignadas a cada hilo */
void *multiMatrix(void *variables){
    struct parametros *data = (struct parametros *)variables;
    
    int idH  = data->idH;  // ID del hilo
    int nH   = data->nH;   // Número total de hilos
    int D    = data->N;    // Tamaño de la matriz
    int filaI = (D/nH) * idH;         // Fila inicial
    int filaF = (D/nH) * (idH+1);     // Fila final
    double Suma, *pA, *pB;

    for (int i = filaI; i < filaF; i++){
        for (int j = 0; j < D; j++){
            pA = matrixA + i*D; // Apuntador a la fila i de A
            pB = matrixB + j;   // Apuntador a la columna j de B
            Suma = 0.0;
            for (int k = 0; k < D; k++, pA++, pB += D){
                Suma += *pA * *pB;
            }
            matrixC[i*D + j] = Suma;
        }
    }

    /* Sección crítica vacía, placeholder para futuras operaciones protegidas */
    pthread_mutex_lock(&MM_mutex);
    pthread_mutex_unlock(&MM_mutex);

    pthread_exit(NULL);
}
