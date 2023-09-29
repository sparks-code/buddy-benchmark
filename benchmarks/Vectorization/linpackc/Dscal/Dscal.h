#include <stdio.h>
#include <math.h>

void dscal_ROLL(int n,float da,float dx[], int incx);
void dscal_UNROLL(int n,float da,float dx[], int incx);
void dscal_ROLL(int n,double da,double dx[], int incx);
void dscal_UNROLL(int n,double da,double dx[], int incx);