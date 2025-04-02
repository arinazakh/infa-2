#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "nonlin.h"
double fun(double x) {
    double f = cos(x)-x;
    return f;
}
double fun1(double x) {
	double f = -sin(x) - 1;
	return f;
}
double newton(double a, double (*pf)(double), double eps, int* iter) {
	int	i;
	double fa, fb, fc, b;

	fa = pf(a);
	/*fb = pf(b);*/

	if (-sin(a) - 1==0)
	{
		*iter = -1;
		return 0;
	}

	for (i = 1; i <= 1000; i++)
	{
		b = a - fa /( - sin(a) - 1);
		fb = pf(b);
		a = b;
		fa = fb;
		


		if (fabs(fb) < eps )
			break;
	}

	*iter = i;
	return b;
}


double siecz(double a, double b, double (*pf)(double), double eps, int* iter) {
	int	i;
	double fa, fb, fc, c;

	fa = pf(a);
	fb = pf(b);
	
	if (fabs(b - a) < eps)
	{
		*iter = -1;
		return 0;
	}

	for (i = 1; i <= 1000; i++)
	{
		c = b - fb*(b - a)/(fb-fa);
		fc = pf(c);

		
			a=b ;
			fa = fb;
			b = c;
			fb = fc;


		if (fabs(fc) < eps )
			break;
	}

	*iter = i;
	return c;
}
int main()
{
    double x;
   /* printf("Podaj eps:\n");
    double e
   /* scanf("%lf", &e);*/
    printf("Podaj a,b:\n");
    double a;
    double b;
    scanf("%lf,%lf", &a, &b);
    
    
    int piter, iter, miter;

  /*  iter= &piter  ;*/
    double g,l,k;
    
    FILE* f;              
    f = fopen("dane.txt", "w");
    
   

   
   /* printf("x0: %lf, iter: %d\n",g,piter);*/
    for (int i = 0; i <= 16; i++) {
       double e = pow(2, -20 + i);
        g = bisec(a, b, *fun, e, &piter);
		
        fprintf(f, "x0: % lf, iter : % d\n", g, piter);
        printf("bisec, x0: %lf, iter: %d\n", g, piter);
		
    }
	for (int i = 0; i <= 16; i++) {
		double e = pow(2, -20 + i);
		
		l = siecz(a, b, *fun, e, &iter);
		fprintf(f, "x0: % lf, iter : % d\n", l, iter);
		
		printf("siecz, x0: %lf, iter: %d\n", l, iter);
	}
	for (int i = 0; i <= 16; i++) {
		double e = pow(2, -20 + i);
		k = newton(a, *fun,e, &miter);
		fprintf(f, "x0: % lf, iter : % d\n", k, miter);
		printf("newton, x0: %lf, iter: %d\n", k, miter);
		
	}
	

    fclose(f);
    return 0;
}
