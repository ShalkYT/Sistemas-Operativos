/*#######################################################################################
 #* Fecha: 14/11/2025
 #* Autor: Andres Eduardo Meneses Rincon y Karol Dayan Torres Vides
 #* Programa:
 #*      Multiplicación de Matrices algoritmo matriz Transpuesta (Filas x Filas) 
 #* Versión:
 #*      Paralelismo con OpenMP
 #######################################################################################*/

#include "moduloFilasOpenMP.h"

int main(int argc, char *argv[]){
	if(argc < 3){
		printf("\n Use: $./clasicaOpenMP SIZE Hilos \n\n");
		exit(0);
	}


	int N = atoi(argv[1]);
	int TH = atoi(argv[2]);
	double *matrixA  = (double *)calloc(N*N, sizeof(double));
	double *matrixB  = (double *)calloc(N*N, sizeof(double));
	double *matrixC  = (double *)calloc(N*N, sizeof(double));
	srand(time(NULL));

	omp_set_num_threads(TH);

	iniMatrix(matrixA, matrixB, N);

	// impMatrix(matrixA, N, 0);
	// impMatrix(matrixB, N, 1);

	InicioMuestra();
	multiMatrixTrans(matrixA, matrixB, matrixC, N);
	FinMuestra();
	printf(";%d;%d \n", N, TH);

	// impMatrix(matrixC, N, 0);

	/*Liberación de Memoria*/
	free(matrixA);
	free(matrixB);
	free(matrixC);
	
	return 0;
}
