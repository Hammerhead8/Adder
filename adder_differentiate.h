/* differentiate.h
 * Numerical differentiation routines for Adder.
 *
 * TODO:  Implement directional derivatives for multi-dimensional functions */
#ifndef ADDER_DIFFERENTIATE_H
#define ADDER_DIFFERENTIATE_H

#include "adder_math.h"

double derivSymDiff (adder_function *f, double x, double h);
double derivCenter (adder_function *f, double x, double h);
double derivForward (adder_function *f, double x, double h);
double derivBackward (adder_function *f, double x, double h);

#endif
