/* complex.c
 * Function definitions for complex numbers
 */
#include <stdio.h>
#include <stdlib.h> /* For malloc and free */
#include <math.h> /* For sqrt and log */
#include "adder_complex.h"

#define M_PI 3.14159265358979323846

/*********************************
 * Initialize and delete numbers *
 *********************************/

/* Create a rectangular number and set its real and imaginary parts */
adder_complex_rect *
initRect (double r, double i)
{
	adder_complex_rect *c;

	c = malloc (sizeof (adder_complex_rect));
	if (c == NULL) {
		fprintf (stderr, "Failed to create the number.\n");
		return NULL;
	}

	c->real = r;
	c->imag = i;

	return c;
}

/* Create a rectangular number and set its values to zero */
adder_complex_rect *
initRect2 ()
{
	adder_complex_rect *c;

	c = malloc (sizeof (adder_complex_rect));
	if (c == NULL) {
		fprintf (stderr, "Failed to create number.\n");
		return NULL;
	}

	c->real = 0;
	c->imag = 0;

	return c;
}

/* Delete a rectangular number */
void
deleteRect (adder_complex_rect *num)
{
	free (num);
}

/* Create a polar number and set its magnitude and angle */
adder_complex_polar *
initPolar (double m, double a)
{
	adder_complex_polar *c;

	c = malloc (sizeof (adder_complex_polar));
	if (c == NULL) {
		fprintf (stderr, "Failed to create number.\n");
		return NULL;
	}

	c->mag = m;
	c->angle = a;

	return c;
}

/* Create a polar number and set its values to zero */
adder_complex_polar *
initPolar2 ()
{
	adder_complex_polar *c;

	c = malloc (sizeof (adder_complex_polar));
	if (c == NULL) {
		fprintf (stderr, "Failed to create number.\n");
		return NULL;
	}

	c->mag = 0;
	c->angle = 0;

	return c;
}

/* Delete a polar number */
void
deletePolar (adder_complex_polar *num)
{
	free (num);
}

/****************
 * IO functions *
 ****************/

/* Print a rectangular number */
void
printRect (adder_complex_rect *num)
{
	printf ("%.8lf%+.8lfj\n", num->real, num->imag);
}

/* Print a polar number */
void
printPolar (adder_complex_polar *num)
{
	printf ("%.8lf<%.8lf\n", num->mag, num->angle);
}

/* Getter functions */

/* Returns the real part of a rectangular number */
double
getReal (adder_complex_rect *num)
{
	return num->real;
}

/* Returns the imaginary part of a rectangular number */
double
getImag (adder_complex_rect *num)
{
	return num->imag;
}

/* Returns the magnitude of a polar number */
double
getMag (adder_complex_polar *num)
{
	return num->mag;
}

/* Returns the angle of a polar number */
double
getAngle (adder_complex_polar *num)
{
	return num->angle;
}

/********************
 * Setter functions *
 ********************/

/* Set the real and imaginary parts of a rectangular number */
void
setRect (adder_complex_rect *num, double r, double i)
{
	num->real = r;
	num->imag = i;
}

/* Set the real part of a rectangular number */
void
setReal (adder_complex_rect *num, double r)
{
	num->real = r;
}

/* Set the imaginary part of a rectangular number */
void
setImag (adder_complex_rect *num, double i)
{
	num->imag = i;
}

/* Set the values of a rectangular number of zero */
void
clearRect (adder_complex_rect *num)
{
	num->real = 0;
	num->imag = 0;
}

/* Set the values of a polar number */
void
setPolar (adder_complex_polar *num, double m, double a)
{
	num->mag = m;
	num->angle = a;
}

/* Set the magnitude ofa polar number */
void
setMag (adder_complex_polar *num, double m)
{
	num->mag = m;
}

/* Set the angle of a polar number */
void
setAngle (adder_complex_polar *num, double a)
{
	num->angle = a;
}

/* Set the values of a polar number to zero */
void
clearPolar (adder_complex_polar *num)
{
	num->mag = 0;
	num->angle = 0;
}

/************************
 * Conversion functions *
 ************************/

