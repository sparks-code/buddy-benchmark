//===- MLIRLinpackCDgeslBenchmark.cpp--------------------------------------===//
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
// This file implements the benchmark for dgesl function.
//
//===----------------------------------------------------------------------===//

#include "Dgesl.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <buddy/Core/Container.h>
#include <iostream>
// Declare the linpackcdgesl C interface.
extern "C" {
void _mlir_ciface_mlir_linpackcdgeslrollf32(int n, float da,
                                            MemRef<float, 1> *dx, int incx,
                                            MemRef<float, 1> *dy, int incy);
void _mlir_ciface_mlir_linpackcdgeslrollf64(int n, double da,
                                            MemRef<double, 1> *dx, int incx,
                                            MemRef<double, 1> *dy, int incy);
void _mlir_ciface_mlir_linpackcdgeslunrollf32(int n, float da,
                                              MemRef<float, 1> *dx, int incx,
                                              MemRef<float, 1> *dy, int incy);
void _mlir_ciface_mlir_linpackcdgeslunrollf64(int n, double da,
                                              MemRef<double, 1> *dx, int incx,
                                              MemRef<double, 1> *dy, int incy);
}
// Define input and output sizes.
static int lda = 50;
static int n_dgesl = 50;
/* if job = 0 to solve  a*x = b ,
else to solve  trans(a)*x = b  where trans(a)  is the transpose. */
static int job = 0; 
intptr_t sizesArrayMLIRLinpackCDgesl_a[1] = {intptr_t(lda * n_dgesl)};
intptr_t sizesArrayMLIRLinpackCDgesl_ipvt[1] = {intptr_t(n_dgesl)};
intptr_t sizesArrayMLIRLinpackCDgesl_info[1] = {1};

// Define the MemRef container for inputs and output.
MemRef<float, 1> MLIRDgesl_af32(sizesArrayMLIRLinpackCDgesl_a, 2.3);
MemRef<float, 1> MLIRDgesl_bf32(sizesArrayMLIRLinpackCDgesl_a, 2.3);
MemRef<int, 1> MLIRDgesl_ipvt(sizesArrayMLIRLinpackCDgesl_ipvt, 0);
MemRef<int, 1> MLIRDgesl_info(sizesArrayMLIRLinpackCDgesl_info, 0);

MemRef<double, 1> MLIRDgesl_af64(sizesArrayMLIRLinpackCDgesl_a, 2.3);
MemRef<double, 1> MLIRDgesl_bf64(sizesArrayMLIRLinpackCDgesl_a, 2.3);
// Define the benchmark function.
// static void MLIR_DgeslRollF32(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgeslrollf32(n, input_da_f32,
//                                              &inputMLIRDgesl_dxf32, input_incx,
//                                              &outputMLIRDgesl_f32, input_incy);
//     }
//   }
// }

// static void MLIR_DgeslRollF64(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgeslrollf64(n, input_da_f64,
//                                              &inputMLIRDgesl_dxf64, input_incx,
//                                              &outputMLIRDgesl_f64, input_incy);
//     }
//   }
// }

// static void MLIR_DgeslUnrollF32(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgeslunrollf32(
//           n, input_da_f32, &inputMLIRDgesl_dxf32, input_incx,
//           &outputMLIRDgesl_f32, input_incy);
//     }
//   }
// }

// static void MLIR_DgeslUnrollF64(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgeslunrollf64(
//           n, input_da_f64, &inputMLIRDgesl_dxf64, input_incx,
//           &outputMLIRDgesl_f64, input_incy);
//     }
//   }
// }

static void Dgesl_ROLL_float_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_ROLL_float_gcc(MLIRDgesl_af32.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(),MLIRDgesl_bf32.getData(), job);
    }
  }
}

static void Dgesl_ROLL_double_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_ROLL_double_gcc(MLIRDgesl_af64.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(), MLIRDgesl_bf64.getData(), job);
    }
  }
}

static void Dgesl_UNROLL_float_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_UNROLL_float_gcc(MLIRDgesl_af32.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(), MLIRDgesl_bf32.getData(), job);
    }
  }
}

static void Dgesl_UNROLL_double_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_UNROLL_double_gcc(MLIRDgesl_af64.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(),MLIRDgesl_bf64.getData(), job);
    }
  }
}
static void Dgesl_ROLL_float_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_ROLL_float_clang(MLIRDgesl_af32.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(), MLIRDgesl_bf32.getData(), job);
    }
  }
}

static void Dgesl_ROLL_double_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_ROLL_double_clang(MLIRDgesl_af64.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(), MLIRDgesl_bf64.getData(), job);
    }
  }
}

static void Dgesl_UNROLL_float_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_UNROLL_float_clang(MLIRDgesl_af32.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(), MLIRDgesl_bf32.getData(), job);
    }
  }
}

static void Dgesl_UNROLL_double_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgesl_UNROLL_double_clang(MLIRDgesl_af64.getData(), lda, n_dgesl, 
      MLIRDgesl_ipvt.getData(),MLIRDgesl_bf64.getData(), job);
    }
  }
}
// Register benchmarking function.
// BENCHMARK(MLIR_DgeslRollF32)->Arg(1);
// BENCHMARK(MLIR_DgeslRollF64)->Arg(1);
// BENCHMARK(MLIR_DgeslUnrollF32)->Arg(1);
// BENCHMARK(MLIR_DgeslUnrollF64)->Arg(1);

BENCHMARK(Dgesl_ROLL_float_gcc)->Arg(1);
BENCHMARK(Dgesl_ROLL_double_gcc)->Arg(1);
BENCHMARK(Dgesl_UNROLL_float_gcc)->Arg(1);
BENCHMARK(Dgesl_UNROLL_double_gcc)->Arg(1);
BENCHMARK(Dgesl_ROLL_float_clang)->Arg(1);
BENCHMARK(Dgesl_ROLL_double_clang)->Arg(1);
BENCHMARK(Dgesl_UNROLL_float_clang)->Arg(1);
BENCHMARK(Dgesl_UNROLL_double_clang)->Arg(1);

// Generate result image.
// void generateResultMLIRLinpackCDgesl() {
//   // Define the MemRef descriptor for inputs and output.

//   // Run the linpackcdgesl.
//   _mlir_ciface_mlir_linpackcdgeslrollf32(n, input_da_f32, &inputMLIRDgesl_dxf32,
//                                          input_incx, &outputMLIRDgesl_f32_roll,
//                                          input_incy);

//   _mlir_ciface_mlir_linpackcdgeslunrollf32(
//       n, input_da_f32, &inputMLIRDgesl_dxf32, input_incx,
//       &outputMLIRDgesl_f32_unroll, input_incy);

//   _mlir_ciface_mlir_linpackcdgeslrollf64(n, input_da_f64, &inputMLIRDgesl_dxf64,
//                                          input_incx, &outputMLIRDgesl_f64_roll,
//                                          input_incy);

//   _mlir_ciface_mlir_linpackcdgeslunrollf64(
//       n, input_da_f64, &inputMLIRDgesl_dxf64, input_incx,
//       &outputMLIRDgesl_f64_unroll, input_incy);
//   // Print the output.
//   std::cout << "--------------------------------------------------------"
//             << std::endl;
//   std::cout << "MLIR_LinpackC: MLIR Dgesl Operation for 'incx = -1, incy = 2'"
//             << std::endl;
//   std::cout << "f32roll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgesl_f32_roll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;

//   std::cout << "f32unroll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgesl_f32_unroll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;

//   std::cout << "f64roll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgesl_f64_roll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;

//   std::cout << "f64unroll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgesl_f64_unroll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;
// }
