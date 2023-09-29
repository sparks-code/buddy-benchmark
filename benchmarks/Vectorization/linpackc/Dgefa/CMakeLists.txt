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
target_link_libraries(MLIRLinpackDgefaRollF32

                      MLIRLinpackDscalRollF32
                      MLIRLinpackDscalUnrollF32

                      MLIRLinpackIdamaxF32

                      MLIRLinpackDaxpyRollF32
                      MLIRLinpackDaxpyUnrollF32
                    )
set_target_properties(MLIRLinpackDgefaRollF32 PROPERTIES LINKER_LANGUAGE CXX)