/* Convert a rectangular number of polar form */
void
rect2polar (adder_complex_rect *rectNum, adder_complex_polar *polarNum)
{
	/* Calculate the magnitude of the rectangular number */
	polarNum->mag = sqrt ((rectNum->real * rectNum->real) + (rectNum->imag * rectNum->imag));

	/* Calculate the angle of the number */
	if (rectNum->imag == 0 && rectNum->real != 0) {
		polarNum->angle = 0;
	}
	else if (rectNum->imag > 0 && rectNum->real == 0) {
		polarNum->angle = M_PI / 2;
	}
	else if (rectNum->imag < 0 && rectNum->real == 0) {
		polarNum->angle = -1 * M_PI / 2;
	}
	else if (rectNum->imag > 0 && rectNum->real > 0) {
		polarNum->angle = atan (rectNum->imag / rectNum->real);
	}
	else if (rectNum->imag > 0 && rectNum->real < 0) {
		polarNum->angle = (M_PI / 2) +  atan (-1 * rectNum->imag / rectNum->real);
	}
	else if (rectNum->imag < 0 && rectNum->real < 0) {
		polarNum->angle = M_PI + atan (rectNum->imag / rectNum->real);
	}
	else if (rectNum->imag < 0 && rectNum->real > 0) {
		polarNum->angle = -1 * atan (-1 * rectNum->imag / rectNum->real);
	}
}

/* Convert a polar number to rectangular */
void
polar2rect (adder_complex_rect *rectNum, adder_complex_polar *polarNum)
{
	rectNum->real = polarNum->mag * cos (polarNum->angle);
	rectNum->imag = polarNum->angle * sin (polarNum->angle);
}

/************************************
 * Rectangular arithmetic functions *
 ************************************/

/* Add two rectangular numbers */
void
addRect (adder_complex_rect *sum, adder_complex_rect *n1, adder_complex_rect *n2)
{
	sum->real = n1->real + n2->real;
	sum->imag = n1->imag + n2->imag;
}

/* Subtract two rectangular numbers */
void
subRect (adder_complex_rect *diff, adder_complex_rect *n1, adder_complex_rect *n2)
{
	diff->real = n1->real - n1->real;
	diff->imag = n1->imag - n2->imag;
}

/* Multiply two rectangular numbers */
void
multRect (adder_complex_rect *prod, adder_complex_rect *n1, adder_complex_rect *n2)
{
	prod->real = n1->real * n2->real - n1->imag * n2->imag;
	prod->imag = n1->real * n2->imag + n1->imag * n2->real;
}

/* Divide two rectangular numbers */
void
divRect (adder_complex_rect *quot, adder_complex_rect *n1, adder_complex_rect *n2)
{
	quot->real = (n1->real * n2->real + n1->imag * n2->imag) / (n2->real * n2->real + n2->imag * n2->imag);
	quot->imag = (n2->real * n1->imag - n2->imag * n1->real) / (n2->real * n2->real + n2->imag * n2->imag);
}

/* Find the reciprocal of the number */
void
invRect (adder_complex_rect *result, adder_complex_rect *num)
{
	result->real = num->real / (num->real * num->real + num->imag * num->imag);
	result->imag = -1 * num->imag / (num->real * num->real + num->imag * num->imag);
}

/* Find the square root of a rectangular number.
 * The square root is defined as the square root of the magnitude and half of the angle */
void
sqrtRect (adder_complex_rect *result, adder_complex_rect *num)
{
	double r, angle;

	/* Get the magnitude and calculate its square root */
	r = magRect (num);
	r = sqrt (r);

	/* Get the angle and divide it by two */
	angle = angleRect (num);
	angle /= 2;

	/* Now convert the magnitude and angle to a rectangular number */
	result->real = r * cos (angle);
	result->imag = r * sin (angle);
}

/* Find the natural log of a rectangular number.
 * This is defined as Log(z) = ln(r) + j theta */
void
logRect (adder_complex_rect *result, adder_complex_rect *num)
{
	double r, angle;

	/* Calculate the magnitude and ahgle of the number */
	r = magRect (num);
	angle = angleRect (num);

	/* Calculate the solution */
	result->real = log (r);
	result->imag = angle;
}

/* Calculate the complex conjugate of the number.
 * This is defined as changing the sign of the imaginary part of the number */
void
conjRect (adder_complex_rect *res, adder_complex_rect *num)
{
	res->imag = -1 * num->imag;
}

/* Calculate the magnitude of a rectangular number */
double
magRect (adder_complex_rect *num)
{
	return sqrt ((num->real * num->real) + (num->imag * num->imag));
}

