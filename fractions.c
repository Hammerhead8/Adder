/* fractions.c
 * Function definitions for the prototypes in fractions.h */
#include <stdlib.h>
#include <math.h> /* For pow */
#include "fractions.h"

/* IO functions */
/* Allocate the memory for a new fraction */
void
newFraction (Fraction *f, long int numerator, long int denominator)
{
	f = malloc (sizeof (Fraction));
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
}

/* Deallocate the memory for the fraction */
void
deleteFraction (Fraction *f)
{
	free (f);
}

/* Print the fraction */
void
print (Fraction *f)
{
	printf ("%ld/%ld\n", f->numer, f->denom);
}

/* Set the numerator of the fraction to the specified value */
void
setNumerator (Fraction *f, long int numerator)
{
	f->numer = numerator;
}

/* Set the denominator of the fraction to the specified value */
void
setDenominator (Fraction *f, long int denominator)
{
	f->denom = denominator;
}

/* Return the value of the numerator */
long int
getNumerator (Fraction *f)
{
	return f->numer;
}

/* Return the value of the denominator */
long int
getDenominator (Fraction *f)
{
	return f->denom;
}

/* Return the decimal value of the fraction in double precision */
double
getDecimal (Fraction *f)
{
	double res;

	res = (double)f->numer / (double)f->denom;
	return res;
}

/* Arithmetic functions */
/* Add two fractions */
void
addFractions (Fraction *sum, Fraction *f1, Fraction *f2)
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
subFractions (Fraction *diff, Fraction *f1, Fraction *f2)
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
	sum->numer = numerator1 - numerator2;
	sum->denom = lcm;
}

/* Multiply two fractions */
void
multFractions (Fraction *prod, Fraction *f1, Fraction *f2)
{
	prod->numer = f1->numer * f2->numer;
	prod->denom = f1->denom * f2->denom;
}

/* Divide two fractions */
void
divFractions (Fraction *quot, Fraction *f1, Fraction *f2)
{
	quot->numer = f1->numer * f2->denom;
	quot->denom = f1->denom * f2->numer;
}

/* Calculate the reciprocal of the fraction */
void
invert (Fraction *f)
{
	long int temp;

	temp = f->numer;
	f->numer = f->denom;
	f->denom = temp;
}

/* Raise the fraction to an exponent */
void
power (Fraction *f, long int exponent)
{
	f->numer = pow (f->numer, (double)exponent);
	f->denom = pow (f->denom, (double)exponent);
}

/* Other functions */
/* Simplify the fraction */
void
simplify (Fraction *f)
{
	long int gcd;

	if (f->numer < 0 && f->denom > 0) {
		gcd = calcGCD (-1 * f->numer, f->denom);
	}
	else {
		gcd = calcGCD (f->numer, f->denom);
	}

	if (gcd == 1) {
		return;
	}
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
