/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Uso básico de la interfaz de creación de hilos con PTHREAD
*   - Intercambio de datos mediante variables globales compartidas
*   - Evidenciar condición de carrera por ausencia de sincronización
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

// Funcion que ejecutara el hilo reporte
void *reportar(void *nousada){
    // Impresion en consola del valor
    printf("El valor calculado es: %d\n", valor);
    // Fin de la funcion
    return NULL;
}

// Funcion que ejecutara el hilo asignacion
void *asignar(void *nousada){
    // Fijacion de variable en 20
    valor = 20;
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