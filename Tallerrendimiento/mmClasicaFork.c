
/*#######################################################################################
 #* 
 #* 
 #* Descripción:
 #*    Programa principal, multiplicacion de matrices con fork()
 #*    
 #*    
 #* Docente:  J. Corredor, PhD 
 #* Autores:
 #* 
 #*    
#######################################################################################*/

#include "moduloClasicaFork.h"

/* 
 * Lee N y número de procesos, reparte las filas entre procesos hijos,
 * y mide el tiempo total de la multiplicación.
 */
int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("\n \t\tUse: $./mmClasicaFork Size Hilos \n");
		exit(0);
	}

	int N     = (int) atoi(argv[1]);
	int num_P = (int) atoi(argv[2]);

	double *matA = (double *) calloc(N*N, sizeof(double));
	double *matB = (double *) calloc(N*N, sizeof(double));
	double *matC = (double *) calloc(N*N, sizeof(double));

	if(matA == NULL || matB == NULL || matC == NULL){
		fprintf(stderr, "Error reservando memoria\n");
		return 1;
	}

	srand(time(0)); 

	iniMatrix(matA, matB, N);
	// impMatrix(matA, N);
	// impMatrix(matB, N);

	int rows_per_process = N / num_P;

	InicioMuestra();

	/* Creamos num_P procesos hijos y repartimos las filas de la matriz resultado. */
	for (int i = 0; i < num_P; i++) {
		pid_t pid = fork();

		if (pid == 0) { 
			int start_row = i * rows_per_process;
			int end_row   = (i == num_P - 1) ? N : start_row + rows_per_process;

			multiMatrix(matA, matB, matC, N, start_row, end_row); 

			if(N < 9){
				for (int r = start_row; r < end_row; r++) {
					for (int c = 0; c < N; c++) {
						/* Aquí podrías imprimir matC si quisieras verlo. */
						// printf(" %.2f ", matC[N*r+c]);
					}
					// printf("\n");
				}
			}
			exit(0); 
		} else if (pid < 0) {
			perror("fork failed");
			exit(1);
		}
	}

	/* Esperamos a que terminen todos los procesos hijos. */
	for (int i = 0; i < num_P; i++) {
		wait(NULL);
	}

	FinMuestra(); 
	printf(";%d;%d\n", N, num_P);

	free(matA);
	free(matB);
	free(matC);

	return 0;
}
