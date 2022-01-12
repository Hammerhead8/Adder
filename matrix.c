/* matrix.c
 * Function definitions for matrix.h */
#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include "matrix.h"

/* TODO:  Result matrix should match orientation of input matrix/matrices */

/* Vector IO functions */
/* Create a new vector and set its values */
adder_vector *
vectorInit (int orient, int numElements, double *values)
{
	adder_vector *v;
	int i;

	/* Allocate the vector in memory */
	v = malloc (sizeof (adder_vector));
	if (v == NULL) {
		return NULL;
	}

	v->vect = malloc (numElements * sizeof (double));
	if (v->vect == NULL) {
		free (v);
		return NULL;
	}

	for (i = 0; i < numElements; i++) {
		v->vect[i] = values[i];
	}

	v->size = numElements;

	/* Set the orientation of the vector and check for invalid entry */
	if (orient == ROW_VECTOR) {
		v->orientation = orient;
	}
	else if (orient == COLUMN_VECTOR) {
		v->orientation = orient;
	}
	else {
		fprintf (stderr, "Invalid orientation.\n");
		return NULL;
	}

	return v;
}

/* Create a new vector and set its values to zero */
adder_vector *
vectorInit2 (int orient, int numElements)
{
	adder_vector *v;
	int i;

	/* Allocate the vector in memory */
	v = malloc (sizeof (adder_vector));
	if (v == NULL) {
		return NULL;
	}

	v->vect = malloc (numElements * sizeof (double));
	if (v->vect == NULL) {
		return NULL;
	}

	for (i = 0; i < numElements; i++) {
		v->vect[i] = 0;
	}

	v->size = numElements;

	return v;
}

/* Set the values of a vector
 * No error checking is done so the size of VALUES must match the size of v */
void
setVector (adder_vector *v, double *values)
{
	int i;

	for (i = 0; i < v->size; i++) {
		v->vect[i] = values[i];
	}
}

/* Delete a vector */
void
deleteVector (adder_vector *v)
{
	free (v->vect);
	free (v);
}

/* Print a vector */
void
printVector (adder_vector *v)
{
	int i;

	/* Check if the vector is a row or column vector and print it accordingly */
	if (v->orientation == ROW_VECTOR) {
		for (i = 0; i < v->size; i++) {
			printf ("%lf ", v->vect[i]);
		}

		printf ("\n\n");
	}
	else {
		for (i = 0; i < v->size; i++) {
			if (v->vect[i] < 0) {
				printf ("%lf\n", v->vect[i]);
			}
			else {
				printf (" %lf\n", v->vect[i]);
			}
		}

		printf ("\n");
	}
}

/* Complex vector IO functions */
adder_complex_vector *
complexVectorInit (int orient, int numElements, double *realValues, double *imagValues)
{
	adder_complex_vector *z;
	int i;
	
    /* Allocate the data type */
	z = malloc (sizeof (adder_complex_vector));
	if (z == 0x00) {
		fprintf (stderr, "Failed to create complex vector.\n");
		return NULL;
	}
	
	/* Allocate the array that holds the values */
	z->vect = malloc (numElements * sizeof (adder_complex_rect));
	if (z->vect == 0x00) {
		fprintf (stderr, "Failed to create complex vector.\n");
		free (z);
		return NULL;
	}
	
	/* Fill the vector with the specified values */
	for (i = 0; i < numElements; i++) {
		z->vect[i].real = realValues[i];
		z->vect[i].imag = imagValues[i];
	}
	
	/* Set the orientation of the vector or return an error if the orientation is invalid */
	if (orient == ROW_VECTOR) {
		z->orientation = ROW_VECTOR;
	}
	else if (orient == COLUMN_VECTOR) {
		z->orientation = COLUMN_VECTOR;
	}
	else {
		fprintf (stderr, "Invalid orientation.\n");
		free (z->vect);
		free (z);
		return NULL;
	}
	
	/* Set the size of the vector */
	z->size = numElements;
	
	return z;
}

