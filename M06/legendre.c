#include <stdlib.h>
#include <math.h>

#include "legendre.h"

double legendre(int n, double x) {
    if (n == 0) return 1;
    if (n == 1) return x;
    n--;
    return ((2*n+1) * x * legendre(n, x) - n * legendre(n-1, x))/(n + 1);
}

double a_legendre(int n, double f(double x)) {
    double sum = 0;
    double h = 2.0/L_PREC;
    double x0, x1, x2;
    for(int i = 0; i < L_PREC; i++) {
        x0 = (2 * (-1 + i * h) + h) / 2;
        x1 = 1/sqrt(3)*h/2 + x0;
        x2 = -1/sqrt(3)*h/2 + x0;
        sum += h/2*(f(x1) * legendre(n, x1) + f(x2) * legendre(n, x2));
    }
    return (2 * n + 1) * sum / 2;
}

double ea_legendre(int i, double a[11]) {
    return 2 * a[i] * a[i] / (2 * i + 1);
}

double er_legendre(int i, double ea[10]) {
    double er = ea[i-1];
    double sum = 0;
    for (int j = 0; j < i; j++) {
        sum += ea[j];
    }
    return er / sum;
}

double aprox_legendre(double x, int degree, double a[11]) {
    double sum = 0;
    for (int i = 0; i <= degree; i++) {
        sum += (a[i] * legendre(i, x));
    }
    return sum;
}
