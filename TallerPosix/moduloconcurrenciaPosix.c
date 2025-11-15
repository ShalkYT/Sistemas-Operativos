#include "moduloconcurrenciaPosix.h"

void *buscarMax(void *parametro){
    param_H *argumentos = (param_H *)parametro;

    // Inicializar el máximo parcial
    argumentos->maxparcial = argumentos->vector[argumentos->inicio];

    // Buscar el máximo en el rango asignado
    for(int i = argumentos->inicio; i < argumentos->fin; i++){
        if(argumentos->vector[i] > argumentos->maxparcial)
            argumentos->maxparcial = argumentos->vector[i];
    }

    pthread_exit(NULL);
}

int maximoValor(int *vec, int n, int nhilos) {

    pthread_t hilos[nhilos];
    param_H datos[nhilos];

    int tam_bloque = n / nhilos;
    int resto = n % nhilos;
    int inicio = 0;

    // Crear los hilos
    for (int i = 0; i < nhilos; i++) {

        datos[i].inicio = inicio;
        datos[i].fin = inicio + tam_bloque + (i < resto ? 1 : 0);
        datos[i].vector = vec;
        datos[i].maxparcial = vec[inicio];

        inicio = datos[i].fin;

        if (pthread_create(&hilos[i], NULL, buscarMax, &datos[i]) != 0) {
            perror("Error creando hilo");
            exit(-1);
        }
    }

    // Esperar hilos
    for (int i = 0; i < nhilos; i++)
        pthread_join(hilos[i], NULL);

    // Calcular máximo global
    int maxGlobal = datos[0].maxparcial;

    for (int i = 1; i < nhilos; i++)
        if (datos[i].maxparcial > maxGlobal)
            maxGlobal = datos[i].maxparcial;

    return maxGlobal;
}
