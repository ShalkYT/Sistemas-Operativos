#include "moduloConcurrenciaPosix.h"

void *buscarMax(void *parametro){
        param_H *argumentos = (param_H *)parametro;
        argumentos->maxparcial = argumentos->vector[argumentos->inicio];
        for(int i=0; i<argumentos->fin; i++){
                if(argumentos->vector[i] > argumentos->maxparcial)
                        argumentos->maxparcial = argumentos->vector[i];
        }
        pthread_exit(0);
        return NULL;
}