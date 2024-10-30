#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 7
#define PREC 0.00001

void mostra_array(double a[N]){
    for(int i = 0; i < N; i++) printf("%+.9E ", a[i]);
    putchar('\n');
}

void le_sistema(double a[N][N], double b[N]){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%lf", &a[i][j]);
        }
    }
    for(int i = 0; i < N; i++){
        scanf("%lf", &b[i]);
    }
}

double calc_err(double a[N], double b[N], double err[N]){
    double err_max = 0;
    for(int i = 0; i < N; i++){
        err[i] = fabs((a[i]-b[i])/a[i]);
        if(err[i] > err_max) err_max = err[i];
    }
    return err_max;
}

void jacobi(double a[N][N], double b[N], double x[N]){
    double xp[N], err[N], soma, err_max = 10;
    int i, j, k = 1;
    for(i = 0; i < N; i++) xp[i] = 0.0;
    printf("x_00: ");
    mostra_array(xp);
    printf("E_00: ---              ---              ---              ---              ---              ---              ---              \n\n");

    while(err_max > PREC){
        for(i = 0; i < N; i++){
            soma = 0;
            for(j = 0; j < N; j++){
                if(i != j) soma += (a[i][j] * xp[j]) / a[i][i];
            }
            x[i] = (b[i] / a[i][i]) - soma;
        }
        err_max = calc_err(x, xp, err);
        printf("x_%02d: ", k);
        mostra_array(x);
        printf("E_%02d: ", k);
        mostra_array(err);
        putchar('\n');
        for(i = 0; i < N; i++) xp[i] = x[i];
        k++;
    }
}

int main(){
    double a[N][N], b[N], x[N];
    le_sistema(a, b);
    jacobi(a, b, x);
}
