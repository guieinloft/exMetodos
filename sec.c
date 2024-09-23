#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PREC 0.000001

int sign(double v){
	return (0.0 < v) - (v < 0.0);
}

double f(double x){
	return pow(x, 3) - 2 * pow(x, 2) - 4 * x + 4;
}

int main(){
	int i = 2;
	double x, x_p, x_pp, f_x, df_x, er;

	x_pp = 0.5;
	x_p = 0.75;
	x = x_p - f(x_p)*(x_p - x_pp)/(f(x_p) - f(x_pp));
	printf("%d: %lf \t %lf \n", i, x, f(x));
	i++;
	do{
		if(f(x) == 0.0) break;
		x_pp = x_p;
		x_p = x;
		x = x_p - f(x_p)*(x_p - x_pp)/(f(x_p) - f(x_pp));
		er = fabs(x - x_p)/fabs(x);
		printf("%d: %lf \t %lf \t %lf \n", i, x, f(x), er);
		i++;
	}
	while(er > PREC);
	return 0;
}
