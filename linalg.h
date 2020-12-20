/* linalg.h
 *
 * This serves as an extension to matrix.h and includes linear algebra
 * routines for matrices and vectors using OpenBLAS and LAPACKE */
#ifndef LINALG_H
#define LINALG_H

#include "matrix.h"

Matrix * transpose (Matrix *m);
void vectorTranspose (Vector *v);
void inverse (Matrix *m);
Vector * linearSolve (Matrix *M, Vector *b);
Vector * eigenValues (Matrix *m);
Matrix * lq (Matrix *m);
Matrix * lu (Matrix *m);
void svd (Matrix *m);
double vectorNorm (Vector *v);
double matrixNorm (Matrix *m);

#endif
