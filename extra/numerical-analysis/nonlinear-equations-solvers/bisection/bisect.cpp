/*
 * source: bisect.cpp
 * author: misael-diaz
 * date:   2021/04/19
 *
 * Synopsis:
 * Possible implementation of the bisection method in C++.
 * 
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 *
 * References:
 * [1] A Gilat and V Subramanian, Numerical Methods for Engineers and 
 *     Scientists, 3rd edition.
 * [2] A Koenig and B Moo, Accelerated C++ Practical Programming by
 *     Example.
 * [3] https://en.cppreference.com/w/cpp/language/lambda
 *
 *
 */

#include <iostream>

// implements the objective function f(x) as a lambda function
auto f = [](const double x) -> double { return (x * x - 1.0) ; } ;
double bisect(double&, double&, double&) ;

int main() {
	// applies the bisection method to solve the nonlinear equation

	double a, b ;	// lower and upper bounds, respectively
	double xm ;	// middle value, xm
	double fm ;	// stores f(xm)

	// sets the numerical method options:
	const double tol = 1.0e-6 ;	// tolerance
	const int max_iter = 50 ;	// maximum number of iterations

	int n = 0 ;		// initializes the iteration counter
	a = 0. ; b = 1.3 ;	// sets the bracketing interval (a, b)
	do fm = bisect(a, b, xm) ;
	while (++n != max_iter && fm > tol) ;

	// displays number of iterations, xm, and f(xm)
	// based on this report the user can take action
	std::cout << "iters: " << n << std::endl ;
	std::cout << "xm:    " << xm << std::endl ;
	std::cout << "f(xm): " << f(xm) << std::endl ;
	return 0 ;
}

double bisect(double& a, double& b, double& xm) {
	// Bisect Method:
        // Computes the middle value xm, selects the bracketing
        // interval, and returns the absolute value of
	// the objective function | f(xm) |.
	
	double fm ;		/* default-initializes  f(xm)  */
        xm = 0.5 * (a + b) ;	/* calculates the middle value */

        fm = f(xm) ;		/* stores to save computations */
	if (f(a) * fm < 0.) 	/* selects bracketing interval */
		b = xm ;
	else
		a = xm ;

	return (fm < 0.) ? fm = -fm: fm ; 	/* implements abs(f(xm)) */
}
