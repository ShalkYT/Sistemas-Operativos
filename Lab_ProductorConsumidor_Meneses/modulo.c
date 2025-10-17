/**************************************************************************************************
* Pontificia Universidad Javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas Operativos
* Descripción: Modulo con la implementacion de la funcion para invertir cadena
**************************************************************************************************/


#include "modulo.h"

// Implementacion de la funcion para invertir cadena
void reverse_string(char *str) { // La funcion recibe un puntero a char (cadena) y lo modifica directamente
    // Declaracion de variables
    int last, limit, first;
    char temp;
    last = strlen(str) - 1;
    limit = last/2;
    first = 0;

    // Ciclo para invertir la cadena
    while (first < last) {
        temp = str[first];
        str[first] = str[last];
        str[last] = temp;
        first++;
        last--;
    }

    // Fin de la funcion
    return;
}