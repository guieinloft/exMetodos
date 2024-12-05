#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define PREC 0.000001

double c1, c2, c3, c4;


double trapezio(double x0, double h, double *f(double x)) {
    return h / 2 * (f(x0 + h) + f(x0));
}
