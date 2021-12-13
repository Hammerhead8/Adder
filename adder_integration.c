/* integration.c
 * Definitions of the numerical integration functions in integration.h */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "integration.h"

/* Three point Gauss-Legendre quadrature
 * f is the function to be integrated
 * a is the lower bound of integration
 * b is the upper bound of integration */
double
guass3 (adder_function *f, double a, double b)
{
	const double xi[3] = {-.7745966692, 0.0, .7745966692}; /* Abscissas */
	const double wi[3] = {.5555554736, .8888888889, .5555554736}; /* Weights */
	double x;
	double mul1, mul2, mul3;
	double fValue;
	double res = 0;

	/* The first step is to change the interval from [a,b] to [-1,1]
	 * The new function is of the form mul1 * f(mul2 * x + mul3) */
	mul1 = (b - a) / 2;
	mul2 = mul1;
	mul3 = (b + a) / 2;

	/* Now perform the integration.
	 * The loop is unrolled since there are only three points */
	x = mul2 * xi[0] + mul3;
	fValue = f->function (x);
	res += wi[0] * fValue;

	x = mul2 * xi[1] + mul3;
	fValue = f->function (x);
	res += wi[1] * fValue;

	x = mul2 * xi[2] + mul3;
	fValue = f->function (x);
	res += wi[2] * fValue;

	/* Multiply res by mul1 to get the final result */
	res *= mul1;

	return res;
}

/* Five point Gauss-Legendre quadrature
 * f is the function to be integrated
 * a is the lower bound of integration
 * b is the upper bound of integration */
double
gauss5 (adder_function *f, double a, double b)
{
	const double xi[5] = {-0.9061798459, -0.5384693101, 0.0, 0.5384693101, 0.9061798459};
	const double wi[5] = {0.2369268005, 0.4786286705, 0.5688888889, 0.4786286705, 0.2369268005};
	double x;
	double mul1, mul2, mul3;
	double fValue;
	double res = 0;

	/* The first step is to change the interval from [a,b] to [-1,1].
	 * The new function will be of the form mul1 * f(mul2 * x + mul3); */
	mul1 = (b - a) / 2;
	mul2 = mul1;
	mul3 = (b + a) / 2;

	/* Now perform the integration */
	x = mul2 * xi[0] + mul3;
	fValue = f->function (x);
	res += wi[0] * fValue;

	x = mul2 * xi[1] + mul3;
	fValue = f->function (x);
	res += wi[1] * fValue;

	x = mul2 * xi[2] + mul3;
	fValue = f->function (x);
	res += wi[2] * fValue;

	x = mul2 * xi[3] + mul3;
	fValue = f->function (x);
	res += wi[3] * fValue;

	x = mul2 * xi[4] + mul3;
	fValue = f->function (x);
	res += wi[4] * fValue;

	/* Multiply res by mul1 to get the final result */
	res *= mul1;

	return res;
}

/* Twenty point Gauss-Legendre quadrature
 * f is the function to be integrated
 * a is the lower bound of integration
 * b is the upper bound of integration */
double
gauss20 (adder_function *f, double a, double b)
{
	const double xi[20] = {-0.9931285992, -0.9639719273, -0.9122344283, -0.8391169718,
			      -0.7463319065, -0.6360536807, -0.5108670020, -0.3737060887,
			      -0.2277858511, -0.0765265211, 0.0765265211, 0.2277858511,
			       0.3737060887, 0.5108670020, 0.6360536807, 0.7463319065,
			       0.8391169718, 0.9122344283, 0.9639719273, 0.9931285992};

	const double wi[20] = {0.0176139968, 0.0406014298, 0.0626720483, 0.0832767416,
			       0.1019300655, 0.1181945135, 0.1316886329, 0.1420961081,
			       0.1491729863, 0.1527533871, 0.1527533871, 0.1491729863,
			       0.1420961081, 0.1316886329, 0.1181945135, 0.1019300655,
			       0.0832767416, 0.0626720483, 0.0406014298, 0.0176139968};

	double x;
	double mul1, mul2, mul3;
	double fValue;
	double res;
	int i;

	/* The first step is to transform the bounds from [a,b] to [-1,1] */
	mul1 = (b - a) / 2;
	mul2 = mul1;
	mul3 = (b + a) / 2;

	/* Perform the integration */
	for (i = 0; i < 20; i++) {
		x = mul2 * xi[i] + mul3;
		fValue = f->function (x);
		res += wi[i] * fValue;
	}

	/* Multiply res by mul1 to get the final result */
	res *= mul1;

	return res;
}