/* Calculate the angle of a rectangular number in radians */
double
angleRect (adder_complex_rect *num)
{
	if (num->real == 0 && num->imag == 0) {
		return 0;
	}

	else if (num->real > 0) {
		if (num->imag == 0) {
			return M_PI / 2;
		}

		else if (num->imag > 0) {
			return atan (num->imag / num->real);
		}

		else {
			return -1 * atan (-1 * num->imag / num->real);
		}
	}

	else {
		if (num->imag == 0) {
			return M_PI / 2;
		}

		else if (num->imag > 0) {
			return M_PI - atan (num->imag / (-1 * num->real));
		}

		else {
			return M_PI + atan (num->imag / num->real);
		}
	}
}

/******************************
 * Polar arithmetic functions *
 ******************************/

/* Add two polar numbers.
 * This is done by first converting the numbers to rectangular form and adding
 * before converting the result back to polar form. */
int
addPolar (adder_complex_polar *sum, adder_complex_polar *num1, adder_complex_polar *num2)
{
	double r1, i1;
	double r2, i2;
	double r, i;
	double m, a;
	adder_complex_rect *res;

	res = initRect2 ();
	if (res == NULL) {
		fprintf (stderr, "ERROR:  Cannot create number for intermediate solution.\n");
		return COMPLEX_ERROR;
	}

	/* Calculate the real and imaginary parts of the two numbers being added */
	r1 = realPolar (num1);
	i1 = imagPolar (num1);
	r2 = realPolar (num2);
	i2 = imagPolar (num2);

	/* Perform the addition */
	r = r1 - r2;
	i = i1 - i2;
	setReal (res, r);
	setImag (res, i);

	/* Convert the result back to polar form */
	m = magRect (res);
	a = angleRect (res);
	setMag (sum, m);
	setAngle (sum, a);

	deleteRect (res);

	return COMPLEX_SUCCESS;
}

/* Subtract two polar numbers.
 * This is done by converting the numbers to rectangular form and subtracting
 * before converting the result back to polar form. */
int
subPolar (adder_complex_polar *diff, adder_complex_polar *num1, adder_complex_polar *num2)
{
	double r1, i1;
	double r2, i2;
	double r, i;
	double m, a;
	adder_complex_rect *res;

	res = initRect2 ();
	if (res == NULL) {
		fprintf (stderr, "ERROR:  Cannot create number for intermediate solution.\n");
		return COMPLEX_ERROR;
	}

	/* Calculate the real and imaginary parts of the two numbers being subtracted */
	r1 = realPolar (num1);
	i1 = imagPolar (num1);
	r2 = realPolar (num2);
	i2 = imagPolar (num2);

	/* Perform the subtraction */
	r = r1 - r2;
	i = i1 - i2;
	setReal (res, r);
	setImag (res, i);

	/* Convert the result back to polar form */
	m = magRect (res);
	a = angleRect (res);
	setMag (diff, m);
	setAngle (diff, a);

	free (res);

	return COMPLEX_SUCCESS;
}

/* Multiply two poalr numbers.
 * This is defined as multiplying their magnitudes and adding their angles */
void
multPolar (adder_complex_polar *prod, adder_complex_polar *num1, adder_complex_polar *num2)
{
	double m, a;

	m = num1->mag * num2->mag;
	a = num1->angle + num2->angle;

	setMag (prod, m);
	setAngle (prod, a);
}

/* Divide two polar numbers.
 * This is defined as dividing their magnitudes and subtracting their angles */
void
divPolar (adder_complex_polar *quot, adder_complex_polar *num1, adder_complex_polar *num2)
{
	double m, a;

	m = num1->mag / num2->mag;
	a = num1->angle - num2->angle;

	setMag (quot, m);
	setAngle (quot, a);
}

/* Calculate the inverse of a polar number.
 * This is defined as keeping the magnitude and multiplying the angle by -1 */
void
invPolar (adder_complex_polar *res, adder_complex_polar *num)
{
	res->angle = -1 * num->angle;
}

/* Calculate the square root of a polar number.
 * This is defined as taking the square root of the magnitude and dividing the angle by 2. */
void
sqrtPolar (adder_complex_polar *res, adder_complex_polar *num)
{
	res->mag = sqrt (num->mag);
	res->angle = num->angle / 2;
}

/* Calculate the natural log of a polar number.
 * This is defined as Log(z) = ln(r) + j theta */
void
logPolar (adder_complex_polar *res, adder_complex_polar *num)
{
	res->mag = log (num->mag);
	res->angle = num->angle;
}

/* Calculate the real part of a polar number */
double
realPolar (adder_complex_polar *num)
{
	return num->mag * cos (num->angle);
}

/* Calculate the imaginary part of a polar number */
double
imagPolar (adder_complex_polar *num)
{
	return num->mag * sin (num->angle);
}
