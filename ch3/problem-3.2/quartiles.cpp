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
 * 	[ ] partition code
 * 	[ ] validate code through extensive unit testing
 *
 */


#include <iostream>
#include <numeric>
#include <vector>

std::vector<double> odd(std::vector<double>) ;
std::vector<double> even(std::vector<double>) ;
std::vector<double> quartiles(const std::vector<double>&) ;

int main() {

	typedef std::vector<double>::size_type size ;

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
	
	typedef std::vector<double>::size_type size ;
	double q1, q2, q3 ;			// quartiles

	std::sort( x.begin(), x.end() ) ;

        // initializes indexes for determining q1, q2, and q3, respectively
	size sz  = x.size() ;
        size ql  =     sz / 4 ;
        size md  =     sz / 2 ;
        size qu  = 3 * sz / 4 ;

        // obtains the quartiles based on the location of the middle value
        if (md % 2 == 0) {
                q1 = x[ql] ;
                q2 = x[md] ;
                q3 = x[qu] ;
        } else {
		if (md == 0) {	// vector of a single element
			q1 = q2 = q3 = x[md] ;
		} else {
                	q1 = (x[ql] + x[ql + 1]) / 2 ;
                	q2 =  x[md] ;
                	q3 = (x[qu] + x[qu - 1]) / 2 ;
		}
        }

	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;
}

std::vector<double> even(std::vector<double> x) {
	// returns the quartiles for a vector having a pair of values

	typedef std::vector<double>::size_type size ;
        double q1, q2, q3 ;                     // quartiles

	std::sort( x.begin(), x.end() ) ;

        // initializes indexes for determining q1, q2, and q3, respectively
        size sz  = x.size() ;
        size ql  =     sz / 4 ;
        size md  =     sz / 2 ;
        size qu  = 3 * sz / 4 ;

	if (md % 2 == 0) {
		q1 = x[  ql  ] - 0.25 * (x[  ql  ] - x[ql - 1]) ;
		q2 =             0.50 * (x[  md  ] + x[md - 1]) ;
		q3 = x[qu - 1] + 0.25 * (x[  qu  ] - x[qu - 1]) ;
	} else {
		q1 = x[  ql  ] + 0.25 * (x[ql + 1] - x[  ql  ]) ;
		q2 =             0.50 * (x[  md  ] + x[md - 1]) ;
		q3 = x[  qu  ] - 0.25 * (x[  qu  ] - x[qu - 1]) ;
	}
	
	std::vector<double> quartiles{q1, q2, q3} ;
	return quartiles ;
}

