/* linalg.c
 * Function definitions for the prototypes in linalg.h
 * This is the linear algebra part of Adder */
#include <stdlib.h> /* For malloc and free */
#include <string.h> /* For memcpy */
#include <math.h> /* For fabs */
#include <cblas.h>
#include <lapacke.h>
#include "adder_math.h"
#include "adder_linalg.h"

#define max(x, y) x >= y ? x : y

/* Calculate the inverse of the matrix */
adder_matrix *
inverse (adder_matrix *M)
{
	adder_matrix *res;
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
	res = matrixInit (M->rows, M->columns, M->mat);

	/* Calculate the LU factorization of the matrix */
	err = LAPACKE_dgetrf (LAPACK_ROW_MAJOR, m, n, res->mat, n, ipvt);
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

/* Calculate the Moore-Penrose pseudoinverse of a matrix
 * using its singular value decomposition */
adder_matrix *
pseudoinverse (adder_matrix *m)
{
	adder_matrix *A;
	adder_matrix *u;
	adder_matrix *vt;
	adder_vector *s;
	adder_matrix *sMatrix;
	adder_matrix *vts;
	adder_matrix *res;
	double *vtNew;
	int aRows, aColumns, aDimMax;
	int i, j;
	int mTrans; /* Flag to check if M was transposed */
	int err;

	/* Check if the input matrix has fewer rows than columns.
	 * If it does then transpose it */
	if (m->rows < m->columns) {
		mTrans = 1;

		m = matrixTranspose (m);
		if (m == 0x00) {
			return 0x00;
		}


		aRows = m->rows;
		aColumns = m->columns;
		aDimMax = max (aRows, aColumns);

		/* Create a matrix called u, which the orthogonal matrix to m */
		u = matrixInit2 (aRows, aRows);
		if (u == 0x00) {
			deleteMatrix (A);
			return 0x00;
		}

		/* Create the s vector, which holds the singular values of m */
		s = vectorInit2 (COLUMN_VECTOR, aColumns);
		if (s == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			return 0x00;
		}

		/* Create sMatrix, which is s represented as a diagonal matrix */
		sMatrix = matrixInit2 (aRows, aColumns);
		if (sMatrix == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			return 0x00;
		}

		/* Create the vt matrix */
		vt = matrixInit2 (aColumns, aColumns);
		if (vt == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			return 0x00;
		}

		/* Create the vts matrix, which is the result of VT * s */
		vts = matrixInit2 (aColumns, aRows);
		if (vts == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			deleteMatrix (sMatrix);
			deleteMatrix (vt);
			return 0x00;
		}

		/* Create the solution matrix, which is the result of vts * U */
		res = matrixInit2 (aColumns, aRows);
		if (res == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			deleteMatrix (sMatrix);
			deleteMatrix (vt);
			deleteMatrix (vts);
			return 0x00;
		}

	}

	else {

		aRows = m->rows;
		aColumns = m->columns;
		aDimMax = max (aRows, aColumns);

		/* Create a matrix called u, which the orthogonal matrix to m */
		u = matrixInit2 (aRows, aRows);
		if (u == 0x00) {
			deleteMatrix (A);
			return 0x00;
		}

		/* Create the s vector, which holds the singular values of m */
		s = vectorInit2 (COLUMN_VECTOR, aColumns);
		if (s == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			return 0x00;
		}
	/*	if (aRows <= aColumns) {*/
	/*		s = vectorInit2 (COLUMN_VECTOR, aRows);*/
	/*	}*/
	/*	else {*/
	/*		s = vectorInit2 (COLUMN_VECTOR, aColumns);*/
	/*	}*/

	/*	if (s == 0x00) {*/
	/*		deleteMatrix (A);*/
	/*		deleteMatrix (u);*/
	/*		return 0x00;*/
	/*	}*/

		/* Create sMatrix, which is s represented as a diagonal matrix */
		sMatrix = matrixInit2 (aRows, aColumns);
		if (sMatrix == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			return 0x00;
		}

		/* Create the vt matrix */
		vt = matrixInit2 (aColumns, aColumns);
		if (vt == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			return 0x00;
		}

		/* Create the vts matrix, which is the result of VT * s */
		vts = matrixInit2 (aColumns, aRows);
		if (vts == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			deleteMatrix (sMatrix);
			deleteMatrix (vt);
			return 0x00;
		}

		/* Create the solution matrix, which is the result of vts * U */
		res = matrixInit2 (aColumns, aRows);
		if (res == 0x00) {
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			deleteMatrix (sMatrix);
			deleteMatrix (vt);
			deleteMatrix (vts);
			return 0x00;
		}
	}

	/* Create a copy of m called A so m doesn't get overwritten */
	A = matrixInit (aRows, aColumns, m->mat);
	if (A == 0x00) {
		return 0x00;
	}

	/* Calculate the singular value decomposition */
	err = LAPACKE_dgesdd (LAPACK_ROW_MAJOR, 'A', A->rows, A->columns, A->mat, A->columns, s->vect, u->mat, u->columns, vt->mat, vt->columns);

	if (err < 0) {
		if (err == -4) {
			fprintf (stderr, "ERROR:  A matrix has a NAN entry.\n");
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			deleteMatrix (sMatrix);
			deleteMatrix (vt);
			deleteMatrix (vts);
			deleteMatrix (res);
			return 0x00;
		}

		else {
			fprintf (stderr, "ERROR:  Illegal argument number %d in SVD subroutine in function pseudoinverse.\n", -1 * err);
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			deleteMatrix (sMatrix);
			deleteMatrix (vt);
			deleteMatrix (vts);
			deleteMatrix (res);
			return 0x00;
		}
	}

	else if (err > 0) {
		fprintf (stderr, "ERROR:  DBDSDC subroutine did not converge in function pseudoInverse\n");
		deleteMatrix (A);
		deleteMatrix (u);
		deleteVector (s);
		deleteMatrix (sMatrix);
		deleteMatrix (vt);
		deleteMatrix (vts);
		deleteMatrix (res);
		return 0x00;
	}

	vtNew = vt->mat;

	/* Convert s to a diagonal matrix whose elements are the reciprocals of those in s */
	for (i = 0; i < s->size; i++) {
		for (j = 0; j < s->size; j++) {
			if (i == j) {
				if (fabs (s->vect[i]) < __FLT_EPSILON__) {
					sMatrix->mat[i * s->size + j] = 0;
				}

				else {
					sMatrix->mat[i * s->size + j] = 1 / s->vect[i];
				}
			}

			else {
				sMatrix->mat[i * s->size + j] = 0;
			}
		}
	}

	vt->mat = vtNew;
	vtNew = 0x00;

	/* Multiply VT' * S' = VTS, followed by VTS * U = res */
	cblas_dgemm (CblasRowMajor, CblasTrans, CblasTrans, vt->rows, sMatrix->columns, vt->columns, 1.0, vt->mat, vt->columns, sMatrix->mat, sMatrix->columns, 0.0, vts->mat, vts->columns);

	cblas_dgemm (CblasRowMajor, CblasNoTrans, CblasTrans, vts->rows, u->columns, vts->columns, 1.0, vts->mat, vts->columns, u->mat, u->columns, 0.0, res->mat, res->columns);

	/* The last step is to transpose the solution matrix if
	 * the input matrix was transposed */
	if (mTrans == 1) {
		res = matrixTranspose (res);
	}

	/* Delete the vectors and matrices used in intermediate calculations */
	deleteMatrix (A);
	deleteMatrix (u);
	deleteVector (s);
	deleteMatrix (sMatrix);
	deleteMatrix (vt);
	deleteMatrix (vts);

	return res;
}

/* Calculate the inverse of a complex-valued matrix */
adder_complex_matrix *
complexInverse (adder_complex_matrix *M)
{
	double complex *res;
	adder_complex_matrix *finalRes;
	int ipvt[M->rows];
	int m, n;
	int err;
	int i, j;

	/* If the matrix isn't square then we can't calculate the inverse */
	if (M->rows != M->columns) {
		fprintf (stderr, "Dimension error:  matrix not square.\n");
		return NULL;
	}

	/* Make res equal to M */
	res = malloc (M->rows * M->columns * sizeof (double complex));
		if (res == 0x00) {
		return NULL;
	}

	/* Extract the real and imaginary values from M */
	for (i = 0; i < M->rows; i++) {
		for (j = 0; j < M->columns; j++) {
			res[i * M->columns + j] = M->mat[i * M->columns + j].real + M->mat[i * M->columns + j].imag * I;
		}
	}

	m = M->rows;
	n = M->columns;

	/* Calculate the LU factorization */
	err = LAPACKE_zgetrf (LAPACK_ROW_MAJOR, m, n, res, n, ipvt);
	if (err < 0) {
		fprintf (stderr, "The value of argument %d is illegal\n", -1 * err);
		free (res);
		return NULL;
	}

	else if (err > 0) {
		fprintf (stderr, "Factorization is singular.\n");
		free (res);
		return NULL;
	}

	/* Invert the matrix */
	err = LAPACKE_zgetri (LAPACK_ROW_MAJOR, n, res, n, ipvt);

	if (err < 0) {
		fprintf (stderr, "The value of argument %d is illegal.\n", -1 * err);
		free (res);
		return NULL;
	}

	else if (err > 0) {
		fprintf (stderr, "Matrix is singular.\n");
		free (res);
		return NULL;
	}

	/* The last step is to convert res to adder_complex_rect for the final result */
	finalRes = complexMatrixInit2 (M->rows, M->columns);
	if (finalRes == 0x00) {
		free (res);
		return NULL;
	}

	/* Copy the values from res into finalRes */
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			finalRes->mat[i * n + j].real = creal (res[i * n + j]);
			finalRes->mat[i * n + j].imag = cimag (res[i * n + j]);
		}
	}

	free (res);

	return finalRes;
}


