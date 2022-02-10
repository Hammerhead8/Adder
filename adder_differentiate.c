/* differentiate.c
 * Function definitions for the numerical differentiation routines.
 *
 * The formulas for the first-order derivatives comes from https://dlmf.nist.gov/3.4#i
 *
 * TODO:  Implement directional derivatives for multi-dimensional functions */
#include "adder_differentiate.h"

/* Differentiate a function of one variable using the symmetric
 * difference quotient.
 * f is the function to be differentiated
 * x is the x value of the point at which to take the derivative
 * h is the size of the interval around the point such that
 * d/dx = lim_{h->0} [f(x+h) - f(x-h)] / 2h */
double
derivSymDiff (adder_function *f, double x, double h)
{
	double a;
	double b;
	double dx;

	a = f->function (x - h);
	b = f->function (x + h);

	dx = (b - a) / (2 * h);

	return dx;
}

/* Differentiate a function of one variable using the five-point method
 * f is the function being differentiated
 * x is the point at which the derivative is taken
 * h is the step size */
double
derivCenter (adder_function *f, double x, double h)
{
	double a, b, c, d, e;
	double dx;

	/* Calculate the values of the Legrange interpolation coefficients */
	a = (1 - x - 3 * x * x + 2 * x * x * x) / 12.0;
	a *= f->function (x - 2 * h);

	b = -1 * (4 - 8 * x - 3 * x * x + 4 * x * x * x) / 6.0;
	b *= f->function (x - h);

	c = -1 * (5 * x - 2 * x * x * x) / 2.0;
	c *= f->function (x);

	d = (4 + 8 * x - 3 * x * x - 4 * x * x * x) / 6.0;
	d *= f->function (x + h);

	e = -1 * (1 + x - 3 * x * x - 2 * x * x * x) / 12.0;
	e *= f->function (x + 2 * h);

	/* Calculate the derivative by adding the coefficients and dividing by h */
	dx = (a + b + c + d + e) / h;

	return dx;
}

/* Differentiate a function of one variable using the forward five-point method
 * f is the function being differentiated
 * x is the point at which the derivative is taken
 * h is the step size */
double
derivForward (adder_function *f, double x, double h)
{
	double a, b, c, d, e;
	double dx;

	/* Calculate the values of the Lagrangian interpolation coefficients */
	a = (1 - x - 3 * x * x + 2 * x * x * x) / 12.0;
	a *= f->function (x);

	b = -1 * (4 - 8 * x - 3 * x * x + 4 * x * x * x) / 6.0;
	b *= f->function (x + h);

	c = -1 * (5 * x - 2 * x * x * x) / 2.0;
	c *= f->function (x + 2 * h);

	d = (4 + 8 * x - 3 * x * x - 4 * x * x * x) / 6.0;
	d *= f->function (x + 3 * h);

	e = -1 * (1 + x - 3 * x * x - 2 * x * x * x) / 12.0;
	e *= f->function (x + 4 * h);

	/* Calculate the derivative by adding the coefficients and dividing by h */
	dx = (a + b + c + d + e) / h;

	return dx;
}

/* Differentiate a function of one variable using the backward five-point method
 * f is the function being differentiated
 * x is the point at which the derivative is taken
 * h is the step size */
double
derivBackward (adder_function *f, double x, double h)
{
	double a, b, c, d, e;
	double dx;

	/* Calculate the values of the Lagrangian interpolation coefficients */
	a = (1 - x - 3 * x * x + 2 * x * x * x) / 12.0;
	a *= f->function (x - 4 * h);

	b = -1 * (4 - 8 * x - 3 * x * x + 4 * x * x * x) / 6.0;
	b *= f->function (x - 3 * h);

	c = -1 * (5 * x - 2 * x * x * x) / 2.0;
	c *= f->function (x - 2 * h);

	d = (4 + 8 * x - 3 * x * x - 4 * x * x * x) / 6.0;
	d *= f->function (x - h);

	e = -1 * (1 + x - 3 * x * x - 2 * x * x * x) / 12.0;
	e *= f->function (x);

	/* Calculate the derivative by adding the coefficients and dividing by h */
	dx = (a + b + c + d + e) / h;

	return dx;
}