/* Create a complex vector without setting any values */
adder_complex_vector *
complexVectorInit2 (int orient, int numElements)
{
	adder_complex_vector *z;
	
    /* Allocate the data type */
	z = malloc (sizeof (adder_complex_vector));
	if (z == 0x00) {
		fprintf (stderr, "Failed to create complex vector.\n");
		return NULL;
	}
	
    /* Allocate the array that holds the values */
	z->vect = malloc (numElements * sizeof (adder_complex_rect));
	if (z->vect == 0x00) {
		fprintf (stderr, "Failed to create complex vector.\n");
		free (z);
		return NULL;
	}
	
	/* Set the orientation of the vector or return an error if the orientation is invalid */
	if (orient == ROW_VECTOR) {
		z->orientation = ROW_VECTOR;
	}
	else if (orient == COLUMN_VECTOR) {
		z->orientation = COLUMN_VECTOR;
	}
	else {
		fprintf (stderr, "Invalid orientation.\n");
		free (z->vect);
		free (z);
	}
	
	/* Set the size of the vector */
	z->size = numElements;
	
	return z;
}

/* Delete a complex-valued vector */
void
deleteComplexVector (adder_complex_vector *z)
{
	free (z->vect);
	free (z);
}

/* Print a complex-valued vector */
void
printComplexVector (adder_complex_vector *z)
{
	int i;
	
    /* If the vector is a row vector */
	if (z->orientation == ROW_VECTOR) {
		for (i = 0; i < z->size; i++) {
			printf ("%.8lf%+.8lfj ", z->vect[i].real, z->vect[i].imag);
		}
		
		printf ("\n\n");
	}
	
	/* Otherwise the vector is a column vector */
	else {
		for (i = 0; i < z->size; i++) {
			printf ("%.8lf%+.8lfj\n", z->vect[i].real, z->vect[i].imag);
		}
		
		printf ("\n");
	}
}
		

/* Vector setting functions */
/* Set an existing vector to be a zero vector */
void
vectorZeros (adder_vector *v)
{
	int i;

	for (i = 0; i < v->size; i++) {
		v->vect[i] = 0;
	}
}

/* Set an existing vector to be all ones */
void
vectorOnes (adder_vector *v)
{
	int i;

	for (i = 0; i < v->size; i++) {
		v->vect[i] = 1;
	}
}

/* Set an existing vector to random values */
int
randVector (adder_vector *v)
{
	long int seed;
	size_t err;
	int i;
	FILE *fp;

	/* Open /dev/urandom */
	fp = fopen ("/dev/urandom", "r");
	if (fp == NULL) {
		fprintf (stderr, "Failed to open random number generator.\n");
		return INVALID_FILE;
	}

	/* Read an int from urandom */
	err = fread (&seed, sizeof (long int), 1, fp);
	if (err == 0) {
		fprintf (stderr, "Failed to read from the random number generator.\n");
		return FILE_READ_ERROR;
	}

	/* Close /dev/urandom */
	fclose (fp);

	/* Seed the random number generator */
	srand (seed);

	/* Generate the random numbers */
	for (i = 0; i < v->size; i++) {
		v->vect[i] = rand () / (double)RAND_MAX;
	}

	return 0;
}

/**************************
 * Other vector functions *
 **************************/

/* Transpose a real-valued vector */
void
vectorTranspose (adder_vector *v)
{
	v->orientation *= -1;
}

/* Transpose a complex-valued vector */
void
complexVectorTranspose (adder_complex_vector *z)
{
    z->orientation *= -1;
}

/********************
 * Matrix functions *
*********************/

