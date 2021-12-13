/* interp.h
 * Contains function prototypes and stuctures for interpolation routines */

#ifndef INTERPOLATE_H
#define INTERPOLATE_H

#include "adder_math.h" /* For adder_function */

double linearInterp (double *x, double *y, double x2);
int polynomialInterp (double *result, int n, double *x0, double *y0, double x2);

#endif
