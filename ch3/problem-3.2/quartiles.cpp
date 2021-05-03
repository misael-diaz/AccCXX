/*
 * source: quartiles.cpp
 * author: misael-diaz
 * date:   2021/05/03
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
 * 	[x] partition code, place functions in a module
 * 	[ ] validate code through extensive unit testing
 *
 */


#include <iostream>
#include <numeric>
#include <vector>
import statistics ;

int main() {

	typedef std::vector<double>::size_type size ;
	const size sz = 16 ;			// defines vector size
	std::vector<double> x(sz) ;		// preallocates vector
	std::iota(x.begin(), x.end(), 0) ;	// defs vector [0, sz)
	
	std::vector<double> q ;			// quartiles vector

	try {
		q = stats::quartiles(x) ;
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

