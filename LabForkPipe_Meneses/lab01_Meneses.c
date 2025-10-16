/*********************************************
* Pontificia universidadjaveriana *
* Autor: Andres Eduardo Meneses Rincon *
* Fecha: 9/10/2025 *
* Materia: Sistemas operatvos *
* Tema:
*	- Identificacion de pocesos padre e hijo
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(){
	// Se invoca la creacion del proceso en un entero para identificarlo
	int proccesID = fork();

	// Se duplica el proceso
	if(proccesID == 0) { // Cuando fork() retorna0 sgnifica que es el hijo
		printf("fork() devuelve 0, ese es el proceso hijo con ID:%d \n\n", getpid()); // Mensaje para identificar al hijo
	}else{ //En caso de que seamayor es el padre (si esnegativo hubo un error pero ese caso no lo tomamos)
		printf("fork() devuelve un valor diferente de 0, ese es el proceso padre con ID: %d \n\n", getpid()); // Mensaje para identificar al padre
	}

	// Impresion y retun paraterminar el programa
	printf("Fin del programa\n");
	return 0;
}
