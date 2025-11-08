/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Suma de varios valores a una misma variable desde diferentes hilos
************************************************/

// Inclusion de las librerias
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
// Declaracion de variable global para guardar la suma final
int acumulado = 0;

// Funcion que realizaran los hilos
void *cuadrados(void *x){
    // Cast para la transformacion del valor recibido al tipo requerido
    int xi = (__intptr_t) x;
    // Operacion a realizar
    acumulado += xi * xi;
    // Final de la funcion
    return NULL;
}

// Funcion main
int main(){
    // Creacion de arreglo de hilos
    pthread_t hilos[20];
    // Declaracion de variable para manejar el error en la creacion de hilos
    int error; 

    // Chiclo de creacion de hilos
    for(int i = 0; i<20; i++){
        error = pthread_create(&hilos[i], NULL, cuadrados,(void *)(__intptr_t)(i+1));
        if(error != 0)
            // Impresion en consola en caso de error
            printf("El hilo %d no pudo ser creado", i);
    }
    // Ciclo de espera de finalizacion de los hilos
    for(int i = 0; i<20; i++){
        pthread_join(hilos[i], NULL);
    }
    // Impresion en consola del resultado final
    printf("La suma de cuadrados es: %d.\n", acumulado);
    
    // Fin del programa
    return 0;
}