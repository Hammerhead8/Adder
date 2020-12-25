/* matrix.c
 * Function definitions for matrix.h */
#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

/* Vector IO functions */
/* Create a new vector and set its values */
Vector *
vectorInit (int orient, int numElements, double *values)
{
	Vector *v;
	int i;

	/* Allocate the vector in memory */
	v = malloc (sizeof (Vector));
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
Vector *
vectorInit2 (int orient, int numElements)
{
	Vector *v;
	int i;

	/* Allocate the vector in memory */
	v = malloc (sizeof (Vector));
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
setVector (Vector *v, double *values)
{
	int i;

	for (i = 0; i < v->size; i++) {
		v->vect[i] = values[i];
	}
}

/* Delete a vector */
void
deleteVector (Vector *v)
{
	free (v->vect);
	free (v);
}

/* Print a vector */
void
printVector (Vector *v)
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
			printf ("%lf\n", v->vect[i]);
		}

		printf ("\n");
	}
}

/* Vector setting functions */
/* Set an existing vector to be a zero vector */
void
vectorZeros (Vector *v)
{
	int i;

	for (i = 0; i < v->size; i++) {
		v->vect[i] = 0;
	}
}

/* Set an existing vector to be all ones */
void
vectorOnes (Vector *v)
{
	int i;

	for (i = 0; i < v->size; i++) {
		v->vect[i] = 1;
	}
}

/* Set an existing vector to random values */
int
randVector (Vector *v)
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
Matrix *
matrixInit (int orient, int numRows, int numColumns, double *values)
{
	Matrix *m;
	int i, j;

	/* Allocate memory for the matrix */
	m = malloc (sizeof (Matrix));
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
Matrix *
matrixInit2 (int orient, int numRows, int numColumns)
{
	Matrix *m;
	int i, j;

	m = malloc (sizeof (Matrix));
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
deleteMatrix (Matrix *m)
{
	free (m->mat);
	free (m);
}

/* Print the matrix */
void
printMatrix (Matrix *m)
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

/* Set the matrix to a zero matrix */
void
matrixZeros (Matrix *m)
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
matrixOnes (Matrix *m)
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
randMatrix (Matrix *m)
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
