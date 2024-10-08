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
	double x, x_prev, a, b, er;

	a = 1;
    b = 3;
    x = a - (b - a) / (f(b) - f(a)) * f(a);
	printf("k  a                x                b                f(x)             er\n");
	printf("00 %+.9E %+.9E %+.9E %+.9E --- \n", a, x, b, f(x));
	do{
		if(f(x) == 0.0) break;
        else if(sign(f(x)) == sign(f(a))) a = x;
        else if(sign(f(x)) == sign(f(b))) b = x;
        x_prev = x;
        x = a - (b - a) / (f(b) - f(a)) * f(a);
		er = fabs(x - x_prev)/fabs(x);
	    printf("%02d %+.9E %+.9E %+.9E %+.9E %+.9E \n", i, a, x, b, f(x), er);
		i++;
	}
	while(er > PREC);
	return 0;
}
