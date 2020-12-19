#ifndef FRACTIONS_H
#define FRACTIONS_H

/* Fraction type definition */
typedef struct
{
	double numer;
	double denom;
} Fraction;

/* IO functions */
Fraction * newFraction (Fraction *f, long int numerator, long int denominator);
void deleteFraction (Fraction *f);
void print (Fraction *f);
void setNumerator (Fraction *f, long int numerator);
void setDenominator (Fraction *f, long int denominator);
long int getNumerator (Fraction *f);
long int getDenominator (Fraction *f);
double getDecimal (Fraction *f);

/* Arithmetic functions */
void addFractions (Fraction *sum, Fraction *f1, Fraction *f2);
void subFractions (Fraction *diff, Fraction *f1, Fraction *f2);
void multFractions (Fraction *prod, Fraction *f1, Fraction *f2);
void divFractions (Fraction *quot, Fraction *f1, Fraction *f2);
void invert (Fraction *f);
void power (Fraction *f, double exponent);

/* Other functions */
long int calcGCD (long int a, long int b);

#endif
