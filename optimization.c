/* optimization.c
 * Function definitions for optimization.c */
#include <stdio.h>
#include "optimization.h"

/* Determine which algorithm to call and then call it */
/*double*/
/*linSearch (int searchMethod, adder_function *f,*/
/*	   double a, double b, int N, double stoppingCriteria)*/
/*{*/
/*	double *res;*/

/*	if (searchMethod == GOLDEN_SECTION) {*/
/*		*res = goldenSectionSearch (f, a, b, stoppingCriteria);*/
/*	}*/
/*	else if (searchMethod == FIBONACCI) {*/
/*		*res = fibonacciSearch (f, a, b, N, stoppingCriteria);*/
/*	}*/
/*	else if (searchMethod == EQUAL_AREA) {*/
/*		*res = equalArea (f, a, b, stoppingCriteria);*/
/*	}*/
/*	else {*/
/*		fprintf (stderr, "Invalid search method specified. ");*/
/*		res = NULL;*/
/*	}*/

/*	return res;*/
/*}*/

/* Golden Section search method of a single variable function
 * retValue is used to determine if the x-value or the function value of the minimum should be returned
 * func is the function being minimized
 * a is the lower bound of the search region
 * b is the upper bound of the initial search region
 * stoppingCriteria is the maximum tolerance for stopping the search */
double
goldenSectionSearch (adder_function *f, double a, double b, double stoppingCriteria, int retValue)
{
	double alpha;
	double beta;
	double gA;
	double gB;
	double x;

	/* Iterate the algorithm */
	while (b - a > stoppingCriteria) {
		alpha = 0.382 * (b - a) + a;
		beta = 0.618 * (b - a) + a;

		gA = f->function (alpha);
		gB = f->function (beta);

		if (gA < gB) {
			b = beta;
		}
		else if (gA > gB) {
			a = alpha;
		}
		else {
			a = alpha;
			b = beta;
		}
	}

	/* Since the stopping criteria is finite, there is still an area of uncertainty
	 * about where the minimum is. We will use the mid-point of the region */
	x = (a + b) / 2;

	if (retValue == X_VALUE) {
		return x;
	}
	else if (retValue == F_VALUE) {
		return f->function (x);
	}
	else {
		fprintf (stderr, "Invalid return value specified. Returning x value.\n");
		return x;
	}
}

/* Fibonacci Search method of a single variable function
 * retValue is used to determine if the x-value or the function value of the minimum should be returned
 * func is the function being minimized
 * a is the lower bound of the search region
 * b is the upper bound of the search region
 * N is the number of iterations to perform */
double
fibonacciSearch (adder_function *f, double a, double b, int N, double stoppingCriteria, int retValue)
{
	double fibNums[N+1];
	double alpha;
	double beta;
	double fA;
	double fB;
	double x;
	int i;

	/* Calculate the fibonacci numbers */
	fibNums[0] = 1;
	fibNums[1] = 2;

	for (i = 2; i < N + 1; i++) {
		fibNums[i] = fibNums[i - 1] + fibNums[i - 2];
	}

	/* Iterate the algorithm */
	for (i = 0; i < N; i++) {
		if ((N - i - 2) < 0) {
			alpha = (1 / fibNums[N - i]) * (b - a) + a;
			beta = (1 / fibNums[N - i]) * (b - a) + a;
		}
		else {
			alpha = (fibNums[N - i - 2] / fibNums[N - i]) * (b - a) + a;
			beta = (fibNums[N - i -1] / fibNums[N - i]) * (b - a) + a;
		}

		fA = f->function (alpha);
		fB = f->function (beta);

		if (fA < fB) {
			b = beta;
		}
		else if (fA > fB) {
			a = alpha;
		}
		else {
			a = alpha;
			b = beta;
		}
	}

	/* Check retValue to determine if the x- or function-value should be returned */
	x = (b + a) / 2;

	if (retValue == X_VALUE) {
		return x;
	}
	else if (retValue == F_VALUE) {
		return f->function (x);
	}
	else {
		fprintf (stderr, "Invalid return value specified. Using x-value.\n");
		return x;
	}
}

/* Equal area search method for a single variable function
 * retValue is used to determine if the x-value or the function value of the minimum should be returned
 * func is the function being minimized
 * a is the lower bound of the search region
 * b is the upper bound of the search region
 * stoppingCriteria is the maximum tolerance for stopping the search */
double
equalAreaSearch (adder_function *f, double a, double b, int N, double stoppingCriteria, int retValue)
{
	double alpha;
	double beta;
	double fA;
	double fB;
	double x;
	int i;

	/* Iterate the algorithm */
	for (i = 0; i < N; i++) {
		alpha = (a + b) / 3;
		beta = 2 * (a + b) / 3;

		fA = f->function (alpha);
		fB = f->function (beta);

		if (fA < fB) {
			b = beta;
		}
		else if (fA > fB) {
			a = alpha;
		}
		else {
			a = alpha;
			b = beta;
		}
	}

	/* Check retValue to determine if the x- or function-value should be returned */
	x = (b + a) / 2;

	if (retValue == X_VALUE) {
		return x;
	}
	else if (retValue == F_VALUE) {
		return f->function (x);
	}
	else {
		fprintf (stderr, "Invalid return value specified. Using x-value.\n");
		return x;
	}
}
