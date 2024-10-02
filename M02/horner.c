#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdarg.h>

#define PREC 0.000001

typedef struct polynomial {
	int degree;
	double *coeficients;
} polynomial;

int sign(double v){
	return (0.0 < v) - (v < 0.0);
}

polynomial create_p(int degree, ...){
	polynomial p;
	p.degree = degree;
	va_list args;
	va_start(args, degree);
	p.coeficients = (double*)malloc(sizeof(double) * (degree + 1));
	for(int i = 0; i <= degree; i++){
		p.coeficients[i] = va_arg(args, double);
		printf("%lf\t", p.coeficients[i]);
	}
	va_end(args);
	printf("\n");
	return p;
}

polynomial find_b0(polynomial p, double x0){
	polynomial b;
	b.degree = p.degree;
	b.coeficients = (double*)malloc(sizeof(double) * (b.degree + 1));
	b.coeficients[0] = p.coeficients[0];
	printf("b: %lf\t", b.coeficients[0]);
	for(int i = 1; i <= b.degree; i++){
		b.coeficients[i] = p.coeficients[i] + b.coeficients[i-1] * x0;
		printf("%lf\t", b.coeficients[i]);
	}
	printf("\n");
	return b;
}

polynomial find_c1(polynomial b, double x0){
	polynomial c;
	c.degree = b.degree - 1;
	c.coeficients = (double*)malloc(sizeof(double) * (c.degree + 1));
	c.coeficients[0] = b.coeficients[0];
	printf("c: %lf\t", c.coeficients[0]);
	for(int i = 1; i <= c.degree; i++){
		c.coeficients[i] = b.coeficients[i] + c.coeficients[i-1] * x0;
		printf("%lf\t", c.coeficients[i]);
	}
	printf("\n");
	return c;
}




int main(){
	int i = 0;
	double x, x_prev, f_x, df_x, er;

	polynomial p = create_p(3, 1.0, -2.0, -4.0, 4.0);
	polynomial b;
	polynomial c;

	x = 0.5;
	printf("%d: %lf\n\n", i, x);
	do{
		x_prev = x;
		b = find_b0(p, x);
		c = find_c1(b, x);
		if (b.coeficients[b.degree] == 0.0) break;
		x = x_prev - b.coeficients[b.degree]/c.coeficients[c.degree];
		er = fabs(x - x_prev)/fabs(x);
		printf("%d: %lf \t %lf\n\n", i, x, er);
		i++;
	}
	while(er > PREC);
	return 0;
}
