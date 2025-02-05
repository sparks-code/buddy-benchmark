//===- MLIRLinpackCDaxpy.mlir ---------------------------------------------===//
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
//===----------------------------------------------------------------------===//
//
// This file provides the MLIR linpackc daxpy function.
//
//===----------------------------------------------------------------------===//


func.func @mlir_linpackcdaxpyrollTYPE_PLACEHOLDER(%n : i32, %da : TYPE_PLACEHOLDER, %dx: memref<?xTYPE_PLACEHOLDER>, %incx : i32,
                                   %dy: memref<?xTYPE_PLACEHOLDER>, %incy : i32) {
  %c0 = arith.constant 0 : index
  %i0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : index
  %i1 = arith.constant 1 : i32
  %c4 = arith.constant 4 : index
  %da_i = arith.fptosi %da : TYPE_PLACEHOLDER to i32
  %da_index = arith.index_cast %da_i : i32 to index
  %n_index = arith.index_cast %n : i32 to index

  %cond1 = arith.cmpi "sle", %n, %i0 : i32
  %cond2 = arith.cmpi "eq", %da_index, %c0 : index
  %cond3 = arith.cmpi "ne", %incx, %i1 : i32
  %cond4 = arith.cmpi "ne", %incy, %i1 : i32
  %cond5 = arith.ori %cond3, %cond4 : i1

  cf.cond_br %cond1, ^terminator, ^continue0
  ^continue0:
    cf.cond_br %cond2, ^terminator, ^continue1

  ^continue1:
    cf.cond_br %cond5, ^continue2, ^continue3

  ^continue2:
    %ix = arith.constant 0 : i32
    %iy = arith.constant 0 : i32
    %cond6 = arith.cmpi "slt", %incx, %i0 : i32
    %cond7 = arith.cmpi "slt", %incy, %i0 : i32
    %ix_0 = scf.if %cond6 -> (i32) {
      %tmp = arith.subi %i1, %n : i32
      %ix_1 = arith.muli %tmp, %incx : i32
      scf.yield %ix_1 : i32
    } else {
      scf.yield %ix : i32
    }
    %iy_0 = scf.if %cond7 -> (i32) {
      %tmp = arith.subi %i1, %n : i32
      %iy_1 = arith.muli %tmp, %incy : i32
      scf.yield %iy_1 : i32
    } else{
      scf.yield %iy : i32
    }

    %incx_index = arith.index_cast %incx : i32 to index
    %incy_index = arith.index_cast %incy : i32 to index
    %ix_0_index = arith.index_cast %ix_0 : i32 to index
    %iy_0_index = arith.index_cast %iy_0 : i32 to index

    %ix_3, %iy_3 = scf.for %i_0 = %c0 to %n_index step %c1
    iter_args(%ix_4 = %ix_0_index, %iy_4 = %iy_0_index) -> (index, index){
      %dx_val_0 = memref.load %dx[%ix_4] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_0 = memref.load %dy[%iy_4] : memref<?xTYPE_PLACEHOLDER>
      %result_0 = arith.mulf %da, %dx_val_0 : TYPE_PLACEHOLDER
      %new_dy_val_0 = arith.addf %dy_val_0, %result_0 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_0, %dy[%iy_4] : memref<?xTYPE_PLACEHOLDER>
      %ix_2 = arith.addi %ix_4, %incx_index : index
      %iy_2 = arith.addi %iy_4, %incy_index : index
      scf.yield %ix_2, %iy_2 : index, index
    }
    return

  ^continue3:
    scf.for %i_1 = %c0 to %n_index step %c1 {
      %dx_val_1 = memref.load %dx[%i_1] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_1 = memref.load %dy[%i_1] : memref<?xTYPE_PLACEHOLDER>
      %result_1 = arith.mulf %da, %dx_val_1 : TYPE_PLACEHOLDER
      %new_dy_val_1 = arith.addf %dy_val_1, %result_1 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_1, %dy[%i_1] : memref<?xTYPE_PLACEHOLDER>
    }
    return
  
  ^terminator:
    return
}

