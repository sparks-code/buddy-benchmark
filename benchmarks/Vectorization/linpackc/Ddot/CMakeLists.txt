#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
# ddot
add_custom_command(OUTPUT mlir-linpackcddotrollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Ddot/MLIRLinpackCDdotRollF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Ddot/mlir-linpackcddotrollf32.o
)
add_library(MLIRLinpackDdotRollF32 STATIC mlir-linpackcddotrollf32.o)
set_target_properties(MLIRLinpackDdotRollF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcddotunrollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Ddot/MLIRLinpackCDdotUnrollF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Ddot/mlir-linpackcddotunrollf32.o
)
add_library(MLIRLinpackDdotUnrollF32 STATIC mlir-linpackcddotunrollf32.o)
set_target_properties(MLIRLinpackDdotUnrollF32 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcddotrollf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Ddot/MLIRLinpackCDdotRollF64.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Ddot/mlir-linpackcddotrollf64.o
)
add_library(MLIRLinpackDdotRollF64 STATIC mlir-linpackcddotrollf64.o)
set_target_properties(MLIRLinpackDdotRollF64 PROPERTIES LINKER_LANGUAGE CXX)

add_custom_command(OUTPUT mlir-linpackcddotunrollf64.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Ddot/MLIRLinpackCDdotUnrollF64.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Ddot/mlir-linpackcddotunrollf64.o
)
add_library(MLIRLinpackDdotUnrollF64 STATIC mlir-linpackcddotunrollf64.o)
set_target_properties(MLIRLinpackDdotUnrollF64 PROPERTIES LINKER_LANGUAGE CXX)

# gcc 编译
# Ddot
if(GCC_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Ddot.o
COMMAND g++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Ddot/Ddot.cpp 
         -c  -ftree-vectorize -o Ddot.o
        
)
add_library(Ddot STATIC Ddot.o)
set_target_properties(Ddot PROPERTIES LINKER_LANGUAGE CXX)

endif()

#  clang 编译
# Ddot
if(CLANG_AUTO_VECTORIZATION)
add_custom_command(OUTPUT Ddot.o
  COMMAND clang++ ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Ddot/Ddot.cpp 
           -c  -fvectorize  -o Ddot.o
          
)
add_library(Ddot STATIC Ddot.o)
set_target_properties(Ddot PROPERTIES LINKER_LANGUAGE CXX)

endif()

