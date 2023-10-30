#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
# dgesl
# add_custom_command(OUTPUT mlir-linpackcdgeslrollf32.o
#   COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
#           ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dgesl/MLIRLinpackCDgeslRollF32.mlir 
#             -convert-scf-to-cf
#             -expand-strided-metadata
#             -convert-arith-to-llvm
#             -llvm-request-c-wrappers
#             -finalize-memref-to-llvm
#             -convert-func-to-llvm 
#             -reconcile-unrealized-casts | 
#           ${LLVM_MLIR_BINARY_DIR}/mlir-translate --mlir-to-llvmir |
#           ${LLVM_MLIR_BINARY_DIR}/llc -mtriple=${BUDDY_OPT_TRIPLE} 
#             -mattr=${BUDDY_OPT_ATTR} --filetype=obj 
#             -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dgesl/mlir-linpackcdgeslrollf32.o
# )
# add_library(MLIRLinpackDgeslRollF32 STATIC mlir-linpackcdgeslrollf32.o)
# set_target_properties(MLIRLinpackDgeslRollF32 PROPERTIES LINKER_LANGUAGE CXX)

# Dgesl gcc
function(build_linpackcdgesl_gcc type compiler)
add_custom_command(OUTPUT Dgesl${type}_gcc.o
COMMAND cat ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dgesl/Dgesl.cpp |
        sed -e 's/TYPE_PLACEHOLDER/${type}/g' -e 's/COMPILER_PLACEHOLDER/${compiler}/g' |
        g++ -x c++ -c  -ftree-vectorize -march=native -static 
        -o Dgesl${type}_gcc.o -
        
)
add_library(Dgesl${type}_gcc STATIC Dgesl${type}_gcc.o)
set_target_properties(Dgesl${type}_gcc PROPERTIES LINKER_LANGUAGE CXX)
endfunction()

build_linpackcdgesl_gcc(float gcc)
build_linpackcdgesl_gcc(double gcc)

#Dgesl clang 
function(build_linpackcdgesl_clang type compiler)
add_custom_command(OUTPUT Dgesl${type}_clang.o
COMMAND cat ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dgesl/Dgesl.cpp |
        sed -e 's/TYPE_PLACEHOLDER/${type}/g' -e 's/COMPILER_PLACEHOLDER/${compiler}/g' |
        ${LLVM_MLIR_BINARY_DIR}/clang++ -x c++ -c  -fvectorize -march=native 
        -o Dgesl${type}_clang.o -    
)
add_library(Dgesl${type}_clang STATIC Dgesl${type}_clang.o)
set_target_properties(Dgesl${type}_clang PROPERTIES LINKER_LANGUAGE CXX)
endfunction()

build_linpackcdgesl_clang(float clang)
build_linpackcdgesl_clang(double clang)




