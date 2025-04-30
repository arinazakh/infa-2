#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "rk4.h"
double lam = 0.1;
double fun(double x, double y) {
   
    double wyn = lam * y;
    return wyn;
}

double euler(double x0, double y0, double h, double (*fun)(double , double )){
    /*double t = 0;
    t = t + h;*/
    double y = y0 + h * fun(x0,y0);
    return y;
}
int main()
{
    double eps1, eps2,y2;
    double y0 = 2.;
    double y1 = 2.;
    double y=2.;
    double t0 = 0;
    double t = 0;
    double h0 = 0.5;
    /*double h = 0.5;*/
   
    double n = 10;
    double tk = 10.;
     //printf("t,Euler, RK4\n");
    printf("N,Eps Euler,Eps RK4\n");
    for (int j = 0; j < 6; j++){
        y = 0;
        y1 = 0;
       double h =  (tk-t0)/ (pow(2, j));
       for (int i = 0; i < pow(2, j); i++) {

           y = euler(t, y, h, fun);

           y1 = rk4(t, y1, h, fun);


           /*printf("%lf,%lf, %lf\n",t,y,y1);*/
           t = t + h;

           y2 = y0 * exp(lam * (t - t0));
           eps1 = fabs(y - y2) / fabs(y2);
           eps2 = fabs(y1 - y2) / fabs(y2);


           if (i == pow(2, j) - 1) {
               printf("%lf,%.15lf,%.15lf\n", pow(2, j), eps1, eps2);
             }
            }
         }
     
     
    /*printf("Wartosc to: %lf, %lf\n", y, y1);
   */
    

    
}
