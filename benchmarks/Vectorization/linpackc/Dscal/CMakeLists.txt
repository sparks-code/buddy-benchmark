#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_custom_command(OUTPUT mlir-linpackcdscalrollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dscal/MLIRLinpackCDscalRollF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dscal/mlir-linpackcdscalrollf32.o
)
add_library(MLIRLinpackDscalRollF32 STATIC mlir-linpackcdscalrollf32.o)
set_target_properties(MLIRLinpackDscalRollF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcdscalunrollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dscal/MLIRLinpackCDscalUnrollF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dscal/mlir-linpackcdscalunrollf32.o
)
add_library(MLIRLinpackDscalUnrollF32 STATIC mlir-linpackcdscalunrollf32.o)
set_target_properties(MLIRLinpackDscalUnrollF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcdscalrollf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dscal/MLIRLinpackCDscalRollF64.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dscal/mlir-linpackcdscalrollf64.o
)
add_library(MLIRLinpackDscalRollF64 STATIC mlir-linpackcdscalrollf64.o)
set_target_properties(MLIRLinpackDscalRollF64 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcdscalunrollf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dscal/MLIRLinpackCDscalUnrollF64.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dscal/mlir-linpackcdscalunrollf64.o
)
add_library(MLIRLinpackDscalUnrollF64 STATIC mlir-linpackcdscalunrollf64.o)
set_target_properties(MLIRLinpackDscalUnrollF64 PROPERTIES LINKER_LANGUAGE CXX)

# gcc 编译
# Dscal
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Dscal.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dscal/Dscal.cpp 
         -c  -ftree-vectorize -o Dscal.o
        
)
add_library(Dscal STATIC Dscal.o)
set_target_properties(Dscal PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Dscal
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Dscal.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dscal/Dscal.cpp 
           -c  -fvectorize  -o Dscal.o
          
)
add_library(Dscal STATIC Dscal.o)
set_target_properties(Dscal PROPERTIES LINKER_LANGUAGE CXX)

endif()