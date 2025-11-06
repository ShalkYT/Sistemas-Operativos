
#include <stdio.h>
#include <pthread.h>

void *print_message_function(void *ptr){
	char *mensaje;
	mensaje = (char *) ptr;
	printf("%s \n", mensaje);
}

int main(){
	pthread_t hilo1, hilo2;
	char *mensaje1 = "Soy el hilo 1";
	char *mensaje2 = "Soy el hilo 2";

	int iret1 = pthread_create(&hilo1, NULL, print_message_function, (void *)mensaje1);
	int iret2 = pthread_create(&hilo2, NULL, print_message_function, (void *)mensaje2);

	printf("El hilo 1 retorna: %d\n", iret1);
	printf("El hilo 2 retorna: %d\n", iret2);

	return 0;
}
