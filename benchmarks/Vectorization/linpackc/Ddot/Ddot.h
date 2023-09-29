#include <stdio.h>
#include <math.h>

float ddot_ROLL(int n,float dx[],int incx,float dy[], int incy);
float ddot_UNROLL(int n,float dx[],int incx,float dy[], int incy);
double ddot_ROLL(int n,double dx[],int incx,double dy[], int incy);
double ddot_UNROLL(int n,double dx[],int incx,double dy[], int incy);