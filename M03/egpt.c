#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 7

typedef struct x {
	int k;
	double v;
} x;

void le_matriz(double a[N][N+1]){
    int temp;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            fscanf(stdin, "%lf", &a[i][j]);
        }
    }
    for(int i = 0; i < N; i++){
        fscanf(stdin, "%lf", &a[i][N]);
    }
}

void mostra_matriz(double a[N][N+1]){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N+1; j++){
			printf("%+.9E ", a[i][j]);
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

void troca_coluna(double a[N][N+1], x xarray[N], int l1, int l2){
	double temp;
	for(int i = 0; i < N; i++){
		temp = a[i][l1];
		a[i][l1] = a[i][l2];
		a[i][l2] = temp;
	}
	int itemp = xarray[l1].k;
	xarray[l1].k = xarray[l2].k;
	xarray[l2].k = itemp;
}

void inicia_xarray(x xarray[N]){
	for(int i = 0; i < N; i++) xarray[i].k = i;
}

void ordena_xarray(x xarray[N]){
    int j;
    x temp;
    for(int i = 1; i < N; i++){
        temp = xarray[i];
        j = i;
        while(j > 0 && xarray[j-1].k > temp.k){
            xarray[j] = xarray[j-1];
            j--;
        }
        xarray[j] = temp;
    }
}

int main(){
	int i, j, k, lmax, cmax;
	double mult, max;
	double a[N][N+1];

    le_matriz(a);
    mostra_matriz(a);
	x xarray[N];
	inicia_xarray(xarray);
	//iterando sobre a matriz
	for(i = 0; i < N-1; i++){
		max = a[i][i];
		lmax = i;
		//encontrando valor maximo
		for(j = i; j < N; j++){
			for(k = i; k < N; k++){
				if(fabs(a[j][k]) > max){
					lmax = j;
					cmax = k;
					max = fabs(a[j][k]);
				}
			}
		}
		if(lmax != i) troca_linha(a, i, lmax);
		if(cmax != i) troca_coluna(a, xarray, i, cmax);
		for(j = i+1; j < N; j++){
			mult = a[j][i] / a[i][i];
			a[j][i] = 0.0;
			for(k = i+1; k <= N; k++) a[j][k] += (-mult * a[i][k]);	
		}
        printf("A_%d:\n", i+1);
        mostra_matriz(a);
	}

	//resolvendo os sistemas formados
	for(i = N-1; i > -1; i--){
		xarray[i].v = a[i][N];
		for(j = N-1; j > i; j--){
			xarray[i].v -= a[i][j] * xarray[j].v;
		}
		xarray[i].v /= a[i][i];	
	}
    ordena_xarray(xarray);
	for(i = 0; i < N; i++){
		printf("x_%d: %.10g\n", (xarray[i].k)+1, xarray[i].v);
	}
	printf("\n");

	return 0;
}
