#ifndef MATRIX_H
#define MATRIX_H

enum { DIMENSION_ERROR = -1 };

/* Vector type definition */
typedef struct
{
	double *vect;
	long int size;
} Vector;

/* Matrix type definition */
typedef struct
{
	double *mat;
	long int rows;
	long int columns;
} Matrix;

/* Vector IO functions */
Vector * vectorInit (long int numElements, double *values);
Vector * vectorInit2 (long int numElements);
void deleteVector (Vector *v);
void printVector (Vector *v);

/* Vector setting functions */
void vectorZeros (Vector *v);
void vectorOnes (Vector *v);
void randVector (Vector *v);

/* Matrix IO functions */
Matrix * matrixInit (long int numRows, long int numColumns, double *values);
Matrix *matrixInit2 (long int numRows, long int numcolumns);
void deleteMatrix (Matrix *m);
void printMatrix (Matrix *m);

/* Matrix setting functions */
void eye (Matrix *m, long int n);
void matrixZeros (Matrix *m);
void matrixOnes (Matrix *m);
void randMatrix (Matrix *m);

#endif
