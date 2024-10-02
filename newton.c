#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PREC 0.000001

int sign(double v){
	return (0.0 < v) - (v < 0.0);
}

double d(double f(double), double x){
	double y1 = f(x - PREC);
	double y2 = f(x + PREC);
	return (y2 - y1)/(x + PREC - x + PREC);
}

double f(double x){
	return pow(x, 5) + 0.725616 * pow(x, 4) - 18.8815 * pow(x, 3) - 0.872976 * pow(x, 2) + 53.87 * x - 16.4925;
}

int main(){
	int i = 1;
	double x, x_prev, f_x, df_x, er;

	x = 0.5;
	printf("k\t x\t\t\t f(x)\t\t\t d(f, x)\t\t\t er\n");
	printf("0\t %.9E \t %.9E \t %.9E \t --- \n", x, f(x), d(f, x));
	do{
		if(f(x) == 0.0) break;
		x_prev = x;
		x = x_prev - f(x_prev)/d(f, x_prev);
		er = fabs(x - x_prev)/fabs(x);
		printf("%d\t %.9E \t %.9E \t %.9E \t %.9E \n", i, x, f(x), d(f, x), er);
		i++;
	}
	while(er > PREC);
	return 0;
}
