//===- Matgen.h -----------------------------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// This file provides the linpackc matgen function declarations.
//
//===----------------------------------------------------------------------===//
#include <math.h>
#include <stdio.h>

void matgen_float_gcc(float a[], int lda, int n, float b[], float *norma);
void matgen_double_gcc(double a[], int lda, int n, double b[], double *norma);
void matgen_float_clang(float a[], int lda, int n, float b[], float *norma);
void matgen_double_clang(double a[], int lda, int n, double b[], double *norma);
