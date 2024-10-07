#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int sign(double v){
	return (0.0 < v) - (v < 0.0);
}

double f(double x){
	return pow(x, 5) + 0.725616 * pow(x, 4) - 18.8815 * pow(x, 3) - 0.872976 * pow(x, 2) + 53.87 * x - 16.4925;
}

int main(){
	int i = 0;
	double a, b, x, x_prev, f_x, f_a, f_b, er;
	scanf("%lf %lf", &a, &b);

	x = (a + b)/2;
	printf("k  a                 x                 b                 f(a)              f(x)              f(b)              er\n");
	printf("%02d %+.10E %+.10E %+.10E %+.10E %+.10E %+.10E ---\n", i, a, x, b, f(a), f(x), f(b));
	do{
		if(f(x) == 0.0) break;
		else {
			if(sign(f(x)) == sign(f(a))) a = x;
			else if(sign(f(x)) == sign(f(b))) b = x;
		}
		x_prev = x;
		x = (a + b)/2;
		er = fabs(x - x_prev)/fabs(x);
        i++;
		printf("%02d %+.10E %+.10E %+.10E %+.10E %+.10E %+.10E %+.10E\n", i, a, x, b, f(a), f(x), f(b), er);
	}
	while(er > pow(10, -6));
	return 0;
}
