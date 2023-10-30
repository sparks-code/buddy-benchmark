#include <math.h>
#include <stdio.h>
#include <Daxpy/Daxpy.h>
#include <Ddot/Ddot.h>

void dgesl_ROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(TYPE_PLACEHOLDER a[],int lda, int n,int ipvt[],TYPE_PLACEHOLDER b[],int job)
{
/*     internal variables	*/

	TYPE_PLACEHOLDER t;
	int k,kb,l,nm1;

	nm1 = n - 1;
	if (job == 0) {

		/* job = 0 , solve  a * x = b
		   first solve  l*y = b    	*/

		if (nm1 >= 1) {
			for (k = 0; k < nm1; k++) {
				l = ipvt[k];
				t = b[l];
				if (l != k){ 
					b[l] = b[k];
					b[k] = t;
				}	
				daxpy_ROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(n-(k+1),t,&a[lda*k+k+1],1,&b[k+1],1);
			}
		} 

		/* now solve  u*x = y */

		for (kb = 0; kb < n; kb++) {
		    k = n - (kb + 1);
		    b[k] = b[k]/a[lda*k+k];
		    t = -b[k];
		    daxpy_ROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(k,t,&a[lda*k+0],1,&b[0],1);
		}
	}
	else { 

		/* job = nonzero, solve  trans(a) * x = b
		   first solve  trans(u)*y = b 			*/

		for (k = 0; k < n; k++) {
			t = ddot_ROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(k,&a[lda*k+0],1,&b[0],1);
			b[k] = (b[k] - t)/a[lda*k+k];
		}

		/* now solve trans(l)*x = y	*/

		if (nm1 >= 1) {
			for (kb = 1; kb < nm1; kb++) {
				k = n - (kb+1);
				b[k] = b[k] + ddot_UNROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(n-(k+1),&a[lda*k+k+1],1,&b[k+1],1);
				l = ipvt[k];
				if (l != k) {
					t = b[l];
					b[l] = b[k];
					b[k] = t;
				}
			}
		}
	}
}


void dgesl_UNROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(TYPE_PLACEHOLDER a[],int lda, int n,int ipvt[],TYPE_PLACEHOLDER b[],int job)
{
/*     internal variables	*/

	TYPE_PLACEHOLDER t;
	int k,kb,l,nm1;

	nm1 = n - 1;
	if (job == 0) {

		/* job = 0 , solve  a * x = b
		   first solve  l*y = b    	*/

		if (nm1 >= 1) {
			for (k = 0; k < nm1; k++) {
				l = ipvt[k];
				t = b[l];
				if (l != k){ 
					b[l] = b[k];
					b[k] = t;
				}	
				daxpy_UNROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(n-(k+1),t,&a[lda*k+k+1],1,&b[k+1],1);
			}
		} 

		/* now solve  u*x = y */

		for (kb = 0; kb < n; kb++) {
		    k = n - (kb + 1);
		    b[k] = b[k]/a[lda*k+k];
		    t = -b[k];
		    daxpy_UNROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(k,t,&a[lda*k+0],1,&b[0],1);
		}
	}
	else { 

		/* job = nonzero, solve  trans(a) * x = b
		   first solve  trans(u)*y = b 			*/

		for (k = 0; k < n; k++) {
			t = ddot_UNROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(k,&a[lda*k+0],1,&b[0],1);
			b[k] = (b[k] - t)/a[lda*k+k];
		}

		/* now solve trans(l)*x = y	*/

		if (nm1 >= 1) {
			for (kb = 1; kb < nm1; kb++) {
				k = n - (kb+1);
				b[k] = b[k] + ddot_UNROLL_TYPE_PLACEHOLDER_COMPILER_PLACEHOLDER(n-(k+1),&a[lda*k+k+1],1,&b[k+1],1);
				l = ipvt[k];
				if (l != k) {
					t = b[l];
					b[l] = b[k];
					b[k] = t;
				}
			}
		}
	}
}