// func.func private @mlir_linpackcidamaxf32(%n : i32,  %dx: memref<?xf32>, %incx : i32) -> i32
// func.func private @mlir_linpackcdscalrollf32(%n : i32, %da : f32, %dx: memref<?xf32>, %incx : i32) 
// func.func private @mlir_linpackcdaxpyrollf32(%n : i32, %da : f32, %dx: memref<?xf32>, %incx : i32,
//                                    %dy: memref<?xf32>, %incy : i32)

func.func @get_val(%a: memref<?xf32>, %lda : index, %i : index, %j : index ) -> f32{
  // m[lda*i+j];
  %lda_mj = arith.muli %lda, %i : index
  %lda_mj_ai = arith.addi %lda_mj, %i : index
  %a_val = memref.load %m[%lda_mj_ai] : memref<?xf32>
  return %a_val : f32
}

func.func @set_val(%a: memref<?xf32>, %lda : index, %i : index, %j : index, %t: f32){
  // m[lda*i+j];
  %lda_mj = arith.muli %lda, %i : index
  %lda_mj_ai = arith.addi %lda_mj, %i : index
  memref.store %t, %a[%lda_mj_ai] : memref<?xf32>
  return 
}        

// dgefa(a,lda,n,ipvt,info)
// REAL a[];
// int lda,n,ipvt[],*info;
func.func @mlir_linpackcdgefaf32(%a : memref<?xf32>, %lda : i32, %n: i32, %ipvt : memref<?xi32>, %info : memref<i32>) 
{
// REAL t;
// int idamax(),j,k,kp1,l,nm1;
// 	*info = 0;
// 	nm1 = n - 1;
  %i0 = arith.constant 0 : i32
  %f0 = arith.constant 0.0 : f32
  %c0 = arith.constant 0 : index
  %c1 = arith.constant 1 : index
  %i1 = arith.constant 1 : i32   
  %nf1 = arith.constant -1.0 : f32  
  memref.store %i0, %info[%c0] : memref<1xi32>
  %nm1 = arith.subi %n, %i1 : i32
 
  %nm1_index = arith.index_cast %nm1 : i32 to index
  %lda_index = arith.index_cast %lda : i32 to index
//   if (nm1 >=  0) {
  %cond1 = arith.cmpi "sge", %nm1, %i0 : i32
  scf.if %cond1{
    scf.for %k_0_index = %c0 to %nm1_index step %c1{
  // 			kp1 = k + 1;
  //           		/* find l = pivot index	*/
  // 			l = idamax(n-k,&a[lda*k+k],1) + k;
  // 			ipvt[k] = l;

      %k_0_index_p1 = arith.addi %k_0_index, %c1 : index
      %k_0 = arith.index_cast %k_0_index : index to i32
      %n_sk = arith.subi %n, %k_0 :i32
      %a_val_0 = func.call @get_val(%a, %lda_index, %k_0_index, %k_0_index ) 
        : (memref<?xf32>, index, index, index) -> f32
      %l_temp = func.call @mlir_linpackcidamaxf32(%n_sk, %a_lda_mk_pk_index, %i1) //地址怎么传递
        : (i32, memref<?xf32>, i32) -> i32
      %l = %arith.addi %l_temp, %k_0 : i32
      memref.store %l, %ipvt[%k_0] : memref<?xi32>

      // if (a[lda*k+l] != ZERO) {
      %l_index = arith.index_cast %l : i32 to index
      %a_val_1 = func.call @get_val(%a, %lda_index, %k_0_index, %l_index ) 
        : (memref<?xf32>, index, index, index) -> f32
      %cond2 = arith.cmpf "une", %a_val_1, %f0 : f32
      scf.if{
          %cond3 = arith.cmpi "une", %l, %k_0 : i32
          scf.if %cond3{
            %t_0 = %a_val_1 : f32
            func.call @set_val(%a, %lda_index, %k_0_index, %l_index, %a_val_0) 
                : (memref<?xf32>, index, index, index, f32)
            func.call @set_val(%a, %lda_index, %k_0_index, %k_0_index, %t_0) 
                : (memref<?xf32>, index, index, index, f32)
          }
          %a_val_2 = func.call @get_val(%a, %lda_index, %k_0_index, %k_0_index ) 
                    : (memref<?xf32>, index, index, index) -> f32
          %t_1 = arith.divf %nf1, %a_val_2 :f32
          %n_sk_p1 = arith.subi %n, %k_p1 : i32
          %a_val_3 = func.call @get_val(%a, %lda_index, %k_0_index, %k_0_index_p1 ) 
                    : (memref<?xf32>, index, index, index) -> f32
          func.call @mlir_linpackcdscalrollf32(%n_sk_p1 , %t_1, %a_lda_mk_pk_p1_index, %i1)
                    : (i32, f32, memref<?xf32>, i32) 

          scf.for %j_0_index = %k_p1_index to %n_index step %c1{
            // t = a[lda*j+l]; 
            %t_2 = func.call @get_val(%a, %lda_index, %k_0_index, %k_0_index_p1 ) 
                    : (memref<?xf32>, index, index, index) -> f32
            //   if (l != k) {
            // 	a[lda*j+l] = a[lda*j+k];
            // 	a[lda*j+k] = t;
            // }
            scf.if %cond3{
                %a_val_4 = func.call @get_val(%a, %lda_index, %j_0_index, %k_0_index ) 
                    : (memref<?xf32>, index, index, index) -> f32
                func.call @set_val(%a, %lda_index, %j_0_index, %l_index, %a_val_4) 
                    : (memref<?xf32>, index, index, index, f32)
                func.call @set_val(%a, %lda_index, %j_0_index, %k_0_index, %t_2) 
                    : (memref<?xf32>, index, index, index, f32)
            }   
            // daxpy(n-(k+1),t,&a[lda*k+k+1],1,
					  //     &a[lda*j+k+1],1);     
            %a_val_4 = func.call @get_val(%a, %lda_index, %k_0_index, %k_0_index_p1 ) 
                    : (memref<?xf32>, index, index, index) -> f32
            %a_val_5 = func.call @get_val(%a, %lda_index, %j_0_index, %k_0_index_p1 ) 
                    : (memref<?xf32>, index, index, index) -> f32
            func.call @daxpy(%n_sk_p1, %t_2, %a_val_4, %i1, %a_val_5, %i1) 
                    : ( i32, f32,  memref<?xf32>,  i32, memref<?xf32>, i32)

          }
      }else{
           //*info = k;
            memref.store %k_0, %info[%c0] : memref<1xi32>
      }
    }
  }
  // ipvt[n-1] = n-1;
	// if (a[lda*(n-1)+(n-1)] == ZERO) *info = n-1;
    %n_s1_index = arith.subi %n_index, %c1 :index
    %n_s1 = arith.subi %n, %i1 :i32
    memref.store %n_s1, %ipvt[%n_s1_index] : memref<?xi32>
    a_val_6 = func.call @get_val(%a, %lda_index, %n_s1_index, %n_s1_index ) 
                    : (memref<?xf32>, index, index, index) -> f32
    %cond4 = arith.cmpf "eq", %a_val_1, %f0 : f32
    scf.if %cond4 {
       memref.store %n_s1, %info[%c0] : memref<?xi32>
    }
  
  return 
}
