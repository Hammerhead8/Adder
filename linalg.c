/* linalg.c
 * Function definitions for the prototypes in linalg.h
 * This is the linear algebra part of Adder */
#include <stdlib.h> /* For malloc and free */
#include <math.h> /* For sqrt */
#include <cblas.h>
#include <lapacke.h>
#include "linalg.h"

/* TODO:  Singular value decomposition
	  Eigenvalues */

/* Transpose the matrix */
Matrix *
transpose (Matrix *m)
{
	Matrix *res;
	long int i, j;
	long int numRows, numColumns;

	numRows = m->rows;
	numColumns = m->columns;

	
	res = matrixInit2 (m->orientation, numColumns, numRows);

	for (i = 0; i < numRows; i++) {
		for (j = 0; j < numColumns; j++) {
			res->mat[j * numRows + i] = m->mat[i * numColumns + j];
		}
	}

	return res;
}

/* Transpose a vector */
void
vectorTranspose (Vector *v)
{
	v->orientation *= -1;
}

/* Calculate the inverse of the matrix */
Matrix *
inverse (Matrix *M)
{
	Matrix *res;
	lapack_int ipvt[M->rows];
	lapack_int info;
	int m, n;
	lapack_int err;

	m = M->rows;
	n = M->columns;

	/* If the matrix isn't square then it's inverse can't be calculated */
	if (m != n) {
		fprintf (stderr, "Dimension error:  Matrix not square.\n");
		return NULL;
	}

	/* Set res to be equal to M */
	res = matrixInit (M->orientation, M->rows, M->columns, M->mat);

	/* If the matrix is row major */
	if (M->orientation == ROW_MAJOR) {	
		/* Calculate the LU factorization of the matrix */
		err = LAPACKE_dgetrf (LAPACK_ROW_MAJOR, n, m, res->mat, n, ipvt);
		if (err < 0) {
			fprintf (stderr, "The value of argument %d is illegal\n", -1 * err);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Factorization is singular.\n");
			return NULL;
		}

		/* Invert the matrix */
		err = LAPACKE_dgetri (LAPACK_ROW_MAJOR, n, res->mat, n, ipvt);

		if (err == 0) {
			return res;
		}

		if (err < 0) {
			fprintf (stderr, "The value of argument %d is illegal\n", -1 * err);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Matrix is singular.\n");
			return NULL;
		}
	}

	/* Otherwise the matrix is column major */
	else {
		/* Calculate the LU factorization of the matrix */
		err = LAPACKE_dgetrf (LAPACK_COL_MAJOR, m, n, res->mat, m, ipvt);
		if (err < 0) {
			fprintf (stderr, "The value of argument %d is illegal\n", -1 * err);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Factorization is singular.\n");
			return NULL;
		}

		/* Invert the matrix */
		err = LAPACKE_dgetri (LAPACK_COL_MAJOR, m, res->mat, m, ipvt);
		if (err < 0) {
			fprintf (stderr, "The value of argument %d is illegal\n", -1 * err);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Matrix is singular.\n");
			return NULL;
		}
	}

	return 0;
}