/********************
 * Equation solving *
 ********************/

/* Solve a linear system of equations */
adder_vector *
linearSolve (adder_matrix *M, adder_vector *b)
{
	adder_vector *res;
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

/* Solve an overdetermined linear system of equations */
adder_vector *
odLinearSolve (adder_matrix *A, adder_vector *b)
{
	int err;
	adder_vector *res;

	res = vectorInit2 (COLUMN_VECTOR, b->size);

	/* Create a result matrix to prevent overwriting b */
//	res = b;
	memcpy (res->vect, b->vect, sizeof (double) * b->size);

	err = LAPACKE_dgels (LAPACK_ROW_MAJOR, 'N', A->rows, A->columns, 1, A->mat, A->columns, res->vect, 1);

	/* If no errors occured then return the solution vector */
	if (err == 0 ) {
		res->vect = realloc (res->vect, sizeof (double) * A->columns);
		res->size = A->columns;
		return res;
	}

	else if (err < 0) {
		fprintf (stderr, "Argument %d is invalid.\n", -1 * err);
		return NULL;
	}

	else {
		fprintf (stderr, "Solution could not be computed\n");
		return NULL;
	}
}

/* Solve a linear least squares problem.
 * The coefficients for the solution are stored
 * in descending order of degree. For example, if
 * a quadratic solution is found, then the solution
 * vector R = {r1, r2, r3} form the polynomial
 * r1 * x^2 + r2 * x + r3 */
adder_vector *
linearLeastSquares (adder_matrix *M, adder_vector *b)
{
	adder_vector *res;
	int *jpvt;
	int err;
	int rank;

	/* Check that M has the same number of columns as b has rows */
	if (M->rows != b->size) {
		fprintf (stderr, "ERROR:  Invalid dimensions in function linearLeastSquares.\n");
		return 0x00;
	}

	res = vectorInit (COLUMN_VECTOR, M->rows, b->vect);
	if (res == 0x00) {
		fprintf (stderr, "ERROR:  Could not create result vector in function linearLeastSquares.\n");
		return 0x00;
	}

	jpvt = malloc (M->columns * sizeof (int));
	if (jpvt == 0x00) {
		fprintf (stderr, "ERROR:  could not create jpvt vector in function linearLeastSquares.\n");
		deleteVector (res);
		return 0x00;
	}

	rank = M->columns;

	err = LAPACKE_dgelsy (LAPACK_ROW_MAJOR, M->rows, M->columns, 1, M->mat, M->columns, res->vect, 1, jpvt, 1e-8, &rank);
	if (err == 0) {
		free (jpvt);

		/* Resize the solution vector to contain only the solution coefficients */
		res->vect = realloc (res->vect, M->columns * sizeof (double));
		res->size = M->columns;
		return res;
		}
	else {
		fprintf (stderr, "ERROR:  illegal argument number %d in LAPACKE_dgelsy subroutine in function linearLeastSquares.\n", -1 * err);
		free (jpvt);
		deleteVector (res);
		return 0x00;
	}
<<<<<<< HEAD
}

/* Solve a complex-valued system of linear equations */
adder_complex_vector *
complexLinearSolve (adder_complex_matrix *M, adder_complex_vector *b)
{
	adder_complex_vector *res; /* Result vector */
	double complex *Z; /* Coefficient matrix */
	double complex *y;
	int ipvt[M->rows];
	int m;
	int err;
	int i, j;

	/* Check that the right-side vector is a column vector */
	if (b->orientation == ROW_VECTOR) {
		fprintf (stderr, "ERROR:  b vector must be a column vector.\n");
		return NULL;
	}

	/* Check that M is a square matrix */
	if (M->rows != M->columns) {
		fprintf (stderr, "ERROR:  Matrix must be square but has dimensions %dx%d.\n", M->rows, M->columns);
		return NULL;
	}

	/* Check that M has as many columns as b has rows */
	if (M->columns != b->size) {
		fprintf (stderr, "ERROR:  Matrix and b vector dimension match.\n");
		return NULL;
	}

	/* Since we know the matrix and vector dimensions match, copy M into Z and b into y */
	m = M->rows;

	Z = malloc (m * m * sizeof (double complex));
	if (Z == 0x00) {
		return NULL;
	}

	y = malloc (m * sizeof (double complex));
	if (y == 0x00) {
		free (Z);
		return NULL;
	}

	/* Copy the values from M and b to Z and y */
	for (i = 0; i < m; i++) {
		for (j = 0; j < m; j++) {
			Z[i * m + j] = M->mat[i * m + j].real + M->mat[i * m + j].imag * I;
		}

		y[i] = b->vect[i].real + b->vect[i].imag * I;
	}

	/* Solve the system */
	err = LAPACKE_zgesv (LAPACK_ROW_MAJOR, m, 1, Z, m, ipvt, y, 1);

	/* Check for errors */
	if (err < 0) {
		fprintf (stderr, "Failed to solve system of equations.\n");
		free (Z);
		free (y);
		return NULL;
	}

	else if (err > 0) {
		fprintf (stderr, "Singular matrix.\n");
		free (Z);
		free (y);
	}

	/* Now copy the solutions into the vector res and return */
	res = complexVectorInit2 (COLUMN_VECTOR, m);
	if (res == 0x00) {
		free (Z);
		free (y);
		return NULL;
	}

	for (i = 0; i < m; i++) {
		res->vect[i].real = creal (y[i]);
		res->vect[i].imag = cimag (y[i]);
	}

	return res;
=======
>>>>>>> 3eac36cb261b33b10bface505a3bb24359817128
}

/* Calculate the eigenvalues of the matrix */
adder_vector *
eigenValues (adder_matrix *M)
{
	adder_vector *res;
	double *wr;
	double *wi;
	double *vl;
	double *vr;
	int i;
	lapack_int n;
	lapack_int err;

	/* Check if the matrix is square */
	if (M->rows != M->columns) {
		fprintf (stderr, "Eigenvalue error:  Matrix is not square.\n");
		return NULL;
	}

	/* Since the matrix is square then rows == columns */
	n = M->rows;

	res = vectorInit2 (COLUMN_VECTOR, n);
	wr = malloc (n * sizeof (double));
	if (wr == NULL) {
		deleteVector (res);
		return NULL;
	}

	wi = malloc (n * sizeof (double));
	if (wi == NULL) {
		deleteVector (res);
		free (wr);
		return NULL;
	}

/*	vl = malloc (n * sizeof (double));*/
/*	if (vl == NULL) {*/
/*		deleteVector (res);*/
/*		free (wr);*/
/*		free (wi);*/
/*		return NULL;*/
/*	}*/

/*	vr = malloc (n * sizeof (double));*/
/*	if (vr == NULL) {*/
/*		deleteVector (res);*/
/*		free (wr);*/
/*		free (wi);*/
/*		free (vl);*/
/*		return NULL;*/
/*	}*/

	/* Calculate the eigenvalues */
	err = LAPACKE_dgeev (LAPACK_ROW_MAJOR, 'N', 'N', n, M->mat, n, res->vect, wi, vl, n, vr, n);

	/* Check for errors */
	if (err == 0) {
		free (wr);
		free (wi);
		return res;
	}
	else if (err < 0) {
		fprintf (stderr, "Invalid arguments.\n");
		deleteVector (res);
		free (wr);
		free (wi);
		return NULL;
	}
	else {
		fprintf (stderr, "Failed to calculate the eigenvalues.\n");
		deleteVector (res);
		free (wr);
		free (wi);
		return NULL;
	}
}

/* Calculate the eigenvalues of a complex-valued matrix */
adder_complex_vector *
complexEigenValues (adder_complex_matrix *M)
{
	adder_complex_vector *res;
	double complex *Z;
	double complex *wi;
	double complex *vl;
	double complex *vr;
	int i, j;
	int n;
	int err;
	
	/* Check that the matrix is square */
	if (M->rows != M->columns) {
		fprintf (stderr, "Eigenvalue error:  Matrix is not square.\n");
		return NULL;
	}
	
	/* Since the matrix is square, n = rows == columns */
	n = M->rows;
	
	res = complexVectorInit2 (COLUMN_VECTOR, n);
	if (res == 0x00) {
		fprintf (stderr, "Failed to create result vector.\n");
		return NULL;
	}
    
	wi = malloc (n * sizeof (double complex));
	if (wi == 0x00) {
		deleteComplexVector (res);
		return NULL;
	}

	Z = malloc (n * n * sizeof (double complex));
	if (Z == 0x00) {
		free (wi);
		deleteComplexVector (res);
		return NULL;
	}

	/* Copy the values from M into Z */
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
		    Z[i * n + j] = M->mat[i * n + j].real + M->mat[i * n + j].imag * I;
		}
	}

	/* Calculate the eigenvalues */
	err = LAPACKE_zgeev (LAPACK_ROW_MAJOR, 'N', 'N', n, Z, n, wi, vl, n, vr, n);

	if (err < 0) {
		fprintf (stderr, "Argument %d is invalid.\n", -1 * err);
		free (wi);
		free (Z);
		deleteComplexVector (res);
		return NULL;
	}

	else if (err > 0) {
		fprintf (stderr, "Failed to calculate eigenvalues.\n");
		free (wi);
		free (Z);
		deleteComplexVector (res);
		return NULL;
	}

	/* The last step is to copy the values from res into finalRes */
	for (i = 0; i < n; i++) {
		res->vect[i].real = creal (wi[i]);
		res->vect[i].imag = cimag (wi[i]);
	}

	free (wi);
	free (Z);
	return res;
}

