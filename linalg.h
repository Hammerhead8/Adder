/* linalg.h
 *
 * This serves as an extension to matrix.h and includes linear algebra
 * routines for matrices and vectors using OpenBLAS and LAPACKE */
#ifndef LINALG_H
#define LINALG_H

#include "matrix.h"

/* Extra matrix functions */
Matrix * transpose (Matrix *m);
Matrix * inverse (Matrix *m);

/* Equation solving */
Vector * linearSolve (Matrix *M, Vector *b);

/* Eigenvalues */
Vector * eigenValues (Matrix *m);

/* Matrix factorizations */
Matrix * qr (Matrix *m);
Matrix * lq (Matrix *m);
Matrix * lu (Matrix *m);

/* Singular value decomposition */
void svd (Matrix *m);

/* Norms */
double vectorNorm (Vector *v);
double matrixNorm (Matrix *m);
void vectorTranspose (Vector *v);

#endif
