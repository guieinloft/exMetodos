#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 7

void le_matriz(double a[N][N+1]){
    int temp;
    for(int i = 0; i < N; i++){
        for(int j = 0; j <= N; j++){
            fscanf(stdin, "%lf", &a[i][j]);
        }
    }
}

void mostra_matriz(double a[N][N+1]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N+1; j++){
			printf("%+.10E ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void troca_linha(double a[N][N+1], int l1, int l2){
	double temp;
	for(int i = 0; i <= N; i++){
		temp = a[l1][i];
		a[l1][i] = a[l2][i];
		a[l2][i] = temp;
	}
}

int main(){
	int i, j, k, lmax;
	double mult, max;
	double a[N][N+1];
	double x[N];

    le_matriz(a);
    mostra_matriz(a);
	//iterando sobre a matriz
	for(i = 0; i < N-1; i++){
		max = fabs(a[i][i]);
		lmax = i;
		//encontrando valor maximo na coluna i
		for(j = i+1; j < N; j++){
			if(fabs(a[j][i]) > max){
				lmax = j;
				max = fabs(a[j][i]);
			}
		}
		if(lmax != i) troca_linha(a, i, lmax);
		for(j = i+1; j < N; j++){
			mult = a[j][i] / a[i][i];
			a[j][i] = 0.0;
			for(k = i+1; k <= N; k++) a[j][k] += (-mult * a[i][k]);	
		}
        mostra_matriz(a);
	}
	for(i = 0; i < N; i++){
		for(j = 0; j < N+1; j++){
			printf("%+.10E ", a[i][j]);
		}
		printf("\n");
	}
	printf("\n");

	//resolvendo os sistemas formados
	for(i = N-1; i > -1; i--){
		x[i] = a[i][N];
		for(j = N-1; j > i; j--){
			x[i] -= (a[i][j] * x[j]);
		}
		x[i] /= a[i][i];	
	}
	for(i = 0; i < N; i++){
		printf("%+.10E ", x[i]);
	}
	printf("\n");

	return 0;
}
