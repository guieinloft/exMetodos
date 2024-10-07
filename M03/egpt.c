#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 4

typedef struct x {
	int k;
	double v;
} x;

void troca_linha(double a[N][N+1], int l1, int l2){
	double temp;
	for(int i = 0; i <= N; i++){
		temp = a[l1][i];
		a[l1][i] = a[l2][i];
		a[l2][i] = temp;
	}
}

void troca_coluna(double a[N][N+1], int l1, int l2){
	double temp;
	for(int i = 0; i < N; i++){
		temp = a[i][l1];
		a[i][l1] = a[i][l2];
		a[i][l2] = temp;
	}
}

void start_xarray(x *xarray[N]){
	for(int i = 0; i < N; i++) xarray[i].k = i;
}

int main(){
	int i, j, k, lmax;
	double mult, max;
	double a[N][N+1] = {{-17.0, 19.0, -3.0, 8.0, 86.0},
			{13.0, -10.0, -18.0, -20.0, -297.0},
			{-1.0, 15.0, -11.0, 9.0, 64.0},
			{-18.0, 2.0, 18.0, -7.0, 6.0}};

	x xarray[N];
	start_xarray(&xarray);

	//iterando sobre a matriz
	for(i = 0; i < N-1; i++){
		max = a[i][i];
		lmax = i;
		//encontrando valor maximo
		for(j = i; j < N; j++){
			//todo
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
			x[i] -= a[i][j] * x[j];
		}
		x[i] /= a[i][i];	
	}
	for(i = 0; i < N; i++){
		printf("%+.10E ", x[i]);
	}
	printf("\n");

	return 0;
}
