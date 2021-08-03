#ifndef MATRIX_H
#define MATRIX_H

enum
ERRORS
{
	DIMENSION_ERROR = -1,
	INVALID_FILE = 1,
	FILE_READ_ERROR = 2,
	ARGUMENT_ERROR = 3,
	SINGULAR_MATRIX = 4,
	INIT_ERROR = 5
};

enum
VECTOR_ORDER
{
	ROW_VECTOR = -1,
	COLUMN_VECTOR = 1
};

enum
MATRIX_ORIENTATION
{
	ROW_MAJOR = 1,
	COLUMN_MAJOR = 2
};

/* Vector type definition */
typedef struct
{
	double *vect;
	int size;
	int orientation;
} adder_vector;

/* Matrix type definition */
typedef struct
{
	double *mat;
	int rows;
	int columns;
	int orientation;
} adder_matrix;

/* Vector IO functions */
adder_vector * vectorInit (int orient, int numElements, double *values);
adder_vector * vectorInit2 (int orient, int numElements);
void deleteVector (adder_vector *v);
void printVector (adder_vector *v);

/* Vector setting functions */
void vectorZeros (adder_vector *v);
void vectorOnes (adder_vector *v);
int randVector (adder_vector *v);

/* Matrix IO functions */
adder_matrix * matrixInit (int orient, int numRows, int numColumns, double *values);
adder_matrix *matrixInit2 (int orient, int numRows, int numcolumns);
void deleteMatrix (adder_matrix *m);
void printMatrix (adder_matrix *m);

/* Matrix arithmetic functions */
adder_vector * mvMultiply (adder_matrix *M, adder_vector *v);

/* Matrix setting functions */
void eye (adder_matrix *m, long int n);
void matrixZeros (adder_matrix *m);
void matrixOnes (adder_matrix *m);
int randMatrix (adder_matrix *m);

#endif
