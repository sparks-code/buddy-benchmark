#include "/root/buddy-benchmark/benchmarks/Vectorization/linpackc/Daxpy/Daxpy.h"
#include "/root/buddy-benchmark/benchmarks/Vectorization/linpackc/Dscal/Dscal.h"
#include "/root/buddy-benchmark/benchmarks/Vectorization/linpackc/Idamax/Idamax.h"
#include <math.h>
#include <stdio.h>

int dgefa_ROLL_float_gcc(float a[], int lda, int n, int ipvt[], int *info);
int dgefa_ROLL_double_gcc(double a[], int lda, int n, int ipvt[], int *info);
int dgefa_UNROLL_float_gcc(float a[], int lda, int n, int ipvt[], int *info);
int dgefa_UNROLL_double_gcc(double a[], int lda, int n, int ipvt[], int *info);

int dgefa_ROLL_float_clang(float a[], int lda, int n, int ipvt[], int *info);
int dgefa_ROLL_double_clang(double a[], int lda, int n, int ipvt[], int *info);
int dgefa_UNROLL_float_clang(float a[], int lda, int n, int ipvt[], int *info);
int dgefa_UNROLL_double_clang(double a[], int lda, int n, int ipvt[], int *info);