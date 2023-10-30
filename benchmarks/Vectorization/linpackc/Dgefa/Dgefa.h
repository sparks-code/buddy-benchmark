#include <Daxpy/Daxpy.h>
#include <Dscal/Dscal.h>
#include <Idamax/Idamax.h>
#include <math.h>
#include <stdio.h>

void dgefa_ROLL_float_gcc(float a[], int lda, int n, int ipvt[], int *info);
void dgefa_ROLL_double_gcc(double a[], int lda, int n, int ipvt[], int *info);
void dgefa_UNROLL_float_gcc(float a[], int lda, int n, int ipvt[], int *info);
void dgefa_UNROLL_double_gcc(double a[], int lda, int n, int ipvt[], int *info);

void dgefa_ROLL_float_clang(float a[], int lda, int n, int ipvt[], int *info);
void dgefa_ROLL_double_clang(double a[], int lda, int n, int ipvt[], int *info);
void dgefa_UNROLL_float_clang(float a[], int lda, int n, int ipvt[], int *info);
void dgefa_UNROLL_double_clang(double a[], int lda, int n, int ipvt[], int *info);