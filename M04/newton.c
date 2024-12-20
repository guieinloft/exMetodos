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
    printf("           x           y");
    for(int i = 1; i < N-1; i++) printf("         DD%d", i);
    printf("         DD%d\n", N-1);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N+1; j++){
            if(j > N-i) printf("         ---");
            else printf("% 12.6g", mat[i][j]);
        }
        putchar('\n');
    }
}

void get_pz(double pz[N][2], double mat[N][N+1], double z, int i){
    pz[i][0] = mat[0][i+1];
    for(int j = 0; j < i; j++){
        pz[i][0] *= (z - mat[j][0]);
    }
    if(i != 0){
        pz[i][0] += pz[i-1][0];
        pz[i][1] = fabs(pz[i][0] - pz[i-1][0])/fabs(pz[i][0]);
    }
}

int get_approx(double pz[N][2]) {
    int k = 2;
    for (int i = 3; i < N; i++) {
        if (pz[i][1] < pz[k][1]) k = i;
        else return k;
    }
}

void print_pz(double pz[N][2], int k){
    int index;

    printf("k        Pk(z)          ER\n");
    for(int i = 0; i < N; i++){
        printf("%d % 12.6g", i, pz[i][0]);
        if(i > 0) printf("% 12.6g\n", pz[i][1]);
        else printf("         ---\n");
    }
}

int main(){
    double mat[N][N+1];
    double z;
    double pz[N][2];
    int k;
    fill_x_y(mat);
    scanf("%lf", &z);
    order_x_y(mat, z);
    for(int i = 2; i < N+1; i++){
        get_dd(mat, i);
    }
    printf("Tabela de Diferenças Divididas:\n");
    print_mat(mat);
    putchar('\n');
    for(int i = 0; i < N; i++){
        get_pz(pz, mat, z, i);
    }
    k = get_approx(pz);
    printf("Aproximações:\n");
    print_pz(pz, k);
    printf("Aproximação mais confiável: %d: %.6g\n", k, pz[k][0]);
    return 0;
}
