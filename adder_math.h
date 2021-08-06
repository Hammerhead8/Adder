/* adder_math.h
 *
 * Defines constants and structures that are used across Adder.
 * More will be added here as they are needed. Structures specific
 * a particular area will not be included here.
 */

#ifndef __ADDER_MATH__
#define __ADDER_MATH__

typedef struct
{
	double (*function)(double x);
} adder_function;

#endif
