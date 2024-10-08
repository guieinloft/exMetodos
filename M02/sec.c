#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PREC 0.000001

int sign(double v){
	return (0.0 < v) - (v < 0.0);
}

double f(double x){
	return pow(x, 5) + 0.725616 * pow(x, 4) - 18.8815 * pow(x, 3) - 0.872976 * pow(x, 2) + 53.87 * x - 16.4925;
}

int main(){
	int i = 2;
	double x, x_p, x_pp, f_x, er;

	x_pp = 0;
	x_p = 0.2;
	x = x_p - f(x_p)*(x_p - x_pp)/(f(x_p) - f(x_pp));
	printf("k  x                f(x)             er\n");
	printf("%02d %+.9E %+.9E --- \n", 0, x_pp, f(x_pp));
	er = fabs(x_p - x_pp)/fabs(x);
	printf("%02d %+.9E %+.9E %+.9E \n", 1, x_p, f(x_p), er);
	er = fabs(x - x_p)/fabs(x);
	printf("%02d %+.9E %+.9E %+.9E \n", i, x, f(x), er);
	i++;
	do{
		if(f(x) == 0.0) break;
		x_pp = x_p;
		x_p = x;
		x = x_p - f(x_p)*(x_p - x_pp)/(f(x_p) - f(x_pp));
		er = fabs(x - x_p)/fabs(x);
		printf("%02d %+.9E %+.9E %+.9E \n", i, x, f(x), er);
		i++;
	}
	while(er > PREC);
	return 0;
}
