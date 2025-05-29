#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "narzedzia.h"
#include <stdlib.h>
double k1, k2,z1,z2,m;
double fun(double t, double z1) {

    double wyn = -k1*(1.+k2*pow(z1,2))*z1/m;
    return wyn;
}

double fun1(double t, double z1) {

    double wyn = z1;
    return wyn;
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
    double t0 = 0;
    double t=t0;
    double tk = 10;
    int N;
    int n = 2;
    double* X = (double*)malloc(n * sizeof(double));
    double* X1 = (double*)malloc(n * sizeof(double));
    printf("Podaj m,k1, k2,x(0),v(0),ilosc przedzialow czasowych:\n");
    scanf("%lf,%lf,%lf,%lf,%lf,%ld", &m,&k1, &k2, &z1,&z2,&N);
    printf("\n");
    double z, zv;
    z = z1;
    zv = z2;
    graphics(500, 500);
    setcolor(2);
    double h = (tk - t0) / (double)N;
    fprintf(f, "t,v,x\n");
    for (int i = 0; i < N; i++) {
        
        z= rk4(t, z, fun, h);
        zv = rk4(t, z, fun1, h);
        t = t + h;
        printf("%lf,%lf,%lf\n", t, z, zv);
        fprintf(f, "%lf,%lf,%lf\n", t, z, zv);
        circle(t + 100, 100 - z, 1);
        circle(t + 100, 100 -zv, 1);
        
    }
    fclose(f);
    wait();
    return 0;
}
