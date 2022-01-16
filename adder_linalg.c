/* linalg.c
 * Function definitions for the prototypes in linalg.h
 * This is the linear algebra part of Adder */
#include <stdlib.h> /* For malloc and free */
#include <string.h> /* For memcpy */
#include <math.h> /* For fabs */
#include <cblas.h>
#include <lapacke.h>
#include "adder_math.h"
#include "adder_matrix.h"
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

	return 0;
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

/* Calculate the QR factorization of a matrix */
adder_matrix *
qr (adder_matrix *M)
{
	adder_matrix *res;
	double *tau;
	lapack_int err;
	lapack_int m, n;

	m = M->rows;
	n = M->columns;

	/* Copy the values in M to res */
	res = matrixInit (M->rows, M->columns, M->mat);
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
	
	return res;
}

/* Calculate LQ factorization of a matrix */
adder_matrix *
lq (adder_matrix *M)
{
	adder_matrix *res;
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

	/* Deallocate tau */
	free (tau);

	return res;
}

/* Calculate the LU factorization of a matrix */
adder_matrix *
lu (adder_matrix *M)
{
	adder_matrix *res;
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
	
	return res;
}

/* Singular value decomposition calculation omitted for now */


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
