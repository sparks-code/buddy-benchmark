#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_custom_command(OUTPUT mlir-linpackcepslonf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Epslon/MLIRLinpackCEpslonF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Epslon/mlir-linpackcepslonf32.o
)
add_library(MLIRLinpackEpslonF32 STATIC mlir-linpackcepslonf32.o)
set_target_properties(MLIRLinpackEpslonF32 PROPERTIES LINKER_LANGUAGE CXX)

#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_custom_command(OUTPUT mlir-linpackcepslonf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Epslon/MLIRLinpackCEpslonF64.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Epslon/mlir-linpackcepslonf64.o
)
add_library(MLIRLinpackEpslonF64 STATIC mlir-linpackcepslonf64.o)
set_target_properties(MLIRLinpackEpslonF64 PROPERTIES LINKER_LANGUAGE CXX)

# gcc 编译
# Epslon
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Epslon.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Epslon/Epslon.cpp 
         -c  -ftree-vectorize -o Epslon.o
        
)
add_library(Epslon STATIC Epslon.o)
set_target_properties(Epslon PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Epslon
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Epslon.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Epslon/Epslon.cpp 
           -c  -fvectorize  -o Epslon.o
          
)
add_library(Epslon STATIC Epslon.o)
set_target_properties(Epslon PROPERTIES LINKER_LANGUAGE CXX)

endif()