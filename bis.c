#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sign(double v){
	return (0.0 < v) - (v < 0.0);
}

double f(double x){
	return pow(x, 3) - 2 * pow(x, 2) - 4 * x + 4;
}

int main(){
	int i = 1;
	double a, b, x, x_prev, f_x, f_a, f_b, er;
	scanf("%lf %lf", &a, &b);

	x = (a + b)/2;
	printf("%d: %lf \t %lf \t %lf \t %lf \n", i, a, x, b, f(x));
	do{
		if(f(x) == 0.0) break;
		else {
			if(sign(f(x)) == sign(f(a))) a = x;
			else if(sign(f(x)) == sign(f(b))) b = x;
		}
		x_prev = x;
		x = (a + b)/2;
		er = fabs(x - x_prev)/fabs(x);
		printf("%d: %lf \t %lf \t %lf \t %lf \t %lf \n", i, a, x, b, f(x), er);
	}
	while(er > 0.001);
	return 0;
}
