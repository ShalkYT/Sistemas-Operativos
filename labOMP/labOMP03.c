/**********************************************
* Pontificia Universidad javeriana
* Autor: Andres Eduardo Meneses Rincon
* Materia: Sistemas operativos
* Tema: Introduccion a OpenMP
* Descripcion:
* 	- Uso de distintos tipos de variables para una tarea dividida en varios hilos
***********************************************/

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Declaracion de variables
    int i;
    const int N = 1000;
    int a = 50;
    int b = 0;

    // Region paralela, tomamos i como privado para que no se comparta y se confuda la informacion
    #pragma omp parallel for private(i) private(a)
    for(i = 0; i<N; i++){
        // Aumento en b, el valor final sera el del ultimo hilo
        b = a +i;
    }
    
    // Impresion por consola para confirmar la informacion (es probable que b no concuerde, ya que se esta tomando cualquier valor final de b y ademas no se esta teniendo cuidado en su acceso)
    printf("a = %d b = %d (se espera a=50 y b = 1049)\n", a, b);

    // Fin del programa
    return 0;
}