/* Solve a linear system of equations */
Vector *
linearSolve (Matrix *M, Vector *b)
{
	Vector *res;
	lapack_int n;
	lapack_int m;
	lapack_int ipvt[M->rows];
	lapack_int err;
	int i;

	/* Check that the right-side vector (b) is a column vector */
	if (b->orientation == ROW_VECTOR) {
		fprintf (stderr, "ERROR:  b vector must be a column vector.\n");
		return NULL;
	}

	/* If the dimensions of M and b match and M is square then copy the
	 * values of b into res. */
	if ((M->rows == M->columns) && (M->rows == b->size) && (b->orientation == COLUMN_VECTOR)) {
		res = vectorInit (COLUMN_VECTOR, b->size, b->vect);
	}
	else {
		fprintf (stderr, "System is either over-determined, under-determined, or matrix and vector dimension mismatch.\n");
		return NULL;
	}

	/* Since M is square, the number of rows and columns is the same, so
	 * n is the same regardless */
	n = M->rows;

	/* If the M is row major */
	if (M->orientation == ROW_MAJOR) {
		/* Solve the system */
		err = LAPACKE_dgesv (LAPACK_ROW_MAJOR, n, 1, M->mat, n, ipvt, res->vect, 1);

		/* If no errors occured return the solution */
		if (err == 0) {
			return res;
		}

		/* Check for errors */
		if (err < 0) {
			fprintf (stderr, "Argument %d is invalid.\n", -1 * err);
			deleteVector (res);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Factorization creates singular matrix.\n");
			deleteVector (res);
			return NULL;
		}
	}

	/* Otherwise M is column major */
	else {
		err = LAPACKE_dgesv (LAPACK_COL_MAJOR, n, 1, M->mat, n, ipvt, res->vect, 1);

		/* If no errors occured return the solution */
		if (err == 0) {
			return res;
		}

		/* Check for errors */
		else if (err < 0) {
			fprintf (stderr, "Argument %d is invalid.\n", -1 * err);
			deleteVector (res);
			return NULL;
		}
		else {
			fprintf (stderr, "Factorization creates singular matrix.\n");
			deleteVector (res);
			return NULL;
		}
	}
}

/* Calculate the eigenvalues of the matrix */
/*Vector **/
/*eigenValues (Matrix *M)*/
/*{*/
/*	Vector *res;*/
/*	double *wr;*/
/*	double *wi;*/
/*	double *vl;*/
/*	double *vr;*/
/*	long int n;*/
/*	lapack_int err;*/

/*	 Check if the matrix is square */
/*	if (M->rows != M->columns) {*/
/*		fprintf (stderr, "Eigenvalue error:  Matrix is not square.\n");*/
/*		return NULL;*/
/*	}*/

/*	 Since the matrix is square then rows == columns */
/*	n = M->rows;*/

/*	res = vectorInit2 (n, COLUMN_VECTOR);*/
/*	wr = malloc (n * sizeof (double));*/
/*	if (wr == NULL) {*/
/*		deleteVector (res);*/
/*		return NULL;*/
/*	}*/

/*	wi = malloc (n * sizeof (double));*/
/*	if (wi == NULL) {*/
/*		deleteVector (res);*/
/*		free (wr);*/
/*		return NULL;*/
/*	}*/

	/* If the matrix is row major */
/*	if (M->orientation == ROW_MAJOR) {*/
		/* Calculate the eigenvalues */
/*		err = LAPACKE_dgeev (LAPACK_ROW_MAJOR, 'N', 'V', n, M->mat, n, wr, wi, */

/* Calculate the QR factorization of a matrix */
Matrix *
qr (Matrix *M)
{
	Matrix *res;
	double *tau;
	lapack_int err;
	lapack_int m, n;

	m = M->rows;
	n = M->columns;

	/* Copy the values in M to res */
	res = matrixInit (M->orientation, M->rows, M->columns, M->mat);
	if (res == NULL) {
		return NULL;
	}

	/* Allocate space for tau */
	if (m < n) {
		tau = malloc (m * sizeof (double));
		if (tau == NULL) {
			deleteMatrix (res);
			return NULL;
		}
	}
	else {
		tau = malloc (n * sizeof (double));
		if (tau == NULL) {
			deleteMatrix (res);
			return NULL;
		}
	}

	/* Check if the matrix is row major */
	if (M->orientation == ROW_MAJOR) {
		err = LAPACKE_dgeqr2 (LAPACK_ROW_MAJOR, m, n, res->mat, n, tau);

		if (err == 0) {
			free (tau);
			return res;
		}
		else {
			free (tau);
			deleteMatrix (res);
			return NULL;
		}
	}

	/* Otherwise the matrix is column major */
	else {
		err = LAPACKE_dgeqr2 (LAPACK_COL_MAJOR, m, n, res->mat, m, tau);

		if (err == 0) {
			free (tau);
			return res;
		}
		else {
			free (tau);
			deleteMatrix (res);
			return NULL;
		}
	}
}

