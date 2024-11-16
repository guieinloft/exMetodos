#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void fill_x_y(double mat[N][N+1]){
    for(int i = 0; i < N; i++){
        scanf("%lf %lf", &mat[i][0], &mat[i][1]);
    }
}

void order_x_y(double mat[N][N+1], double z) {
    for (int i = 1; i < N; i++) {
        double temp_x = mat[i][0];
        double temp_y = mat[i][1];
        int j = i;
        while (j > 0 && fabs(temp_x - z) < fabs(mat[j-1][0] - z)) {
            mat[j][0] = mat[j-1][0];
            mat[j][1] = mat[j-1][1];
            j--;
        }
        mat[j][0] = temp_x;
        mat[j][1] = temp_y;
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
            if(j > N-i) printf("-------");
            else printf("%+.6g", mat[i][j]);
            if(j < N) putchar(',');
        }
        putchar('\n');
    }
}

void get_pz(double pz[N], double mat[N][N+1], double z, int i){
    pz[i] = mat[0][i+1];
    for(int j = 0; j < i; j++){
        pz[i] *= (z - mat[j][0]);
    }
    if(i != 0) pz[i] += pz[i-1];
}

void print_pz(double pz[1000][N]){
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < N; j++){
            printf("%+.6g,", i, pz[i][j]);
        }
        putchar('\n');
    }
}

void plot_csv(int n, double pz[1000][N]){
    char fname[32];
    FILE *file;
    sprintf(fname, "plot_%02d.dat", n);
    file = fopen(fname, "w");
    for(int i = 0; i < 1000; i++) fprintf(file, "%.6g %.6g\n", 2.0*i/1000, pz[i][n]);
    fclose(file);
}

int main(){
    double mat[N][N+1];
    double z;
    double pz[1000][N];
    fill_x_y(mat);
    scanf("%lf", &z);
    order_x_y(mat, z);
    for(int i = 2; i < N+1; i++){
        get_dd(mat, i);
    }
    print_mat(mat);
    putchar('\n');
    for(int i = 0; i < 1000; i++){
        for(int j = 0; j < N; j++){
            get_pz(pz[i], mat, 2.0*i/1000, j);
        }
    }
    for(int i = 0; i < N; i++){
        plot_csv(i, pz);
    }
    return 0;
}
