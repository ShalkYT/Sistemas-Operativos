#ifndef __MODULOCONCURRENCIAPOSIX_H__
#define __MODULOCONCURRENCIAPOSIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

struct argHilos {
    int inicio;
    int fin;
    int *vector;
    int maxparcial;
};

typedef struct argHilos param_H;

int maximoValor(int *vec, int n, int nhilos);
void *buscarMax(void *parametro);

#endif
