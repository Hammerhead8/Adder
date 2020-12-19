/* optimization.h
 *
 * Contains function prototypes for optimization routines */

#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include "matrix.h"

enum
LineSearchAlgorithms
{
	GOLDEN_SECTION = 1,
	FIBONACCI = 2,
	EQUAL_AREA = 3
};

enum
2DSearchAlgorithms
{
	STEEPEST_DESCENT = 1,
	NEWTON_RAPHSON = 2,
	CONJUGATE_GRADIENT = 3
};

/* Line search methods */
double lineSearch (double (*function)(double), double a, double b, int N, double stoppingCriteria);
double goldenSectionSearch (double (*function)(double), double a, double b, double stoppingCriteria);
double fibonacciSearch (double (*function)(double), double a, double b, int N, double stoppingCriteria);
double equalAreaSearch (double (*function)(double), double a, double b, double stoppingCriteria);

/* Multi-dimensional search methods */
double mdSearch (double (*function)(Vector*), (Vector*)(*gradient)(Vector*), Vector *x0, double stoppingCriteria);
double steepestDescent (double (*function)(Vector*), (Vector*)(*function)(Vector*), Vector *x0, double stoppingCriteria);
double newtonRaphson (double (*function)(Vector*), Vector *x0, double stoppingCriteria);
double conjugateGradient (double (*function)(Vector*), (Vector*)(*gradient)(Vector*), Vector *x0, double stoppingCriteria);

#endif
