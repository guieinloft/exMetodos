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
	printf("P(x): ");  
	for(int i = 0; i <= degree; i++){
		p.coeficients[i] = va_arg(args, double);
		printf("%+.9E ", p.coeficients[i]);
	}
	va_end(args);
	printf("\n\n");
	return p;
}

polynomial find_b(polynomial p, double x0, int k){
	polynomial b;
	b.degree = p.degree;
	b.coeficients = (double*)malloc(sizeof(double) * (b.degree + 1));
	b.coeficients[0] = p.coeficients[0];
	printf("b%d: %+.9E ", k, b.coeficients[0]);
	for(int i = 1; i <= b.degree; i++){
		b.coeficients[i] = p.coeficients[i] + b.coeficients[i-1] * x0;
		printf("%+.9E ", b.coeficients[i]);
	}
	printf("\n");
	return b;
}

polynomial find_c(polynomial b, double x0, int k){
	polynomial c;
	c.degree = b.degree - 1;
	c.coeficients = (double*)malloc(sizeof(double) * (c.degree + 1));
	c.coeficients[0] = b.coeficients[0];
	printf("c%d: %+.9E ", k, c.coeficients[0]);
	for(int i = 1; i <= c.degree; i++){
		c.coeficients[i] = b.coeficients[i] + c.coeficients[i-1] * x0;
		printf("%+.9E ", c.coeficients[i]);
	}
	printf("\n");
	return c;
}




int main(){
	int i = 0;
	double x, x_prev, f_x, df_x, er;

	polynomial p = create_p(5, 1.0, 0.725616, -18.8815, -0.872976, 53.87, -16.4925);
	polynomial b;
	polynomial c;

	x = 3.5;
	do{
		x_prev = x;
		b = find_b(p, x, i);
		c = find_c(b, x, i);
		if (b.coeficients[b.degree] == 0.0) break;
		printf("x%d: %+.9E %+.9E %+.9E %+.9E \n\n", i, x, b.coeficients[b.degree], c.coeficients[c.degree], er);
		x = x_prev - b.coeficients[b.degree]/c.coeficients[c.degree];
		er = fabs(x - x_prev)/fabs(x);
		i++;
	}
	while(er > PREC);
	printf("x%d: %+.9E ---------------- ---------------- %+.9E \n\n", i, x, b.coeficients[b.degree], c.coeficients[c.degree], er);
	return 0;
}
