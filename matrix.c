/* matrix.c
 * Function definitions for matrix.h */
#include <stdio.h>
#include <stdlib.h>
#include <cblas.h>
#include "matrix.h"

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
	srand48 (seed);

	/* Generate the random numbers */
	for (i = 0; i < v->size; i++) {
		v->vect[i] = drand48 ();
	}

	return 0;
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
	srand48 (seed);

	/* Generate the random numbers */
	for (i = 0; i < m->rows; i++) {
		for (j = 0; j < m->columns; j++) {
			m->mat[i * m->columns + j] = drand48 ();
		}
	}

	return 0;
}
