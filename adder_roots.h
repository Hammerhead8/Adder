/* roots.h
 * Defines function prototypes for root finding algorithms.
 * Systems of linear equations are solving using the routines in linalg.h
 */
#ifndef ADDER_ROOTS_H
#define ADDER_ROOTS_H

#include "adder_math.h" /* For adder_function */

/* Methods without derivatives */
double bisection (adder_function *f, double leftGuess, double rightGuess, double tol, unsigned int iterLimit);
double regulaFalsi (adder_function *f, double leftGuess, double rightGuess, double tol, unsigned int iterLimit);
double steffensen (adder_function *f, double guess, double tol, unsigned int iterLimit);

/* Methods with derivatives */
double newton (adder_function *f, adder_function *df, double guess, double tol, unsigned int iterLimit);
double halley (adder_function *f, adder_function *df, adder_function *ddf, double guess, double tol, unsigned int iterLimit);

/* Other functions */
int sign (double x, double y);

#endif
