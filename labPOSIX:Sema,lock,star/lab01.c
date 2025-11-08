/***********************************************
*   Pontificia Universidad Javeriana
*
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Descripcion: 
*   - Uso de interfaz de creaciond e hilos PTHREAD
************************************************/

// Inclucion de las librerias
#include <stdio.h> 
#include <pthread.h>
#include <stdlib.h>

// Funcion que se utiliza por los hilos
void *imprimirMensaje(void * ptr){
    // Declaracion de variable que almacena el mensaje
    char *mensaje;
    // Cast en el mensaje para almacenarlo en la variable declarada anteriormente
    mensaje = (char*) ptr;
    // Impresion del mensaje
    printf("%s \n", mensaje);
    // return que completa la estructura de la funcion (Se coloca para evitar un warning)
    return NULL;
}

// Funcion main 
int main(){
    // Declaracion de las variables que contendran los hilos
    pthread_t hilo1, hilo2;

    // Declaracion de mensaje que se enviaran a los hilos 1 y 2
    char *mensaje1 = "Soy el hilo 1";
    char *mensaje2 = "Soy el hilo 2";

    // Declaracion de variables que sirven para la verificacion de la correcta creacion de un hilo
    int iret1, iret2;

    // Creacion de los hilos //
    iret1 = pthread_create(&hilo1, NULL, imprimirMensaje, mensaje1);
    // Verificacion de la correcta creacion del hilo
    if(iret1 != 0){
        printf("ERROR al crear el hilo 1");
        return 0;
    }
    iret2 = pthread_create(&hilo2, NULL, imprimirMensaje, mensaje2);
    // Verificacion de la correcta creacion del hilo
    if(iret2 != 0){
        printf("ERROR al crear el hilo 2");
        return 0;
    }

    // Espera la finalizacion de los hilos
    pthread_join(hilo1, NULL);
    pthread_join(hilo2,NULL);

    // Finalizacion del programa
    return 0;
}