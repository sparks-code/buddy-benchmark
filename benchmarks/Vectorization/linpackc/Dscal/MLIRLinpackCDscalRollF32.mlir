// /*dscal(n,da,dx,incx)

// /*     scales a vector by a constant.
//       jack dongarra, linpack, 3/11/78.
// */
// REAL da,dx[];
// int n, incx;
// {
// 	int i,m,mp1,nincx;

// 	if(n <= 0)return;
// 	if(incx != 1) {

// 		/* code for increment not equal to 1 */

// 		nincx = n*incx;
// 		for (i = 0; i < nincx; i = i + incx)
// 			dx[i] = da*dx[i];
// 		return;
// 	}

// 	/* code for increment equal to 1 */

// #ifdef ROLL
// 	for (i = 0; i < n; i++)
// 		dx[i] = da*dx[i];
// #endif

// }
func.func @mlir_linpackcdscalrollf32(%n : i32, %da : f32, %dx: memref<?xf32>, %incx : i32) 
{
  %i0 = arith.constant 0 : i32
  %c0 = arith.constant 0 : index
  %c1 = arith.constant 1 : index
  %i1 = arith.constant 1 : i32
  %c4 = arith.constant 4 : index
  %da_i = arith.fptosi %da : f32 to i32
  %n_index = arith.index_cast %n : i32 to index
  %incx_index = arith.index_cast %incx : i32 to index

  %cond1 = arith.cmpi "sle", %n, %i0 : i32
  %cond2 = arith.cmpi "ne", %incx, %i1 : i32

  cf.cond_br %cond1, ^terminator, ^continue0
  
  ^continue0:
    cf.cond_br %cond2, ^continue1, ^continue2

  ^continue1:
// 		nincx = n*incx;
// 		for (i = 0; i < nincx; i = i + incx)
// 			dx[i] = da*dx[i];
// 		return;
    %nincx = arith.muli %n , %incx : i32
    %nincx_index = arith.index_cast %nincx : i32 to index
    scf.for %i_0 = %c0 to %nincx_index step %incx_index
    {
      %dx_val_0 = memref.load %dx[%i_0] : memref<?xf32>
      %result_0 = arith.mulf %da, %dx_val_0 : f32
      memref.store %result_0, %dx[%i_0] : memref<?xf32>
    }
    return

  ^continue2:
// #ifdef ROLL
// 	for (i = 0; i < n; i++)
// 		dx[i] = da*dx[i];
// #endif
    scf.for %i_1 = %c0 to %n_index step %c1 {
      %dx_val_1 = memref.load %dx[%i_1] : memref<?xf32>
      %result_1 = arith.mulf %da, %dx_val_1 : f32
      memref.store %result_1, %dx[%i_1] : memref<?xf32>
    }
    return
  
  ^terminator:
    return
}
