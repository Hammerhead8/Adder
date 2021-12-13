/* differentiate.c
 * Function definitions for the numerical differentiation routines.
 *
 * TODO:  Implement directional derivatives for multi-dimensional functions */
#include "differentiate.h"

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

	a = f->function (x - 2 * h);
	b = -8 * f->function (x - h);
	c = 8 * f->function (x + h);
	d = -1 * f->function (x + 2 * h);

	dx = (a + b + c + d) / (12 * h);

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

	a = -25 * f->function (x);
	b = 48 * f->function (x + h);
	c = -36 * f->function (x + 2 * h);
	d = 16 * f->function (x + 3 * h);
	e = -3 * f->function (x + 4 * h);

	dx = (a + b + c + d + e) / (12 * h);

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

	a = -25 * f->function (x - 4 * h);
	b = 48 * f->function (x - 3 * h);
	c = -36 * f->function (x - 2 * h);
	d = 16 * f->function (x - h);
	e = -3 * f->function (x);

	dx = (a + b + c + d + e) / (12 * h);

	return dx;
}
