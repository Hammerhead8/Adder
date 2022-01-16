# Adder
Adder is a numerical library for C/C++ similar to the GNU Scientific Library. The difference is that it only includes
that are most useful to me, which includes complex numbers, linear algebra, and random number generation.
This project came out of needing some of the features in GSL, but wanting an easier to use programming interface and not needing all of its features.

Note that these functions are written and tested under Linux, so some functions might use features that are specific to Linux (i.e. /dev/urandom
to seed some random number generators). There is currently no plan to support Windows, MacOS, or other operating systems.

# Features
Adder is still under development and is incomplete, but the currently supported features are:
* Matrices and vectors
  * Matrix-vector multiplication
  * Matrix-matrix multiplication
* Linear algebra
  * Matrix and vector transpose
  * Matrix inverse
  * Moore-Penrose pseudoinverse
  * Linear equation solve
  * Overdetermined linear equation solve
  * Linear least squares
  * Eigenvalues
  * Singular value decomposition
  * QR factorization
  * LQ factorization
  * LU factorization
  * Vector norm
  * Matrix norm
* Fractions
* Numerical integration
  * Gauss-Legendre quadrature
    * 3-point
    * 5-point
    * 20-point
    * 100-point
    * User selected number of points
  * Trapezoid Rule
  * Simpson's Rule
* Optimization
  * One-dimensional search
    * Golden Section search
    * Fibbonacci search
    * Equal Area search
* Nonlinear equation solving
  * Methods without derivatives
    * Bisection method
    * Regula Falsi method
    * Steffensen's Method
  * Methods with derivatives
    * Newton's Method
    * Halley's Method
* Interpolation
  * Linear interpolation
  * Polynomial interpolation

<!--Linear algebra operations are performed using LAPACKE (https://performance.netlib.org/lapack/lapacke.html), a C language-->
<!--interface for LAPACK.-->

# Planned features
* Fractions
	* Create fraction from an arbitrary decimal
* Numerical differentiation
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
both complex-valued vectors and matrices.

# Dependencies
The following libraries are required:
* BLAS (tested with OpenBLAS)
* LAPACKE:  https://performance.netlib.org/lapack/lapacke.html

More will be added as features are developed.

# Installation
To build from source, first download the latest available release. Building requires GNU Make to be installed. Once the source files are unpacked in the desired directory, the following commands can be used to build Adder:
1. `./configure`
2. `make`
3. `make install`

Once installed, Adder can be linked during compilation using `-ladder`. If an `Error loading shared libraries` occurs after building then run `ldconfig`.
