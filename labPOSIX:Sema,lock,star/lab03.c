/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Sincronización entre dos hilos mediante condicionantes
*   - Uso de variables de condición para controlar el flujo del programa
*   - Incremento de una variable compartida respetando rangos de ejecución
************************************************/

// Inclusión de las librerías necesarias
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Declaración de mutex para proteger la variable compartida
pthread_mutex_t countMutex = PTHREAD_MUTEX_INITIALIZER;
// Declaración de mutex para control de sincronización
pthread_mutex_t conditionMutex = PTHREAD_MUTEX_INITIALIZER;
// Variable de condición para despertar hilos dependiendo del contador
pthread_cond_t conditionCond = PTHREAD_COND_INITIALIZER;

// Variable compartida entre los hilos
int count;

// Definición de límites para el funcionamiento del programa
#define CONT_DONE 15    // Límite donde el programa finaliza
#define CONT_HALT1 4    // Primer valor en el que se detiene count01
#define CONT_HALT2 11   // Último valor en el que se detiene count01

// Función ejecutada por el hilo 1
void *count01(){
    for(;;){
        // Bloqueo del mutex de condición para evaluar el estado de count
        pthread_mutex_lock(&conditionMutex);
        // Si count está dentro del rango prohibido, se pone en espera
        while(count >= CONT_HALT1 && count <= CONT_HALT2){
            pthread_cond_wait(&conditionCond, &conditionMutex);
        }
        // Libera el mutex de condición al continuar
        pthread_mutex_unlock(&conditionMutex);

        // Incremento seguro de la variable compartida
        pthread_mutex_lock(&countMutex);
        count++;
        printf("Valor de la variable contador en la funcion 01: %d \n", count);
        pthread_mutex_unlock(&countMutex);

        // Control del fin del programa
        if(count >= CONT_DONE) return NULL;
    }
}

// Función ejecutada por el hilo 2
void *count02(){
    for(;;){
        // Bloqueo del mutex de condición para evaluar si count está dentro del rango válido
        pthread_mutex_lock(&conditionMutex);
        // Si count aún no está en el rango permitido para este hilo, despierta al otro
        while(count < CONT_HALT1 || count > CONT_HALT2){
            pthread_cond_signal(&conditionCond);
        }
        // Libera el mutex de condición
        pthread_mutex_unlock(&conditionMutex);

        // Incremento seguro de la variable compartida
        pthread_mutex_lock(&countMutex);
        count++;
        printf("Valor de la variable contador en la funcion 02: %d \n", count);
        pthread_mutex_unlock(&countMutex);

        // Control del fin del programa
        if(count >= CONT_DONE) return NULL;
    }
}

// Función principal del programa
int main(){
    // Declaración de hilos que ejecutarán las funciones anteriores
    pthread_t hilo1, hilo2;

    // Creación de los hilos
    pthread_create(&hilo1, NULL, count01, NULL);
    pthread_create(&hilo2, NULL, count02, NULL);

    // Espera a que ambos hilos finalicen su ejecución
    pthread_join(hilo1, NULL);
    pthread_join(hilo2, NULL);

    // Fin del programa
    return 0;
}
