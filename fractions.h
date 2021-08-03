#ifndef FRACTIONS_H
#define FRACTIONS_H

/* Fraction type definition */
typedef struct
{
	long int numer;
	long int  denom;
} adder_fraction;

/* IO functions */
adder_fraction * newFraction (long int numerator, long int denominator);
void deleteFraction (adder_fraction *f);
void print (adder_fraction *f);
void setNumerator (adder_fraction *f, long int numerator);
void setDenominator (adder_fraction *f, long int denominator);
long int getNumerator (adder_fraction *f);
long int getDenominator (adder_fraction *f);
double getDecimal (adder_fraction *f);

/* Arithmetic functions */
void addFractions (adder_fraction *sum, adder_fraction *f1, adder_fraction *f2);
void subFractions (adder_fraction *diff, adder_fraction *f1, adder_fraction *f2);
void multFractions (adder_fraction *prod, adder_fraction *f1, adder_fraction *f2);
void divFractions (adder_fraction *quot, adder_fraction *f1, adder_fraction *f2);
void fractionInvert (adder_fraction *f);
void fractionPower (adder_fraction *f, double exponent);

/* Other functions */
void simplify (adder_fraction *f);
long int calcGCD (long int a, long int b);

#endif