/* Calculate LQ factorization of a matrix */
Matrix *
lq (Matrix *M)
{
	Matrix *res;
	double *tau;
	lapack_int err;
	lapack_int m, n;

	m = M->rows;
	n = M->columns;

	res = M;

	if (m < n) {
		tau = malloc (m * sizeof (double));
	}
	else {
		tau = malloc (n * sizeof (double));
	}

	/* Calculate the factorization */
	/* If the matrix is row major */
	if (M->orientation == ROW_MAJOR) {
		err = LAPACKE_dgelq2 (LAPACK_ROW_MAJOR, m, n, res->mat, m, tau);
		if (err < 0) {
			fprintf (stderr, "Argument %d is illegal.\n");
			free (tau);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Matrix is singular.\n");
			free (tau);
			return NULL;
		}
	}

	/* Otherwise the matrix is column major */
	else {
		err = LAPACKE_dgelq2 (LAPACK_COL_MAJOR, m, n, res->mat, m, tau);
		if (err < 0) {
			fprintf (stderr, "Argument %d is illegal.\n");
			free (tau);
			return NULL;
		}
		else if (err > 0) {
			fprintf (stderr, "Matrix is singular.\n");
			free (tau);
			return NULL;
		}
	}

	/* Deallocate tau */
	free (tau);

	return res;
}

/* Calculate the LU factorization of a matrix */
Matrix *
lu (Matrix *M)
{
	Matrix *res;
	lapack_int m, n;
	lapack_int *ipvt;
	lapack_int err;

	res = M;

	m = M->rows;
	n = M->columns;

	/* ipvt  has dimension (min(m,n)) */
	if (m < n) {
		ipvt = malloc (m * sizeof (lapack_int));
	}
	else {
		ipvt = malloc (n * sizeof (lapack_int));
	}

	/* Calculate the factorization */
	err = LAPACKE_dgetrf2 (LAPACK_ROW_MAJOR, m, n, res->mat, m, ipvt);

	/* Check for errors.
	 * err == 0 means successful exit
	 * err < 0 means one of the arguments is illegal
	 * err > 0 means the factor U is singular */
	if (err == 0) {
		free (ipvt);
		return res;
	}
	else if (err < 0) {
		fprintf (stderr, "Argument %d in factorization is illegal. This is an internal error.\n", -1 * err);
		return NULL;
	}
	else {
		fprintf (stderr, "U factor is singular\n");
		return NULL;
	}
}

/* Singular value decomposition calculation omitted for now */


/* Calculate the norm of a vector */
double
vectorNorm (Vector *v)
{
	const blasint n = v->size;
	double res;

	/* Calculate the norm */
	res = cblas_dnrm2 (n, v->vect, 1);

	return res;
}

/* Calculate the norm of a matrix */
/* TODO:  use dlange LAPACK function */
double
matrixNorm (Matrix *M)
{
	/* norm (M) = sqrt (trace (M' * M)) */
	double res;
	lapack_int m;
	lapack_int n;

	m = M->rows;
	n = M->columns;

	/* If the matrix is row major */
	if (M->orientation == ROW_MAJOR) {
		/* Calculate the frobinius norm */
		res = LAPACKE_dlange (LAPACK_ROW_MAJOR, 'F', m, n, M->mat, n);
	}

	/* Otherwise the matrix is column major */
	else {
		res = LAPACKE_dlange (LAPACK_COL_MAJOR, 'F', m, n, M->mat, m);
	}

	return res;

	/* Multiply the matrix with its transpose using cblas_dgemm */
/*	cblas_dgemm (CblasRowMajor, CblasTrans, CblasNoTrans, m, n, k, 1.0, M->mat, k, M->mat, n, 0.0, res->mat, n);*/

	/* Calculate the trace of the product matrix */
/*	for (i = 0; i < m; i++) {*/
/*		trace += res->mat[i * m + i];*/
/*	}*/

/*	return sqrt (trace);*/
}
