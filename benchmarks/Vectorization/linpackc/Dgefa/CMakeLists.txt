#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
# dgefa
add_custom_command(OUTPUT mlir-linpackcdgefarollf32.o
  COMMAND ${LLVM_MLIR_BINARY_DIR}/mlir-opt
          ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dgefa/MLIRLinpackCDgefaRollF32.mlir 
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
            -o ${BUDDY_BINARY_DIR}/../benchmarks/Vectorization/linpackc/Dgefa/mlir-linpackcdgefarollf32.o
)
add_library(MLIRLinpackDgefaRollF32 STATIC mlir-linpackcdgefarollf32.o)
# target_link_libraries(MLIRLinpackDgefaRollF32

#                       MLIRLinpackDscalRollF32
#                       MLIRLinpackDscalUnrollF32

#                       MLIRLinpackIdamaxF32

#                       MLIRLinpackDaxpyRollF32
#                       MLIRLinpackDaxpyUnrollF32
#                     )
set_target_properties(MLIRLinpackDgefaRollF32 PROPERTIES LINKER_LANGUAGE CXX)


# Dgefa gcc
function(build_linpackcdgefa_gcc type compiler)
add_custom_command(OUTPUT Dgefa${type}_gcc.o
COMMAND cat ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dgefa/Dgefa.cpp |
        sed -e 's/TYPE_PLACEHOLDER/${type}/g' -e 's/COMPILER_PLACEHOLDER/${compiler}/g' |
        g++ -x c++ -c  -ftree-vectorize -march=native -static 
        -L /root/buddy-benchmark/build/benchmarks/Vectorization/linpackc/Idamax
        # -lDaxpyfloat_gcc -lDaxpydouble_gcc
        # -lDscalfloat_gcc -lDscaldouble_gcc
        # -lIdamaxfloat_gcc -lIdamaxdouble_gcc
        -o Dgefa${type}_gcc.o -
        
)
add_library(Dgefa${type}_gcc STATIC Dgefa${type}_gcc.o)
set_target_properties(Dgefa${type}_gcc PROPERTIES LINKER_LANGUAGE CXX)
endfunction()

build_linpackcdgefa_gcc(float gcc)
build_linpackcdgefa_gcc(double gcc)

#Dgefa clang 
function(build_linpackcdgefa_clang type compiler)
add_custom_command(OUTPUT Dgefa${type}_clang.o
COMMAND cat ${BUDDY_SOURCE_DIR}/benchmarks/Vectorization/linpackc/Dgefa/Dgefa.cpp |
        sed -e 's/TYPE_PLACEHOLDER/${type}/g' -e 's/COMPILER_PLACEHOLDER/${compiler}/g' |
        ${LLVM_MLIR_BINARY_DIR}/clang++ -x c++ -c  -fvectorize -march=native 
        # -lDaxpyfloat_clang -lDaxpydouble_clang
        # -lDscalfloat_clang -lDscaldouble_clang
        # -lIdamaxfloat_clang -lIdamaxdouble_clang
        -o Dgefa${type}_clang.o -    
)
add_library(Dgefa${type}_clang STATIC Dgefa${type}_clang.o)
set_target_properties(Dgefa${type}_clang PROPERTIES LINKER_LANGUAGE CXX)
endfunction()

build_linpackcdgefa_clang(float clang)
build_linpackcdgefa_clang(double clang)




