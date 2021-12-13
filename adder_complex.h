/* complex.h
 * type definitions and function prototypes for complex numbers
 * Both rectangular and polar numbers are supported
 * part of the Adder library */
#ifndef ADDER_COMPLEX_H
#define ADDER_COMPLEX_H

enum
{
	COMPLEX_SUCCESS,
	COMPLEX_ERROR
};

/* Rectangular form */
typedef struct
{
	double real;
	double imag;
} adder_complex_rect;

/* Polar form */
typedef struct
{
	double mag;
	double angle;
} adder_complex_polar;

/* Initialization functions */
adder_complex_rect * initRect (double r, double i);
adder_complex_rect * initRect2 ();
void deleteRect (adder_complex_rect *num);

adder_complex_polar * initPolar (double m, double a);
adder_complex_polar * initPolar2 ();
void deletePolar (adder_complex_polar *num);

/* IO functions */
void setRect (adder_complex_rect *num, double r, double i);
void setReal (adder_complex_rect *num, double r);
void setImag (adder_complex_rect *num, double i);
void clearRect (adder_complex_rect *num);
void printRect (adder_complex_rect *num);

void setPolar (adder_complex_polar *num, double m, double a);
void setMagnitude (adder_complex_polar *num, double m);
void setAngle (adder_complex_polar *num, double a);
void clearPolar (adder_complex_polar *num);
void polarPrint (adder_complex_polar *num);

/* Getter functions */
double getReal (adder_complex_rect *num);
double getImag (adder_complex_rect *num);

double getMagnitude (adder_complex_polar *num);
double getAngle (adder_complex_polar *num);

/* Rectangular arithmetic functions */
void addRect (adder_complex_rect *sum, adder_complex_rect *n1, adder_complex_rect *n2);
void subRect (adder_complex_rect *diff, adder_complex_rect *n1, adder_complex_rect *n2);
void multRect (adder_complex_rect *prod, adder_complex_rect *n1, adder_complex_rect *n2);
void divRect (adder_complex_rect *quot, adder_complex_rect *n1, adder_complex_rect *n2);
void invRect (adder_complex_rect *result, adder_complex_rect *num);
void sqrtRect (adder_complex_rect *result, adder_complex_rect *num);
void logRect (adder_complex_rect *result, adder_complex_rect *num);
void conjRect (adder_complex_rect *result, adder_complex_rect *num);
double magRect (adder_complex_rect *num);
double angleRect (adder_complex_rect *num);

/* Polar arithmetic functions */
int addPolar (adder_complex_polar *sum, adder_complex_polar *n1, adder_complex_polar *n2);
int subPolar (adder_complex_polar *diff, adder_complex_polar *n1, adder_complex_polar *n2);
void multPolar (adder_complex_polar *prod, adder_complex_polar *n1, adder_complex_polar *n2);
void divPolar (adder_complex_polar *quot, adder_complex_polar *n1, adder_complex_polar *n2);
void invPolar (adder_complex_polar *res, adder_complex_polar *num);
void sqrtPolar (adder_complex_polar *res, adder_complex_polar *num);
void logPolar (adder_complex_polar *res, adder_complex_polar *num);
double realPolar (adder_complex_polar *num);
double imagPolar (adder_complex_polar *num);

/* Other functions */
void complexExp (adder_complex_rect *result, double x);
void rect2polar (adder_complex_rect *rectNum, adder_complex_polar *polNum);
void polar2rect (adder_complex_rect *rectNum, adder_complex_polar *polNum);

#endif
