/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your unoptimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("NEOPT SOLVER\n");
	double *At = (double *)calloc(N * N, sizeof(double));
	double *aux1 = (double *)calloc(N * N, sizeof(double));
	double *aux2 = (double *)calloc(N * N, sizeof(double));
	double *aux3 = (double *)calloc(N * N, sizeof(double));
	double *rez = (double *)calloc(N * N, sizeof(double));
	int index = -1, i2 = -1, i3 = -1;
	int i, j, k;
	
	//At va contine A transpus
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (i <= j) {
				i2 = i * N + j;
				i3 = j * N + i;
				At[i3] = A[i2];
			}
		}
	}
	
	//aux1 va contine A patrat
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			index = i * N + j;
			if (i <= j) {
				for ( k = 0; k < N; k++) {
					i2 = i * N + k;
					i3 = k * N + j;
					aux1[index] += A[i2] * A[i3];
				}
			}
		}
	}
	//aux2 va contine A^2*B
	//aux3 va contine B*A^t
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			index = i * N + j;
			for (k = 0; k < N; k++) {
				i2 = i * N + k;
				i3 = k * N + j;
				aux2[index] += B[i2] * At[i3];
				aux3[index] += aux1[i2] * B[i3];
			}
		}
	}
	//in rez se aduca aux2 si aux3, obtinandu-se rezultatul dorit
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			rez[i*N + j] = aux3[i * N + j] + aux2[i*N + j]; 
		}
	}
	return rez;
}