/* Create a matrix and set its values */
adder_matrix *
matrixInit (int orient, int numRows, int numColumns, double *values)
{
	adder_matrix *m;
	int i, j;

	/* Allocate memory for the matrix */
	m = malloc (sizeof (adder_matrix));
	if (m == NULL) {
		return NULL;
	}

	/* Allocate space for the values in the matrix */
	m->mat = malloc (numRows * numColumns * sizeof (double));
	if (m->mat == NULL) {
		free (m);
		return NULL;
	}

	m->rows = numRows;
	m->columns = numColumns;

	/* Check if the matrix is to be row or column major */
	if (orient == ROW_MAJOR) {
		m->orientation = ROW_MAJOR;

		/* Enter the values */
		for (i = 0; i < numRows; i++) {
			for (j = 0; j < numColumns; j++) {
				m->mat[i * numColumns + j] = values[i * numColumns + j];
			}
		}
	}
	else if (orient == COLUMN_MAJOR) {
		m->orientation = COLUMN_MAJOR;

		/* Enter the values */
		for (i = 0; i < numRows; i++) {
			for (j = 0; j < numColumns; j++) {
				m->mat[i * numColumns + j] = values[j * numRows + i];
			}
		}
	}
	else {
		fprintf (stderr, "Invalid orientation. Assuming row major.\n");
		m->orientation = ROW_MAJOR;

		/* Enter the values */
		for (i = 0; i < numRows; i++) {
			for (j = 0; j < numColumns; j++) {
				m->mat[i * numColumns + j] = values[i * numColumns + j];
			}
		}
	}

	return m;
}

/* Create a matrix without settings its values */
adder_matrix *
matrixInit2 (int orient, int numRows, int numColumns)
{
	adder_matrix *m;
	int i, j;

	m = malloc (sizeof (adder_matrix));
	if (m == NULL) {
		return NULL;
	}

	m->mat = malloc (numRows * numColumns * sizeof (double));
	if (m->mat == NULL) {
		fprintf (stderr, "Failed to create matrix.\n");
		free (m);
		return NULL;
	}

	m->rows = numRows;
	m->columns = numColumns;

	/* Set the matrix to be either row or column major */
	if (orient == ROW_MAJOR) {
		m->orientation = ROW_MAJOR;
	}
	else if (orient == COLUMN_MAJOR) {
		m->orientation = COLUMN_MAJOR;
	}
	else {
		fprintf (stderr, "Invalid orientation. Assuming row major.\n");
		m->orientation = ROW_MAJOR;
	}

	return m;
}

/* Delete the matrix */
void
deleteMatrix (adder_matrix *m)
{
	free (m->mat);
	free (m);
}

/* Print the matrix */
void
printMatrix (adder_matrix *m)
{
	int i, j;

	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			printf ("%lf ", m->mat[i * m->columns + j]);
		}

		printf ("\n");
	}

	printf ("\n");
}

/* Multiply a matrix and with a vector */
adder_vector *
mvMultiply (adder_matrix *M, adder_vector *v)
{
	adder_vector *res;

	/* Check that the dimensions of M and v are valid for multiplication */
	if (v->orientation == COLUMN_VECTOR) {
		if (M->columns == v->size) {
			res = vectorInit2 (COLUMN_VECTOR, M->rows);
		}

		else {
			fprintf (stderr, "ERROR:  Dimension mismatch\n");
			return NULL;
		}
	}

	else {
		fprintf (stderr, "Vector needs to be a column vector for multiplication\n");
		return NULL;
	}

	/* If the dimensions are valid then we can perform the multiplication */

	/* Check if the matrix is row major or column major */
	if (M->orientation == ROW_MAJOR) {
		cblas_dgemv (CblasRowMajor, CblasNoTrans, M->rows, M->columns, 1.0, M->mat, M->columns, v->vect, 1, 0, res->vect, 1);
		return res;
	}

	/* Otherwise the matrix must be column major */
	else {
		cblas_dgemv (CblasColMajor, CblasNoTrans, M->rows, M->columns, 1.0, M->mat, M->rows, v->vect, 1, 0, res->vect, 1);
		return res;
	}
}

