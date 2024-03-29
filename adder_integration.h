/* integration.h
 * Prototypes numerical integration functions.
 * Integration can be done using Gauss-Legendre quadrature or
 * the Trapezoidal rule.
 * All integration routines use double precision */
#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "adder_math.h" /* For adder_function */

enum
IntegralErrors
{
	INTEGRAL_SUCCESS,
	INTEGRAL_ERROR
};

/* Gauss-Legendre quadrature */
double gauss3 (adder_function *f, double a, double b);
double gauss5 (adder_function *f, double a, double b);
double gauss20 (adder_function *f, double a, double b);
double gauss50 (adder_function *f, double a, double b);
double gauss100 (adder_function *f, double a, double b);
int galeQuad (adder_function *f, double *res, double a, double b, int N);

/*Other integration routines */
double trapezoidIntegrate (adder_function *f, double a, double b, int N);
double simpsonIntegrate (adder_function *f, double a, double b, int N);
double monteCarloIntegrate (adder_function *f, double a, double b, long unsigned int N);

/* Other routines */
long unsigned int xorshift (long unsigned int y);

#endif
