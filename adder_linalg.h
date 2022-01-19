/* linalg.h
 *
 * This serves as an extension to matrix.h and includes linear algebra
 * routines for matrices and vectors using OpenBLAS and LAPACKE */
#ifndef LINALG_H
#define LINALG_H

#include "adder_matrix.h"

/* Extra matrix functions */
adder_matrix * inverse (adder_matrix *m);
adder_matrix * pseudoinverse (adder_matrix *m);
adder_complex_matrix * complexInverse (adder_complex_matrix *m);

/* Equation solving */
adder_vector * linearSolve (adder_matrix *M, adder_vector *b);
adder_vector * odLinearSolve (adder_matrix *M, adder_vector *b);
adder_vector * linearLeastSquares (adder_matrix *M, adder_vector *b);

/* Eigenvalues */
adder_vector * eigenValues (adder_matrix *m);
adder_complex_vector * complexEigenValues (adder_complex_matrix *m);

/* Matrix factorizations */
adder_matrix * qr (adder_matrix *m);
adder_matrix * lq (adder_matrix *m);
adder_matrix * lu (adder_matrix *m);

/* Singular value decomposition */
adder_vector * svd (adder_matrix *m);

/* Norms */
double vectorNorm (adder_vector *v);
double matrixNorm (adder_matrix *m);

#endif
