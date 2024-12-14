#ifndef LEGENDRE_H
#define LEGENDRE_H

#define L_PREC 2048

double legendre(int n, double x);
double a_legendre(int n, double f(double x));
double ea_legendre(int i, double a[11]);
double er_legendre(int i, double ea[10]);
double aprox_legendre(double x, int degree, double a[11]);

#endif
