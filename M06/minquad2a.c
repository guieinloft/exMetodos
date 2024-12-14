#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 15

void load_xy(double r[N][4]) {
    for (int i = 0; i < N; i++) {
        fscanf(stdin, "%lf %lf", &r[i][0], &r[i][1]);
    }
}

void fill_results(double r[N][4], double s[4]) {
    for (int j = 0; j < 4; j++) {
        s[j] = 0.0;
    }
    for (int i = 0; i < N; i++) {
        r[i][1] = log(r[i][1]);
        r[i][2] = r[i][0] * r[i][0];
        r[i][3] = r[i][0] * r[i][1];
        
        s[0] += r[i][0];
        s[1] += r[i][1];
        s[2] += r[i][2];
        s[3] += r[i][3];
    }
}

void plot_gr(char *name, double a[2], double l_lim, double r_lim) {
    double incr = (r_lim - l_lim)/1000;
    double x, y;
    FILE *file = fopen(name, "w");
    for (int i = 0; i < 1000; i++) {
        x = l_lim + i * incr;
        y = a[0] * pow(a[1], x);
        fprintf(file, "%.6g %.6g\n", x, y);
    }
    fclose(file);
}

void print_table(double r[N][4], double s[4]) {
    // printf("%- 3s %- 14s %- 15s %- 15s %- 16s %- 14s %- 16s %- 15s\n", "k", "xₖ", "x²ₖ", "x³ₖ", "x⁴ₖ", "yₖ", "yₖxₖ", "yₖx²ₖ");
    for (int i = 0; i < N; i++) {
        printf("%02d", i+1);
        for (int j = 0; j < 4; j++) {
            printf(" %- 12.6g", r[i][j]);
        }
        putchar('\n');
    }
    printf(" Σ");
    for (int j = 0; j < 4; j++) {
        printf(" %- 12.6g", s[j]);
    }
    putchar('\n');
}

int main(int argc, char **argv) {
    double r[N][4], s[4], a[2];
    int k, i, j;

    load_xy(r);
    fill_results(r, s);
    print_table(r, s);

    // linear:
    printf("\nAJUSTE LINEAR:\n");
    a[0] = (s[2] * s[1] - s[0] * s[3]) / (N * s[2] - s[0] * s[0]);
    a[1] = (N * s[3] - s[0] * s[1]) / (N * s[2] - s[0] * s[0]);
    printf("a₀ = %- 12.6g a₁ = %- 12.6g\n", a[0], a[1]);

    // ajuste exponencial:
    a[0] = pow(M_E, a[0]);
    a[1] = pow(M_E, a[1]);
    printf("a = %- 12.6g b = %- 12.6g\n", a[0], a[1]);

    plot_gr("gr/exp.dat", a, floor(r[0][0]) - 1, ceil(r[N-1][0]) + 1);

    return 0;
}
