// /*----------------------*/ 
// matgen(a,lda,n,b,norma)
// REAL a[],b[],*norma;
// int lda, n;

// /* We would like to declare a[][lda], but c does not allow it.  In this
// function, references to a[i][j] are written a[lda*j+i].  */

// {
// 	int init, i, j;

// 	init = 1325;
// 	*norma = 0.0;
// 	for (j = 0; j < n; j++) {
// 		for (i = 0; i < n; i++) {
// 			init = 3125*init % 65536;
// 			a[lda*j+i] = (init - 32768.0)/16384.0;
// 			*norma = (a[lda*j+i] > *norma) ? a[lda*j+i] : *norma;
// 		}
// 	}
// 	for (i = 0; i < n; i++) {
//           b[i] = 0.0;
// 	}
// 	for (j = 0; j < n; j++) {
// 		for (i = 0; i < n; i++) {
// 			b[i] = b[i] + a[lda*j+i];
// 		}
// 	}
// }

func.func @mlir_linpackcmatgenf32(%a : memref<?xf32>, %lda : index, %n : index, %b : memref<?xf32>, %norma : memref<1xf32>)
{
	%c0 = arith.constant 0 : index
  	%c1 = arith.constant 1 : index
	%c3125 = arith.constant 3125 : i32
	%c65536 = arith.constant 65536 : i32
	%c0.0 = arith.constant 0.0 :f32
	%c32768.0 = arith.constant 32768.0 : f32
	%c16384.0 = arith.constant 16384.0 : f32
	%init_0 = arith.constant 1325 : i32
	//*norma = 0.0;
	memref.store %c0.0, %norma[%c0] : memref<1xf32>
	scf.for %j_0 = %c0 to %n step %c1 
	iter_args(%init_iter1 = %init_0) ->(i32){	
		%init = scf.for %i_0 = %c0 to %n step %c1 
			iter_args(%init_iter2 = %init_iter1) ->(i32){
			%temp_a_index = arith.muli %lda, %j_0: index
			%a_index = arith.addi %temp_a_index, %i_0 : index
			// init = 3125*init % 65536;
			// a[lda*j+i] = (init - 32768.0)/16384.0;
			%temp_init = arith.muli %c3125 , %init_iter2 : i32
			%new_init = arith.remsi %temp_init, %c65536 : i32
			%new_init_f32 = arith.sitofp %new_init : i32 to f32
			%temp_data = arith.subf %new_init_f32, %c32768.0 : f32
			%new_data = arith.divf %temp_data, %c16384.0 : f32
			memref.store %new_data, %a[%a_index] : memref<?xf32>
			//*norma = (a[lda*j+i] > *norma) ? a[lda*j+i] : *norma;
			%old_data = memref.load  %norma[%c0] : memref<1xf32>
			%cond_0 = arith.cmpf ugt, %new_data, %old_data :f32
			%max_data = arith.select %cond_0, %new_data, %old_data : f32
			memref.store  %max_data, %norma[%c0] : memref<1xf32>
			scf.yield %new_init : i32
		}
		scf.yield %init : i32
	}
	// for (i = 0; i < n; i++) {
    //       b[i] = 0.0;
	// }
	scf.for %i_1 = %c0 to %n step %c1 {
		memref.store %c0.0 , %b[%i_1] : memref<?xf32>
	}

	// for (j = 0; j < n; j++) {
	// 	for (i = 0; i < n; i++) {
	// 		b[i] = b[i] + a[lda*j+i];
	// 	}
	// }
	scf.for %j_2 = %c0 to %n step %c1 {
		scf.for %i_2 = %c0 to %n step %c1 {
			%temp_a_index_2 = arith.muli %lda, %j_2 : index
			%a_index_2 = arith.addi %temp_a_index_2, %i_2 : index
			%b_data = memref.load %b[%i_2] : memref<?xf32>
			%a_data = memref.load %a[%a_index_2] : memref<?xf32>
			%result = arith.addf %b_data, %a_data : f32
			memref.store %result , %b[%i_2] : memref<?xf32>
		}
	}

	return
}

