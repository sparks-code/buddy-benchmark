//===- MLIRLinpackCDgefaBenchmark.cpp--------------------------------------===//
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
// This file implements the benchmark for dgefa function.
//
//===----------------------------------------------------------------------===//

#include "Dgefa.h"
#include <algorithm>
#include <benchmark/benchmark.h>
#include <buddy/Core/Container.h>
#include <iostream>
// Declare the linpackcdgefa C interface.
extern "C" {
void _mlir_ciface_mlir_linpackcdgefarollf32(MemRef<float, 1> *a, int lda,int n,
                                            MemRef<int, 1> *ipvt, MemRef<int, 1>* info);                               
void _mlir_ciface_mlir_linpackcdgefarollf64(MemRef<double, 1> *a, int lda,int n,
                                            MemRef<int, 1> *ipvt, MemRef<int, 1>* info); 
void _mlir_ciface_mlir_linpackcdgefaunrollf32(MemRef<float, 1> *a, int lda,int n,
                                            MemRef<int, 1> *ipvt, MemRef<int, 1>* info); 
void _mlir_ciface_mlir_linpackcdgefaunrollf64(MemRef<double, 1> *a, int lda,int n,
                                            MemRef<int, 1> *ipvt, MemRef<int, 1>* info); 
}
// Define input and output sizes.
static int lda = 50;
static int n_dgefa = 50;

intptr_t sizesArrayMLIRLinpackCDgefa_a[1] = {intptr_t(lda * n_dgefa)};
intptr_t sizesArrayMLIRLinpackCDgefa_ipvt[1] = {intptr_t(n_dgefa)};
intptr_t sizesArrayMLIRLinpackCDgefa_info[1] = {1};

// Define the MemRef container for inputs and output.
MemRef<float, 1> MLIRDgefa_af32(sizesArrayMLIRLinpackCDgefa_a, 2.3);
MemRef<int, 1> MLIRDgefa_ipvt(sizesArrayMLIRLinpackCDgefa_ipvt, 0);
MemRef<int, 1> MLIRDgefa_info(sizesArrayMLIRLinpackCDgefa_info, 0);

MemRef<double, 1> MLIRDgefa_af64(sizesArrayMLIRLinpackCDgefa_a, 2.3);

// Define the benchmark function.
static void MLIR_DgefaRollF32(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      _mlir_ciface_mlir_linpackcdgefarollf32(&MLIRDgefa_af32, lda, n_dgefa, 
                             &MLIRDgefa_ipvt, &MLIRDgefa_info);
    }
  }
}

// static void MLIR_DgefaRollF64(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgefarollf64(n, input_da_f64,
//                                              &inputMLIRDgefa_dxf64, input_incx,
//                                              &outputMLIRDgefa_f64, input_incy);
//     }
//   }
// }

// static void MLIR_DgefaUnrollF32(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgefaunrollf32(
//           n, input_da_f32, &inputMLIRDgefa_dxf32, input_incx,
//           &outputMLIRDgefa_f32, input_incy);
//     }
//   }
// }

// static void MLIR_DgefaUnrollF64(benchmark::State &state) {
//   for (auto _ : state) {
//     for (int i = 0; i < state.range(0); ++i) {
//       _mlir_ciface_mlir_linpackcdgefaunrollf64(
//           n, input_da_f64, &inputMLIRDgefa_dxf64, input_incx,
//           &outputMLIRDgefa_f64, input_incy);
//     }
//   }
// }

static void Dgefa_ROLL_float_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_ROLL_float_gcc(MLIRDgefa_af32.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}

static void Dgefa_ROLL_double_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_ROLL_double_gcc(MLIRDgefa_af64.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}

static void Dgefa_UNROLL_float_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_UNROLL_float_gcc(MLIRDgefa_af32.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}

static void Dgefa_UNROLL_double_gcc(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_UNROLL_double_gcc(MLIRDgefa_af64.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}
static void Dgefa_ROLL_float_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_ROLL_float_clang(MLIRDgefa_af32.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}

static void Dgefa_ROLL_double_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_ROLL_double_clang(MLIRDgefa_af64.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}

static void Dgefa_UNROLL_float_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_UNROLL_float_clang(MLIRDgefa_af32.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}

static void Dgefa_UNROLL_double_clang(benchmark::State &state) {
  for (auto _ : state) {
    for (int i = 0; i < state.range(0); ++i) {
      dgefa_UNROLL_double_clang(MLIRDgefa_af64.getData(), lda, n_dgefa, 
      MLIRDgefa_ipvt.getData(), MLIRDgefa_info.getData());
    }
  }
}
// Register benchmarking function.
BENCHMARK(MLIR_DgefaRollF32)->Arg(1);
// BENCHMARK(MLIR_DgefaRollF64)->Arg(1);
// BENCHMARK(MLIR_DgefaUnrollF32)->Arg(1);
// BENCHMARK(MLIR_DgefaUnrollF64)->Arg(1);

BENCHMARK(Dgefa_ROLL_float_gcc)->Arg(1);
BENCHMARK(Dgefa_ROLL_double_gcc)->Arg(1);
BENCHMARK(Dgefa_UNROLL_float_gcc)->Arg(1);
BENCHMARK(Dgefa_UNROLL_double_gcc)->Arg(1);
BENCHMARK(Dgefa_ROLL_float_clang)->Arg(1);
BENCHMARK(Dgefa_ROLL_double_clang)->Arg(1);
BENCHMARK(Dgefa_UNROLL_float_clang)->Arg(1);
BENCHMARK(Dgefa_UNROLL_double_clang)->Arg(1);

// Generate result image.
// void generateResultMLIRLinpackCDgefa() {
//   // Define the MemRef descriptor for inputs and output.

//   // Run the linpackcdgefa.
//   _mlir_ciface_mlir_linpackcdgefarollf32(n, input_da_f32, &inputMLIRDgefa_dxf32,
//                                          input_incx, &outputMLIRDgefa_f32_roll,
//                                          input_incy);

//   _mlir_ciface_mlir_linpackcdgefaunrollf32(
//       n, input_da_f32, &inputMLIRDgefa_dxf32, input_incx,
//       &outputMLIRDgefa_f32_unroll, input_incy);

//   _mlir_ciface_mlir_linpackcdgefarollf64(n, input_da_f64, &inputMLIRDgefa_dxf64,
//                                          input_incx, &outputMLIRDgefa_f64_roll,
//                                          input_incy);

//   _mlir_ciface_mlir_linpackcdgefaunrollf64(
//       n, input_da_f64, &inputMLIRDgefa_dxf64, input_incx,
//       &outputMLIRDgefa_f64_unroll, input_incy);
//   // Print the output.
//   std::cout << "--------------------------------------------------------"
//             << std::endl;
//   std::cout << "MLIR_LinpackC: MLIR Dgefa Operation for 'incx = -1, incy = 2'"
//             << std::endl;
//   std::cout << "f32roll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgefa_f32_roll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;

//   std::cout << "f32unroll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgefa_f32_unroll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;

//   std::cout << "f64roll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgefa_f64_roll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;

//   std::cout << "f64unroll: [ ";
//   for (size_t i = 0; i < n; i++) {
//     std::cout << outputMLIRDgefa_f64_unroll.getData()[i] << " ";
//   }
//   std::cout << "]" << std::endl;
// }
