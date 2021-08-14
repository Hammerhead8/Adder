/* roots.c
 * Function definitions for the root finding algorithms */
#include "roots.h"
#include <math.h> /* For fabs */

/* Non-derivative methods */

/* Bisection Method
 *
 * f is the function being solved
 * lGuess is the initial lower bound of the interval containing the solution
 * rGuess is the initial upper bound of the interval containing the solution
 * tol is the desired accuracy of the solution
 * iterLimit is the maximum number of iterations
 */
double
bisection (adder_function *f, double lGuess, double rGuess, double tol, unsigned iterLimit)
{
	double a = lGuess; /* Lower bound of the interval */
	double b = rGuess; /* Upper bound of the interval */
	double c; /* Midpoint of the interval */
	double fa; /* Value of the function at a */
	double fb; /* Value of the function at b */
	double fc; /* Value of the function at c */
	unsigned int i;

	fa = f->function (a);
	fb = f->function (b);

	/* Main algorithm */
	for (i = 0; i < iterLimit; i++) {
		c = (a + b) / 2;
		fc = f->function (c);

		if (fabs (fc) < tol) {
			break;
		}
		else {
			if (sign (fa, fc) == 1) {
				a = c;
				fa = fc;
			}
			else {
				b = c;
				fb = fc;
			}
		}
	}

	return c;
}

/* Regula Falsi
 *
 * f is the function being solved
 * guess is the initial guess of the solution
 * tol is the desired tolerance
 * iterLimit is the maximum number of iterations
 */
double
regulaFalsi (adder_function *f, double lGuess, double rGuess, double tol, unsigned int iterLimit)
{
	double x0 = lGuess; /* Lower bound of the interval */
	double x1 = rGuess; /* Upper bound of the interval */
	double x2; /* The next approximation */
	double f0; /* Value of the function at x = x0 */
	double f1; /* Value of the function at x = x1 */
	double f2; /* Value of the function at x = x2 */
	unsigned int i;

	/* Calculate the intial values of the endpoints */
	f0 = f->function (x0);
	f1 = f->function (x1);

	/* Check if the endpoints are the solution */
	if (f0 == 0) {
		return x0;
	}
	else if (f1 == 0) {
		return x1;
	}

	/* Main algoritm. Digital Library of Mathematical Functions
	 * describes the method as using inverse linear interpolation */
	for (i = 0; i < iterLimit; i++) {
		/* Calculate the next approximation and the value of the function at that point */
		x2 = x1 - ((x1 - x0) / (f1 - f0)) * f1;
		f2 = f->function (x2);

		/* Check if x2 is within the desired tolerance */
		if (fabs (f2) < tol) {
			break;
		}
		else {
			/* Check the sign of x2 */
			if (sign (f0, f2) == 1) {
				x1 = x2;
				f1 = f->function (x1);
			}
			else {
				x0 = x2;
				f0 = f->function (x0);
			}
		}
	}

	return x2;
}

/* Steffensen's Method
 *
 * f is the function being solved
 * guess is the initial guess of the solution
 * tol is the desired tolerance
 * iterLimit is the maximum number of iterations
 */
double
steffensen (adder_function *f, double guess, double tol, unsigned int iterLimit)
{
	double xn;
	double xn1;
	double fxn;
	double f1xn;
	unsigned int i;

	xn = guess;

	/* The algorithm */
	for (i = 0; i < iterLimit; i++) {
		fxn = f->function (xn);
		f1xn = f->function (fxn + xn);

		/* Definition of Steffensen's Method */
		xn1 = xn - (fxn * fxn) / (f1xn - fxn);
//		xn1 = xn - (pow (fxn - xn, 2) / (f1xn - 2 * fxn + xn));

		/* Check if the tolerance for the solution has been met */
		if (fabs (xn - xn1) <= tol) {
			break;
		}

		/* If it hasn't then update the value of xn and repeat the loop */
		xn = xn1;
	}

	return xn;
}

/* Derivative methods */
/* Newton's Method
 *
 * f is the function being solved
 * df is the derivative of the function
 * guess is the initial guess of the solution
 * tol is the desired tolerance
 * iterLimit is the maximum number of iterations
 */
double
newton (adder_function *f, adder_function *df, double guess, double tol, unsigned int iterLimit)
{
	double xn;
	double xn1;
	double fxn;
	double dfxn;
	unsigned int i;

	xn = guess;

	/* The algorithm */
	for (i = 0; i < iterLimit; i++) {
		fxn = f->function (xn);
		dfxn = df->function (xn);

		/* Definition of Newton's Method */
		xn1 = xn - fxn / dfxn;

		/* Check if the tolerance for the solution has been met */
		if (fabs (xn - xn1) <= tol) {
			break;
		}

		/* Otherewise update the value of xn and repeat the loop */
		xn = xn1;
	}

	return xn;
}

/* Halley's Method
 * f is the function being solved
 * df is the first derivative of the function
 * ddf is the second derivative of the function
 * guess is the initial guess for the solution
 * tol is the desired tolerance for the solution
 * iterLimit is the maximum number of iterations
 */
double
halley (adder_function *f, adder_function *df, adder_function *ddf, double guess, double tol, unsigned int iterLimit)
{
	double xn; /* The current x value */
	double xnPlusOne; /* The next x value */
	double fxn; /* The value of the function at xn */
	double dfxn; /* The current value of the derivative of the function at xn */
	double ddfxn; /* The current value of the second derivative of the function at xn */
	unsigned int i;

	xn = guess;

	/* Iterate the algorithm */
	for (i = 0; i < iterLimit; i++) {
		/* Calculate the values of the function and its derivatives */
		fxn = f->function (xn);
		dfxn = df->function (xn);
		ddfxn = ddf->function (xn);

		/* Calculate the next value of x using Halley's Method */
		xnPlusOne = xn - (fxn / (dfxn - (ddfxn * fxn) / (2 * dfxn)));

		/* If the new and old values are within the desired tolerance then end the loop */
		if (fabs (xn - xnPlusOne) <= tol) {
			xn = xnPlusOne;
			break;
		}

		/* Otherwise update the value of xn and repeat the loop */
		xn = xnPlusOne;
	}

	return xn;
}


/* Other routines */

/* Compare the sign of two number */
int
sign (double x, double y)
{
	int signX;
	int signY;

	if (x < 0) {
		signX = -1;
	}
	else {
		signX = 1;
	}

	if (y < 0) {
		signY = -1;
	}
	else {
		signY = 1;
	}

	if (signX == signY) {
		return 1;
	}
	else {
		return 0;
	}
}
