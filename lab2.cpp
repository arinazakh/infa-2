#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "kwad.h"
#include <stdlib.h>
double fun1(double x) {
        return 1./ x;
    }
double fun2(double a, double b) {
    double j = -log(a) + log(b);
        return j;
    }
int main()
{
    double a, b, cn,cn1, ca, g,e, h,h1;
    int n, n1,m;
    FILE* f;
    f = fopen("dane.txt", "w");
    a = 0.1;
    b = 5.0; 
    n = 100;
    cn = simpson(a, b, fun1, n);
    ca = fun2(a,b);
    cn1 = trapez(a, b, fun1, n);
   /* g = fabs(cn - ca);*/
    h = (double)(b - a) /(double)n;
    scanf("%d",&m);
    /*printf("%lf, %lf, %lf,\n", h, ca, cn);*/
    fprintf(f, "N,H,ca,ct,cs,bt,bs\n");
    /*fprintf(f, "%lf, %lf, %lf,\n", h, ca, cn);*/
    for(int i=0;i<m;i++){
        n1 = pow(2,i);
        h1 = (double)(b - a) /(double)n1;
        cn = simpson(a, b, fun1, n1);
        cn1 = trapez(a, b, fun1, n1);
        g = fabs(cn - ca);
        e= fabs(cn1 - ca);
        fprintf(f, "%d,%15.15lf, %15.15lf, %0.15lf,%0.15lf,%0.15lf,%0.15lf\n",i+1,h1,ca,cn1,cn,e,g);
    }
    fclose(f);
    
    
}
