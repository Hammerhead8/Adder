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
double goldenSectionSearch (adder_function *f, double a, double b, double stoppingCriteria);
double fibonacciSearch (adder_function *f, double a, double b, int N, double stoppingCriteria);
double equalAreaSearch (adder_function *f, double a, double b, double stoppingCriteria);

#endif
