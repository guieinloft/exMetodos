#ifndef TRIG_H
#define TRIG_H

#define T_PREC 2048

double a_trig(int k, double f(double x));
double b_trig(int k, double f(double x));
double ea_trig(int i, double a[11], double b[11]);
double er_trig(int i, double a[11], double b[11]);
double aprox_trig(double x, int degree, double a[11], double b[11]);

#endif
