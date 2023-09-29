add_custom_command(OUTPUT mlir-linpackcmatgenf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Matgen/MLIRLinpackCMatgenF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Matgen/mlir-linpackcmatgenf32.o
)
add_library(MLIRLinpackMatgenF32 STATIC mlir-linpackcmatgenf32.o)
set_target_properties(MLIRLinpackMatgenF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcmatgenf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Matgen/MLIRLinpackCMatgenF64.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Matgen/mlir-linpackcmatgenf64.o
)
add_library(MLIRLinpackMatgenF64 STATIC mlir-linpackcmatgenf64.o)
set_target_properties(MLIRLinpackMatgenF64 PROPERTIES LINKER_LANGUAGE CXX)

# gcc 编译
# Matgen
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Matgen.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Matgen/Matgen.cpp 
         -c  -ftree-vectorize -o Matgen.o
        
)
add_library(Matgen STATIC Matgen.o)
set_target_properties(Matgen PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Matgen
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Matgen.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Matgen/Matgen.cpp 
           -c  -fvectorize  -o Matgen.o
          
)
add_library(Matgen STATIC Matgen.o)
set_target_properties(Matgen PROPERTIES LINKER_LANGUAGE CXX)

endif()