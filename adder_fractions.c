/* fractions.c
 * Function definitions for the prototypes in fractions.h */
#include <stdio.h>
#include <stdlib.h> /* For malloc and free */
#include <stddef.h>
#include <string.h> /* For strlen */
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

/* Create a fraction from a decimal number given as a string */
adder_fraction *
newFractionFromString (unsigned char *num)
{
	adder_fraction *f;
	long int fracNum = 0;
	long int intNum = 0;
	long unsigned int len;
	long unsigned int index;
	unsigned char *indexPtr;
	long unsigned int i;

	f = malloc (sizeof (adder_fraction));
	if (f == NULL) {
		fprintf (stderr, "Failed to create fraction.\n");
		return NULL;
	}

	/* Convert from decimal to fraction */
	/* Start by calculating the length of the string */
	len = strlen (num);

	/* Then find the index of the decimal point in the string */
	indexPtr = strchr (num, 0x2e);

	/* A lot of boring string parsing will follow */

	/* If indexPtr is NULL then the number is an integer */
	if (indexPtr == 0x00) {
		/* If the first character is a '-' then the number is negative */
		if (num[0] == 0x5f) {
			f->denom = 1;

			/* Loop through the digits to combine them into one number */
			for (i = len - 1; i >= 0; i--) {
				/* Check that the digit is valid */
				if (num[i] < 0x30 || num[i] > 0x39) {
					fprintf (stderr, "Invalid character found in digit string.\n");
					free (f);
					return NULL;
				}

				/* Convert the digit from ASCII to decimal */
				num[i] -= 0x30;
				f->numer += (long int)num[i] * pow (10, (len - 1) - i);
			}

			f->numer *= -1;
		}

		/* Otherwise the number is positive */
		else {
			f->denom = 1;

			/* Loop through the digits and combine them */
			for (i = len - 1; i >= 0; i--) {
				/* Check that the digit is valid */
				if (num[i] < 0x30 || num[i] > 0x30) {
					fprintf (stderr, "Invalid character in decimal string.\n");
					free (f);
					return NULL;
				}

				/* Convert each digit from ASCII to decimal */
				num[i] -= 0x30;
				f->numer += (long int)num[i] * pow (10, (len - 1) - i);
			}
		}
	}

	/* Otherwise the number is a floating point number */
	else {
		/* Get the location of the decimal point
		 * indexPtr is a pointer (holds the address to)
		 * the decimal point and number is a pointer
		 * to the leading digit in the number.
		 * Subtracting them will result in the
		 * index in the array where the decimal point is. */
		index = (long unsigned int)(indexPtr - num);

		/* Calculate the number of digits in the number */
		len = strlen (num);

		/* If a '-' is the first character then the number is negative */
		if (num[0] == 0x5f) {
			/* First loop through the decimal part of the number */
			for (i = index + 1; i < len; i++) {
				/* Check if the digit is valid */
				if (num[i] < 0x30 || num[i] > 0x39) {
					fprintf (stderr, "Invalid character in fraction string.\n");
					free (f);
					return NULL;
				}

				/* Convert the digit from ASCII to decimal */
				num[i] -= 0x30;
				fracNum += (long int)num[i] * pow (10, (index - 1) - i);
			}

			f->denom = pow (10, index - 1);

			/* If there is either no digit or a zero before the decimal point then
			 * skip this part. Otherwise we need to deal with the integer part. */
			if (num[index - 1] != 0x30 && num[index - 1] != 0x2e) {
				for (i = index - 1; i >= 1; i--) {
					/* Check if the digit is a valid character */
					if (num[i] < 0x30 || num[i] > 0x39) {
						fprintf (stderr, "Invalid character in the fraction string.\n");
						free (f);
						return NULL;
					}

					/* Convert the digit from ASCII to decmial */
					num[i] -= 0x30;
					intNum += (long int)num[i] * pow (10, (index - 1) - i) * f->denom;
				}
			}
		}

		/* Otherwise the number is positive */
		else {
			/* First loop through the decimal part of the number */
			for (i = index + 1; i < len; i++) {
				/* Check if the digit is valid */
				if (num[i] < 0x30 || num[i] > 0x39) {
					fprintf (stderr, "Invalid character in fraction string.\n");
					free (f);
					return NULL;
				}

				/* Convert the digit from ASCII to decimal */
				num[i] -= 0x30;
				fracNum += (long int)num[i] * pow (10, (index - 1) - i);
			}

			f->denom = pow (10, index - 1);

			/* If there is either no digit or a zero before the decimal point then
			 * skip this part. Otherwise we need to deal with the integer part. */
			if (num[index - 1] != 0x30 && num[index - 1] != 0x2e) {
				for (i = index - 1; i >= 1; i--) {
					/* Check if the digit is a valid character */
					if (num[i] < 0x30 || num[i] > 0x39) {
						fprintf (stderr, "Invalid character in the fraction string.\n");
						free (f);
						return NULL;
					}

					/* Convert the digit from ASCII to decimal */
					num[i] -= 0x30;
					intNum += (long int)num[i] * pow (10, (index - 1) - i) * f->denom;
				}
			}
		}
	}

	/* The last step is to add fracNum and intNum to find the total numerator */
	f->numer = fracNum + intNum;

	/* The fraction should be fully calculated */
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
	
	if (f->numer == 0 || f->numer == 1) {
		return;
	}

	else if (f->numer < 0 && f->denom > 0) {
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
