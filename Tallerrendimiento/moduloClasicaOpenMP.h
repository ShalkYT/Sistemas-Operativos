/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: J. Corredor, PhD
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices clásico con OpenMP
* Descripción:
*  - Declaración de funciones para inicialización, impresión, multiplicación y medición de tiempo.
*  - Implementa paralelismo usando OpenMP para la multiplicación de matrices NxN.
**************************************************************************************************/

#ifndef __MMCLASICAOPENMP_H__
#define __MMCLASICAOPENMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

/* Marca el inicio de la medición de tiempo */
void InicioMuestra();

/* Calcula y muestra el tiempo transcurrido en microsegundos */
void FinMuestra();

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 9) para visualización */
void impMatrix(double *matrix, int D);

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *m1, double *m2, int D);

/* Multiplica matrices usando el algoritmo clásico y paralelismo OpenMP */
void multiMatrix(double *mA, double *mB, double *mC, int D);

#endif
