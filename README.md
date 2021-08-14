# Adder
Adder is a numerical library for C similar to the GNU Scientific Library. The difference is that it only includes
that are most useful to me, which includes complex numbers, linear algebra, and random number generation.
This project came out of needing some of the features in GSL, but wanting an easier to use programming interface and not needing all of its features.

# Features
Adder is still under development and is incomplete, but the currently supported features are:
* Matrices and vectors
* Linear algebra
  * Matrix and vector transpose
  * Matrix inverse
  * Linear equation solve
  * Eigenvalues
  * QR factorization
  * LQ factorization
  * LU factorization
  * Vector norm
  * Matrix norm
* Fractions
* Complex numbers
* Numerical integration
  * Gauss-Legendre quadrature
    * 3-point
    * 5-point
    * 20-point
    * 100-point
    * User selected number of points
  * Trapezoid Rule
* Numerical differentiation
  * Symetric difference quotient
  * Five point method
    * Center
    * Forward
    * Backward
* Optimization
  * One-dimensional unconstrained search
    * Golden Section search
    * Fibbonacci search
    * Equal Area search

<!--Linear algebra operations are performed using LAPACKE (https://performance.netlib.org/lapack/lapacke.html), a C language-->
<!--interface for LAPACK.-->

# Planned features
* Fractions
	* Create fraction from an arbitrary decimal
	* Complex number fractions
* Numerical integration
	* Simpson's Rule
	* Monte Carlo integration
* Optimization
	* Two-dimensional search methods
	 * Constrained search methods
* Support for complex vectors and matrices
* Complex linear algebra
* Random number generation

Currently the linear algebra functions only support real-valued matrices and
use only the general matrix routines. It is planned to eventually support
both complex-valued matrices as well as symmetric, positive definite, and other
types of matrices suppoted by LAPACK.

# Dependencies
The following libraries are required:
* BLAS (tested with OpenBLAS)
* LAPACKE:  https://performance.netlib.org/lapack/lapacke.html

More will be added as features are developed.
