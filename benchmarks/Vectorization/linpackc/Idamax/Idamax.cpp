#include "Idamax.h"

/*----------------------*/ 
int idamax(int n,float dx[],int incx)

/*
     finds the index of element having max. absolute value.
     jack dongarra, linpack, 3/11/78.
*/
{
	float dmax;
	int i, ix, itemp;

	if( n < 1 ) return(-1);
	if(n ==1 ) return(0);
	if(incx != 1) {

		/* code for increment not equal to 1 */

		ix = 0;
		dmax = fabs((double)dx[0]);
		ix = ix + incx;
		for (i = 1; i < n; i++) {
			if(fabs((double)dx[ix]) > dmax)  {
				itemp = i;
				dmax = fabs((double)dx[ix]);
			}
			ix = ix + incx;
		}
	}
	else {

		/* code for increment equal to 1 */

		itemp = 0;
		dmax = fabs((double)dx[0]);
		for (i = 1; i < n; i++) {
			if(fabs((double)dx[i]) > dmax) {
				itemp = i;
				dmax = fabs((double)dx[i]);
			}
		}
	}
	return (itemp);
}

int idamax(int n,double dx[],int incx)

/*
     finds the index of element having max. absolute value.
     jack dongarra, linpack, 3/11/78.
*/
{
	double dmax;
	int i, ix, itemp;

	if( n < 1 ) return(-1);
	if(n ==1 ) return(0);
	if(incx != 1) {

		/* code for increment not equal to 1 */

		ix = 0;
		dmax = fabs((double)dx[0]);
		ix = ix + incx;
		for (i = 1; i < n; i++) {
			if(fabs((double)dx[ix]) > dmax)  {
				itemp = i;
				dmax = fabs((double)dx[ix]);
			}
			ix = ix + incx;
		}
	}
	else {

		/* code for increment equal to 1 */

		itemp = 0;
		dmax = fabs((double)dx[0]);
		for (i = 1; i < n; i++) {
			if(fabs((double)dx[i]) > dmax) {
				itemp = i;
				dmax = fabs((double)dx[i]);
			}
		}
	}
	return (itemp);
}