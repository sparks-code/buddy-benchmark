#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_custom_command(OUTPUT mlir-linpackcdmxpyf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dmxpy/MLIRLinpackCDmxpyF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dmxpy/mlir-linpackcdmxpyf32.o
)
add_library(MLIRLinpackDmxpyF32 STATIC mlir-linpackcdmxpyf32.o)
set_target_properties(MLIRLinpackDmxpyF32 PROPERTIES LINKER_LANGUAGE CXX)

# gcc 编译
# Dmxpy
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Dmxpy.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dmxpy/Dmxpy.cpp 
         -c  -ftree-vectorize -o Dmxpy.o
        
)
add_library(Dmxpy STATIC Dmxpy.o)
set_target_properties(Dmxpy PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Dmxpy
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Dmxpy.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dmxpy/Dmxpy.cpp 
           -c  -fvectorize  -o Dmxpy.o
          
)
add_library(Dmxpy STATIC Dmxpy.o)
set_target_properties(Dmxpy PROPERTIES LINKER_LANGUAGE CXX)

endif()


