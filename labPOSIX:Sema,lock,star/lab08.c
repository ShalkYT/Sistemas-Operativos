/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Sincronización entre hilos utilizando mutex y variables de condición
*   - Control de acceso a una variable compartida entre hilos
*   - Garantizar el orden de ejecución evitando condiciones de carrera
************************************************/

// Inclusion de las librerias
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>
// Esta libreria es necesaria porque c no reconoce os bool de forma nativa
#include <stdbool.h>

// Declaracion de variables globales usadas por ambos hilos
int valor = 100;
bool notificar = 0;

// Declaracion de variable de semaforo
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// Declaracion de variable de variable para sincronizacion
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// Funcion que ejecutara el hilo reporte
void *reportar(void *nousada){
    // Cierre del semaforo
    pthread_mutex_lock(&mutex);
    // Ciclo para mantener en espera el hilo 
    while(!notificar){
        // Funcion de espera hasta obtener la señal del otro hilo
        pthread_cond_wait(&cond, &mutex);
    }
    // Impresion en consola del valor
    printf("El valor calculado es: %d\n", valor);
    // Fin de la funcion
    return NULL;
}

// Funcion que ejecutara el hilo asignacion
void *asignar(void *nousada){
    // Fijacion de variable en 20
    valor = 20;
    // Cierre del semaforo para cambiar el estado de notificar
    pthread_mutex_lock(&mutex);
    // Activacion de notificar
    notificar = 1;
    // Señal para que el otro hilo pueda continuar
    pthread_cond_signal(&cond);
    // Liberacion del semaforo para el siguiente hilo
    pthread_mutex_unlock(&mutex);
    // Fin de la funcion
    return NULL;
}

// Funcion main
int main(){
    // Declaracion de hilos
    pthread_t reporte, asignacion;
    // Declaracion de variables para 
    int irep, iasi;

    // Creacion de los hilos //
    irep = pthread_create(&reporte, NULL, reportar, NULL);
    // Verificacion de la correcta creacion del hilo
    if(irep != 0){
        printf("ERROR al crear el hilo 1");
        return 0;
    }
    iasi = pthread_create(&asignacion, NULL, asignar, NULL);
    // Verificacion de la correcta creacion del hilo
    if(iasi != 0){
        printf("ERROR al crear el hilo 2");
        return 0;
    }

    // Creacion de variable que almacenara un valor (no se utiliza y por esto mismo genera un warning)
    void *nousada;
    pthread_join(reporte, nousada);
    pthread_join(asignacion, nousada);

    // Fin del programa
    return 0;
}