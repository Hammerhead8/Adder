/* integration.h
 * Prototypes numerical integration functions.
 * Integration can be done using Gauss-Legendre quadrature or
 * the Trapezoidal rule.
 * All integration routines use double precision */
#ifndef INTEGRATION_H
#define INTEGRATION_H

/* Gauss-Legendre quadrature */
double gauss3 (double (*function)(double), double a, double b);
double gauss5 (double (*function)(double), double a, double b);
double gauss20 (double (*function)(double), double a, double b);
double gauss100 (double (*function)(double), double a, double b);
double gaussQuad (double (*function)(double), double a, double b, int N);

/* Other integration routines */
double trapezoidIntegrate (double (*function)(double), double a, double b, int N);

#endif
