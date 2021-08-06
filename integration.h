/* integration.h
 * Prototypes numerical integration functions.
 * Integration can be done using Gauss-Legendre quadrature or
 * the Trapezoidal rule.
 * All integration routines use double precision */
#ifndef INTEGRATION_H
#define INTEGRATION_H

#include "adder_math.h"

// #include "rng.h" /* Needed for Monte Carlo integration */

enum
IntegralErrors
{
	INTEGRAL_SUCCESS,
	INTEGRAL_ERROR
};

typedef struct
{
	double I;
	double (*f)(double);
} adder_integral;

/* Gauss-Legendre quadrature */
double gauss3 (adder_function *f, double a, double b);
double gauss5 (adder_function *f, double a, double b);
double gauss20 (adder_function *f, double a, double b);
double gauss50 (adder_function *f, double a, double b);
double gauss100 (adder_function *f, double a, double b);
double gaussQuad (adder_function *f, double a, double b, double *xi, double *wi, int N);
/*double gauss3 (double (*function)(double), double a, double b);*/
/*double gauss5 (double (*function)(double), double a, double b);*/
/*double gauss20 (double (*function)(double), double a, double b);*/
/*double gauss100 (double (*function)(double), double a, double b);*/
/*double gaussQuad (double (*function)(double), double a, double b, int N);*/

/* Other integration routines */
double trapezoidIntegrate (adder_function *f, double a, double b, double *points, int N);
double simpsonIntegrate (adder_function *f, double a, double b, double *points, int N);
//int monteCarloIntegrate (adder_integral *ovi, double a, double b, int N, unsigned long int seed);
/*int trapezoidIntegrate (double (*function)(double), double a, double b, int N);*/
/*int simpsonIntegrate (double (*function)(double), double a, double b, int N);*/

#endif
