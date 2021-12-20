/* fractions.c
 * Function definitions for the prototypes in fractions.h */
#include <stdio.h>
#include <stdlib.h> /* For malloc and free */
#include <math.h> /* For pow */
#include "adder_fractions.h"

/******************
 * Real fractions *
 ******************/

/* IO functions */
/* Allocate the memory for a new fraction */
adder_fraction *
newFraction (long int numerator, long int denominator)
{
	adder_fraction *f;
	f = malloc (sizeof (adder_fraction));
	if (f == NULL) {
		return f;
	}

	/* Set the numerator and denominator values */
	if (denominator < 0) {
		f->numer = -1 * numerator;
		f->denom = -1 * denominator;
	}
	else {
		f->numer = numerator;
		f->denom = denominator;
	}

	return f;
}

/* Deallocate the memory for the fraction */
void
deleteFraction (adder_fraction *f)
{
	free (f);
}

/* Print the fraction */
void
printFraction (adder_fraction *f)
{
	printf ("%ld/%ld\n", f->numer, f->denom);
}

/* Set the numerator of the fraction to the specified value */
void
setNumerator (adder_fraction *f, long int numerator)
{
	f->numer = numerator;
}

/* Set the denominator of the fraction to the specified value */
void
setDenominator (adder_fraction *f, long int denominator)
{
	f->denom = denominator;
}

/* Return the value of the numerator */
long int
getNumerator (adder_fraction *f)
{
	return f->numer;
}

/* Return the value of the denominator */
long int
getDenominator (adder_fraction *f)
{
	return f->denom;
}

/* Return the decimal value of the fraction in double precision */
double
getDecimal (adder_fraction *f)
{
	double res;

	res = (double)f->numer / (double)f->denom;
	return res;
}

/* Arithmetic functions */
/* Add two fractions */
void
addFractions (adder_fraction *sum, adder_fraction *f1, adder_fraction *f2)
{
	long int N1, N2;
	long int numerator1, numerator2;
	long int lcm;

	/* Calculate the LCM of the two denominators */
	lcm = calcGCD (f1->denom, f2->denom);
	lcm = (f1->denom * f2->denom) / lcm;

	/* Now calculate the value by which to multiply each numerator */
	N1 = lcm / f1->denom;
	N2 = lcm / f2->denom;

	numerator1 = f1->numer * N1;
	numerator2 = f2->numer * N2;

	/* Perform the addition */
	sum->numer = numerator1 + numerator2;
	sum->denom = lcm;
}

/* Subtract two fractions */
void
subFractions (adder_fraction *diff, adder_fraction *f1, adder_fraction *f2)
{
	long int N1, N2;
	long int numerator1, numerator2;
	long int lcm;

	/* Calculate the LCM of the two denominators */
	lcm = calcGCD (f1->denom, f2->denom);
	lcm = (f1->denom * f2->denom) / lcm;

	/* Now calculate the value by which to multiply each numerator */
	N1 = lcm / f1->denom;
	N2 = lcm / f2->denom;

	numerator1 = f1->numer * N1;
	numerator2 = f2->numer * N2;

	/* Perform the subtraction */
	diff->numer = numerator1 - numerator2;
	diff->denom = lcm;
}

/* Multiply two fractions */
void
multFractions (adder_fraction *prod, adder_fraction *f1, adder_fraction *f2)
{
	prod->numer = f1->numer * f2->numer;
	prod->denom = f1->denom * f2->denom;
}

/* Divide two fractions */
void
divFractions (adder_fraction *quot, adder_fraction *f1, adder_fraction *f2)
{
	quot->numer = f1->numer * f2->denom;
	quot->denom = f1->denom * f2->numer;
}

/* Calculate the reciprocal of the fraction */
void
invert (adder_fraction *f)
{
	long int temp;

	temp = f->numer;
	f->numer = f->denom;
	f->denom = temp;
}

/* Raise the fraction to an exponent */
void
power (adder_fraction *f, long int exponent)
{
	f->numer = pow (f->numer, (double)exponent);
	f->denom = pow (f->denom, (double)exponent);
}

/* Other functions */
/* Simplify the fraction */
void
simplify (adder_fraction *f)
{
	long int gcd;

	/* Calculate the GCD of the numerator and denominator */

	if (f->numer == 0 || f->numer == 1) {
		return;
	}

	else if (f->numer < 0 && f->denom > 0) {
		gcd = calcGCD (-1 * f->numer, f->denom);
	}

	else {
		gcd = calcGCD (f->numer, f->denom);
	}

	/* If the GCD is 1 then the fraction can't be simplified */
	if (gcd == 1) {
		return;
	}

	/* Otherwise simplify by dividing the numerator and denominator by the GCD */
	else {
		f->numer /= gcd;
		f->denom /= gcd;
	}
}

/* Calculate the GCD using Euler's Method */
long int
calcGCD (long int a, long int b)
{
	long int temp;

	while (b != 0) {
		temp = b;
		b = a % b;
		a = temp;
	}

	return a;
}
