#ifndef MATRIX_H
#define MATRIX_H

enum
ERRORS
{
	DIMENSION_ERROR = -1,
	INVALID_FILE = 1,
	FILE_READ_ERROR = 2,
	ARGUMENT_ERROR = 3,
	SINGULAR_MATRIX = 4
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
} Vector;

/* Matrix type definition */
typedef struct
{
	double *mat;
	int rows;
	int columns;
	int orientation;
} Matrix;

/* Vector IO functions */
Vector * vectorInit (int orient, int numElements, double *values);
Vector * vectorInit2 (int orient, int numElements);
void deleteVector (Vector *v);
void printVector (Vector *v);

/* Vector setting functions */
void vectorZeros (Vector *v);
void vectorOnes (Vector *v);
int randVector (Vector *v);

/* Matrix IO functions */
Matrix * matrixInit (int orient, int numRows, int numColumns, double *values);
Matrix *matrixInit2 (int orient, int numRows, int numcolumns);
void deleteMatrix (Matrix *m);
void printMatrix (Matrix *m);

/* Matrix setting functions */
void eye (Matrix *m, long int n);
void matrixZeros (Matrix *m);
void matrixOnes (Matrix *m);
int randMatrix (Matrix *m);

#endif
