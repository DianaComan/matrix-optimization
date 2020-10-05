/*
 *  * Tema 2 ASC
 *   * 2020 Spring
 *    */
#include "utils.h"
#include "cblas.h"

/* 
 *  * Add your BLAS implementation here
 *   */
double* my_solver(int N, double *A, double *B) {
	printf("BLAS SOLVER\n");
	
	double *aux1 = (double *)calloc(N * N, sizeof(double));
	double *aux2 = (double *)calloc(N * N, sizeof(double));
	double *aux3 = (double *)calloc(N * N, sizeof(double));
	double *rez = (double *)calloc(N * N, sizeof(double));
	int i, j;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			aux2[i *N + j] = A[i * N + j];
		}
	}
	//se foloseste dgmemm pentru inmultire normala si dtrmm pt A^2
	//deoarece A este matrice supra triunghiulara
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasTrans, N,
		N, N, 1, B, N, A, N, 0, aux1, N);
	cblas_dtrmm(CblasRowMajor, CblasRight, CblasUpper, CblasNoTrans,
		CblasNonUnit, N, N, 1, A, N, aux2, N);
	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N,
		N, N, 1, aux2, N, B, N, 0, aux3, N);
	//in rez se calculeaza suma dintre A^2*B si B*At
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			rez[i * N + j] = aux1[i * N + j] + aux3[i * N + j]; 
		}
	}
	free(aux1);
	free(aux2);
	free(aux3);
	return rez;
}