/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Realizacion de tareas demandantes en distintos hilos
*   - Separacion de tareas de alta demanda usando semaforos
************************************************/

// Inclusion de las librerias
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>

// Declaracion del arreglo de hilos
pthread_t tid[3];
// Declaracion de variable contador para identificar los hilos
int contador;
// Declaracion de semaforo (mutex) para sincronizar los hilos
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Funcion que usaran los hilos
void* computar(){
    // Declaracion de una variable entera de uno de los tamaños mas grandes posibles
    unsigned long i = 0;

    // Cierre del semaforo para solo trabajar en este hilo
    pthread_mutex_lock(&lock);
    //Aumento en el contador para cambiar el idenificardor del hilo (para que todos los hilos tengan identificadores diferentes)
    contador++;
    // Impresion en consola para notificar el inicio
    printf("\nEl trabajo %d ha empezado\n", contador);
    // Ciclo que se repite 2 elevado a la 8 veces
    for(i = 0; i < (0xFFFFFFFF); i++){}
    // Impresion en consola para notificar el final
    printf("\nEl trabajo %d ha finalizado\n", contador);
    // liberacion del semaforo para permitir la ejecucion del proximo hilo
    pthread_mutex_unlock(&lock);

    // Fin de la funcion
    return NULL;
}

// Funcion main
int main(){
    // Declaracion de variable para manejar el error en la creacion de hilos
    int error; 
    // Declaracion de variable para el ciclo de creacion
    int i = 0;

    // Ciclo en el cual se crean los hilos
    while(i < 3){
        // Creacion de cada uno de los hilos y almacenamiento del estado en variable
        error = pthread_create(&tid[i],NULL, computar, NULL);
        // Verificacion de creacion de hilos
        if(error != 0)
            // Impresion en consola en caso de error
            printf("El hilo %d no pudo ser creado", i);
        // Movimiento al siguiente hilo
        i++;
    }

    // Espera a que todos los hilos terminen
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_join(tid[2], NULL);

    // Fin del programa
    return 0;
}