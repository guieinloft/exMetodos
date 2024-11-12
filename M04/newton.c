#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void fill_x_y(double mat[N][N+1]){
    for(int i = 0; i < N; i++){
        scanf("%lf %lf", &mat[i][0], &mat[i][1]);
    }
}

void get_dd(double mat[N][N+1], int col){
    for(int i = 0; i <= N-col; i++){
        mat[i][col] = (mat[i+1][col-1] - mat[i][col-1])/(mat[i+col-1][0] - mat[i][0]);
    }
}

void print_mat(double mat[N][N+1]){
    printf("x,y,");
    for(int i = 1; i < N-1; i++) printf("DD%d,", i);
    printf("DD%d\n", N-1);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N+1; j++){
            if(j > N-i) printf("%+.6g", 0.0);
            else printf("%+.6g", mat[i][j]);
            if(j < N) putchar(',');
        }
        putchar('\n');
    }
}

void get_pz(double pz[N+1], double mat[N][N+1], double z, int i){
    pz[i] = mat[0][i+1];
    for(int j = 0; j < i; j++){
        pz[i] *= (z - mat[j][0]);
    }
    if(i != 0) pz[i] += pz[i-1];
}

void print_pz(double pz[N+1]){
    printf("k,P_k(z),ER\n");
    for(int i = 0; i < N+1; i++){
        printf("%d,%+.6g,", i, pz[i]);
        if(i > 0) printf("%.6g\n", fabs(pz[i] - pz[i-1])/fabs(pz[i]));
        else printf("-------\n");
    }
}

int main(){
    double mat[N][N+1];
    double z;
    double pz[N+1];
    fill_x_y(mat);
    scanf("%lf", &z);
    for(int i = 2; i < N+1; i++){
        get_dd(mat, i);
    }
    print_mat(mat);
    putchar('\n');
    for(int i = 0; i < N+1; i++){
        get_pz(pz, mat, z, i);
    }
    print_pz(pz);
    return 0;
}
