#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_custom_command(OUTPUT mlir-linpackcdaxpyrollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Daxpy/MLIRLinpackCDaxpyRollF32.mlir 
            -convert-scf-to-cf
            -expand-strided-metadata
            -convert-arith-to-llvm
            -llvm-request-c-wrappers
            --convert-math-to-llvm
            -finalize-memref-to-llvm
            -convert-func-to-llvm 
            -reconcile-unrealized-casts | 
          ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
          ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
            -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Daxpy/mlir-linpackcdaxpyrollf32.o
)
add_library(MLIRLinpackDaxpyRollF32 STATIC mlir-linpackcdaxpyrollf32.o)
set_target_properties(MLIRLinpackDaxpyRollF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcdaxpyrollf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Daxpy/MLIRLinpackCDaxpyRollF64.mlir 
            -convert-scf-to-cf
            -expand-strided-metadata
            -convert-arith-to-llvm
            --convert-math-to-llvm
            -llvm-request-c-wrappers
            -finalize-memref-to-llvm
            -convert-func-to-llvm 
            -reconcile-unrealized-casts |
          ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
          ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
            -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Daxpy/mlir-linpackcdaxpyrollf64.o
)
add_library(MLIRLinpackDaxpyRollF64 STATIC mlir-linpackcdaxpyrollf64.o)
set_target_properties(MLIRLinpackDaxpyRollF64 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcdaxpyunrollf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Daxpy/MLIRLinpackCDaxpyUnrollF64.mlir 
            -convert-scf-to-cf
            -expand-strided-metadata
            -convert-arith-to-llvm
            -llvm-request-c-wrappers
            -finalize-memref-to-llvm
            -convert-func-to-llvm 
            -reconcile-unrealized-casts |
          ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
          ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
            -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Daxpy/mlir-linpackcdaxpyunrollf64.o
)
add_library(MLIRLinpackDaxpyUnrollF64 STATIC mlir-linpackcdaxpyunrollf64.o)
set_target_properties(MLIRLinpackDaxpyUnrollF64 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcdaxpyunrollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Daxpy/MLIRLinpackCDaxpyUnrollF32.mlir 
            -convert-scf-to-cf
            -expand-strided-metadata
            -convert-arith-to-llvm
            -llvm-request-c-wrappers
            -finalize-memref-to-llvm
            -convert-func-to-llvm 
            -reconcile-unrealized-casts |
          ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
          ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
            -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Daxpy/mlir-linpackcdaxpyunrollf32.o
)
add_library(MLIRLinpackDaxpyUnrollF32 STATIC mlir-linpackcdaxpyunrollf32.o)
set_target_properties(MLIRLinpackDaxpyUnrollF32 PROPERTIES LINKER_LANGUAGE CXX)


# gcc 编译
# Daxpy
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Daxpy.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Daxpy/Daxpy.cpp 
         -c  -ftree-vectorize -o Daxpy.o
        
)
add_library(Daxpy STATIC Daxpy.o)
set_target_properties(Daxpy PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Daxpy
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Daxpy.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Daxpy/Daxpy.cpp 
           -c  -fvectorize  -o Daxpy.o
          
)
add_library(Daxpy STATIC Daxpy.o)
set_target_properties(Daxpy PROPERTIES LINKER_LANGUAGE CXX)

endif()