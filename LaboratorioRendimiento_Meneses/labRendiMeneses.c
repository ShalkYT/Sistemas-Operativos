/**************************************************************************************
 * Fecha: 11/09/2025
 * Autor: Andres Eduardo Meneses Rincon
 * Materia: Sistemas Operativos
 * Tema: Concurrencia
 * Objetivo: Hacer una metodología para la implementación de la multiplicación de matrices.
 * La idea principal, es construir paso a paso la implementación para hacer uso de la
 * biblioteca PTHREAD. Se implementa el Algoritmo Clásico de multiplicación de matrices, para
 * matrices cuadradas, es decir, la dimensión de filas es igual a la de columnas.
 * A continuación se describen los paso
 *  - Reserva de memoria
 *      - Creación de punteros para matrices del tipo doble
 *      - Asignación de memoria
 *      - Ingreso de argumentos de entrada (Dimensión matriz, número de hilos)
 *      - Validación argumentos de entrada
 *      - Inicializar las matrices
 *      - Imprimir las matrices
 *      - Función para inicializar las matrices
 *      - Función para imprimir las matrices
 *      - Algoritmo clásico de multiplicación matrices
 *  - Se verifica el resultado
 *      - Función para multiplicación las matrices
 *      - Declaración vector de hilos
 *      - Creación de hilos según tamaño de vector de hilos
 *      - Crear estructura de datos que encapsule los argumentos de entrada de la función MM
 * Implementación de paralelismo: resolución de la multiplicación de matrices
 *  - Se crea el vector de hilos
 *  - Se tiene pendiente la exclusión de los hilos
 *  - Se pasa a globales las matrices
 *  - Encapsular los datos para enviarlos a la función MxM
 *  - Se desencapsulan los datos dentro de la función MxM (descomprimen)
*************************************************************************************/

#include "interfaz.h"
#include <stdio.h>
#include <stdlib.h>

// Funcion main del programa
int main(int argc, char *argv[]) {

    // Confirmacion del correcto uso del programa (Confirmacion de 2 argumentos, el llamado y el tamaño de las matrices)
    if(argc != 2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe SIZE \n");
        return -1;
    }

    // Almacenamiento del argumento que contiene el tamaño en un variable
    int N = (int) atof(argv[1]);
    // Confirmacion de que el tamaño es mayor a 0
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };

    // Declaracion de 3 apuntadores para las 3 matrices
    double *mA, *mB, *mC;

    /** Se le asigna memoria dinamica a los 3 apuntadores globales teniendo en cuenta el tamaño dado en los argumentos**/
    mA = (double *) malloc(N*N*sizeof(double));
    mB = (double *) malloc(N*N*sizeof(double));
    mC = (double *) calloc(N*N,sizeof(double));

	/** Se inicializan las 2 matrices **/
	iniMatriz(N, mA, mB);

	// Uso de funcion para imprimir matrices
	imprMatrices(N, mA);
	imprMatrices(N, mB);

    // Inicio de la medicion de tiempo
    InicioMuestra();

    // Algoritmo de multiplicacion de matrices
	multiMatrizClasica(N, mA, mB, mC);

    // Impresion de la matriz resultado
    imprMatrices(N, mC);

    // Impresion del tiempo de ejecucion, el if se usa solo para mejorar el formato de salida
    if(N<9){// En caso de que se impriman las matrices se necesita un doble salto
        printf("\n\n Tiempo en microsegundos:");
    }else{// En caso de que no se impriman las matrices se necesita un solo salto
        printf("\nTiempo en microsegundos:");
    }

    // Fin de la medicion de tiempo
	FinMuestra();	

    // Salto de linea para mejorar el formato de salida
    printf("\n");

    /** Se libera la emoria de las matrices **/
	free(mA);
    free(mB);
    free(mC);

    // Final del programa
    return 0;
}
