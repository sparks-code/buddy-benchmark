#include"Epslon.h"

/*----------------------*/ 
float epslon (float x)
/*
     estimate unit roundoff in quantities of size x.
*/

{
	float a,b,c,eps;
/*
     this program should function properly on all systems
     satisfying the following two assumptions,
        1.  the base used in representing dfloating point
            numbers is not a power of three.
        2.  the quantity  a  in statement 10 is represented to 
            the accuracy used in dfloating point variables
            that are stored in memory.
     the statement number 10 and the go to 10 are intended to
     force optimizing compilers to generate code satisfying 
     assumption 2.
     under these assumptions, it should be true that,
            a  is not exactly equal to four-thirds,
            b  has a zero for its last bit or digit,
            c  is not exactly equal to one,
            eps  measures the separation of 1.0 from
                 the next larger dfloating point number.
     the developers of eispack would appreciate being informed
     about any systems where these assumptions do not hold.

     *****************************************************************
     this routine is one of the auxiliary routines used by eispack iii
     to avoid machine dependencies.
     *****************************************************************

     this version dated 4/6/83.
*/

	a = 4.0e0/3.0e0;
	eps = float(0.0);
	while (eps == float(0.0)) {
		b = a - float(1.0);
		c = b + b + b;
		eps = fabs((double)(c-float(1.0)));
	}
	return(eps*fabs((double)x));
}

/*----------------------*/ 
double epslon (double x)
/*
     estimate unit roundoff in quantities of size x.
*/

{
	double a,b,c,eps;
/*
     this program should function properly on all systems
     satisfying the following two assumptions,
        1.  the base used in representing ddoubleing point
            numbers is not a power of three.
        2.  the quantity  a  in statement 10 is represented to 
            the accuracy used in ddoubleing point variables
            that are stored in memory.
     the statement number 10 and the go to 10 are intended to
     force optimizing compilers to generate code satisfying 
     assumption 2.
     under these assumptions, it should be true that,
            a  is not exactly equal to four-thirds,
            b  has a zero for its last bit or digit,
            c  is not exactly equal to one,
            eps  measures the separation of 1.0 from
                 the next larger ddoubleing point number.
     the developers of eispack would appreciate being informed
     about any systems where these assumptions do not hold.

     *****************************************************************
     this routine is one of the auxiliary routines used by eispack iii
     to avoid machine dependencies.
     *****************************************************************

     this version dated 4/6/83.
*/

	a = 4.0e0/3.0e0;
	eps = double(0.0);
	while (eps == double(0.0)) {
		b = a - double(1.0);
		c = b + b + b;
		eps = fabs((double)(c-double(1.0)));
	}
	return(eps*fabs((double)x));
}