/* Calculate the singular values of a matrix */
adder_vector *
svd (adder_matrix *m)
{
	adder_matrix *A;
	adder_matrix *u;
	adder_vector *s;
	adder_matrix *vt;
	int i;
	int err;

	/* Create a copy of m called A so m doesn't get overwritten */
	A = matrixInit (m->rows, m->columns, m->mat);
	if (A == 0x00) {
		return 0x00;
	}

	/* Create a matrix called u, which the orthogonal matrix to m */
	u = matrixInit2 (m->rows, m->rows);
	if (u == 0x00) {
		deleteMatrix (A);
		return 0x00;
	}

	/* Create the s vector, which holds the singular values of m */
	if (m->rows <= m->columns) {
		s = vectorInit2 (COLUMN_VECTOR, m->rows);
	}
	else {
		s = vectorInit2 (COLUMN_VECTOR, m->columns);
	}

	if (s == 0x00) {
		deleteMatrix (A);
		deleteMatrix (u);
		return 0x00;
	}

	/* Create the vt matrix */
	vt = matrixInit2 (m->columns, m->columns);
	if (vt == 0x00) {
		deleteMatrix (A);
		deleteMatrix (u);
		deleteVector (s);
		return 0x00;
	}

	err = LAPACKE_dgesdd (LAPACK_ROW_MAJOR, 'A', A->rows, A->columns, A->mat, A->columns, s->vect, u->mat, u->columns, vt->mat, vt->columns);

	if (err < 0) {
		if (err == -4) {
			fprintf (stderr, "ERROR:  A matrix has a NAN entry.\n");
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			return 0x00;
		}

		else {
			fprintf (stderr, "ERROR:  Illegal argument number %d in SVD subroutine in function pseudoinverse.\n", -1 * err);
			deleteMatrix (A);
			deleteMatrix (u);
			deleteVector (s);
			return 0x00;
		}
	}

	else if (err > 0) {
		fprintf (stderr, "ERROR:  DBDSDC subroutine did not converge in function pseudoInverse\n");
		deleteMatrix (A);
		deleteMatrix (u);
		deleteVector (s);
		return 0x00;
	}

	return s;
}

