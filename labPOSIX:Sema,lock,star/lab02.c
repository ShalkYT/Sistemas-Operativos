/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Uso de interfaz de creaciond e hilos PTHREAD
*   - Uso de un arreglo de hilos para el almacenamiento de estos
*   - Uso del ID e identificacion de los hilos
************************************************/

// Inclusion de las librerias
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>

// Declaracion del numero total de hilos
#define NHILOS 10
// Creacion de semaforo (mutex) para sincronizar los hilos
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// Declaracion de contador global (Para que todos los hilos lo puedan utilizar)
int contador = 0;

// Funcion que se utiliza por los hilos
void *funcionHilo(void * arg){
    // Cast en el valor que se le da a la funcion para que se interprete como un apuntador a un entero
    int i = *(int *)(arg);
    // Impresion en consola de informacion del hilo(ID) y del contador (Numero del hilo)
    printf("Numero del hilo: %d | ID del hilo: %ld \n", i, pthread_self());
    // Uso de semaforo para bloquear otros hilos
    pthread_mutex_lock(&mutex);
    // Aumento en el contador que se debe realizar uno a uno para mantener el orden del numero de hilo
    contador++;
    // Uso del semaforo para dejar que los otros hilos puedan ejecutar su funcion
    pthread_mutex_unlock(&mutex);
    // return que completa la estructura de la funcion (Se coloca para evitar un warning)
    return NULL;
}

int main(){
    // Declaracion de un arreglo de hilos de tamaño NHILOS (10)
    pthread_t hilo_id[NHILOS];
    // Declaraciond de variable para controlar errores al crear los hilos
    int error;

    // Ciclo que maneja la ejecucion de todos los hilos
    for(int i = 0; i < NHILOS; i++){
        // Ejecucion de la funcion de los hilos por cada uno de estos
        pthread_create(&hilo_id[i], NULL, funcionHilo, &i);
    }
    
    // Ciclo que espera a que todos los hilos terminen
    for(int i = 0; i < NHILOS; i++){
        // Espera la finalizacion de los hilos
        pthread_join(hilo_id[i], NULL);
    }

    // Impresion en consola para verificaciones, se coloca despues de que todos los hilos terminen para mantener el orden
    printf("Valor final del contador: %d \n", contador);

    // Fin del programa
    return 0;
}