/*#######################################################################################
 #* Fecha: 14/11/2025
 #* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
#* Programa:
#*      Multiplicación de Matrices algoritmo clásico
#* Versión:
#*      Paralelismo con Hilos Pthreads "Posix" 
######################################################################################*/

#include "moduloClasicaPosix.h"

int main(int argc, char *argv[]){
	if (argc < 3){
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		exit(0);	
	}
    int N = atoi(argv[1]); 
    int n_threads = atoi(argv[2]); 

    pthread_t p[n_threads];
    pthread_attr_t atrMM;

	matrixA  = (double *)calloc(N*N, sizeof(double));
	matrixB  = (double *)calloc(N*N, sizeof(double));
	matrixC  = (double *)calloc(N*N, sizeof(double));

	iniMatrix(matrixA, matrixB, N);
	// impMatrix(matrixA, N);
	// impMatrix(matrixB, N);

	InicioMuestra();

	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

    for (int j=0; j<n_threads; j++){
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = N;

        pthread_create(&p[j],&atrMM,multiMatrix,(void *)datos);
	}

    for (int j=0; j<n_threads; j++)
        pthread_join(p[j],NULL);

	FinMuestra();
	printf(";%d;%d \n", N, n_threads);
	
	// impMatrix(matrixC, N);

	/*Liberación de Memoria*/
	free(matrixA);
	free(matrixB);
	free(matrixC);

	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit (NULL);

	return 0;
}

