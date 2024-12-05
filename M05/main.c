#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdbool.h>

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

double trapezio(double x0, double h, double (*f)(double x)) {
    return h / 2 * (f(x0 + h) + f(x0));
}

double simpson(double x0, double h, double (*f)(double x)) {
    return h/3 * (f(x0) + 4*f(x0 + h) + f(x0 + 2*h));
}

double gauss_2pts(double x0, double h, double (*f)(double x)) {
    double c1 = 1, c2 = 1;
    x0 = (2*x0 + h)/2;
    double x1 = 1/sqrt(3)*h/2 + x0;
    double x2 = -1/sqrt(3)*h/2 + x0;
    return h/2*(c1*f(x1) + c2*f(x2));
}

double gauss_3pts(double x0, double h, double (*f)(double x)) {
    double c0 = 8.0/9, c1 = 5.0/9, c2 = 5.0/9;
    x0 = (2*x0 + h)/2;
    double x1 = sqrt(0.6)*h/2 + x0;
    double x2 = -sqrt(0.6)*h/2 + x0;
    return h/2*(c0*f(x0) + c1*f(x1) + c2*f(x2));
}

int main(int argc, char **argv) {
    double a, b, r, h_subint;
    double area_trap = 0, area_ant_trap = 0, er_trap = 1;
    double area_simp = 0, area_ant_simp = 0, er_simp = 1;
    double area_g2 = 0, area_ant_g2 = 0, er_g2 = 1;
    double area_g3 = 0, area_ant_g3 = 0, er_g3 = 1;
    bool cont_trap = 1, cont_simp = 1, cont_g2 = 1, cont_g3 = 1;
    int i, n_subint;
    assert(argc == 7);
    a = atof(argv[1]);
    b = atof(argv[2]);
    c1 = atof(argv[3]);
    c2 = atof(argv[4]);
    c3 = atof(argv[5]);
    c4 = atof(argv[6]);

    r = (b - a) / 4;

    i = 0;
    printf("k               A_T             ER_T              A_S             ER_S             A_G2            ER_G2             A_G3            ER_G3\n");
    do {
        area_ant_trap = area_trap * cont_trap;
        area_ant_simp = area_simp * cont_simp;
        area_ant_g2 = area_g2 * cont_g2;
        area_ant_g3 = area_g3 * cont_g3;
        area_trap = area_trap * !cont_trap;
        area_simp = area_simp * !cont_simp;
        area_g2 = area_g2 * !cont_g2;
        area_g3 = area_g3 * !cont_g3;
        n_subint = (int)pow(2, i);
        h_subint = r / n_subint;
        for(int j = 0; j < (int)pow(2, i); j++) {
            area_trap += trapezio(a + j * h_subint, h_subint, e) * cont_trap;
            area_simp += simpson(a + r + j * h_subint, h_subint/2, e) * cont_simp;
            area_g2 += gauss_2pts(a + 2*r + j * h_subint, h_subint, e) * cont_g2;
            area_g3 += gauss_3pts(a + 3*r + j * h_subint, h_subint, e) * cont_g3;
        }
        if (cont_trap) er_trap = fabs((area_trap - area_ant_trap)/area_trap);
        if (cont_simp) er_simp = fabs((area_simp - area_ant_simp)/area_simp);
        if (cont_g2) er_g2 = fabs((area_g2 - area_ant_g2)/area_g2);
        if (cont_g3) er_g3 = fabs((area_g3 - area_ant_g3)/area_g3);
        printf("%02d ", i);
        printf("% 16.10g % 16.10g ", area_trap, er_trap);
        printf("% 16.10g % 16.10g ", area_simp, er_simp);
        printf("% 16.10g % 16.10g ", area_g2, er_g2);
        printf("% 16.10g % 16.10g\n", area_g3, er_g3);
        cont_trap = er_trap >= PREC;
        cont_simp = er_simp >= PREC;
        cont_g2 = er_g2 >= PREC;
        cont_g3 = er_g3 >= PREC;
        i++;
    } while (cont_trap || cont_simp || cont_g2 || cont_g3);
    printf("INTEGRAL NUMÉRICA: A = %.10g\n", area_trap + area_simp + area_g2 + area_g3); 
    return 0;
}
