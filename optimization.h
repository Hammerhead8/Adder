/* optimization.h
 *
 * Contains function prototypes for optimization routines */

#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include "../adder_math.h"

enum
Errors
{
	OPT_SUCCESS, /* 0 */
	OPT_ERROR, /* 1 */
	INVALID_SEARCH /* 2 */
};

enum
ReturnValue
{
	X_VALUE, /* 0 */
	F_VALUE /* 1 */
};

enum
LineSearchAlgorithms
{
	GOLDEN_SECTION = 1,
	FIBONACCI = 2,
	EQUAL_AREA = 3
};

/* Line search methods */
double goldenSectionSearch (adder_function *f, double a, double b, double stoppingCriteria, int retValue);
double fibonacciSearch (adder_function *f, double a, double b, int N, double stoppingCriteria, int retValue);
double equalAreaSearch (adder_function *f, double a, double b, int N, double stoppingCriteria, int retValue);

#endif
