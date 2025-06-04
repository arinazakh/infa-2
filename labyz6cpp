#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "rk4.h"
#include <stdlib.h>
double g = 9.8;
double l = 1;
int n = 2;
int m = 10;
void rhs_fun(double t, double* X, double* F) {
    F[0] = X[1];
    F[1] = -g *sin(X[0])/l;

}
void veuler(double t, double* X, double h, int n,
    void (*fun)(double, double*, double*), double* X1) {
    double* F = (double*)malloc(n * sizeof(double));
    rhs_fun(t, X, F);
    for (int i = 0; i < n; i++) {
        X1[i] = X[i] + F[i] * h;
    }
}
int main()
{
    FILE *g1;
    g1 = fopen("dane.txt", "w");
    if (g1 == NULL) {
        printf("Blad otwarcia pliku!\n");  // drukujemy komunikat o bledzie
        exit(1);                           // konczymy prace programu (funkcja exit()
        // znajduje sie w bibliotece stdlib.h)
    }

    
    graphics(500,500);
    scale(-0.5, -1, 2, 1);
    setlinestyle(0, 0, 5);
    double t,t0,tk,h;
    double X[2], X1[2], X4[2] , X14[ 2 ], E, E1;
    double a0 = 0.1;
    double o0 = 0;
    t0 = 0; 
    tk = 10;
    h = 0.01;
    t = t0;
    X[0] = a0;
    X[1] = o0;
    X4[0] = a0;
    X4[1] = o0;
    fprintf(g1, "t,a,o,E,a4,o4,E4\n");
    while (t < tk) {
        veuler(t, X, h, n, rhs_fun,X1);
        vrk4(t, X4, h, n, rhs_fun, X14);
        t = t + h;
        X[0] = X1[0];
        X[1] = X1[1];
        X4[0] = X14[0];
        X4[1] = X14[1];
        E = m * pow(l, 2) / 2 * pow(X[1], 2) + m * g * l * (1 - cos(X[0]));
        E1 = m * pow(l, 2) / 2 * pow(X4[1], 2) + m * g * l * (1 - cos(X4[0]));
        printf("t=%lf,wych=%lf,predk=%lf, energia=%lf\n", t, X[0], X[1],E);
        printf("t=%lf,wych=%lf,predk=%lf, energia=%lf\n", t, X4[0], X14[1], E1);
        fprintf(g1,"%lf,%lf,%lf,%lf,", t, X[0], X[1], E);
        fprintf(g1,"%lf,%lf,%lf\n",  X4[0], X14[1], E1);

        circle( t, X[0] ,1);
        circle(t, X[1], 1);
        circle(X[0], X[1], 1);
        circle(t, X4[0], 1);
        circle(t, X14[1], 1);
        circle(X4[0], X4[1], 1);
        circle(t, E, 1);
        circle(t, E1, 1);
    }
    

    fclose(g1);
    wait();
    return 0;
}