/* Calculate the singular values of a complex-valued matrix */
adder_complex_vector *
complexSVD (adder_complex_matrix *m)
{
	adder_complex_vector *res;
	double complex *A;
	double *s;
	double complex *u;
	double complex *vt;
	int M, N;
	int resLen;
	int i, j;
	int err;
	
	M = m->rows;
	N = m->columns;
	
	/* Create a copy of m called A since we need to convert between types
	 * double complex and adder_complex_rect */
	A = malloc (M * N * sizeof (double complex));
	if (A == 0x00) {
		return NULL;
 	} 
	/* Create a matrix called u, which is orthogonal to m */
	u = malloc (M * M * sizeof (double complex));
	if (u == 0x00) {
		free (A);
		return NULL;
	}
	 
	/* Create a vector s, which holds the singular values of m */
	if (M <= N) {
		resLen = M;
		s = malloc (M * sizeof (double));
	}
	else {
		resLen = N;
		s = malloc (N * sizeof (double));
	}
	
	if (s == 0x00) {
		free (A);
		free (u);
		return NULL;
	}
	
	/* Create a matrix vt */
	vt = malloc (N * N * sizeof (double complex));
	if (vt == 0x00) {
		free (A);
		free (u);
		free (s);
		return NULL;
	}
	
	/* Initialize A by converting type adder_complex_rect to type double complex */
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			A[i * M + j] = m->mat[i * M + j].real + m->mat[i * M + j].imag * I;
		}
	}
	
	/* Calculate the singular value decomposition */
	err = LAPACKE_zgesdd (LAPACK_ROW_MAJOR, 'A', M, N, A, N, s, u, M, vt, N);
	if (err < 0) {
		if (err == -4) {
			fprintf (stderr, "ERROR:  input matrix has a NAN entry.\n");
		}
		
		else {
			fprintf (stderr, "ERROR:  argument %d in function LAPACKE_zgesdd has illegal value.\n", -1 * err);
		}
		
		free (A);
		free (u);
		free (s);
		free (vt);
		return NULL;
	}
	
	else if (err > 0) {
		fprintf (stderr, "Failed to calculate singular value decomposition.\n");
		free (A);
		free (u);
		free (s);
		free (vt);
		return NULL;
	}
	
	/* Otherwise the calculation succeeded.
	 * Now we can convert the values in s from type double complex back to
	 * type adder_complex_rect and return the final result */
	res = complexVectorInit2 (COLUMN_VECTOR, resLen);
	if (res == 0x00) {
		free (A);
		free (u);
		free (s);
		free (vt);
		return NULL;
	}
	
	for (i = 0; i < resLen; i++) {
		res->vect[i].real = creal (s[i]);
		res->vect[i].imag = cimag (s[i]);
	}
	
	free (A);
	free (s);
	free (u);
	free (vt);
	
	return res;
}

/* Calculate the norm of a vector */
double
vectorNorm (adder_vector *v)
{
	const blasint n = v->size;
	double res;

	/* Calculate the norm */
	res = cblas_dnrm2 (n, v->vect, 1);

	return res;
}

/* Calculate the norm of a matrix */
double
matrixNorm (adder_matrix *M)
{
	/* norm (M) = sqrt (trace (M' * M)) */
	double res;
	lapack_int m;
	lapack_int n;

	m = M->rows;
	n = M->columns;
    
	/* Calculate the frobinius norm */
	res = LAPACKE_dlange (LAPACK_ROW_MAJOR, 'F', m, n, M->mat, n);

	return res;

	/* Multiply the matrix with its transpose using cblas_dgemm */
/*	cblas_dgemm (CblasRowMajor, CblasTrans, CblasNoTrans, m, n, k, 1.0, M->mat, k, M->mat, n, 0.0, res->mat, n);*/

	/* Calculate the trace of the product matrix */
/*	for (i = 0; i < m; i++) {*/
/*		trace += res->mat[i * m + i];*/
/*	}*/

/*	return sqrt (trace);*/
}
