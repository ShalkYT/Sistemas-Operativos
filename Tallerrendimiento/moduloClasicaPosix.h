/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: J. Corredor, PhD
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices clásico con Pthreads (Posix)
* Descripción:
*  - Declaración de funciones para inicialización, impresión, multiplicación y medición de tiempo.
*  - La multiplicación de matrices se realiza dividiendo filas entre los hilos disponibles.
*  - Incluye estructura de parámetros para pasar información a cada hilo.
**************************************************************************************************/

#ifndef __MODULOCLASICAPOSIX_H__
#define __MODULOCLASICAPOSIX_H__

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/* Mutex para sincronización de hilos */
extern pthread_mutex_t MM_mutex;

/* Matrices globales compartidas */
extern double *matrixA, *matrixB, *matrixC;

/* Variables globales para medición de tiempo */
extern struct timeval inicio, fin;

/* Estructura de parámetros para pasar información a los hilos */
struct parametros{
    int nH;   /* Número total de hilos */
    int idH;  /* ID del hilo */
    int N;    /* Tamaño de la matriz */
};

/* Marca el inicio de la medición de tiempo */
void InicioMuestra();

/* Calcula y muestra el tiempo transcurrido en microsegundos */
void FinMuestra();

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *m1, double *m2, int D);

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 9) */
void impMatrix(double *matriz, int D);

/* Función de multiplicación de matrices para hilos */
void *multiMatrix(void *variables);

#endif
