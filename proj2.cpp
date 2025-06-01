#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"

#include <stdlib.h>
#include "rk4.h"
double k1, k2,x0,v0,m;
void fun(double t, double* X, double* F) {

    F[0]  = -k1/m* X[1]*(1.+k2*pow(X[1], 2))  ;
    F[1] = X[0];
}

//double fun1(double t, double z1) {
//
//    double wyn = z1;
//    return wyn;
//}
double energia(double* X)
{
    return (k1 * (pow(x0, 2) / 2. + k2 / 4. * pow(x0, 4))*(1/2.*m) + pow(m, 2)* pow(v0, 2)/ 4. );
}
double energiap(double* X)
{
    return (k1 * ( (pow(X[1], 2) / 2. + k2 / 4. * pow(X[1], 4)) ));
}
int main()
{
    
    /*double *pk1, *pk2, *pz1, *pz2, *pm;
    pk1 = &k1;
    pk2 = &k2;
    pz1 = &z1;
    pz2 = &z2;*/
   /* pm = &m;*/
    FILE* f;              // deklarujemy wskaznik do typu FILE, o nazwie f

    f = fopen("dane.txt", "w");
    if (f == NULL) {
        printf("Blad otwarcia pliku!\n");  // drukujemy komunikat o bledzie
        exit(1);                           // konczymy prace programu (funkcja exit()
        // znajduje sie w bibliotece stdlib.h)
    }
    double t0 = 0.0;
    double t=t0;
    double tk = 10.;
    int N;
    int n = 2;
    double* X = (double*)malloc(n * sizeof(double));
    double* X1 = (double*)malloc(n * sizeof(double));
    printf("Podaj m,k1, k2,x(0),v(0),ilosc przedzialow czasowych:\n");
    scanf("%lf,%lf,%lf,%lf,%lf,%ld", &m,&k1, &k2, &x0,&v0, &N);
    printf("\n");
    double E,Ep;
    X[1] =x0;
    X[0] = v0;
    graphics(500, 500);
    scale(t0, -20, tk, 20);
    setcolor(2);
    double h = (tk - t0) / (double)N;
    fprintf(f, "t,v,x,E,Ep,Ek\n");
    printf( "t,v,x,E,Ep,Ek\n");
    for (t = t0; t <= tk; t += h) {
        vrk4(t, X, h, n, fun, X1);
       
       /* z= rk4(t, z, fun, h);
        zv = rk4(t, z, fun1, h);*/
       /* t = t + h;*/
        E=energia(X);
        Ep= energiap(X);
        if (E < 0) {
            break;
        }
        printf("%lf,%lf,%lf,%lf,%lf,%lf\n", t, X[0], X[1],E,Ep,(E-Ep));
        
        fprintf(f, "%lf,%lf,%lf,%lf,%lf,%lf\n", t, X[0], X[1],E, Ep, (E - Ep));
        setcolor(0.9999);
        circle(t ,  X[0], 1);
        setcolor(0.4444);
        circle(t ,  X[1], 1);
       
        circle(0.5 * X[1], 0.5 * X1[0], 1); 
        X[0] = X1[0];
        X[1] = X1[1];
        
    }
    printf( "m=%.0lf,k1=%.0lf,k2=%.0lf,x(0)=%.0lf,v(0)=%.0lf,N=%.0ld\n", m, k1, k2, x0, v0, N);
    fclose(f);
    wait();
    return 0;
}
