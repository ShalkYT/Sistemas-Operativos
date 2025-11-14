#ifndef __MODULOFILASOPENMP_H__
#define __MODULOFILASOPENMP_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>

extern struct timeval inicio, fin; 

void InicioMuestra();
void FinMuestra();
void impMatrix(double *matrix, int D, int t);
void iniMatrix(double *m1, double *m2, int D);
void multiMatrixTrans(double *mA, double *mB, double *mC, int D);


#endif