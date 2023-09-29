// REAL ddot(n,dx,incx,dy,incy)
// /*
//      forms the dot product of two vectors.
//      jack dongarra, linpack, 3/11/78.
// */
// REAL dx[],dy[];

// int incx,incy,n;
// {
// 	REAL dtemp;
// 	int i,ix,iy,m,mp1;

// 	dtemp = ZERO;

// 	if(n <= 0) return(ZERO);

// 	if(incx != 1 || incy != 1) {

// 		/* code for unequal increments or equal increments
// 		   not equal to 1					*/

// 		ix = 0;
// 		iy = 0;
// 		if (incx < 0) ix = (-n+1)*incx;
// 		if (incy < 0) iy = (-n+1)*incy;
// 		for (i = 0;i < n; i++) {
// 			dtemp = dtemp + dx[ix]*dy[iy];
// 			ix = ix + incx;
// 			iy = iy + incy;
// 		}
// 		return(dtemp);
// 	}

// 	/* code for both increments equal to 1 */

// #ifdef ROLL
// 	for (i=0;i < n; i++)
// 		dtemp = dtemp + dx[i]*dy[i];
// 	return(dtemp);
// #endif
// #ifdef UNROLL

// 	m = n % 5;
// 	if (m != 0) {
// 		for (i = 0; i < m; i++)
// 			dtemp = dtemp + dx[i]*dy[i];
// 		if (n < 5) return(dtemp);
// 	}
// 	for (i = m; i < n; i = i + 5) {
// 		dtemp = dtemp + dx[i]*dy[i] +
// 		dx[i+1]*dy[i+1] + dx[i+2]*dy[i+2] +
// 		dx[i+3]*dy[i+3] + dx[i+4]*dy[i+4];
// 	}
// 	return(dtemp);
// #endif
// }

func.func @mlir_linpackcddotrollf64(%n : i32, %dx: memref<?xf64>, %incx : i32, 
                                   %dy: memref<?xf64>, %incy : i32) -> f64 {
  %c0 = arith.constant 0 : index
  %i0 = arith.constant 0 : i32
  %c1 = arith.constant 1 : index
  %i1 = arith.constant 1 : i32
  %c4 = arith.constant 4 : index
  %f_0 = arith.constant 0.0 : f64
  %n_index = arith.index_cast %n : i32 to index
  %dtemp_0 = arith.constant 0.0 : f64

  %cond1 = arith.cmpi "sle", %n, %i0 : i32
  %cond2 = arith.cmpi "ne", %incx, %i1 : i32
  %cond3 = arith.cmpi "ne", %incy, %i1 : i32
  %cond4 = arith.ori %cond2, %cond3 : i1

  cf.cond_br %cond1, ^terminator0, ^continue0

  ^terminator0: 
    return %f_0 :f64

  ^continue0:
    cf.cond_br %cond4, ^continue1, ^continue2

  ^continue1:
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

    %ix_3, %iy_3, %dtemp_1 = scf.for %i_0 = %c0 to %n_index step %c1
    iter_args(%ix_4 = %ix_0_index, %iy_4 = %iy_0_index, %dtemp_iter_1 = %dtemp_0) -> (index, index, f64){
      %dx_val_0 = memref.load %dx[%ix_4] : memref<?xf64>
      %dy_val_0 = memref.load %dy[%iy_4] : memref<?xf64>
      %result_0 = arith.mulf %dx_val_0, %dy_val_0 : f64
      %dtemp_next_1 = arith.addf %dtemp_iter_1, %result_0 : f64
      %ix_2 = arith.addi %ix_4, %incx_index : index
      %iy_2 = arith.addi %iy_4, %incy_index : index
      scf.yield %ix_2, %iy_2, %dtemp_next_1 : index, index, f64
    }
    return %dtemp_1 : f64
    
  ^continue2:
    %dtemp_2 = scf.for %i_1 = %c0 to %n_index step %c1 
      iter_args(%dtemp_iter_2 = %dtemp_0) -> (f64) {
      %dx_val_1 = memref.load %dx[%i_1] : memref<?xf64>
      %dy_val_1 = memref.load %dy[%i_1] : memref<?xf64>
      %result_1 = arith.mulf %dx_val_1, %dy_val_1 : f64
      %dtemp_next_2 = arith.addf %dtemp_iter_2, %result_1 : f64 
      scf.yield %dtemp_next_2 : f64
    }
    return %dtemp_2 : f64
  
}
