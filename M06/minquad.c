#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 10

void load_xy(double r[N][7]) {
    for (int i = 0; i < N; i++) {
        fscanf(stdin, "%lf %lf", &r[i][0], &r[i][4]);
    }
}

void fill_results(double r[N][7], double s[7]) {
    for (int j = 0; j < 7; j++) {
        s[j] = 0.0;
    }
    for (int i = 0; i < 10; i++) {
        r[i][1] = r[i][0] * r[i][0];
        r[i][2] = r[i][1] * r[i][0];
        r[i][3] = r[i][2] * r[i][0];
        r[i][5] = r[i][4] * r[i][0];
        r[i][6] = r[i][4] * r[i][1];
        
        s[0] += r[i][0];
        s[1] += r[i][1];
        s[2] += r[i][2];
        s[3] += r[i][3];
        s[4] += r[i][4];
        s[5] += r[i][5];
        s[6] += r[i][6];
    }
}

void print_table(double r[N][7], double s[7]) {
    printf("%- 3s %- 14s %- 15s %- 15s %- 16s %- 14s %- 16s %- 15s\n", "k", "xₖ", "x²ₖ", "x³ₖ", "x⁴ₖ", "yₖ", "yₖxₖ", "yₖx²ₖ");
    for (int i = 0; i < N; i++) {
        printf("%02d", i+1);
        for (int j = 0; j < 7; j++) {
            if (j == 1) printf(" %- 12.6g", r[i][4]);
            else if (j > 1 && j < 5) printf(" %- 12.6g", r[i][j-1]);
            else printf(" %- 12.6g", r[i][j]);
        }
        putchar('\n');
    }
    printf(" Σ");
    for (int j = 0; j < 7; j++) {
        if (j == 1) printf(" %- 12.6g", s[4]);
        else if (j > 1 && j < 5) printf(" %- 12.6g", s[j-1]);
        else printf(" %- 12.6g", s[j]);
    }
    putchar('\n');
}

void plot_gr(char *name, int degree, double a[3], double l_lim, double r_lim) {
    double incr = (r_lim - l_lim)/1000;
    double x, y;
    FILE *file = fopen(name, "w");
    for (int i = 0; i < 1000; i++) {
        x = l_lim + i * incr;
        y = a[0];
        for (int j = 1; j <= degree; j++) {
            y += a[j] * pow(x, j);
        }
        fprintf(file, "%.6g %.6g\n", x, y);
    }
    fclose(file);
}

void print_system(double b[3][4]) {
    for (int i = 0; i < 3; i++) {
        printf("% 12.6ga₀ + % 12.6ga₁ + % 12.6ga₂ = % 12.6g\n", b[i][0], b[i][1], b[i][2], b[i][3]);
    }
}

int main(int argc, char **argv) {
    double r[N][7], s[7], b[3][4], a[3], mult;
    int k, i, j;

    load_xy(r);
    fill_results(r, s);
    print_table(r, s);

    // linear:
    printf("\nAJUSTE LINEAR:\n");
    a[0] = (s[1] * s[4] - s[0] * s[5]) / (N * s[1] - s[0] * s[0]);
    a[1] = (N * s[5] - s[0] * s[4]) / (N * s[1] - s[0] * s[0]);
    printf("a₀ = %- 12.6g a₁ = %- 12.6g\n", a[0], a[1]);
    plot_gr("gr/lin.dat", 2, a, floor(r[0][0]) - 1, ceil(r[N-1][0]) + 1);

    // quadratic:
    printf("\nAJUSTE QUADRÁTICO:\n");
    for (i = 0; i < 3; i++) {
        if (i > 0) b[i][0] = s[i-1];
        else b[i][0] = N;
        b[i][1] = s[i];
        b[i][2] = s[i+1];
        b[i][3] = s[i+4];
    }
    printf("\nSISTEMA LINEAR:\n");
    print_system(b);
	for (i = 0; i < 4; i++){
		for (j = i+1; j < 3; j++){
			mult = b[j][i] / b[i][i];
			b[j][i] = 0.0;
			for(k = i+1; k <= 3; k++) b[j][k] -= (mult * b[i][k]);	
		}
	}
	for(i = 2; i > -1; i--){
		a[i] = b[i][3];
		for(j = 2; j > i; j--){
			a[i] -= b[i][j] * a[j];
		}
		a[i] /= b[i][i];	
	}
    printf("\nSOLUÇÃO:\n");
	printf("a₀ = %- 12.6g a₁ = %- 12.6g a₂ = %- 12.6g\n", a[0], a[1], a[2]);
    putchar('\n');
    plot_gr("gr/quad.dat", 2, a, floor(r[0][0]) - 1, ceil(r[N-1][0]) + 1);

    return 0;
}
