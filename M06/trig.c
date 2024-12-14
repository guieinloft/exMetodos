#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#include "trig.h"

double a_trig(int k, double f(double x)) {
    double sum = 0;
    double h = 2.0 * M_PI/ T_PREC;
    double x0, x1, x2;
    for(int i = 0; i < T_PREC; i++) {
        x0 = (2 * (-M_PI + i * h) + h) / 2;
        x1 = 1/sqrt(3)*h/2 + x0;
        x2 = -1/sqrt(3)*h/2 + x0;
        sum += h/2*(f(x1) * cos(k * x1) + f(x2) * cos(k * x2));
        //printf("%.6g %.6g\n", x0, x0+h);
    }
    return ;
}

double b_trig(int k, double f(double x)) {
    double sum = 0;
    double h = 2 * M_PI / T_PREC;
    double x0, x1, x2;
    for(int i = 0; i < T_PREC; i++) {
        x0 = (2 * (-M_PI + i * h) + h) / 2;
        x1 = 1/sqrt(3)*h/2 + x0;
        x2 = -1/sqrt(3)*h/2 + x0;
        sum += h/2*(f(x1) * sin(k * x1) + f(x2) * sin(k * x2));
    }
    return (2 * k + 1) * sum / 2 * M_PI;
}

double ea_trig(int i, double a[11], double b[11]) {
    return M_PI * (a[i] * a[i] + b[i] * b[i]);
}

double er_trig(int i, double a[11], double b[11]) {
    double er = (a[i] * a[i] + b[i] * b[i]);
    double sum = 0;
    for (int j = 1; j <= i; j++) {
        sum += (a[j] * a[j] + b[j] * b[j]);
    }
    return er / (a[0]/4 + sum);
}

double aprox_trig(double x, int degree, double a[11], double b[11]) {
    double sum = a[0]/2;
    for (int i = 1; i <= degree; i++) {
        sum += (a[i] * cos(i * x) + b[i] * sin(i * x));
    }
    return sum;
}