/* General Gauss-Legendre quadrature
 * Since the number of points to use is only known at run time, the
 * weights and abscissas are not calculated beforehand
 * f is the function to be integrated
 * a is the lower bound of integration
 * b is the upper bound of integration
 * N is the number of points to use
 *
 * Routine is a reimplementation of that by Pazus at
 * https://github.com/Pazus/Legendre-Gauss-Quadrature */
int
galeQuad (adder_function *f, double a, double b, double *xi, double *wi, int N)
{
	double mul1, mul2, mul3;
	double fValue;
	double x;
	double z, z1;
	double p, p1, p2, p3;
	double h;
	int i, j;
	int m;
	double res = 0;

	/* Check if the number of points to be used is an even number */
	if (N % 2 == 0) {
		m = N / 2;
	}
	else {
		m = (N + 1) / 2;
	}

	/* Calculate the abscissas and weights */
	for (i = 1; i <= m; i++) {
		z = cos(M_PI * (i - 0.25) / ((double)N + 0.5)); //initial estimate
		z1 = z + 1;

		while (fabs (z - z1) > __DBL_EPSILON__) {
			p1 = 1;
			p2 = 0;

			for (j = 1; j <= N; j++) {
				p3 = p2;
				p2 = p1;
				p1 = ((2 * j - 1) * z * p2 - (j - 1) * p3) / j; //The Legendre Polynomial
			}

			p = (double)N * (z * p1 - p2) / (z * z - 1); //derivative of the Legendre Polynomial
			z1 = z;
			z = z1 - p1 / p;
		}

		/* Abscissas */
		xi[i - 1] = -1 * z;
		xi[N - i] = z;

		/* Weights */
		wi[i - 1] = 2.0 / ((1.0 - z * z) * (p * p));
		wi[N - i] = wi[i - 1];
	}

	/* Now we can apply the quadrature algorithm */

	/* The first step is to transform the bounds from [a,b] to [-1,1] */
	mul1 = (b - a) / 2;
	mul2 = mul1;
	mul3 = (b + a) / 2;

	/* Perform the integration */
	for (i = 0; i < N; i++) {
		x = mul2 * xi[i] + mul3;
		fValue = f->function (x);
		res += wi[i] * fValue;
	}

	/* Multiply res by mul1 to get the final result */
	res *= mul1;

	return res;
}


/******************************
 * Other integration routines *
 ******************************/

/* Apply the Trapezoidal Rule
 * f is the function being integrated
 * a is the lower bound of integration
 * b is the upper bound of integration
 * N is the number of points to use */
double
trapezoidIntegrate (adder_function *f, double a, double b, double *points, int N)
{
	double dX;
	double x;
	double res = 0;
	int i;

	dX = (b - a) / (double)N;

	/* Calculate the points that form the edges of the intervals */
	for (i = 0; i <= N; i++) {
		x = a + i * dX;
		points[i] = f->function (x);
	}

	/* Perform the integration */
	for (i = 0; i <= N; i++) {
		if (i == 0 || i == N) {
			res += points[i];
		}
		else {
			res += 2 * points[i];
		}
	}

	res *= dX / 2;
	return res;
}

/* Apply the Composite Simpson's Rule
 * f is the function being integrated
 * a is the lower bound of integration
 * b is the upper bound of integration
 * N is the number of points to use.
 * NOTE:  n must be an even number */
double
simpsonIntegrate (adder_function *f, double a, double b, double *points, int N)
{
	double dx;
	double x;
	double res = 0;
	int i;

	/* Calculate the constants */
	dx = (b - a) / (double)N;

	/* Calculate the function values for each point */
	for (i = 0; i <= N; i++) {
		x = a + i * dx;
		points[i] = f->function (x);
	}

	/* Calculate the first and last points */
	res += points[0];
	res += points[N - 1];

	/* Iterate the rest of the algorithm */
	for (i = 1; i <= N - 1; i++) {
		if (i % 2 == 0) {
			res += 2 * points[i];
		}
		else {
			res += 4 * points[i];
		}
	}

	/* Multiply the sum by dx/3 to get the final result */
	res *= dx / 3;

	return res;
}
