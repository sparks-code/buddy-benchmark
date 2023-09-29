#-------------------------------------------------------------------------------
# MLIR SCF Dialect linpackc Operation + Upstream Lowering Passes
#-------------------------------------------------------------------------------
add_subdirectory(Daxpy)
add_subdirectory(Ddot)
add_subdirectory(Dgefa)
# add_subdirectory(Dgesl)
add_subdirectory(Dmxpy)
add_subdirectory(Dscal)
add_subdirectory(Epslon)
add_subdirectory(Idamax)
add_subdirectory(Matgen)

add_dependencies(MLIRLinpackDgefaRollF32 
                MLIRLinpackDscalRollF32
                MLIRLinpackDscalUnrollF32

                MLIRLinpackIdamaxF32

                MLIRLinpackDaxpyRollF32
                MLIRLinpackDaxpyUnrollF32
                )
#-------------------------------------------------------------------------------
# Vectorization Benchmark Targets
#-------------------------------------------------------------------------------

add_executable(vectorization-linpackc-benchmark
  Main.cpp
  ./Daxpy/MLIRLinpackCDaxpyBenchmark.cpp
  ./Matgen/MLIRLinpackCMatgenBenchmark.cpp
  ./Ddot/MLIRLinpackCDdotBenchmark.cpp
  ./Dscal/MLIRLinpackCDscalBenchmark.cpp
  ./Idamax/MLIRLinpackCIdamaxBenchmark.cpp
  ./Dmxpy/MLIRLinpackCDmxpyBenchmark.cpp
  ./Epslon/MLIRLinpackCEpslonBenchmark.cpp
  )

target_link_libraries(vectorization-linpackc-benchmark
  GoogleBenchmark
  
  MLIRLinpackDaxpyRollF32
  MLIRLinpackDaxpyRollF64
  MLIRLinpackDaxpyUnrollF32
  MLIRLinpackDaxpyUnrollF64
  Daxpy

  MLIRLinpackMatgenF32
  MLIRLinpackMatgenF64
  Matgen

  MLIRLinpackDdotRollF32
  MLIRLinpackDdotRollF64
  MLIRLinpackDdotUnrollF32
  MLIRLinpackDdotUnrollF64
  Ddot

  MLIRLinpackDscalRollF32
  MLIRLinpackDscalUnrollF32
  MLIRLinpackDscalRollF64
  MLIRLinpackDscalUnrollF64
  Dscal

  MLIRLinpackIdamaxF32
  MLIRLinpackIdamaxF64
  Idamax
  
  MLIRLinpackDmxpyF32
  MLIRLinpackDmxpyF64
  Dmxpy
  
  MLIRLinpackEpslonF32
  MLIRLinpackEpslonF64
  Epslon

  MLIRLinpackDgefaRollF32
  )

