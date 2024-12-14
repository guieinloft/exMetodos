#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 15

void load_xy(double r[N][2]) {
    for (int i = 0; i < N; i++) {
        fscanf(stdin, "%lf %lf", &r[i][0], &r[i][1]);
    }
}

void change(double r[N][2]) {
    for (int i = 0; i < N; i++) {
        r[i][0] = pow(M_E, r[i][0]); 
        r[i][1] = pow(M_E, r[i][1]); 
    }
}

int main() {
    double r[N][2];
    load_xy(r);
    change(r);
    for (int i = 0; i < N; i++) {
        printf("%.6g %.6g\n", r[i][0], r[i][1]);
    }
    return 0;
}
