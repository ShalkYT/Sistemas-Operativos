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

#include "modulo.h"
#include <stdio.h>
#include <stdlib.h>

// Funcion main del programa
int main(int argc, char *argv[]) {

    // Confirmacion del correcto uso del programa (Confirmacion de 2 argumentos, el llamado y el tamaño de las matrices)
    if(argc != 2){
        printf("Numero argumentos incorrectos\n");
        printf("\n\t $ejecutable.exe TAMAÑO \n");
        return -1;
    }

    // Almacenamiento del argumento que contiene el tamaño en un variable
    int N = (int) atof(argv[1]);
    // Confirmacion de que el tamaño es mayor a 0
    if(N<=0){
        printf("\n Valores deben ser mayor que cero\n");
        return -1;
    };

    float *mA, *mB, *mC;

    /** Se le asigna memoria dinamica a los 3 apuntadores globales teniendo en cuenta el tamaño dado en los argumentos**/
    mA = (double *) malloc(N*N*sizeof(double));
    mB = (double *) malloc(N*N*sizeof(double));
    mC = (double *) calloc(N*N,sizeof(double));

	/** Se inicializan las 2 matrices **/
	iniMatriz(N, mA, mB);

	// Uso de funcion para imprimir matrices
	imprMatrices(N, mA);
	imprMatrices(N, mB);

     // Algoritmo de multiplicacion de matrices
     	InicioMuestra();
	multiMatrizClasica(N, mA, mB, mC);
	FinMuestra();

	imprMatrices(N, mC);

        /** Se libera la emoria de las matrices **/
	free(mA);
        free(mB);
        free(mC);
        return 0;
}
