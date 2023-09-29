// /*----------------------*/ 
// REAL epslon (x)
// REAL x;
// /*
//      estimate unit roundoff in quantities of size x.
// */

// {
// 	REAL a,b,c,eps;
// 	a = 4.0e0/3.0e0;
// 	eps = ZERO;
// 	while (eps == ZERO) {
// 		b = a - ONE;
// 		c = b + b + b;
// 		eps = fabs((double)(c-ONE));
// 	}
// 	return(eps*fabs((double)x));
// }
 func.func @mlir_linpackcepslonf64(%x : f64) -> f64 {
     %f4 = arith.constant 4.0 : f64
     %f3 = arith.constant 3.0 : f64
     %a = arith.divf %f4, %f3 : f64
     %f0 = arith.constant 0.0 : f64
     %f1 = arith.constant 1.0 :f64
     %eps_0 = arith.constant 0.0 :f64
     %eps_final = scf.while (%eps = %eps_0) : (f64) -> f64 {
          %condition = arith.cmpf ueq, %eps, %f0 : f64
          scf.condition(%condition) %eps : f64
     } do {
          ^bb0(%eps: f64):
          %b = arith.subf %a , %f1 : f64
          %c_temp = arith.addf %b, %b :f64
          %c = arith.addf %c_temp, %b :f64
          //   eps = fabs((double)(c-ONE));
          %c_one = arith.subf %c, %f1 : f64
          %eps_next = math.absf %c_one :f64
          scf.yield %eps_next : f64
     }
// return(eps*fabs((double)x));
     %x_abs = math.absf %x : f64
     %res = arith.mulf %eps_final, %x_abs : f64
     return %res : f64    
 }