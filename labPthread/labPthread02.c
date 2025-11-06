#include <stdio.h>
#include <pthread.h>


pthread_mutex_t mutex01 = PTHREAD_MUTEX_INITIALIZER;
int contador = 0;

void *print_message_function(void *ptr){
	int i = *(int *)(ptr);
	printf("Numero de hilo: %d | Hilo ID: %d\n", i, pthread_self());
	pthread_mutex_lock(&var_mutex);
	contador++;
	pthread_mutex_unlock(&var_mutex);
}

int main(){
	pthread_t hilos[NHILOS];

	int i, j;

	for(i = ; i < NHILOS; i++){
		pthread_create(&hilos[i], NULL, print_message_function, &i)
	}

	printf("El hilo 1 retorna: \n", );
	printf("El hilo 2 retorna: \n", );

	return 0;
}
