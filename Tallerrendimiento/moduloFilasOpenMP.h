/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices usando transpuesta (Filas x Filas) con OpenMP
* Descripción:
*  - Declaración de funciones para inicialización, impresión, multiplicación y medición de tiempo.
*  - La multiplicación se realiza usando la transpuesta de la segunda matriz para mejorar la localidad de memoria.
*  - Implementa paralelismo con OpenMP.
**************************************************************************************************/

#ifndef __MODULOFILASOPENMP_H__
#define __MODULOFILASOPENMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

/* Variables globales para medir el tiempo de ejecución */
extern struct timeval inicio, fin;

/* Marca el inicio de la medición de tiempo */
void InicioMuestra();

/* Calcula y muestra el tiempo transcurrido en microsegundos */
void FinMuestra();

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 6)
 * t = 0 -> impresión por filas
 * t = 1 -> impresión por columnas
 */
void impMatrix(double *matrix, int D, int t);

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *m1, double *m2, int D);

/* Multiplicación de matrices usando transpuesta de B para mejorar localidad de memoria
 * Paralelizado con OpenMP
 */
void multiMatrixTrans(double *mA, double *mB, double *mC, int D);

#endif
