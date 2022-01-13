#ifndef MATRIX_H
#define MATRIX_H

#include "complex.h"

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

/*enum
MATRIX_ORIENTATION
{
	ROW_MAJOR = 1,
	COLUMN_MAJOR = 2
}; */

/* Vector type definition */
typedef struct
{
	double *vect;
	int size;
	int orientation;
} adder_vector;

/* Complex vector type definition */
typedef struct
{
	adder_complex_rect *vect;
	int size;
	int orientation;
} adder_complex_vector;

/* Matrix type definition */
typedef struct
{
	double *mat;
	int rows;
	int columns;
} adder_matrix;

/* Complex matrix type definition */
typedef struct
{
    adder_complex_rect *mat;
    int rows;
    int columns;
} adder_complex_matrix;

/* Vector IO functions */
adder_vector * vectorInit (int orient, int numElements, double *values);
adder_vector * vectorInit2 (int orient, int numElements);
void deleteVector (adder_vector *v);
void printVector (adder_vector *v);

/* Complex vector IO functions */
adder_complex_vector * complexVectorInit (int orient, int numElements, double *realValues, double *imagValues);
adder_complex_vector * complexVectorInit2 (int orient, int numElements);
void deleteComplexVector (adder_complex_vector *z);
void printComplexVector (adder_complex_vector *z);

/* Vector setting functions */
void vectorZeros (adder_vector *v);
void vectorOnes (adder_vector *v);
int randVector (adder_vector *v);

/* Other vector functions */
void vectorTranspose (adder_vector *v);
void complexVectorTranspose (adder_complex_vector *z);

/* Matrix IO functions */
adder_matrix * matrixInit (int numRows, int numColumns, double *values);
adder_matrix *matrixInit2 (int numRows, int numcolumns);
void deleteMatrix (adder_matrix *m);
void printMatrix (adder_matrix *m);

/* Complex matrix IO functions */
adder_complex_matrix * complexMatrixInit (int numRows, int numColumns, double *realValues, double *imagValues);
adder_complex_matrix * complexMatrixInit2 (int numRows, int numColumns);
void deleteComplexMatrix (adder_complex_matrix *Z);
void printComplexMatrix (adder_complex_matrix *Z);

/* Matrix arithmetic functions */
adder_vector * mvMultiply (adder_matrix *M, adder_vector *v);
adder_matrix * mmMultiply (adder_matrix *A, adder_matrix *B);
adder_complex_vector * mvMultiplyComplex (adder_complex_matrix *Z, adder_complex_vector *v);
adder_complex_matrix * mmMultiplyComplex (adder_complex_matrix *Y, adder_complex_matrix *Z);

/* Matrix setting functions */
void eye (adder_matrix *m, long int n);
void matrixZeros (adder_matrix *m);
void matrixOnes (adder_matrix *m);
int randMatrix (adder_matrix *m);

/* Other matrix functions */
adder_matrix * matrixTranspose (adder_matrix *m);

#endif
