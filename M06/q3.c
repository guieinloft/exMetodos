#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include "legendre.h"
#include "trig.h"

#define INT_PREC 16

double c0, c1, c2;

double f(double x) {
    return cos(c0 + sin(c1 * x) / (x * x + 1)) + sin(c2 * x * x);
}

void plot_func(void) {
    FILE *file = fopen("gr/func.dat", "w");
    double incr = 1.0/500;
    double x, y;
    for (int i = 0; i < 1000; i++) {
        x = -1 + i * incr;
        y = f(x);
        fprintf(file, "%.6g %.6g\n", x, y);
    }
    fclose(file);
}

void plot_legendre(int degree, double a[11]) {
    char str[20];
    sprintf(str, "gr/legendre_%02d.dat", degree);
    FILE *file = fopen(str, "w");
    double incr = 1.0/500;
    double x, y;
    for (int i = 0; i < 1000; i++) {
        x = -1 + i * incr;
        y = aprox_legendre(x, degree, a);
        fprintf(file, "%.6g %.6g\n", x, y);
    }
    fclose(file);
}

void plot_trig(int degree, double a[11], double b[11]) {
    char str[20];
    sprintf(str, "gr/trig_%02d.dat", degree);
    FILE *file = fopen(str, "w");
    double incr = 1.0/500;
    double x, y;
    for (int i = 0; i < 1000; i++) {
        x = -1 + i * incr;
        y = aprox_trig(x, degree, a, b);
        fprintf(file, "%.6g %.6g\n", x, y);
    }
    fclose(file);
}

int main(int argc, char **argv) {
    assert(argc == 4);
    c0 = atof(argv[1]);
    c1 = atof(argv[2]);
    c2 = atof(argv[3]);
    plot_func();

    double al[11], at[11], bt[11];
    double ea_l[10], er_l[10];
    double ea_t[10], er_t[10];

    printf("%.6g %.6g %.6g\n", c0, c1, c2);
    for (int i = 0; i < 11; i++) {
        al[i] = a_legendre(i, f);
        printf("%+ 12.6g ", al[i]);
        if (i > 0) {
            ea_l[i-1] = ea_legendre(i, al);
            er_l[i-1] = er_legendre(i, ea_l);
            printf("%+ 12.6g %+ 12.6g", ea_l[i-1], er_l[i-1]);
        }
        else printf("% 12s %+ 12s", "---", "---");
        
        at[i] = a_trig(i, f);
        bt[i] = b_trig(i, f);
        printf("%+ 12.6g %+ 12.6g ", at[i], bt[i]);
        if (i > 0) {
            ea_t[i-1] = ea_trig(i, at, bt);
            er_t[i-1] = er_trig(i, at, bt);
            printf("%+ 12.6g %+ 12.6g", ea_t[i-1], er_t[i-1]);
        }
        else printf("% 12s %+ 12s", "---", "---");
        putchar('\n');
    }
    for (int i = 0; i < 11; i += 2) {
        plot_legendre(i, al);
        plot_trig(i, at, bt);
    }

    return 0;
}