/* Multiply two matrices */
adder_matrix *
mmMultiply (adder_matrix *A, adder_matrix *B)
{
	int err;
	adder_matrix *res;

	/* Check that the dimensions of A and B are valid for multiplication */
	if (A->columns != B->rows) {
		fprintf (stderr, "ERROR:  Dimension of A is %dx%d and B is %dx%d\n", A->rows, A->columns, B->rows, B->columns);
		return NULL;
	}

	/* Also check that the orientations of the matrices match */
	else if (A->orientation != B->orientation) {
		fprintf (stderr, "ERROR:  Orientations of A and B don't match.\n");
		return NULL;
	}

	/* We can now create the result matrix and multiply */

	/* Check if the matrix is row major */
	if (A->orientation == ROW_MAJOR) {
		/* Create the result matrix */
		res = matrixInit2 (ROW_MAJOR, A->rows, B->columns);
		if (res == NULL) {
			fprintf (stderr, "Failed to create result matrix.\n");
			return NULL;
		}

		/* Now we can perform the multiplication */
		cblas_dgemm (CblasRowMajor, CblasNoTrans, CblasNoTrans, A->rows, B->columns, A->columns, 1.0, A->mat, A->columns, B->mat, B->columns, 0.0, res->mat, res->columns);
		return res;
	}

	/* Otherwise the matrix must be column major */
	else {
		/* Create the result matrix */
		res = matrixInit2 (COLUMN_MAJOR, A->rows, B->columns);
		if (res == NULL) {
			fprintf (stderr, "Failed to create result matrix.\n");
			return NULL;
		}

		/* Perform the multiplication */
		cblas_dgemm (CblasColMajor, CblasNoTrans, CblasNoTrans, A->rows, B->columns, A->rows, 1.0, A->mat, A->columns, B->mat, B->rows, 0.0, res->mat, res->columns);
		return res;
	}
}

/* Set the matrix to a zero matrix */
void
matrixZeros (adder_matrix *m)
{
	int i, j;

	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			m->mat[i * m->columns + j] = 0;
		}
	}
}

/* Set the matrix to all ones */
void
matrixOnes (adder_matrix *m)
{
	int i, j;

	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			m->mat[i * m->columns + j] = 1;
		}
	}
}

/* Set the matrix to random values uniformly distributed between 0 and 1 */
int
randMatrix (adder_matrix *m)
{
	long int seed;
	size_t err;
	int i, j;
	FILE *fp;

	/* Open the random number generator */
	fp = fopen ("/dev/urandom", "r");
	if (fp == NULL) {
		fprintf (stderr, "Failed to open random number generator.\n");
		return INVALID_FILE;
	}

	/* Read an int from the random number generator */
	err = fread (&seed, sizeof (long int), 1, fp);
	if (err == 0) {
		fprintf (stderr, "Failed to read from the random number generator.\n");
		return FILE_READ_ERROR;
	}

	/* Close the random number generator */
	fclose (fp);

	/* Seed the random number generator */
	srand (seed);

	/* Generate the random numbers */
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			m->mat[i * m->columns + j] = rand () / (double)RAND_MAX;
		}
	}

	return 0;
}

/**************************
 * Other matrix functions *
 **************************/

/* Transpose a matrix */
adder_matrix *
matrixTranspose (adder_matrix *m)
{
	adder_matrix *T;
	long int i, j;

	T = matrixInit2 (ROW_MAJOR, m->columns, m->rows);
	if (T == 0x00) {
		fprintf (stderr, "Failed to create transpose matrix.\n");
		return 0x00;
	}

	/* Perform the transposition */
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			T->mat[j * m->rows + i] = m->mat[i * m->columns + j];
		}
	}

	/* Switch the values of rows and columns */
	m->rows += m->columns;
	m->columns = m->rows - m->columns;
	m->rows -= m->columns;

	return T;
}
