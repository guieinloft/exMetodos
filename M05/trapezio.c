#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define PREC 0.000001

double c1, c2, c3, c4;

double g(double x) {
    return 2 * cos(2 * M_PI * x * (c3 - c4 * x));
}

double f(double x) {
    return sin(2 * M_PI * (x * (c1 - c2 * x) + g(x)));
}

double e(double x) {
    return pow(M_E, -x) * f(x);
}

double trapezio(double x0, double h) {
    return h / 2 * (e(x0 + h) + e(x0));
}

int main(int argc, char **argv) {
    double a, b, r, h_subint, area, area_ant, er;
    int i, n_subint;
    assert(argc == 7);
    a = atof(argv[1]);
    b = atof(argv[2]);
    c1 = atof(argv[3]);
    c2 = atof(argv[4]);
    c3 = atof(argv[5]);
    c4 = atof(argv[6]);

    r = (b - a) / 4;
    b = a + r;

    i = 0;
    do {
        area_ant = area;
        area = 0;
        n_subint = (int)pow(2, i);
        h_subint = r / n_subint;
        for(int j = 0; j < (int)pow(2, i); j++) {
            area += trapezio(a + j * h_subint, h_subint);
        }
        er = fabs((area - area_ant)/area);
        printf("%d: %.10g, %.10g\n", i, area, er);
        i++;
    } while (er > PREC);
    return 0;
}
