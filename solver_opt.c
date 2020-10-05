/*
 * Tema 2 ASC
 * 2020 Spring
 */
#include "utils.h"

/*
 * Add your optimized implementation here
 */
double* my_solver(int N, double *A, double* B) {
	printf("OPT SOLVER\n");
	double *aux1 = (double *)calloc(N * N, sizeof(double));
	double *aux2 = (double *)calloc(N * N, sizeof(double));
	double *aux3 = (double *)calloc(N * N, sizeof(double));
	double *rez = (double *)calloc(N * N, sizeof(double));
	double *At = (double *)calloc(N * N, sizeof(double));
	double *p1, *p2, *p;
	register double suma;
	int index = -1;
	int i, j, k;
	//se foloseste metoda register pentru suma, si pointeri pentru
	//a minimaliza accesul la matrice
	
	//A transpus
	for (i = 0; i < N; ++i) {
		p = &A[i * N];
		for (j = 0; j < N; ++j) {
			index = j * N + i;
			At[index] = *p;
			p++;
		}
	}
	//A^2
	for (i = 0; i < N; ++i) {
		p = &A[i * N];
		for (j = 0; j < N; ++j) {
			if (i<=j) {
				suma = 0.0;
				p1 = p;
				p2 = &A[j];
				index = i * N + j;
				for (k = 0; k < N; ++k) {
					suma += *p1 * *p2;
					p1++;
					p2 += N;
				}
				aux1[index] = suma;
			}
		}
	}
	//A^2*B
	for (i = 0; i < N; ++i) {
		p = &aux1[i * N];
		for (j = 0; j < N; ++j) {
			p1 = p;
			p2 = &B[j];
			suma = 0.0;
			index = i * N + j;
			for (k = 0; k < N; ++k) {
				suma += *p1 * *p2;
				p1++;
				p2 += N;
			}
			aux2[index] = suma;
		}
	}
	//B*At
	for (i = 0; i < N; ++i) {
		p = &B[i * N];
		for (j = 0; j < N; ++j) {
			p1 = p;
			p2 = &At[j];
			suma = 0.0;
			for (k = 0; k < N; ++k) {
				suma += *p1 * *p2;
				p1++;
				p2 += N;
			}
			index = i * N + j;
			aux3[index] = suma;
		}
	}
	//rezultatul final
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			rez[i*N + j] = aux3[i*N + j] + aux2[i*N + j]; 
		}
	}
	free(aux1);
	free(aux2);
	free(At);
	free(aux3);
	return rez;	
}