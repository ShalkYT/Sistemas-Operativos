/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: J. Corredor, PhD
* Materia: Sistemas Operativos
* Tema: Funciones auxiliares para multiplicación de matrices clásico con fork()
* Descripción:
*  - Declaración de funciones para la multiplicación de matrices usando procesos hijos.
*  - Incluye inicialización, impresión y medición de tiempo.
*  - Cada proceso hijo puede calcular un bloque de filas de la matriz resultado.
**************************************************************************************************/

#ifndef MMCLASICAFORK_H
#define MMCLASICAFORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

/* Variables globales para medir el tiempo de ejecución */
extern struct timeval inicio, fin;

/* Marca el inicio de la medición de tiempo */
void InicioMuestra(void);

/* Calcula y muestra el tiempo transcurrido en microsegundos */
void FinMuestra(void);

/* 
 * Multiplica un bloque de filas de la matriz A por la matriz B 
 * y guarda el resultado en C.
 * filaI y filaF indican el rango de filas que procesa este proceso hijo.
 */
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

/* Imprime la matriz cuadrada si su tamaño es pequeño (D < 9) para visualización */
void impMatrix(double *matrix, int D);

/* Inicializa matrices con valores aleatorios en rangos definidos */
void iniMatrix(double *mA, double *mB, int D);

#endif