func.func @mlir_linpackcdaxpyunrollTYPE_PLACEHOLDER(%n : i32, %da : TYPE_PLACEHOLDER, %dx: memref<?xTYPE_PLACEHOLDER>, %incx : i32,
                                   %dy: memref<?xTYPE_PLACEHOLDER>, %incy : i32) {
  %c0 = arith.constant 0 : index
  %i0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : index
  %i1 = arith.constant 1 : i32
  %c2 = arith.constant 2 : index
  %c3 = arith.constant 3 : index
  %c4 = arith.constant 4 : index
  %n_index = arith.index_cast %n : i32 to index
  %da_i = arith.fptosi %da : TYPE_PLACEHOLDER to i32
  %da_index = arith.index_cast %da_i : i32 to index
  %m = arith.remui %n_index, %c4 : index

  %cond1 = arith.cmpi "sle", %n, %i0 : i32
  %cond2 = arith.cmpi "eq", %da_index, %c0 : index
  %cond3 = arith.cmpi "ne", %incx, %i1 : i32
  %cond4 = arith.cmpi "ne", %incy, %i1 : i32
  %cond5 = arith.ori %cond3, %cond4 : i1
  
  cf.cond_br %cond1, ^terminator, ^continue0
  ^continue0:
    cf.cond_br %cond2, ^terminator, ^continue1

  ^continue1:
    cf.cond_br %cond5, ^continue2, ^continue3

  ^continue2:
    %ix = arith.constant 0 : i32
    %iy = arith.constant 0 : i32
    %cond6 = arith.cmpi "slt", %incx, %i0 : i32
    %cond7 = arith.cmpi "slt", %incy, %i0 : i32
    %ix_0 = scf.if %cond6 -> (i32) {
      %tmp = arith.subi %i1, %n : i32
      %ix_1 = arith.muli %tmp, %incx : i32
      scf.yield %ix_1 : i32
    } else {
      scf.yield %ix : i32
    }
    %iy_0 = scf.if %cond7 -> (i32) {
      %tmp = arith.subi %i1, %n : i32
      %iy_1 = arith.muli %tmp, %incy : i32
      scf.yield %iy_1 : i32
    } else{
      scf.yield %iy : i32
    }

    %incx_index = arith.index_cast %incx : i32 to index
    %incy_index = arith.index_cast %incy : i32 to index
    %ix_0_index = arith.index_cast %ix_0 : i32 to index
    %iy_0_index = arith.index_cast %iy_0 : i32 to index

    %ix_3, %iy_3 = scf.for %i_0 = %c0 to %n_index step %c1
    iter_args(%ix_4 = %ix_0_index, %iy_4 = %iy_0_index) -> (index, index){
      %dx_val_0 = memref.load %dx[%ix_4] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_0 = memref.load %dy[%iy_4] : memref<?xTYPE_PLACEHOLDER>
      %result_0 = arith.mulf %da, %dx_val_0 : TYPE_PLACEHOLDER
      %new_dy_val_0 = arith.addf %dy_val_0, %result_0 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_0, %dy[%iy_4] : memref<?xTYPE_PLACEHOLDER>
      %ix_2 = arith.addi %ix_4, %incx_index : index
      %iy_2 = arith.addi %iy_4, %incy_index : index
      scf.yield %ix_2, %iy_2 : index, index
    }
    return

  ^continue3:
    %cond8 = arith.cmpi "ne", %m, %c0 : index
    scf.if %cond8 {
      scf.for %i_1 = %c0 to %m step %c1 {
        %dx_val_1 = memref.load %dx[%i_1] : memref<?xTYPE_PLACEHOLDER>
        %dy_val_1 = memref.load %dy[%i_1] : memref<?xTYPE_PLACEHOLDER>
        %result_1 = arith.mulf %da, %dx_val_1 : TYPE_PLACEHOLDER
        %new_dy_val_1 = arith.addf %dy_val_1, %result_1 : TYPE_PLACEHOLDER
        memref.store %new_dy_val_1, %dy[%i_1] : memref<?xTYPE_PLACEHOLDER>
      }
    }

  %cond9 = arith.cmpi "slt", %n_index, %c4 : index
  cf.cond_br %cond9, ^terminator, ^continue4

  ^continue4:
    scf.for %i_2 = %m to %n_index step %c4 {
      %dx_val_2 = memref.load %dx[%i_2] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_2 = memref.load %dy[%i_2] : memref<?xTYPE_PLACEHOLDER>
      %result_2 = arith.mulf %da, %dx_val_2 : TYPE_PLACEHOLDER
      %new_dy_val_2 = arith.addf %dy_val_2, %result_2 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_2, %dy[%i_2] : memref<?xTYPE_PLACEHOLDER>

      %i_2_1 = arith.addi %i_2, %c1 : index
      %dx_val_3 = memref.load %dx[%i_2_1] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_3 = memref.load %dy[%i_2_1] : memref<?xTYPE_PLACEHOLDER>
      %result_3 = arith.mulf %da, %dx_val_3 : TYPE_PLACEHOLDER
      %new_dy_val_3 = arith.addf %dy_val_3, %result_3 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_3, %dy[%i_2_1] : memref<?xTYPE_PLACEHOLDER>

      %i_2_2 = arith.addi %i_2, %c2 : index
      %dx_val_4 = memref.load %dx[%i_2_2] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_4 = memref.load %dy[%i_2_2] : memref<?xTYPE_PLACEHOLDER>
      %result_4 = arith.mulf %da, %dx_val_4 : TYPE_PLACEHOLDER
      %new_dy_val_4 = arith.addf %dy_val_4, %result_4 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_4, %dy[%i_2_2] : memref<?xTYPE_PLACEHOLDER>

      %i_2_3 = arith.addi %i_2, %c3 : index
      %dx_val_5 = memref.load %dx[%i_2_3] : memref<?xTYPE_PLACEHOLDER>
      %dy_val_5 = memref.load %dy[%i_2_3] : memref<?xTYPE_PLACEHOLDER>
      %result_5 = arith.mulf %da, %dx_val_5 : TYPE_PLACEHOLDER
      %new_dy_val_5 = arith.addf %dy_val_5, %result_5 : TYPE_PLACEHOLDER
      memref.store %new_dy_val_5, %dy[%i_2_3] : memref<?xTYPE_PLACEHOLDER>
    }
    return

  ^terminator:
    return
}

