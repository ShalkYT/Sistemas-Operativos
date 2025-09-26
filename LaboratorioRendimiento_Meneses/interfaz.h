/**************************************************************************************
 * Fecha: 11/09/2025
 * Autor: Andres Eduardo Meneses Rincon
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Aprender el uso de modularización en usando un archivo .h para 
 * la declaración de funciones
*************************************************************************************/

#ifndef __MODULO_H__
#define __MODULO_H__

// Inclusión de librerías necesarias para la implementación de las funciones
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

// Función para tomar el tiempo inicial
void InicioMuestra();

// Funcion para tomar el tiempo final
void FinMuestra();

// Funcion para llenar 2 matrices con varios valores
void iniMatriz(int n, double *m1, double *m2);

// Funcion para imprimir una matriz
void imprMatrices(int n, double *matriz);

// Funcion clasica que multiplica 2 matrices
void multiMatrizClasica(int N, double* m1, double* m2, double* m3);

#endif
