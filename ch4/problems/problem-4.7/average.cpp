/*
 * source: average.cpp
 * author: misael-diaz
 * date:   2021/05/05
 *
 * Synopsis:
 * Solves problem 4-7, obtains the average of a vector of doubles.
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
 * A. Koenig and B. Moo, Accelerated C++ Practical Programming by Example
 *
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
	
	double avg ;				// average

	try {
		avg = stats::mean(x) ;
	} catch (std::domain_error err) {
		std::cout << err.what() << std::endl ;
		return 1 ;
	}

	// displays values of vector
	std::cout << "vector: "  << std::endl ;
	for(const auto& value: x)
		std::cout << value << " " << std::endl ;

	// reports the average
	std::cout << "average: " << avg << std::endl ;

	return 0 ;
}

