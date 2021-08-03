/* roots.h
 * Defines function prototypes for root finding algorithms.
 * Systems of linear equations are solving using the routines in linalg.h
 */
#ifndef ROOTS_H
#define ROOTS_H

/* Methods without derivatives */
double bisection (adder_function *f, double leftGuess, double rightGuess, double tol, unsinged int iterLimit);
double regulaFalsi (adder_function *f, double leftGuess, double rightGuess, double tol);
double steffensen (adder_function *f, double guess, double tol, unsigned int iterLimit);

/* Methods with derivatives */
double newton (adder_function *f, adder_function *df, double guess, double tol, unsigned int iterLimit);

/* Other functions */
int sign (double x, double y);

#endif
