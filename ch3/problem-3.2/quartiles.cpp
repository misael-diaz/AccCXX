/*
 * source: quartiles.cpp
 * author: misael-diaz
 * date:   2021/05/01
 *
 * Synopsis:
 * Solves problem 3-2, obtains the quartiles of a vector.
 *
 * References:
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 * https://github.com/dwyl/english-words
 *
 * Copyright (c) 2021 Misael Diaz-Maldonado
 *
 * This file is released under the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * TODO:
 * 	[x] implement for vectors having an even number of elements
 * 	[ ] partition code, place functions in a module
 * 	[ ] validate code through extensive unit testing
 *
 */


#include <iostream>
#include <numeric>
#include <vector>


// interface (to be public in module)
std::vector<double> quartiles(const std::vector<double>&) ;

// implementation (to be private in module)
typedef std::vector<double>::size_type size ;
std::vector<double> odd(std::vector<double>) ;
std::vector<double> even(std::vector<double>) ;
std::vector<double> avg(size, size, size, const std::vector<double>&) ;
std::vector<double> exact(size, size, size, const std::vector<double>&) ;
std::vector<double> odd(size, size, size, const std::vector<double>&) ;
std::vector<double> even(size, size, size, const std::vector<double>&) ;
double interpolate(double, double, double) ;

int main() {

	const size sz = 16 ;			// defines vector size
	std::vector<double> x(sz) ;		// preallocates vector
	std::iota(x.begin(), x.end(), 0) ;	// defs vector [0, sz)
	
	std::vector<double> q ;			// quartiles vector

	try {
		q = quartiles(x) ;
	} catch (std::domain_error err) {
		std::cout << err.what() << std::endl ;
		return 1 ;
	}

	// displays values of vector
	std::cout << "vector: "  << std::endl ;
	for(const auto& value: x)
		std::cout << value << " " << std::endl ;

	// reports the quartiles
	std::cout << "quartiles: "  << std::endl ;
	std::cout << "q1: " << q[0] << std::endl ;
	std::cout << "q2: " << q[1] << std::endl ;
	std::cout << "q3: " << q[2] << std::endl ;

	return 0 ;
}

std::vector<double> quartiles(const std::vector<double>& x) {
	// returns the quartiles of a vector
	
	if (x.size() == 0) {
		throw std::domain_error("empty vector") ;
	}

	std::vector<double> q ;	// quartiles
	if (x.size() % 2) {
                q = odd(x) ;
        } else {
                q = even(x) ;
        }

	return q ;
}

std::vector<double> odd(std::vector<double> x) {
	// returns the quartiles of a vector with an odd number of elements
	
	std::vector<double> quartiles ;
	std::sort( x.begin(), x.end() ) ;

	// initializes indexes for determining q1, q2, and q3, respectively
	size sz  = x.size() ;
	size b  =     sz / 4 ;
	size m  =     sz / 2 ;
	size a  = 3 * sz / 4 ;

	// obtains the quartiles based on the location of the middle value
	if (m % 2) {
		quartiles = avg(b, m, a, x) ;
	} else {
		quartiles = exact(b, m, a, x) ;
	}

	return quartiles ;
}
std::vector<double> exact(size b, size m, size a,
		         const std::vector<double>& x) {
	// obtains the quartiles through indexing (exact values)

	double q1, q2, q3 ;		// quartiles
	q1 = x[b] ;	q2 = x[m] ;	q3 = x[a] ;
	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;

}
std::vector<double> avg(size b, size m, size a,
		        const std::vector<double>& x) {
	// obtains quartiles with averages

	double q1, q2, q3 ;		// quartiles

	if (m == 0) {
		q1 = q2 = q3 = x[m] ;	// vector of a single element
	} else {
		q1 = 0.5 * (x[b] + x[b + 1]) ;
		q2 = x[m] ;
		q3 = 0.5 * (x[a] + x[a - 1]) ;
	}

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;

}

std::vector<double> even(std::vector<double> x) {
	// returns the quartiles for a vector having a pair of values

	double alpha ;
	std::vector<double> quartiles ;
	std::sort( x.begin(), x.end() ) ;

	// initializes indexes for determining q1, q2, and q3, respectively
	size sz  = x.size() ;
	size b  =     sz / 4 ;	// below the median
	size m  =     sz / 2 ;	// median
	size a  = 3 * sz / 4 ;	// above the median

	if (m % 2) {
		quartiles = odd(b, m, a, x) ;
	} else {
		quartiles = even(b, m, a, x) ;
	}

	return quartiles ;

}

std::vector<double> even(size b, size m, size a,
		         const std::vector<double>& x) {
	// Computes the quartiles when x.size() / 4 is an even integer,
	// that is the number of elements in vector is a multiple of 4.

	double alpha ;
	double q1, q2, q3 ;                     // quartiles

	alpha = 0.25 ;  q1 = interpolate(x[b - 1], x[b], 1. - alpha) ;
	alpha = 0.50 ;  q2 = alpha * (x[m - 1] + x[m]) ;
	alpha = 0.75 ;  q3 = interpolate(x[a - 1], x[a], 1. - alpha) ;

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;
}


std::vector<double> odd(size b, size m, size a,
		         const std::vector<double>& x) {
	// Computes the quartiles when x.size() / 4 is an odd integer.
	// The vector has an even number of elements but the number of
	// elements is not a multiple of 4.

	double alpha ;
	double q1, q2, q3 ;                     // quartiles

	alpha = 0.25 ;  q1 = interpolate(x[b], x[b + 1], alpha) ;
	alpha = 0.50 ;  q2 = alpha * (x[m - 1] + x[m]) ;
	alpha = 0.75 ;  q3 = interpolate(x[a - 1], x[a], alpha) ;

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;

}

double interpolate(double x1, double x2, double alpha) {
	// applies linear interpolation to obtain the quartile

	double x = x1 + alpha * (x2 - x1) ;
	return x ;
}
