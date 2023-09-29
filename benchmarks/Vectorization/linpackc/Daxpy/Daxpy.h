#include <cstdio>
#include <cmath>

void daxpy_ROLL(int n,float da, float dx[],int incx, float dy[], int incy);
void daxpy_ROLL(int n,double da, double dx[],int incx,double dy[], int incy);
void daxpy_UNROLL(int n,float da, float dx[],int incx,float dy[], int incy);
void daxpy_UNROLL(int n,double da, double dx[],int incx,double dy[], int incy);



