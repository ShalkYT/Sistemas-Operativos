/*#######################################################################################
 #* 
 #* 
 #* Descripción:
 #*    Implementa las funciones de la multiplicación de matrices (algoritmo clásico)
 #*    usando paralelismo con procesos fork(), repartiendo bloques de filas entre
 #*    procesos hijos para aprovechar mejor la CPU.
 #* Docente:  J. Corredor, PhD 
 #* Autores:
 #* 
 #*    
#######################################################################################*/
#ifndef MMCLASICAFORK_H
#define MMCLASICAFORK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

extern struct timeval inicio, fin;

/* Marca el inicio de la medición de tiempo. */
void InicioMuestra(void);

/* Calcula y muestra el tiempo transcurrido en microsegundos. */
void FinMuestra(void);

/* 
 * Multiplica un bloque de filas de la matriz A por B y guarda el resultado en C.
 * filaI y filaF indican el rango de filas que procesa este proceso hijo.
 */
void multiMatrix(double *mA, double *mB, double *mC, int D, int filaI, int filaF);

/* Imprime una matriz cuadrada si su tamaño es pequeño. */
void impMatrix(double *matrix, int D);

/* Inicializa las matrices con valores aleatorios en un rango fijo. */
void iniMatrix(double *mA, double *mB, int D);

#endif
