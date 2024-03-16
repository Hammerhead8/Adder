/* interp.c
 *
 * Interpolation function definitions */

#include <stdlib.h> /* For malloc and free */
#include <math.h> /* For pow */
#include "adder_interp.h"
#include "adder_matrix.h"
#include "adder_linalg.h"

/* Linear interpolation.
 * This is defined as calculating y = y0 + (x2 - x0) * ((y1 - y0) / (x1 - x0))
 *
 * x0 is the two x values that form the endpoints of the interval
 * y0 is the function values at the x values
 * x2 is the x-value of the intermediate point */
double
linearInterp (double *x0, double *y0, double x2)
{
	double y;

	y = y0[0] + (x2 - x0[0]) * ((y0[1] - y0[0]) / (x0[1] - x0[0]));

	return y;
}

/* Polynomial interpolation.
 * This is defined as finding a polynomial that approximates the given function
 * and then calculating the value of the approximating function at the intermediate point.
 *
 * result is the value of the interpolating function at the intermediate point
 * n is the number of points being used (the order of the interpolating polynomial is n - 1)
 * x0 is the x values of the points
 * y0 is the y values of the points
 * x2 is the intermediate point being interpolated */
int
polynomialInterp (double *result, int n, double *x0, double *y0, double x2)
{
	int i, j;
	adder_matrix *m;
	adder_vector *b;
	adder_vector *resVect;

	m = matrixInit2 (n, n);
	if (m == 0x00) {
		return INIT_ERROR;
	}

	b = vectorInit2 (COLUMN_VECTOR, n);
	if (b == 0x00) {
		deleteMatrix (m);
		return INIT_ERROR;
	}

	/* Fill the matrix and vector with values.
	 * The matrix is a Vandermonde matrix and the vector
	 * contains the y values at the points */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			m->mat[i * n + j] = pow (x0[i], n - j - 1);
		}

		b->vect[i] = y0[i];
	}

	/* The coefficients are solved by multiplying the inverse of M by b */
	m = inverse (m);
	resVect = mvMultiply (m, b);

	/* Now calculate the value of the interpolated function at the intermediate point
	 * The coefficients are stored in resVect from lowest to highest degree in the polynomial. */
	*result = 0;
	for (i = 0; i < n; i++) {
		*result += resVect->vect[i] * pow (x2, n - 1 - i);
	}

	/* Now we can delete m and b */
	deleteMatrix (m);
	deleteVector (b);
	deleteVector (resVect);

	return 0;
}

/* Fit an (n-1)-order polynomial to n points.
 *
 * coefficients is an n element array that will hold the calculated coefficients of the polynomial
 * n is the number of points
 * x0 is a pointer to an array holding the x-values of the points
 * y0 is a pointer to an array holding the y-values of the points */
int
polynomialInterpFunction (double *coefficients, int n, double *x0, double *y0)
{
	int i, j;
	adder_matrix *m;
	adder_vector *b;
	adder_vector *res;

	m = matrixInit2 (n, n);
	if (m == 0x00) {
//		fprintf (stderr, "Failed to create matrix in function polynomialInterpFunction.\n");
		return INIT_ERROR;
	}

	b = vectorInit2 (COLUMN_VECTOR, n);
	if (b == 0x00) {
		deleteMatrix (m);
//		fprintf (stderr, "Failed to create vector in function polynomialInterpFunction.\n");
		return INIT_ERROR;
	}

	/* Fill the matrix and vector with values */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			m->mat[i * n + j] = pow (x0[i], n - j - 1);
		}

		b->vect[i] = y0[i];
	}

	/* Calculate the coefficients by multiplying the inverse of m with b */
	m = inverse (m);
	res = mvMultiply (m, b);

	/* Copy the results into coefficients */
	for (i = 0; i < n; i++) {
		coefficients[i] = res->vect[i];
	}

	/* The last step is to delete the matrix and vectors */
	deleteMatrix (m);
	deleteVector (b);
	deleteVector (res);

	return 0;
}
