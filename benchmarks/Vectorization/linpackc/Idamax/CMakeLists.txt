#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_custom_command(OUTPUT mlir-linpackcidamaxf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Idamax/MLIRLinpackCIdamaxF32.mlir 
            -convert-scf-to-cf
            -expand-strided-metadata
            -convert-arith-to-llvm
            -llvm-request-c-wrappers
            -finalize-memref-to-llvm
            -convert-func-to-llvm 
            --convert-math-to-llvm
            -reconcile-unrealized-casts | 
          ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
          ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
            -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Idamax/mlir-linpackcidamaxf32.o
)
add_library(MLIRLinpackIdamaxF32 STATIC mlir-linpackcidamaxf32.o)
set_target_properties(MLIRLinpackIdamaxF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcidamaxf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Idamax/MLIRLinpackCIdamaxF64.mlir 
            -convert-scf-to-cf
            -expand-strided-metadata
            -convert-arith-to-llvm
            -llvm-request-c-wrappers
            -finalize-memref-to-llvm
            -convert-func-to-llvm 
            --convert-math-to-llvm
            -reconcile-unrealized-casts | 
          ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
          ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
            -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Idamax/mlir-linpackcidamaxf64.o
)
add_library(MLIRLinpackIdamaxF64 STATIC mlir-linpackcidamaxf64.o)
set_target_properties(MLIRLinpackIdamaxF64 PROPERTIES LINKER_LANGUAGE CXX)

# gcc 编译
# Idamax
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Idamax.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Idamax/Idamax.cpp 
         -c  -ftree-vectorize -o Idamax.o
        
)
add_library(Idamax STATIC Idamax.o)
set_target_properties(Idamax PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Idamax
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Idamax.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Idamax/Idamax.cpp 
           -c  -fvectorize  -o Idamax.o
          
)
add_library(Idamax STATIC Idamax.o)
set_target_properties(Idamax PROPERTIES LINKER_LANGUAGE CXX)

endif()