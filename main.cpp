#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include "winbgi2.h"
#include "gauss.h"
#include <stdlib.h>
#define l 58
#define PI 3.14

void computeMatrix(int N, double** K) {
    for (int i = 0; i < N+1; i++) {
        for (int j = 0; j < N + 1; j++) {
            K[i][j] = 0;
            if (i == j&&i>=1&&i<N) {
                K[i][j] = -2;
            }
            if ((i == j - 1 || i == j + 1)&&i>0 && i < N) {
                K[i][j] = 1;
            }
        }
        K[0][0] = 1;
        K[N][N] =1;
    }
    
   
}
  void displayMatrix(int N, double** K) {
        for (int i = 0; i < N+1; i++) {
            for (int j = 0; j < N + 1; j++) {
                printf("%1.0lf ",K[i][j]);
            }
            printf("\n");
        }
    }
  void computeVector(int N, double* F) {
      double h = 1./N;
      double x = 0;
      for (int i = 0; i <= N; ++i){
          x = x + h;
          F[i] = -pow(10, 4) * sin(x * PI)* pow(h, 2) / l;
      }
      F[0] = 273;
      F[N] = 300;
  }
  void displayVector(int N, double* F) {
      for (int j = 0; j < N + 1; j++) {
          printf("%lf ", F[j]);
          printf("\n");
      }
      
  }
  void displaydet(int N, double* F) {

  }
    /*for (int i = ; i < N + 1; i++) {
        for (int j = 0; j < N + 1; j++) {
            K[i][j] = -2.;
        }
    }*/

//#define PI 3.14
//void rhs_fun(double t, double* X, double* F) {
//    F[0] = X[1];
//    F[1] = -pow(10,4)* sin(X[0]*PI) / l;
//
//}
int main()
{
    double** K;
    int N=50;
    K = (double**)malloc((N + 1) * sizeof(double*));
    for (int i = 0; i < N+1; ++i)
        K[i] = (double*)malloc((N+1) * sizeof(double));
    double* F;                                 // wskaznik do pierwszego
    // elementu tablicy

    F = (double*)malloc((N + 1) * sizeof(double));   // alokacja tablicy
    double* x;                                 // wskaznik do pierwszego
    // elementu tablicy

    x= (double*)malloc((N + 1) * sizeof(double));

    computeMatrix(N, K);
    displayMatrix(N, K);
    computeVector(N, F);
    displayVector(N, F);
    gauss(N+1, K, x, F);
    displayVector(N, x);
    graphics(1000, 1000);
    scale(0, 200, 1, 350);
    setlinestyle(0, 0, 5);
    double y = 0;
    double h = 1. / N;
    for (int j = 0; j < N + 1; j++) {
        circle(y + j*h, x[j], 1);
    }
    wait();
    for (int i = 0; i < N; ++i)
        free(K[i]);
    free(K);
    free(F);
    free(x);
    
    return 0;
}
